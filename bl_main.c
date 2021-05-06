#include <stdint.h>
#include <stdbool.h>


#include <inc/hw_ints.h>
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <inc/hw_sysctl.h>
#include "inc/hw_nvic.h"
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/rom_map.h>
#include <driverlib/interrupt.h>

#include <pins.h>
#include <peripherals.h>
#include <foe_flash.h>

#include <cc.h>
#include <soes/esc.h>
#include <soes/hal/advr_esc/soes.h>

#include <tiva-morser/morse.h>


extern esc_cfg_t config;

static void jump2app(void) {
    // disable interrupts
    MAP_IntMasterDisable();
    // redirect the vector table
    HWREG(NVIC_VTABLE) = FLASH_APP_START;
    // Load the stack pointer from the application's vector table.
    __asm(" ldr r1, [r0, #0]\n"
          " mov sp, r1\n");
    // Load the initial PC from the application's vector table and branch to
    // the application's entry point.
    __asm(" ldr r0, [r0, #4]\n"
          " blx r0\n");
}

static uint32_t read_user_RAM(void) {

    volatile uint32_t value;
    ESC_read(0xF80, (void*)&value, sizeof(value));
    DPRINT("user_RAM 0x%X\n", value);
    return value;
}

/*
 * jump to app conditions :
 * 1) valid crc
 * 2) none of
 *      - hold button switch
 *      - ecat chip output pin high
 *      - ecat chip user RAM == 0xB007B007
 *
 * return > 0 will jump to app
 */
static uint8_t test_jump2app(void) {

    uint8_t ret = 0;
    uint8_t sw1 = 0;
    uint8_t ecat_boot = 0;
    uint8_t user_ram = 0;
#if HW_TYPE == LP
    // poll switch ... 0 pressed
    // sw1 == 1 ==> pressed
    sw1 = ((uint8_t)(~MAP_GPIOPinRead(SWITCH_BASE, SW1_PIN))&SW1_PIN) >> 4;
#endif
#ifdef HAVE_BOOT_PIN
    ecat_boot = MAP_GPIO_getInputPinValue(PORT_ECAT_BOOT, PIN_ECAT_BOOT);
#else
    user_ram = (read_user_RAM() == 0xB007B007);
#endif
    ret = (!(sw1 || ecat_boot || user_ram)) && crc_ok;
    DPRINT("%s : %d = (not( %d || %d || %d )) && %d\n",
           __FUNCTION__, ret, sw1, ecat_boot, user_ram, crc_ok);

    return ret;
}

void try_boot(void)
{
    if ( test_jump2app() ) {
        jump2app();
    }
}

void do_morse_led(void) {

	static volatile uint32_t led_status;
	static char *morser_string = "boot";
	static bool sending = false;
	static struct morser m;
	enum OUTPUT res;

    if (sending) {
        res = tick(&m);
        switch(res) {
          case HIGH:
        	  led_status = 1;
			  break;
          case LOW:
        	  led_status = 0;
			  break;
          case END:
        	  led_status = 0;
			  sending = false;
            break;
        }
    } else {
		sending = true;
		init_morser(&m, morser_string);
    }
    /////////////////////////////////////////////////////////////////

    MAP_GPIOPinWrite(LED_BASE, LED_PIN, led_status ? LED_PIN : 0 );

}
//*****************************************************************************
//
//
//
//*****************************************************************************

void main(void)
{
    static uint32_t loop_cnt;

    MAP_IntMasterDisable();

    // Set the clocking to run directly from the crystal.
    MAP_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    Configure_UART();
    Configure_GPIO();
    // Set up ET1100 PDI interface
    Configure_EcatPDI();
    // Enable processor interrupts.
    MAP_IntMasterEnable();

    gCalc_crc = calc_CRC(FLASH_APP_START, FLASH_APP_SIZE);
    crc_ok = (gCalc_crc == bldr_info.crc_app) ? 1 : 0;
    DPRINT("bldr ver %s HW ver 0x%02X\n", BLDR_Version, HW_TYPE);
    DPRINT("CRC : calc 0x%04X flash 0x%04X\n", gCalc_crc, bldr_info.crc_app);
    DPRINT("fw_flash_cnt : %u\n", bldr_info.fw_flash_cnt);

    //
    soes_init(&config);

    try_boot();

    while (1) {

    	loop_cnt ++;
        soes_loop();
        if ( ! (loop_cnt % 100) ) {
        	do_morse_led();
        }

        MAP_SysCtlDelay(MAP_SysCtlClockGet() / 10000);

    }

}


