#include "cclient/api/core/core_api.h"
#include "cclient/api/extended/extended_api.h"

#include "common/trinary/tryte_ascii.h"
#include "utils/time.h"
#include <inttypes.h>

#include "iota_client_service/config.h"
#include "iota_client_service/client_service.h"


static tryte_t const *const ADDR_HASH =
        (tryte_t *)"TOKLOARHKXQCVPPVVIPIJGLUTLTKFHYGMBBLOXJFYGSARLOTYFFSDZNYCOBOCNPGRMJWZCQBNOROUCE9G";

retcode_t get_balance(iota_client_service_t *service) {
    retcode_t ret_code = RC_OK;
    flex_trit_t tmp_hash[FLEX_TRIT_SIZE_243];
    get_balances_req_t *balance_req = get_balances_req_new();
    get_balances_res_t *balance_res = get_balances_res_new();

    if (!balance_req || !balance_res) {
        printf("Error: OOM\n");
        goto done;
    }

    if (flex_trits_from_trytes(tmp_hash, NUM_TRITS_HASH, ADDR_HASH, NUM_TRYTES_HASH, NUM_TRYTES_HASH) == 0) {
        printf("Error: converting flex_trit failed\n");
        goto done;
    }

    if ((ret_code = hash243_queue_push(&balance_req->addresses, tmp_hash)) != RC_OK) {
        printf("Error: Adding hash to list failed!\n");
        goto done;
    }

    balance_req->threshold = 100;

    if ((ret_code = iota_client_get_balances(service, balance_req, balance_res)) == RC_OK) {
        hash243_queue_entry_t *q_iter = NULL;
        size_t balance_cnt = get_balances_res_balances_num(balance_res);
        printf("balances: [");
        for (size_t i = 0; i < balance_cnt; i++) {
            printf(" %" PRIu64 " ", get_balances_res_balances_at(balance_res, i));
        }
        printf("]\n");

        CDL_FOREACH(balance_res->references, q_iter) {
            printf("reference: ");
            flex_trit_print(q_iter->hash, NUM_TRITS_HASH);
            printf("\n");
        }
    }

    done:
    get_balances_req_free(&balance_req);
    get_balances_res_free(&balance_res);

    return ret_code;
}

int main(void){
    retcode_t ret = RC_ERROR;
    iota_client_service_t iota_client_service;
    init_iota_client(&iota_client_service);

    ret = get_balance(&iota_client_service);
    if(ret == RC_OK){
        printf("Check balances done.\n");
    }else{
        printf("Check balances done with error code: %i\n", ret);
    }
}