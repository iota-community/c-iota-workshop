#include "cclient/api/core/core_api.h"
#include "cclient/api/extended/extended_api.h"

#include "common/trinary/tryte_ascii.h"
#include <inttypes.h>
#include "iota_client_service/config.h"
#include "iota_client_service/client_service.h"

static tryte_t const *const ADDRESS =
(tryte_t *)"ZLGVEQ9JUZZWCZXLWVNTHBDX9G9KZTJP9VEERIIFHY9SIQKYBVAHIMLHXPQVE9IXFDDXNHQINXJDRPFDXNYVAPLZAW";

retcode_t send_transaction(iota_client_service_t *service){
    retcode_t ret_code = RC_OK;

    char message[] = "Hello world";

    bundle_transactions_t *bundle = NULL;
    bundle_transactions_new(&bundle);
    
    // Create a transfers array to which you can add transaction data
    transfer_array_t *transfers = transfer_array_new();

    // Create an empty transfer object
    transfer_t tf = {};

    // Convert the address from trytes to trits
    // For more information about trits and trytes, see the IOTA documentation portal: https://docs.iota.org/docs/getting-started/0.1/introduction/ternary
    flex_trits_from_trytes(tf.address, NUM_TRITS_ADDRESS, ADDRESS, NUM_TRYTES_ADDRESS, NUM_TRYTES_ADDRESS);

    // Convert the ASCII message to trytes and add it to the transfer object
    transfer_message_set_string(&tf, message);

    // Add the transfer object to the transfers array
    transfer_array_add(transfers, &tf);

    // Create a bundle from the transfers array and send it to the node
    ret_code = iota_client_send_transfer(
            service, NULL, SECURITY_LEVEL, DEPTH,
            MINIMUM_WEIGHT_MAGNITUDE, false, transfers, NULL, NULL, NULL, bundle);

    printf("Send \'hello world\' %s\n", error_2_string(ret_code));
    if (ret_code == RC_OK) {
        flex_trit_t const *bundle_hash = bundle_transactions_bundle_hash(bundle);
        printf("Bundle hash: ");
        // Print the bundle hash to the console
        flex_trit_print(bundle_hash, NUM_TRITS_HASH);
        printf("\n");
    }

    // Free the objects
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
        printf("Transaction failed to send with error code: %i\n", ret);
    }
}