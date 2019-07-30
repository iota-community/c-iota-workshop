#include "cclient/api/core/core_api.h"
#include "cclient/api/extended/extended_api.h"

#include "common/trinary/tryte_ascii.h"
#include "utils/time.h"
#include <inttypes.h>
#include "iota_client_service/config.h"
#include "iota_client_service/client_service.h"

#include "iota_client_service/config.h"

static tryte_t const *const SEED =
        (tryte_t *)"G9JEMIRJKUXDKUPPAIMEQSGVADYLSJRSBTEIRDWSCTLCVQOJWBM9XESTWTSONOTDDQUXMYCNVAKZWPPYW";

retcode_t get_new_address(iota_client_service_t *s) {
    retcode_t ret = RC_ERROR;
    flex_trit_t seed[FLEX_TRIT_SIZE_243];
    hash243_queue_t addresses = NULL;
    //get five addresses.
    // address_opt_t opt = {.security = 2, .start = 0, .total = 5};
    // get an unused address and all used addresses.
    address_opt_t opt = {.security = SECURITY_LEVEL, .start = 0, .total = 0};

    //Get trits from seed char trytes
    //Read for more information: https://docs.iota.org/docs/iota-basics/0.1/references/tryte-alphabet
    if (flex_trits_from_trytes(seed, NUM_TRITS_ADDRESS, SEED, NUM_TRYTES_ADDRESS, NUM_TRYTES_ADDRESS) == 0) {
        printf("Error: converting flex_trit failed\n");
        return ret;
    }

    if ((ret = iota_client_get_new_address(s, seed, opt, &addresses)) == RC_OK) {
        printf("unused: ");
        flex_trit_print(addresses->prev->hash, NUM_TRITS_ADDRESS);
        printf("\n");

        size_t count = hash243_queue_count(addresses);
        hash243_queue_t curr = addresses;
        for (size_t i = 0; i < count; i++) {
            printf("[%ld]: ", i);
            flex_trit_print(curr->hash, NUM_TRITS_ADDRESS);
            printf("\n");
            curr = curr->next;
        }
    } else {
        printf("new address failed: %s\n", error_2_string(ret));
    }
    hash243_queue_free(&addresses);

    return ret;
}

int main(void){
    retcode_t ret = RC_ERROR;
    iota_client_service_t iota_client_service;
    init_iota_client(&iota_client_service);

    ret = get_new_address(&iota_client_service);
    if(ret == RC_OK){
        printf("Addresses generated.\n");
    }else{
        printf("Addresses generated with error code: %i\n", ret);
    }
}
