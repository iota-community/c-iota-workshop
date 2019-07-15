#include "cclient/api/core/core_api.h"
#include "cclient/api/extended/extended_api.h"

#include "common/trinary/tryte_ascii.h"
#include <inttypes.h>

#include "config.h"
#include "client_service.h"

void init_iota_client(iota_client_service_t *const service)
{
    service->http.path = "/";
    service->http.content_type = "application/json";
    service->http.accept = "application/json";
    service->http.host = CONFIG_IRI_NODE_URI;
    service->http.port = CONFIG_IRI_NODE_PORT;
    service->http.api_version = 1;
#ifdef CONFIG_ENABLE_HTTPS
    service->http.ca_pem = TLS_CERTIFICATE_PEM;
#else
    service->http.ca_pem = NULL;
#endif
    service->serializer_type = SR_JSON;
    iota_client_core_init(service);
    iota_client_extended_init();
}
