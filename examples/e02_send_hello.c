#include "cclient/api/core/core_api.h"
#include "cclient/api/extended/extended_api.h"

#include "common/trinary/tryte_ascii.h"
//#include "utils/time.h"
#include <inttypes.h>
#include "iota_client_service/config.h"
#include "iota_client_service/client_service.h"

static tryte_t const *const RECEIVER_ADDR =
(tryte_t *)"TOKLOARHKXQCVPPVVIPIJGLUTLTKFHYGMBBLOXJFYGSARLOTYFFSDZNYCOBOCNPGRMJWZCQBNOROUCE9G";

static tryte_t const *const TAG =
        (tryte_t *)"HELLOWORLD99999999999999999";


retcode_t send_transaction(iota_client_service_t *service){
    retcode_t ret_code = RC_OK;

    char message[] = "You did it!";

    bundle_transactions_t *bundle = NULL;
    bundle_transactions_new(&bundle);
    transfer_array_t *transfers = transfer_array_new();

    transfer_t tf = {};

    //Getting trits from address tryte chars
    //Read for more information: https://docs.iota.org/docs/iota-basics/0.1/references/tryte-alphabet
    flex_trits_from_trytes(tf.address, NUM_TRITS_ADDRESS, RECEIVER_ADDR, NUM_TRYTES_ADDRESS, NUM_TRYTES_ADDRESS);

    //Getting trits from tag chars
    flex_trits_from_trytes(tf.tag, NUM_TRITS_TAG, (const tryte_t *)TAG, NUM_TRYTES_TAG,
                           NUM_TRYTES_TAG);

    //Add the ascii message to the transfer
    transfer_message_set_string(&tf, message);

    //Preparing transfer array
    transfer_array_add(transfers, &tf);

    //Send transfer and setting seed = NULL, because we are sending a zero value transaction
    ret_code = iota_client_send_transfer(
            service, NULL, SECURITY_LEVEL, TIP_SELECTION_DEPTH,
            MINIMUM_WEIGHT_MAGNITUDE, false, transfers, NULL, NULL, NULL, bundle);

    printf("send transfer %s\n", error_2_string(ret_code));
    if (ret_code == RC_OK) {
        flex_trit_t const *bundle_hash = bundle_transactions_bundle_hash(bundle);
        printf("bundle hash: ");
        flex_trit_print(bundle_hash, NUM_TRITS_HASH);
        printf("\n");
    }

    bundle_transactions_free(&bundle);
    transfer_message_free(&tf);
    transfer_array_free(transfers);

    return ret_code;
}

int main(void){
    retcode_t ret = RC_ERROR;
    iota_client_service_t iota_client_service;
    init_iota_client(&iota_client_service);

    ret = send_transaction(&iota_client_service);
    if(ret == RC_OK){
        printf("Transaction was sent.\n");
    }else{
        printf("Transaction failed with error code: %i\n", ret);
    }
}