#include <stdint.h>
#include <stdbool.h>

#include <inc/hw_memmap.h>
#include <inc/hw_sysctl.h>
#include <driverlib/sysctl.h>
#include <driverlib/flash.h>
#include <driverlib/sw_crc.h>
#include <driverlib/rom_map.h>

#include <foe_flash.h>
#include <soes/esc_foe.h>


extern foe_cfg_t gFOE_config;

const uint8_t BLDR_Version[8] = "tm4c_1.0";

#pragma RETAIN(bldr_info)
#pragma DATA_SECTION(bldr_info, ".bldr_info")
const bldr_info_t bldr_info;

uint32_t gCalc_crc;
uint16_t crc_ok;

uint32_t calc_CRC(uint32_t start_addr, uint32_t length)
{
    int i,k;
    uint32_t crc = 0xFFFFFFFF; //0xF0CACC1A;

    for(i=0, k=0; k < length; i++, k=i*4  ) {
        crc = MAP_Crc32(crc, (uint8_t*)(start_addr+k), 4);
        //crc ^= *(uint32_t*)(start_addr+k);
    }
    crc ^= 0xFFFFFFFF;
    return crc;
}


uint32_t foe_write_flash(foe_writefile_cfg_t * writefile_cfg, uint8_t * data, size_t length) {

    uint32_t bytestowrite = gFOE_config.buffer_size;
    uint32_t ui32FlashAddr = writefile_cfg->address_offset + \
                             writefile_cfg->dest_start_address;;

    DPRINT("[%s] FlashAddr 0x%04X with %d bytes\n", __FUNCTION__, ui32FlashAddr,
               bytestowrite);
    int32_t ret = MAP_FlashProgram((uint32_t*)data, ui32FlashAddr, bytestowrite);

    // 0 on success.
    return ret;
}

uint32_t on_foe_open_cb(uint8_t op)
{
    // Erase application memory section
    int32_t ret = 0;
    // size of a single eraseable sector of flash
    uint32_t sect_size = MAP_SysCtlFlashSectorSizeGet();
    uint32_t addr = FLASH_APP_START;
    DPRINT("[%s] Erase flash 0x%04X 0x%04X\n", __FUNCTION__, addr, FLASH_APP_END);
    while ( addr < FLASH_APP_END && ret == 0 ) {
        ret = MAP_FlashErase(addr);
        addr += sect_size;
        //DPRINT("%s Erase flash 0x%04X\n", __FUNCTION__, addr);
    }

    // 0 on success
    return ret;
}

uint32_t on_foe_close_cb(void)
{
    // write crc
    int32_t ret;
    bldr_info_t tmp;

    gCalc_crc = calc_CRC(FLASH_APP_START, FLASH_APP_SIZE);

    tmp.crc_app = gCalc_crc;
    if ( bldr_info.fw_flash_cnt == 0xFFFFFFFF ) {
        tmp.fw_flash_cnt = 1;
    } else {
        tmp.fw_flash_cnt = bldr_info.fw_flash_cnt+1;
    }

    ret = MAP_FlashErase((uint32_t)&bldr_info);
    ret = MAP_FlashProgram((uint32_t*)&tmp, (uint32_t)&bldr_info, sizeof(bldr_info));
    DPRINT("[%s] Write CRC_App 0x%04X at 0x%04X\n", __FUNCTION__, gCalc_crc, (uint32_t)&bldr_info);

    crc_ok = (gCalc_crc == bldr_info.crc_app) ? 1 : 0;

    // 0 on success
    return (!ret);
}


