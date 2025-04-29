#ifndef __objectlist__
#define __objectlist__

#include <soes/esc_coe.h>
#include <soes_hook.h>
#include <foe_flash.h>

extern uint16_t 	flash_cmd;
extern uint16_t 	flash_cmd_ack;
extern uint16_t   	crc_ok;
extern uint16_t   	et1100_boot_pin;

extern const uint32_t 	CRC_App;
extern const uint8_t 	BLDR_Version[];
extern const uint8_t	git_hash[];
extern const uint8_t	git_branch[];
extern const uint8_t    git_tag[];
extern const uint8_t	build_ts[];

static const char Number_of_elements[] = "Number of Elements";
//static const char mapped_obj[] = "Mapped Object";

const _objd SDO1000[] =
{
  {0x0, DTYPE_UNSIGNED32, 32, ATYPE_RO, "Device Type", 0x01901389, 0},
};

const _objd SDO1008[] =
{
  {0x0, DTYPE_VISIBLE_STRING, 72, ATYPE_RO, "Manufacturer Device Name", 0, "Tm4c"},
};

const _objd SDO1009[] =
{
  {0x0, DTYPE_VISIBLE_STRING, 24, ATYPE_RO, "Manufacturer Hardware Version", 0, "1.0"},

};

const _objd SDO100A[] =
{
  {0x0, DTYPE_VISIBLE_STRING, 24, ATYPE_RO, "Manufacturer Software Version", 0, "bl_tm4c"},
};

const _objd SDO1018[] =
{
  {0x0, DTYPE_UNSIGNED8, 8, ATYPE_RO, Number_of_elements, 4, 0},
  {0x1, DTYPE_UNSIGNED32, 32, ATYPE_RO, "Vendor ID", 664, 0},			// Vendor ID
  {0x2, DTYPE_UNSIGNED32, 32, ATYPE_RO, "Product Code", 0, 0},			// Product code
  {0x3, DTYPE_UNSIGNED32, 32, ATYPE_RO, "Revision Number", 0, 0},		// Revision number
  {0x4, DTYPE_UNSIGNED32, 32, ATYPE_RO, "Serial Number", 0x00000000, 0},// Serial number
};

const _objd SDO10F1[] =
{
  {0x0, DTYPE_UNSIGNED8, 8, ATYPE_RO, Number_of_elements, 2, 0},
  {0x1, DTYPE_UNSIGNED32, 32, ATYPE_RW, "Local Error Reaction", 0, 0},
  {0x2, DTYPE_UNSIGNED16, 16, ATYPE_RW, "Sync Error Counter Limit", 4, 0},
};

const _objd SDO1C00[] =
{
  {0x0, DTYPE_UNSIGNED8, 8, ATYPE_RO, Number_of_elements, 4, 0},
  {0x1, DTYPE_UNSIGNED8, 8, ATYPE_RO, "Communications Type SM0", 1, 0},
  {0x2, DTYPE_UNSIGNED8, 8, ATYPE_RO, "Communications Type SM1", 2, 0},
  {0x3, DTYPE_UNSIGNED8, 8, ATYPE_RO, "Communications Type SM2", 3, 0},
  {0x4, DTYPE_UNSIGNED8, 8, ATYPE_RO, "Communications Type SM3", 4, 0},
};

const _objd SDO1C12[] =
{
  {0x0, DTYPE_UNSIGNED8, 	8, 	ATYPE_RO, Number_of_elements, 1, 0},
  {0x1, DTYPE_UNSIGNED16, 	16, ATYPE_RO, "PDO Mapping", 0x1600, 0},
};

const _objd SDO1C13[] =
{
  {0x0, DTYPE_UNSIGNED8, 8, ATYPE_RO, Number_of_elements, 1, 0},
  {0x1, DTYPE_UNSIGNED16, 16, ATYPE_RO, "PDO Mapping", 0x1A00, 0},
};

const _objd SDO1C32[] =
{
  {0x00, DTYPE_UNSIGNED8, 8, ATYPE_RO, Number_of_elements, 5, 0},
  {0x01, DTYPE_UNSIGNED16, 16, ATYPE_RO, "SyncType",  1, 0},
  {0x02, DTYPE_UNSIGNED32, 32, ATYPE_RO, "CycleTime", 0, 0},
  {0x03, DTYPE_UNSIGNED32, 32, ATYPE_RO, "ShiftTime", 0, 0},
  {0x04, DTYPE_UNSIGNED16, 16, ATYPE_RO, "Synchronization Types supported", 0x1F, 0},
  {0x05, DTYPE_UNSIGNED32, 32, ATYPE_RO, "Minimum Cycle Time", 125000, 0},
};

