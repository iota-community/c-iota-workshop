#include "cclient/api/core/core_api.h"
#include "cclient/api/extended/extended_api.h"

#include <inttypes.h>

//Todo: If needed, replace it with your node configuration
#define CONFIG_IRI_NODE_URI "nodes.thetangle.org"
#define CONFIG_IRI_NODE_PORT 443
//Todo: Comment out, if you want to disbale HTTPS
#define CONFIG_ENABLE_HTTPS

//Todo: If needed, replace with your valid SSL certificate
static char const *ssl_certificate_pem =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\r\n"
        "ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\r\n"
        "b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\r\n"
        "MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\r\n"
        "b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\r\n"
        "ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\r\n"
        "9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\r\n"
        "IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\r\n"
        "VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\r\n"
        "93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\r\n"
        "jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\r\n"
        "AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\r\n"
        "A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\r\n"
        "U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\r\n"
        "N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\r\n"
        "o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\r\n"
        "5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\r\n"
        "rqXRfboQnoZsG4q5WTP468SQvvG5\r\n"
        "-----END CERTIFICATE-----\r\n";

static void init_iota_client(iota_client_service_t *const service) {
    service->http.path = "/";
    service->http.content_type = "application/json";
    service->http.accept = "application/json";
    service->http.host = CONFIG_IRI_NODE_URI;
    service->http.port = CONFIG_IRI_NODE_PORT;
    service->http.api_version = 1;
#ifdef CONFIG_ENABLE_HTTPS
    service->http.ca_pem = ssl_certificate_pem;
#else
    service->http.ca_pem = NULL;
#endif
    service->serializer_type = SR_JSON;
    iota_client_core_init(service);
    iota_client_extended_init();
}

retcode_t get_iota_node_info(iota_client_service_t *iota_client_service, get_node_info_res_t *node_response) {
    retcode_t ret = RC_ERROR;
    ret = iota_client_get_node_info(iota_client_service, node_response);

    trit_t trytes_out[NUM_TRYTES_HASH + 1];
    size_t trits_count = 0;
    if (ret == RC_OK) {
        printf("appName %s \n", node_response->app_name->data);
        printf("appVersion %s \n", node_response->app_version->data);
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
        trits_count = flex_trits_to_trytes(trytes_out, NUM_TRYTES_HASH,
                                           node_response->latest_milestone, NUM_TRITS_HASH,
                                           NUM_TRITS_HASH);
        if (trits_count == 0) {
            printf("trit converting failed\n");
            goto done;
        }
        trytes_out[NUM_TRYTES_HASH] = '\0';
        printf("latestSolidSubtangleMilestone %s \n", trytes_out);

        printf("latestSolidSubtangleMilestoneIndex %u\n",
               node_response->latest_solid_subtangle_milestone_index);
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