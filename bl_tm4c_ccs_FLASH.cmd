/******************************************************************************
 *
 * Linker Command file for the Texas Instruments TM4C123AH6PM
 * 32-bit Arm Cortex-M4F based MCU with 80-MHz
 * Flash Size: 256KB
 * RAM Size: 32KB
 * Sector Size: 1KB
 * Family: Blizzard
 *****************************************************************************/

--retain=g_pfnVectors

/* The following command line options are set as part of the CCS project.    */
/* If you are building using the command line, or for some reason want to    */
/* define them here, you can uncomment and modify these lines as needed.     */
/* If you are using CCS for building, it is probably better to make any such */
/* modifications in your CCS project and leave this file alone.              */
/*                                                                           */
/* --heap_size=0                                                             */
/* --stack_size=256                                                          */
/* --library=rtsv7M3_T_le_eabi.lib                                           */

// Properties: Build->ARM Linker->Advanced Options->Runtime Environment->Initialization mode->--rom_model

/* System memory map */
#define FLASH_SIZE  0x00040000

#define BLDR_START  0x00000000
#define BLDR_SIZE   0x00008000

#define INFO_START  0x00008000
#define INFO_SIZE   0x00000400

#define RAM_BASE    0x20000000

MEMORY
{
    FLASH       (RX)  : origin = BLDR_START, length = BLDR_SIZE
    FLASH_INFO  (R)   : origin = INFO_START, length = INFO_SIZE
    SRAM        (RWX) : origin = RAM_BASE,   length = 0x00008000
}


SECTIONS
{
    .intvecs    :   > BLDR_START
    .text       :   > FLASH
    .const      :   > FLASH
    .cinit      :   > FLASH
    .pinit      :   > FLASH
    .init_array :   > FLASH
    .TI.ramfunc : {} load=FLASH, run=SRAM, table(BINIT)
    .binit      : {}  > FLASH

    .bldr_info : > FLASH_INFO
    //.BLDR_VER: > FLASH_INFO

    .vtable :   > RAM_BASE
    .data   :   > SRAM
    .bss    :   > SRAM
    .sysmem :   > SRAM
    .stack  :   > SRAM (HIGH)

}

__STACK_TOP = __stack + 512;



