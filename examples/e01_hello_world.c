#include "cclient/api/core/core_api.h"
#include "cclient/api/extended/extended_api.h"

#include <inttypes.h>
#include "iota_client_service/config.h"
#include "iota_client_service/client_service.h"

retcode_t get_iota_node_info(iota_client_service_t *iota_client_service, get_node_info_res_t *node_response) {
    retcode_t ret = RC_ERROR;
    ret = iota_client_get_node_info(iota_client_service, node_response);

    trit_t trytes_out[NUM_TRYTES_HASH + 1];
    size_t trits_count = 0;
    if (ret == RC_OK) {
        printf("appName %s \n", node_response->app_name->data);
        printf("appVersion %s \n", node_response->app_version->data);

        //Converting returned latest_milestone trits to tryte chars
        //Read for more information: https://docs.iota.org/docs/iota-basics/0.1/references/tryte-alphabet
        trits_count = flex_trits_to_trytes(trytes_out, NUM_TRYTES_HASH,
                                           node_response->latest_milestone, NUM_TRITS_HASH,
                                           NUM_TRITS_HASH);
        if (trits_count == 0) {
            printf("trit converting failed\n");
            goto done;
        }
        trytes_out[NUM_TRYTES_HASH] = '\0';
        printf("latestMilestone %s \n", trytes_out);
        printf("latestMilestoneIndex %u\n", (uint32_t) node_response->latest_milestone_index);

        printf("milestoneStratIndex %u\n", node_response->milestone_start_index);
        printf("neighbors %d \n", node_response->neighbors);
        printf("packetsQueueSize %d \n", node_response->packets_queue_size);
        printf("time %"
        PRIu64
        "\n", node_response->time);
        printf("tips %u \n", node_response->tips);
        printf("transactionsToRequest %u\n", node_response->transactions_to_request);
    }else{
        printf("Node info failed.");
    }

    done:
    get_node_info_res_free(&node_response);
    return ret;
}

int main(void) {
    iota_client_service_t iota_client_service;
    init_iota_client(&iota_client_service);
    get_node_info_res_t *node_response = get_node_info_res_new();
    get_iota_node_info(&iota_client_service, node_response);
}