#include "boilerplate_plugin.h"

size_t convert_hex(uint8_t *dest, size_t count, const char *src) {
    size_t i;
    int value;
    for (i = 0; i < count && sscanf(src + i * 2, "%2x", &value) == 1; i++) {
        dest[i] = value;
    }
    return i;
}

void handle_finalize(void *parameters) {
    ethPluginFinalize_t *msg = (ethPluginFinalize_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    msg->uiType = ETH_UI_TYPE_GENERIC;

    // EDIT THIS: set `tokenLookup1` (and maybe `tokenLookup2`) to point to
    // token addresses you will info for (such as decimals, ticker...).
    if (context->selectorIndex == SWAP_EXACT_ETH_FOR_TOKENS) {
        msg->numScreens = 2;

        // If the beneficiary is NOT the sender, we will need an additional screen to display it.
        if (memcmp(msg->address, context->beneficiary, ADDRESS_LENGTH) != 0) {
            msg->numScreens += 1;
        }
        msg->tokenLookup1 = context->token_received;
    } else if (
        context->selectorIndex == DEPOSIT ||
        context->selectorIndex == DEPOSIT_ETH
    ) {
        msg->numScreens = 1;

        // Convert destination address into string
        // uint8_t dest[ADDRESS_LENGTH];
        // copy_address(dest,
        //              msg->pluginSharedRO->txContent->destination,
        //              sizeof(msg->pluginSharedRO->txContent->destination));
        // char destAddr[43] = "";
        // int i;
        // for (i = 0; i < ADDRESS_LENGTH; i++) {
        //     char buffer[10];
        //     // sprintf(buffer, "%x", dest[i]);
        //     itoa(dest[i], buffer, 16);
        //     // strncat(destAddr, &buffer[0], 1);
        // }
        // msg->tokenLookup1 = &

        // if (strcmp(destAddr, "e63151a0ed4e5fafdc951d877102cf0977abd365")) {
            // context->gotem = true;
        // }

        // AAVE TOKEN 0x7Fc66500c84A76Ad7e9c93437bFc5Ac33E2DDaE9
        // VAULT CONTRACT 0xe63151a0ed4e5fafdc951d877102cf0977abd365

        // msg->tokenLookup1 = context->deposit_token_address;
        // TODO: - Change token lookup address based on destination address
        // PRINTF("DESTINATION: %d\n", msg->pluginSharedRO->txContent->destination);
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}
