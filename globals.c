#include <cc.h>
#include <foe_flash.h>
#include <build_info.h>


const uint8_t BLDR_Version[8] = GIT_TAG;

#pragma RETAIN(bldr_info)
#pragma DATA_SECTION(bldr_info, ".bldr_info")
const bldr_info_t bldr_info;

uint32_t gCalc_crc;
uint16_t crc_ok;

const uint8_t git_hash[] = GIT_HASH;
const uint8_t git_branch[] = GIT_BRANCH;
const uint8_t build_ts[] = BUILD_TIMESTAMP;

void print_build_info(void) {

	printf("\n");
	printf("Build Timestamp: %s\n", BUILD_TIMESTAMP);
    printf("Git Hash: %s\n", GIT_HASH);
    printf("Git Commit Hash: %s\n", GIT_COMMIT_HASH);
    printf("Git Branch: %s\n", GIT_BRANCH);
    printf("Git Tag: %s\n", GIT_TAG);
    printf("Repository Dirty: %d\n", GIT_DIRTY);
    printf("Git Repository URL: %s\n", GIT_REPO_URL);
    printf("Build Host: %s\n", BUILD_HOST);
    printf("Build User: %s\n", BUILD_USER);
    printf("Build OS: %s\n", BUILD_OS);
    printf("\n");

}
