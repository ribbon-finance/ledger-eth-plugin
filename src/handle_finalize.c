#include "ribbon_plugin.h"

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

    if (context->selectorIndex == DEPOSIT || context->selectorIndex == DEPOSIT_ETH ||
        context->selectorIndex == DEPOSIT_YIELD_TOKEN) {
        msg->numScreens = 2;
    } else if (context->selectorIndex == INITIATE_WITHDRAWAL) {
        msg->numScreens = 2;
    } else if (context->selectorIndex == COMPLETE_WITHDRAWAL ||
               context->selectorIndex == INSTANT_WITHDRAW) {
        msg->numScreens = 1;
    } else {
        msg->numScreens = 0;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}
