#include "cclient/api/core/core_api.h"
#include "cclient/api/extended/extended_api.h"

#include "common/trinary/tryte_ascii.h"
#include "utils/time.h"
#include <inttypes.h>

#define FIND_BY_ADDR

#define TX_INDEX 0

static tryte_t const *const ADDR_HASH =
        (tryte_t *)"TOKLOARHKXQCVPPVVIPIJGLUTLTKFHYGMBBLOXJFYGSARLOTYFFSDZNYCOBOCNPGRMJWZCQBNOROUCE9G";

retcode_t find_transaction(iota_client_service_t *s, tryte_t const *const address) {
    retcode_t ret_code = RC_ERROR;
    find_transactions_req_t *find_tran = find_transactions_req_new();
    transaction_array_t *out_tx_objs = transaction_array_new();
    if (!find_tran || !out_tx_objs) {
        printf("Error: OOM\n");
        goto done;
    }

    flex_trit_t tmp_hash[FLEX_TRIT_SIZE_243];
    if (flex_trits_from_trytes(tmp_hash, NUM_TRITS_HASH, address, NUM_TRYTES_HASH, NUM_TRYTES_HASH) == 0) {
        printf("Error: converting flex_trit failed.\n");
        goto done;
    }

    if ((ret_code = hash243_queue_push(&find_tran->addresses, tmp_hash)) != RC_OK) {
        printf("Error: push queue %s\n", error_2_string(ret_code));
        goto done;
    }

    if ((ret_code = iota_client_find_transaction_objects(s, find_tran, out_tx_objs)) == RC_OK) {
        printf("find transaction count: %lu\n", transaction_array_len(out_tx_objs));
        iota_transaction_t *tx1 = transaction_array_at(out_tx_objs, TX_INDEX);
        if (tx1) {
            printf("dump first transaction:\n");
            printf("value = %" PRId64 ", curr_index = %" PRIu64 ", last_index = %" PRIu64 "\n", transaction_value(tx1),
                    transaction_current_index(tx1), transaction_last_index(tx1));
            printf("addr: ");
            flex_trit_print(transaction_address(tx1), NUM_TRITS_ADDRESS);
            printf("\n");

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
    find_transactions_req_free(&find_tran);
    transaction_array_free(out_tx_objs);

    return ret_code;
}

int main(void){
    retcode_t ret = RC_ERROR;
    iota_client_service_t iota_client_service;
    init_iota_client(&iota_client_service);

    ret = find_transaction(&iota_client_service, ADDR_HASH);
    if(ret == RC_OK){
        printf("Transaction is received.\n");
    }else{
        printf("Transaction is received with error code: %i\n", ret);
    }
}