#include "boilerplate_plugin.h"

// EDIT THIS: You need to adapt / remove the static functions (set_send_ui, set_receive_ui ...) to
// match what you wish to display.

// Set UI for the "Send" screen.
// EDIT THIS: Adapt / remove this function to your needs.
static void set_send_ui(ethQueryContractUI_t *msg) {
    strlcpy(msg->title, "Send", msg->titleLength);

    const uint8_t *eth_amount = msg->pluginSharedRO->txContent->value.value;
    uint8_t eth_amount_size = msg->pluginSharedRO->txContent->value.length;

    // Converts the uint256 number located in `eth_amount` to its string representation and
    // copies this to `msg->msg`.
    amountToString(eth_amount, eth_amount_size, WEI_TO_ETHER, "ETH ", msg->msg, msg->msgLength);
}

// Set UI for "Receive" screen.
// EDIT THIS: Adapt / remove this function to your needs.
static void set_receive_ui(ethQueryContractUI_t *msg, const context_t *context) {
    strlcpy(msg->title, "Receive Min.", msg->titleLength);

    uint8_t decimals = context->decimals;
    const char *ticker = context->ticker;

    // If the token look up failed, use the default network ticker along with the default decimals.
    if (!context->token_found) {
        decimals = WEI_TO_ETHER;
        ticker = msg->network_ticker;
    }

    amountToString(context->amount_received,
                   sizeof(context->amount_received),
                   decimals,
                   ticker,
                   msg->msg,
                   msg->msgLength);
}

// Set UI for "Beneficiary" screen.
// EDIT THIS: Adapt / remove this function to your needs.
static void set_beneficiary_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Beneficiary", msg->titleLength);

    // Prefix the address with `0x`.
    msg->msg[0] = '0';
    msg->msg[1] = 'x';

    // We need a random chainID for legacy reasons with `getEthAddressStringFromBinary`.
    // Setting it to `0` will make it work with every chainID :)
    uint64_t chainid = 0;

    // Get the string representation of the address stored in `context->beneficiary`. Put it in
    // `msg->msg`.
    getEthAddressStringFromBinary(
        context->beneficiary,
        msg->msg + 2,  // +2 here because we've already prefixed with '0x'.
        msg->pluginSharedRW->sha3,
        chainid);
}

static void set_vault_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Vault", msg->titleLength);
    strlcpy(msg->msg,
            (char *) context->vaultName,
            msg->msgLength);
}

static void set_deposit_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "DEPOSIT", msg->titleLength);
    strlcpy(msg->msg, "AAVE 69.69", msg->msgLength);

    // strlcpy(msg->title, "Deposit", msg->titleLength);

    // uint8_t decimals = context->decimals;
    // const char *ticker = context->ticker;

    // // If the token look up failed, use the default network ticker along with the default decimals.
    // if (!context->token_found) {
    //     decimals = WEI_TO_ETHER;
    //     ticker = "ETH";
    // }

    // amountToString(context->deposit_amount,
    //                sizeof(context->deposit_amount),
    //                decimals,
    //                ticker,
    //                msg->msg,
    //                msg->msgLength);
}

void handle_query_contract_ui(void *parameters) {
    ethQueryContractUI_t *msg = (ethQueryContractUI_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    // msg->title is the upper line displayed on the device.
    // msg->msg is the lower line displayed on the device.

    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    msg->result = ETH_PLUGIN_RESULT_OK;

    if (context->selectorIndex == SWAP_EXACT_ETH_FOR_TOKENS) {
        switch (msg->screenIndex) {
            case 0:
                set_send_ui(msg);
                break;
            case 1:
                set_receive_ui(msg, context);
                break;
            case 2:
                set_beneficiary_ui(msg, context);
                break;
            // Keep this
            default:
                PRINTF("Received an invalid screenIndex\n");
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                return;
        }
    } else if (context->selectorIndex == DEPOSIT || context->selectorIndex == DEPOSIT_ETH) {
        switch (msg->screenIndex) {
            case 0:
                set_vault_ui(msg, context);
                break;
            case 1:
                set_deposit_ui(msg, context);
                break;
            // Keep this
            default:
                PRINTF("Received an invalid screenIndex\n");
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                return;
        }
    }
}
