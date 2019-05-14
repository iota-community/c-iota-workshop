#include "cclient/api/core/core_api.h"
#include "cclient/api/extended/extended_api.h"
#include "cclient/types/types.h"
#include "common/trinary/tryte_ascii.h"
#include <inttypes.h>

//Todo: If needed, replace it with your node configuration
#define CONFIG_IRI_NODE_URI "nodes.thetangle.org"
#define CONFIG_IRI_NODE_PORT 443
#define CONFIG_ENABLE_HTTPS true

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

#define TIP_SELECTION_DEPTH 3
//TESTNET => 9, PROD => 13
#define MINIMUM_WEIGHT_MAGNITUDE 13
#define DO_LOCAL_POW false

#define ADDRESS "TOKLOARHKXQCVPPVVIPIJGLUTLTKFHYGMBBLOXJFYGSARLOTYFFSDZNYCOBOCNPGRMJWZCQBNOROUCE9G"
#define TAG "HELLOWORLD"

static void init_iota_client(iota_client_service_t *const service)
{
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

retcode_t send_transaction(iota_client_service_t *service){
    retcode_t ret = RC_ERROR;
    char test_data[] = "You did it!";
    uint64_t timestamp = 0;

    flex_trit_t address[FLEX_TRIT_SIZE_243];
    flex_trits_from_trytes(address, NUM_TRITS_ADDRESS, (tryte_t *)ADDRESS, NUM_TRYTES_ADDRESS, NUM_TRYTES_ADDRESS);

    flex_trit_t tag[FLEX_TRIT_SIZE_81];
    flex_trits_from_trytes(tag, NUM_TRITS_TAG, (tryte_t *)TAG, NUM_TRYTES_TAG, NUM_TRYTES_TAG);


    tryte_t data_trytes[NUM_TRYTES_ADDRESS];
    ascii_to_trytes(test_data, data_trytes);

    flex_trit_t data[FLEX_TRIT_SIZE_243];
    flex_trits_from_trytes(data, NUM_TRITS_ADDRESS, data_trytes, NUM_TRYTES_ADDRESS, NUM_TRYTES_ADDRESS);

    transfer_t *transfer = transfer_data_new(address, tag, data, NUM_TRITS_ADDRESS, timestamp);
    transfer_t *transfers[1] = {transfer};
    uint32_t num_transfer = 1;

    bundle_transactions_t *bundle = NULL;
    bundle_transactions_new(&bundle);

    ret = iota_client_send_transfer(
            service, TIP_SELECTION_DEPTH, MINIMUM_WEIGHT_MAGNITUDE,
            DO_LOCAL_POW, transfers, num_transfer, NULL, bundle);

    return ret;
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