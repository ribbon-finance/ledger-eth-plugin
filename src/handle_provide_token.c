#include "boilerplate_plugin.h"

void handle_provide_token(void *parameters) {
    ethPluginProvideInfo_t *msg = (ethPluginProvideInfo_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    switch (context->selectorIndex) {
        case SWAP_EXACT_ETH_FOR_TOKENS:
            if (msg->item1) {
                // The Ethereum App found the information for the requested token!
                // Store its decimals.
                context->decimals = msg->item1->token.decimals;
                // Store its ticker.
                strlcpy(context->ticker,
                        (char *) msg->item1->token.ticker,
                        sizeof(context->ticker));
                context->token_found = true;
            } else {
                context->token_found = false;
            }
            break;
        default:
            break;
    }
    msg->result = ETH_PLUGIN_RESULT_OK;
}