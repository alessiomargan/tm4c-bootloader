#ifndef __FOE_FLASH_H__
#define __FOE_FLASH_H__

#include <stdint.h>
#include <soes/esc_foe.h>
/*
 * Flash Size: 256KB
 * RAM Size: 32KB
 * Sector Size: 1KB
 * Family: Blizzard
 */

#define FLASH_SIZE 			0x40000
#define FLASH_APP_START		0x10000
#define FLASH_APP_END		0x3F000
#define FLASH_PAR_START		0x3F000
#define FLASH_PAR_SIZE		0x01000
#define FLASH_APP_SIZE 		FLASH_SIZE - FLASH_PAR_SIZE - FLASH_APP_START

typedef struct {
    uint32_t    crc_app;
    uint32_t    fw_flash_cnt;
} bldr_info_t;

extern const bldr_info_t bldr_info;

extern const uint8_t BLDR_Version[8];
extern uint32_t gCalc_crc;
extern uint16_t crc_ok;

uint32_t calc_CRC(uint32_t addr, uint32_t length);
uint32_t foe_write_flash(foe_writefile_cfg_t * writefile_cfg, uint8_t * data, size_t length);
uint32_t on_foe_open_cb(uint8_t op);
uint32_t on_foe_close_cb(void);

#endif
