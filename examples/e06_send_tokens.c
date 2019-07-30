#include "cclient/api/core/core_api.h"
#include "cclient/api/extended/extended_api.h"

#include "common/trinary/tryte_ascii.h"
#include "utils/time.h"
#include <inttypes.h>

#include "iota_client_service/config.h"
#include "iota_client_service/client_service.h"


static tryte_t const *const SEED =
        (tryte_t *)"G9JEMIRJKUXDKUPPAIMEQS9VADYLSJRSBTEIRDWSCTLCVQOJWBM9XESTWTSONOTDDQUXMYCNVAKZWPPYW";

static tryte_t const *const RECEIVER_ADDR =
        (tryte_t *)"TOKLOARHKXQCVPPVVIPIJGLUTLTKFHYGMBBLOXJFYGSARLOTYFFSDZNYCOBOCNPGRMJWZCQBNOROUCE9G";

retcode_t send_balance(iota_client_service_t *s) {
    retcode_t ret_code = RC_OK;

    bundle_transactions_t *bundle = NULL;
    bundle_transactions_new(&bundle);
    transfer_array_t *transfers = transfer_array_new();

    // transfer setup
    transfer_t tf = {};
    // seed
    flex_trit_t seed[NUM_FLEX_TRITS_ADDRESS];
    flex_trits_from_trytes(seed, NUM_TRITS_ADDRESS, SEED, NUM_TRYTES_ADDRESS, NUM_TRYTES_ADDRESS);

    // receiver
    flex_trits_from_trytes(tf.address, NUM_TRITS_ADDRESS, RECEIVER_ADDR, NUM_TRYTES_ADDRESS, NUM_TRYTES_ADDRESS);

    // tag
    flex_trits_from_trytes(tf.tag, NUM_TRITS_TAG, (const tryte_t *)"CCLIENT99999999999999999999", NUM_TRYTES_TAG,
                           NUM_TRYTES_TAG);

    // value
    tf.value = 1;  // send 5i to receiver

    // message (optional)
    transfer_message_set_string(&tf, "Sending 1i!!");

    transfer_array_add(transfers, &tf);
 // send with input options
    /* input setup (optional) */
  inputs_t input_list = {};  // input list
  input_t input_a = {
      .balance = 1, .key_index = 1, .security = SECURITY_LEVEL, .address = {},  // set address later
  };

  // address of the input
  //Fixme: Take a look into e04_generate_address.c and e05_check_balance.c in order to generate and check addresses.
  // e04, e05 and 06 should be combined in production code
  flex_trits_from_trytes(
      input_a.address, NUM_TRITS_ADDRESS,
      (const tryte_t *)"RJBYLCIOUKWJVCUKZQZCPIKNBUOGRGVXHRTTE9ZFSCGTFRKELMJBDDAKEYYCLHLJDNSHQ9RTIUIDLMUOB",
      NUM_TRYTES_ADDRESS, NUM_TRYTES_ADDRESS);

  // adding input object to the input list
  inputs_append(&input_list, &input_a);


  flex_trit_t *reminder_addr = NULL;
  flex_trit_t *reference = NULL;


  ret_code = iota_client_send_transfer(s, seed, SECURITY_LEVEL, TIP_SELECTION_DEPTH, MINIMUM_WEIGHT_MAGNITUDE,
          false, transfers, reminder_addr, reference,
                                       &input_list, bundle);
  inputs_clear(&input_list);

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

    ret = send_balance(&iota_client_service);
    if(ret == RC_OK){
        printf("Send tokens done.\n");
    }else{
        printf("Send tokens done with error code: %i\n", ret);
    }
}