#include "ribbon_plugin.h"

// Sets the first screen to display.
void handle_query_contract_id(void *parameters) {
    ethQueryContractID_t *msg = (ethQueryContractID_t *) parameters;
    const context_t *context = (const context_t *) msg->pluginContext;
    // msg->name will be the upper sentence displayed on the screen.
    // msg->version will be the lower sentence displayed on the screen.

    // For the first screen, display the plugin name.
    strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);

    // EDIT THIS: Adapt the cases by modifying the strings you pass to `strlcpy`.
    if (context->selectorIndex == DEPOSIT || context->selectorIndex == DEPOSIT_ETH ||
        context->selectorIndex == DEPOSIT_YIELD_TOKEN) {
        strlcpy(msg->version, "Deposit", msg->versionLength);
        msg->result = ETH_PLUGIN_RESULT_OK;
    } else if (context->selectorIndex == INITIATE_WITHDRAWAL) {
        strlcpy(msg->version, "Initiate Withdraw", msg->versionLength);
        msg->result = ETH_PLUGIN_RESULT_OK;
    } else if (context->selectorIndex == INSTANT_WITHDRAW) {
        strlcpy(msg->version, "Instant Withdraw", msg->versionLength);
        msg->result = ETH_PLUGIN_RESULT_OK;
    } else if (context->selectorIndex == COMPLETE_WITHDRAWAL) {
        strlcpy(msg->version, "Complete Withdraw", msg->versionLength);
        msg->result = ETH_PLUGIN_RESULT_OK;
    } else {
        PRINTF("Selector index: %d not supported\n", context->selectorIndex);
        msg->result = ETH_PLUGIN_RESULT_ERROR;
    }
}