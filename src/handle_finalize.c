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
    } else if (context->selectorIndex == DEPOSIT || context->selectorIndex == DEPOSIT_ETH) {
        msg->numScreens = 2;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}