/*
 *
 *
 *
 */

// RxPdo 1600 
const _objd SDO1600[] =
{
  {0x0, DTYPE_UNSIGNED8,   8, ATYPE_RO, Number_of_elements, 0, 0},
};

// TxPdo
const _objd SDO1A00[] =
{
  {0x0, DTYPE_UNSIGNED8,   8, ATYPE_RO, Number_of_elements, 0, 0},
};

const _objd SDO6000[] =
{
  {0x0, DTYPE_UNSIGNED8,   8, ATYPE_RO, Number_of_elements, 0, 0},
};

const _objd SDO7000[] =
{
  {0x0, DTYPE_UNSIGNED8,   8, ATYPE_RO, Number_of_elements, 0, 0},
};

const _objd SDO8000[] =
{
  {0x0, DTYPE_UNSIGNED8,     	 8, ATYPE_RO,   Number_of_elements,   6, 0},
  {0x1, DTYPE_UNSIGNED16,   	16, ATYPE_RW, 	"flash_cmd",  	0, &flash_cmd},
  {0x2, DTYPE_UNSIGNED16,   	16, ATYPE_RO, 	"flash_cmd_ack",0, &flash_cmd_ack},
  {0x3, DTYPE_UNSIGNED32,   	32, ATYPE_RO, 	"flash_crc",  	0, &bldr_info.crc_app},
  {0x4, DTYPE_VISIBLE_STRING,   64, ATYPE_RO,   "bl_ver",   	0, &BLDR_Version},
  {0x5, DTYPE_UNSIGNED16,   	16, ATYPE_RO, 	"crc_ok",  		0, &crc_ok},
  {0x6, DTYPE_UNSIGNED16,   	16, ATYPE_RO, 	"et1100_boot_pin",0, &et1100_boot_pin},
};

// build info
const _objd SDO9009[] =
{
  {0x0,  DTYPE_UNSIGNED8,        8, ATYPE_RO,   "NumElem",      4, 0},
  {0x1, DTYPE_VISIBLE_STRING,   64, ATYPE_RO,   "git_hash",     0, &git_hash},
  {0x2, DTYPE_VISIBLE_STRING,   64, ATYPE_RO,   "git_branch",   0, &git_branch},
  {0x3, DTYPE_VISIBLE_STRING,   64, ATYPE_RO,   "git_tag",      0, &git_tag},
  {0x4, DTYPE_VISIBLE_STRING,   64, ATYPE_RO,   "build_ts",     0, &build_ts},
};

const _objectlist SDOobjects[] =
{
  {0x1000, OTYPE_VAR, 		 0,  0, "Device Type", SDO1000},
  {0x1008, OTYPE_VAR, 		 0,  0, "Manufacturer Device Name", SDO1008},
  {0x1009, OTYPE_VAR, 		 0,  0, "Manufacturer Hardware Version", SDO1009},
  {0x100A, OTYPE_VAR, 		 0,  0, "Manufacturer Software Version", SDO100A},
  {0x1018, OTYPE_RECORD, 	 4,  0, "Identity Object", SDO1018},
  {0x10F1, OTYPE_RECORD, 	 2,  0, "Error Setting Object", SDO10F1},
  {0x1600, OTYPE_RECORD,	 0,  0, "Receive PDO Mapping", SDO1600},
  {0x1A00, OTYPE_RECORD,	 0,  0, "Transmit PDO Mapping", SDO1A00},
  {0x1C00, OTYPE_ARRAY, 	 4,  0, "Sync Manager Communication Type", SDO1C00},
  {0x1C12, OTYPE_ARRAY, 	 1,  0, "Sync Manager 2 PDO Assignment", SDO1C12},
  {0x1C13, OTYPE_ARRAY, 	 1,  0, "Sync Manager 3 PDO Assignment", SDO1C13},
  {0x1C32, OTYPE_RECORD, 	 5,  0, "SM2(Output) Synchronisation  Parameter", SDO1C32},
  {0x6000, OTYPE_RECORD,	 0,  0, "Inputs", SDO6000},
  {0x7000, OTYPE_RECORD,     0,  0, "Outputs", SDO7000},
  {0x8000, OTYPE_RECORD,     6,  0, "Flash Parameters", SDO8000},
  {0x9009, OTYPE_RECORD,     4,  0, "Build_info",  SDO9009},
  {0xffff, 0xff, 0xff, 0xff, 0, 0}
};

#endif
