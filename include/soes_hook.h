#ifndef __SOES_HOOK_H__
#define __SOES_HOOK_H__

#include <ecat_options.h>

#ifdef ccs
	#define IAR_PACKED
	#define CCS_PACKED	__attribute__((__packed__))
#else
	#define IAR_PACKED 	__packed
	#define CCS_PACKED
#endif

typedef IAR_PACKED struct {
	uint8_t _rx[MAX_RXPDO_SIZE];
} CCS_PACKED rx_pdo_t;

typedef IAR_PACKED struct {
	uint8_t _tx[MAX_TXPDO_SIZE];
} CCS_PACKED tx_pdo_t;

void bootstrap_foe_init(void);

#endif 
