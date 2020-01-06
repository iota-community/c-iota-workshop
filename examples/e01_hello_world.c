#include "cclient/api/core/core_api.h"
#include "cclient/api/extended/extended_api.h"

#include <inttypes.h>
#include "iota_client_service/config.h"
#include "iota_client_service/client_service.h"

retcode_t get_iota_node_info(iota_client_service_t *iota_client_service, get_node_info_res_t *node_response) {
    retcode_t ret = RC_ERROR;
    // Connect to the node
    ret = iota_client_get_node_info(iota_client_service, node_response);

    // Define variables to determine whether trit conversion succeeds
    trit_t trytes_out[NUM_TRYTES_HASH + 1];
    size_t trits_count = 0;
    // If the node returned data, print it to the console
    if (ret == RC_OK) {
        printf("appName %s \n", node_response->app_name->data);
        printf("appVersion %s \n", node_response->app_version->data);

        // Convert the returned trits to trytes
        // For more information about trits and trytes, see the IOTA documentation portal: https://docs.iota.org/docs/getting-started/0.1/introduction/ternary
        trits_count = flex_trits_to_trytes(trytes_out, NUM_TRYTES_HASH,
                                        node_response->latest_milestone, NUM_TRITS_HASH,
                                        NUM_TRITS_HASH);
        if (trits_count == 0) {
            printf("Failed to convert trits to trytes\n");
            goto done;
        }
        // Empty this string: we don't need it anymore
        trytes_out[NUM_TRYTES_HASH] = '\0';

        printf("latestMilestone %s \n", trytes_out);
        printf("latestMilestoneIndex %u\n", (uint32_t) node_response->latest_milestone_index);
        printf("latestSolidSubtangleMilestoneIndex %u\n", (uint32_t)
        node_response->latest_solid_subtangle_milestone_index);

        printf("milestoneStartIndex %u\n", node_response->milestone_start_index);
        printf("neighbors %d \n", node_response->neighbors);
        printf("packetsQueueSize %d \n", node_response->packets_queue_size);
        printf("tips %u \n", node_response->tips);
        printf("transactionsToRequest %u\n", node_response->transactions_to_request);
        printf("features: ");
        size_t num_features = get_node_info_req_features_len(node_response);
        for (; num_features > 0; num_features--) {
          printf("%s, ", get_node_info_res_features_at(node_response, num_features - 1));
          printf("\n");
        }
    } else {
        printf("Failed to connect to the node.");
    }

    done:
    // Free the response object
    get_node_info_res_free(&node_response);
    return ret;
}

int main(void) {
    // Create the client service
    iota_client_service_t iota_client_service;
    init_iota_client(&iota_client_service);
    // Allocate a response object
    get_node_info_res_t *node_response = get_node_info_res_new();
    // Call the getNodeInfo endpoint
    get_iota_node_info(&iota_client_service, node_response);
}
