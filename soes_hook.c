#include <soes/esc.h>
#include <soes/esc_coe.h>
#include <soes/esc_foe.h>
#include <soes/hal/advr_esc/soes.h>
#include <ecat_options.h>
#include <soes_hook.h>


esc_cfg_t gESC_config;
foe_cfg_t gFOE_config = { 0, 0, 0, 0 };
uint8_t foe_buffer[1024];

uint16_t flash_cmd;
uint16_t flash_cmd_ack;
uint16_t et1100_boot_pin;

// dummy pdo
rx_pdo_t rx_pdo;
tx_pdo_t tx_pdo;
uint8_t *rxpdo = (uint8_t*) &rx_pdo;
uint8_t *txpdo = (uint8_t*) &tx_pdo;

extern uint16_t crc_ok;
extern foe_file_cfg_t gFOE_firmware_files[];

extern void try_boot(void);

void pre_state_change_hook(uint8_t *as, uint8_t *an);
void post_state_change_hook(uint8_t *as, uint8_t *an);
void ESC_App_objecthandler(uint16_t index, uint8_t subindex, uint16_t flags);

/* Setup config hooks */
const esc_cfg_t config = {
    .user_arg = "hello_world",
    .use_interrupt = 1,
    .watchdog_cnt = 0,
    .set_defaults_hook = NULL,
    .pre_state_change_hook = pre_state_change_hook,
    .post_state_change_hook = post_state_change_hook,
    .application_hook = NULL,
    .safeoutput_override = NULL,
    .pre_object_download_hook = NULL,
    .post_object_download_hook = ESC_App_objecthandler,
    .rxpdo_override = NULL,
    .txpdo_override = NULL,
    .esc_hw_interrupt_enable = NULL,
    .esc_hw_interrupt_disable = NULL,
    .esc_hw_eep_handler = NULL,
    .esc_check_dc_handler = NULL,
};

/** Mandatory: Hook called from the slave stack SDO Download handler to act on
 * user specified Index and Sub-index.
 *
 * @param[in] index      = index of SDO download request to handle
 * @param[in] sub-index  = sub-index of SDO download request to handle
 */
void ESC_App_objecthandler(uint16_t index, uint8_t subindex, uint16_t flags) {
	switch (index) {
	case 0x8001:
		/* Handle post-write of parameter values */
		switch (subindex) {
		default:
			DPRINT("post-write param 0x%04X %d\n", index, subindex);
			break;
		}
		break;
	default:
		DPRINT("SDO 0x%04X %d NOT Handled\n", index, subindex);
		break;
	}
}

/** Mandatory: Hook called from the slave stack ESC_stopoutputs to act on state changes
 * forcing us to stop outputs. Here we can set them to a safe state.
 */
void APP_safeoutput(void) {
	DPRINT("APP_safeoutput\n");
}

/** Optional: Hook called BEFORE state change for application
 * specific actions for specific state changes. 
 */
void pre_state_change_hook(uint8_t *as, uint8_t *an) {
	DPRINT("pre_state_change_hook 0x%02X 0x%02X\n", *as, *an);
}

/** Optional: Hook called AFTER state change for application
 * specific actions for specific state changes. 
 */
void post_state_change_hook(uint8_t *as, uint8_t *an) {
	DPRINT("post_state_change_hook 0x%02X 0x%02X\n", *as, *an);

	if (*an & ESCerror) {
		DPRINT("Error in state transition\n");
	}

	if ((*as == BOOT_TO_INIT) && (*an == ESCinit)) {
	    try_boot();
	}
}

void bootstrap_foe_init(void) {

	/* setup application foe_file structs */
	int file_cnt = 0;
	foe_file_cfg_t *tmp_foe_files = gFOE_firmware_files;

	while (tmp_foe_files->name != 0) {
		DPRINT("foe_file %s addr 0x%04X\n", tmp_foe_files->name,
				tmp_foe_files->dest_start_address);
		tmp_foe_files++;
		file_cnt++;
	}

	/** Allocate static in caller func to fit buffer_size */
	gFOE_config.fbuffer = foe_buffer;
	/** Buffer size before we flush to destination */
	gFOE_config.buffer_size = sizeof(foe_buffer);
	/** Number of files used in firmware update */
	gFOE_config.n_files = file_cnt;
	/** Pointer to files configured to be used by FoE */
	gFOE_config.files = gFOE_firmware_files;

	FOE_config(&gFOE_config);

	DPRINT("config %d foe_file(s)\n", file_cnt);

}
