#include "ribbon_plugin.h"

void handle_provide_token(void *parameters) {
    ethPluginProvideInfo_t *msg = (ethPluginProvideInfo_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    // Nothing to do here

    msg->result = ETH_PLUGIN_RESULT_OK;
}