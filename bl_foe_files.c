
#include <foe_flash.h>
#include <soes/esc_foe.h>


foe_writefile_cfg_t      gFOE_firmware_files[] = {
    // launchpad
	{
		.name =					"soes_tm4c.bin",
		.max_data = 			FLASH_APP_SIZE,
		.dest_start_address =	FLASH_APP_START,
		.address_offset =		0,
		.filepass =				0xB007,
		.write_function =		foe_write_flash,
		.read_function =		0,
		.on_foe_open = 			on_foe_open_cb,
		.on_foe_close =			on_foe_close_cb,
    },
	// hyq hub_board
    {
		.name =					"hub_board.bin",
		.max_data = 			FLASH_APP_SIZE,
		.dest_start_address =	FLASH_APP_START,
		.address_offset =		0,
		.filepass =				0xB001,
        .write_function =       foe_write_flash,
        .read_function =        0,
        .on_foe_open =          on_foe_open_cb,
        .on_foe_close =         on_foe_close_cb,
    },
	// hyq valve_board
    {
		.name =					"valve_tm4c.bin",
		.max_data = 			FLASH_APP_SIZE,
		.dest_start_address =	FLASH_APP_START,
		.address_offset =		0,
		.filepass =				0xB002,
        .write_function =       foe_write_flash,
        .read_function =        0,
        .on_foe_open =          on_foe_open_cb,
        .on_foe_close =         on_foe_close_cb,
    },
	//
	{
		.name =					"fake.it",
		.max_data = 			0,
		.dest_start_address =	0,
		.address_offset =		0,
		.filepass =				0xDEAD,
		.write_function =		0,
		.read_function =		0,
		.on_foe_open = 			0,
		.on_foe_close =			0,
    },
    //
    {
    	.name = 				0,
		.max_data = 			0,
		.dest_start_address =	0,
		.address_offset =		0,
		.filepass =				0,
		.write_function =		0,
		.read_function =		0,
		.on_foe_open = 			0,
		.on_foe_close =			0,
    },
};

