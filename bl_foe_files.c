#include <foe_flash.h>
#include <soes/esc_foe.h>

foe_file_cfg_t      gFOE_firmware_files[] = {
    // launchpad
	{
		.name =					"soes_tm4c.bin",
		.max_data = 			&__FLASH_APP_SIZE,
		.dest_start_address =	&__FLASH_APP_START,
		.address_offset =		0,
		.filepass =				0xB007,
		.write_function =		foe_write_flash,
		.read_function =		0,
		.on_foe_open = 			on_foe_open_cb,
		.on_foe_close =			on_foe_close_cb,
    },
	// hyq IOv5_board
    {
		.name =					"ioV5_tm4c.bin",
		.max_data = 			&__FLASH_APP_SIZE,
		.dest_start_address =	&__FLASH_APP_START,
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
		.max_data = 			&__FLASH_APP_SIZE,
		.dest_start_address =	&__FLASH_APP_START,
		.address_offset =		0,
		.filepass =				0xB002,
        .write_function =       foe_write_flash,
        .read_function =        0,
        .on_foe_open =          on_foe_open_cb,
        .on_foe_close =         on_foe_close_cb,
    },
	// imu_board
    {
		.name =					"imu_tm4c.bin",
		.max_data = 			&__FLASH_APP_SIZE,
		.dest_start_address =	&__FLASH_APP_START,
		.address_offset =		0,
		.filepass =				0xB003,
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

