#include <stdint.h>
#include <stdbool.h>

#include <inc/hw_ints.h>
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <inc/hw_sysctl.h>
#include <inc/hw_gpio.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <driverlib/interrupt.h>
#include <driverlib/pin_map.h>
#include <driverlib/rom.h>
#include <driverlib/rom_map.h>
#include <driverlib/ssi.h>
#include <driverlib/uart.h>
#include <driverlib/crc.h>
#include <utils/uartstdio.h>

#include <pins.h>
#include <dprint.h>

void Configure_UART(void)
{
    // Enable the GPIO Peripheral used by the UART.
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    // Enable UART0
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    // Configure GPIO Pins for UART mode.
    MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
    MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    // Use the internal 16MHz oscillator as the UART clock source.
    MAP_UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    // Initialize the UART for console I/O.
    UARTStdioConfig(0, 115200, 16000000);

    DPRINT("%s\n",__FUNCTION__);

}

void Configure_EcatPDI (void)
{
    // enable SSI and GPIO periph
    MAP_SysCtlPeripheralEnable(ECAT_SSI_SYSCTL_PERIPH);
    MAP_SysCtlPeripheralEnable(ECAT_SSI_GPIO_SYSCTL_PERIPH);
    MAP_SysCtlPeripheralEnable(ECAT_GPIO_SYSCTL_PERIPH);

    MAP_GPIOPinTypeGPIOOutput(ECAT_SSI_GPIO_PORTBASE, ECAT_SSI_CS);
    MAP_GPIOPinWrite(ECAT_SSI_GPIO_PORTBASE, ECAT_SSI_CS, ECAT_SSI_CS);

    // Configure the pin muxing for SSI2 functions on port
#if HW_TYPE == LP
    MAP_GPIOPinConfigure(GPIO_PB4_SSI2CLK);
    MAP_GPIOPinConfigure(GPIO_PB6_SSI2RX); // MISO
    MAP_GPIOPinConfigure(GPIO_PB7_SSI2TX); // MOSI
#elif HW_TYPE == VV_IO
    MAP_GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    MAP_GPIOPinConfigure(GPIO_PA4_SSI0RX); // MISO
    MAP_GPIOPinConfigure(GPIO_PA5_SSI0TX); // MOSI
#else
	#error "Unknown HW_TYPE"
#endif
    // Configure the GPIO settings for the SSI pins.  This function also gives
    // control of these pins to the SSI hardware.
    MAP_GPIOPinTypeSSI(ECAT_SSI_GPIO_PORTBASE, ECAT_SSI_PINS);
    // Configure and enable the SSI port for SPI master mode.
    // Use SSI, system clock supply, idle clock level low and active low clock in
    // freescale SPI mode, master mode, 8MHz SSI frequency, and 8-bit data.
    MAP_SSIConfigSetExpClk(ECAT_SSI_BASE, MAP_SysCtlClockGet(), SSI_FRF_MOTO_MODE_3, SSI_MODE_MASTER, 7500000, 8);
    // Enable the SSI module.
    MAP_SSIEnable(ECAT_SSI_BASE);

    // Configure the SPI INT pin as an input.
    // Configure the SPI EPROM_LOADED pin as an input.
    MAP_GPIOPinTypeGPIOInput(ECAT_GPIO_PORTBASE, ECAT_IRQ);
    MAP_GPIOPinTypeGPIOInput(ECAT_GPIO_PORTBASE, ECAT_EEPROM_LOADED);
    // Configure the SPI INT pin as interrupt on falling edge.
    MAP_GPIOIntTypeSet(ECAT_GPIO_PORTBASE, ECAT_IRQ, GPIO_FALLING_EDGE);
    // Ecat pin
    //GPIOPinTypeGPIOInput(ECAT_GPIO_PORTBASE, ECAT_BOOT);
    
    // NO ethercat irq
    
    //GPIOIntEnable(SPI_ECAT_SSI_PORT, SPI_ECAT_IRQ_PIN);
    //ROM_IntEnable(INT_GPIOB);

    DPRINT("%s\n",__FUNCTION__);

}

void Configure_GPIO(void)
{
    // Enable the GPIO port that is used for the on-board LED.
    MAP_SysCtlPeripheralEnable(LED_PERIPH);
    // Enable the GPIO pins for the LED (R PF1 - B PF2 - G PF3).
    MAP_GPIOPinTypeGPIOOutput(LED_BASE, LED_PIN);
    //GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
    //GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);

#if HW_TYPE == LP
    // Unlock PF0 so we can change it to a GPIO input
    // Once we have enabled (unlocked) the commit register then re-lock it
    // to prevent further changes.  PF0 is muxed with NMI thus a special case.
    HWREG(SWITCH_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(SWITCH_BASE + GPIO_O_CR) |= 0x01;
    HWREG(SWITCH_BASE + GPIO_O_LOCK) = 0;
    // Set each of the button GPIO pins as an input with a pull-up.
    MAP_GPIODirModeSet(SWITCH_BASE, SW1_PIN|SW2_PIN, GPIO_DIR_MODE_IN);
    MAP_GPIOPadConfigSet(SWITCH_BASE, SW1_PIN|SW2_PIN,
                     GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    //GPIOPinTypeGPIOInput(SWITCH_BASE, SW1_PIN);
    //GPIOPinTypeGPIOInput(SWITCH_BASE, SW2_PIN);
#endif
    DPRINT("%s\n",__FUNCTION__);

}

