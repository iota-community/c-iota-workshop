#include "cclient/api/core/core_api.h"
#include "cclient/api/extended/extended_api.h"

#include "common/trinary/tryte_ascii.h"
#include "utils/time.h"
#include <inttypes.h>

#include "iota_client_service/config.h"
#include "iota_client_service/client_service.h"

#define FIND_BY_ADDR

#define TX_INDEX 0

static tryte_t const *const ADDRESS =
        (tryte_t *)"ZLGVEQ9JUZZWCZXLWVNTHBDX9G9KZTJP9VEERIIFHY9SIQKYBVAHIMLHXPQVE9IXFDDXNHQINXJDRPFDXNYVAPLZAW";

retcode_t find_transaction(iota_client_service_t *s, tryte_t const *const address) {
    retcode_t ret_code = RC_ERROR;
    find_transactions_req_t *find_tran = find_transactions_req_new();
    transaction_array_t *out_tx_objs = transaction_array_new();
    if (!find_tran || !out_tx_objs) {
        printf("Error: Out of memory\n");
        goto done;
    }

    flex_trit_t hash[FLEX_TRIT_SIZE_243];

    // Convert the address from trytes to trits
    // For more information about trits and trytes, see the IOTA documentation portal: https://docs.iota.org/docs/getting-started/0.1/introduction/ternary
    if (flex_trits_from_trytes(hash, NUM_TRITS_HASH, address, NUM_TRYTES_HASH, NUM_TRYTES_HASH) == 0) {
        printf("Failed to convert trytes to trits\n");
        goto done;
    }

    // Add the address trits to find_transactions_req_t
    if ((ret_code = hash243_queue_push(&find_tran->addresses, hash)) != RC_OK) {
        printf("Error: push queue %s\n", error_2_string(ret_code));
        goto done;
    }

    // Find any transactions that were sent to the address
    if ((ret_code = iota_client_find_transaction_objects(s, find_tran, out_tx_objs)) == RC_OK) {
        // Print the total number of transactions that the node returned
        printf("find transaction count: %lu\n", transaction_array_len(out_tx_objs));
        iota_transaction_t *tx1 = transaction_array_at(out_tx_objs, TX_INDEX);
        // Print information about the first transaction that was found
        if (tx1) {
            printf("dump first transaction:\n");
            printf("value = %" PRId64 ", current_index in the bundle = %" PRIu64 ", last_index of the bundle = %" PRIu64 "\n", transaction_value(tx1),
                    transaction_current_index(tx1), transaction_last_index(tx1));
            printf("address: ");
            flex_trit_print(transaction_address(tx1), NUM_TRITS_ADDRESS);
            printf("\n");

            // Print the value in the transaction's signatureMessageFragment field
            printf("data: ");
            tryte_t * trytes = transaction_message(tx1);
            size_t tryte_size = strlen((char*)trytes);
            char buffer[tryte_size / 2 + 1];
            trytes_to_ascii(trytes, tryte_size, buffer);

            printf("%s\n", buffer);
        }
    } else {
        printf("Error: %s \n", error_2_string(ret_code));
    }

    done:
    // Free the objects
    find_transactions_req_free(&find_tran);
    transaction_array_free(out_tx_objs);

    return ret_code;
}

int main(void){
    retcode_t ret = RC_ERROR;
    iota_client_service_t iota_client_service;
    init_iota_client(&iota_client_service);

    ret = find_transaction(&iota_client_service, ADDRESS);
    if(ret == RC_OK){
        printf("Transaction read.\n");
    }else{
        printf("Transaction could not be received. Error code: %i\n", ret);
    }
}