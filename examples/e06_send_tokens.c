#include "cclient/api/core/core_api.h"
#include "cclient/api/extended/extended_api.h"

#include "common/trinary/tryte_ascii.h"
#include "utils/time.h"
#include <inttypes.h>

#include "iota_client_service/config.h"
#include "iota_client_service/client_service.h"

static tryte_t const *const RECEIVER_ADDR =
    (tryte_t *)"RJBYLCIOUKWJVCUKZQZCPIKNBUOGRGVXHRTTE9ZFSCGTFRKELMJBDDAKEYYCLHLJDNSHQ9RTIUIDLMUOB";

static tryte_t const *const MY_SEED =
    (tryte_t *)"HFYDTJZIVDJ9TQTQPIJXRXVJVOBOXAHZYZMVQBMFQYEAITJZKPHKUKERFQNAXNVTJRAHBGFJJIZTOTGJC";

retcode_t send_balance(iota_client_service_t *s) {
    printf("\n [%s]\n", __FUNCTION__);
    retcode_t ret_code = RC_OK;
    bundle_transactions_t *bundle = NULL;
    bundle_transactions_new(&bundle);
    transfer_array_t *transfers = transfer_array_new();

    // Define an input transaction object
    // that sends 1 i to the address
    transfer_t tf = {};
    // Convert the seed from trytes to trits
    flex_trit_t seed[NUM_FLEX_TRITS_ADDRESS];
    flex_trits_from_trytes(seed, NUM_TRITS_ADDRESS, MY_SEED, NUM_TRYTES_ADDRESS, NUM_TRYTES_ADDRESS);

    // Convert the receiver's address from trytes to trits
    flex_trits_from_trytes(tf.address, NUM_TRITS_ADDRESS, RECEIVER_ADDR, NUM_TRYTES_ADDRESS, NUM_TRYTES_ADDRESS);

    // Convert the transaction tag from trytes to trits
    flex_trits_from_trytes(tf.tag, NUM_TRITS_TAG, (const tryte_t *)"MYFIRSTVALUETRANSACTION9999", NUM_TRYTES_TAG,
                            NUM_TRYTES_TAG);

    // The amount of IOTA tokens to send to the receiver's address
    tf.value = 1;

    transfer_array_add(transfers, &tf);

    // Create a bundle from the transfers array and send it to the node
    ret_code = iota_client_send_transfer(s, seed, SECURITY_LEVEL, TIP_SELECTION_DEPTH, MINIMUM_WEIGHT_MAGNITUDE, false, transfers, NULL, NULL, NULL, bundle);

    printf("Sending 1 i to %s\n", RECEIVER_ADDR);
    printf("Send transfer function %s\n", error_2_string(ret_code));
    if (ret_code == RC_OK) {
        flex_trit_t const *bundle_hash = bundle_transactions_bundle_hash(bundle);
        printf("Bundle hash: ");
        flex_trit_print(bundle_hash, NUM_TRITS_HASH);
        printf("\n");
    }

    // Free the objects
    bundle_transactions_free(&bundle);
    transfer_message_free(&tf);
    transfer_array_free(transfers);
}

int main(void){
    retcode_t ret = RC_ERROR;
    iota_client_service_t iota_client_service;
    init_iota_client(&iota_client_service);

    ret = send_balance(&iota_client_service);
    if(ret == RC_OK){
        printf("Sent IOTA tokens\n");
    }else{
        printf("Failed to send IOTA tokens. Error code: %i\n", ret);
    }
}
