#include "cclient/api/core/core_api.h"
#include "cclient/api/extended/extended_api.h"

#include "common/trinary/tryte_ascii.h"
#include "utils/time.h"
#include <inttypes.h>

#include "config.h"

static tryte_t const *const SEED =
        (tryte_t *)"G9JEMIRJKUXDKUPPAIMEQSGVADYLSJRSBTEIRDWSCTLCVQOJWBM9XESTWTSONOTDDQUXMYCNVAKZWPPYW";

retcode_t get_new_address(iota_client_service_t *s) {
    retcode_t ret = RC_ERROR;
    flex_trit_t seed[FLEX_TRIT_SIZE_243];
    hash243_queue_t addresses = NULL;
    // Set the options to get one new address
    address_opt_t opt = {.security = SECURITY_LEVEL, .start = 0, .total = 0};

    // Convert the seed from trytes to trits
    // For more information about trits and trytes, see the IOTA documentation portal: https://docs.iota.org/docs/getting-started/0.1/introduction/ternary
    if (flex_trits_from_trytes(seed, NUM_TRITS_ADDRESS, SEED, NUM_TRYTES_ADDRESS, NUM_TRYTES_ADDRESS) == 0) {
        printf("Failed to convert trytes to trits\n");
        return ret;
    }

    // Generate an unspent address with security level 2
    if ((ret = iota_client_get_new_address(s, seed, opt, &addresses)) == RC_OK) {
        printf("Your new address is: ");
        flex_trit_print(addresses->prev->hash, NUM_TRITS_ADDRESS);
        printf("\n");
    } else {
        printf("Failed to get a new address: Error code %s\n", error_2_string(ret));
    }
    hash243_queue_free(&addresses);

    return ret;
}

int main(void){
    iota_client_service_t *iota_client_service;

#ifdef CONFIG_ENABLE_HTTPS
    iota_client_service = iota_client_core_init(CONFIG_IRI_NODE_URI, CONFIG_IRI_NODE_PORT, TLS_CERTIFICATE_PEM);
#else
    iota_client_service = iota_client_core_init(CONFIG_IRI_NODE_URI, CONFIG_IRI_NODE_PORT, NULL);
#endif

    retcode_t ret = RC_ERROR;
    ret = get_new_address(iota_client_service);

    if(ret == RC_OK){
        printf("Addresses generated.\n");
    }else{
        printf("Addresses generated with error code: %i\n", ret);
    }
}
