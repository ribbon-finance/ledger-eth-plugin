#include "ribbon_plugin.h"

static void set_vault_ui(ethQueryContractUI_t *msg) {
    strlcpy(msg->title, "Vault", msg->titleLength);
    strlcpy(msg->msg, "Unknown", msg->msgLength);

    vault_address_ticker_t *currentVault = NULL;
    for (uint8_t i = 0; i < NUM_VAULT_ADDRESS_COLLECTION; i++) {
        currentVault = (vault_address_ticker_t *) PIC(&CONTRACT_ADDRESS_COLLECTION[i]);
        if (memcmp(currentVault->contract_address,
                   msg->pluginSharedRO->txContent->destination,
                   ADDRESS_LENGTH) == 0) {
            memset(msg->msg, 0, msg->msgLength);
            strlcpy(msg->msg, (char *) currentVault->vault_ticker, msg->msgLength);
            break;
        }
    }
}

static void set_deposit_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Deposit", msg->titleLength);

    // Defaults to ETH if no vault found.
    uint8_t decimals = WEI_TO_ETHER;
    char ticker[MAX_TICKER_LEN] = "??? ";

    vault_address_ticker_t *currentVault = NULL;
    for (uint8_t i = 0; i < NUM_VAULT_ADDRESS_COLLECTION; i++) {
        currentVault = (vault_address_ticker_t *) PIC(&CONTRACT_ADDRESS_COLLECTION[i]);
        if (memcmp(currentVault->contract_address,
                   msg->pluginSharedRO->txContent->destination,
                   ADDRESS_LENGTH) == 0) {
            decimals = currentVault->decimals;
            strncpy(ticker, (char *) currentVault->asset_ticker, sizeof(ticker));
            break;
        }
    }

    amountToString(context->deposit_amount,
                   sizeof(context->deposit_amount),
                   decimals,
                   ticker,
                   msg->msg,
                   msg->msgLength);
}

static void set_deposit_eth_ui(ethQueryContractUI_t *msg) {
    strlcpy(msg->title, "Deposit", msg->titleLength);
    uint8_t decimals = WEI_TO_ETHER;
    char ticker[MAX_TICKER_LEN] = "ETH ";

    amountToString(msg->pluginSharedRO->txContent->value.value,
                   msg->pluginSharedRO->txContent->value.length,
                   decimals,
                   ticker,
                   msg->msg,
                   msg->msgLength);
}

static void set_initiate_or_instant_withdraw_ui(ethQueryContractUI_t *msg,
                                                context_t *context,
                                                bool isInstant) {
    if (isInstant) {
        strlcpy(msg->title, "Instant Withdraw", msg->titleLength);
    } else {
        strlcpy(msg->title, "Initiate Withdraw", msg->titleLength);
    }

    uint8_t decimals = WEI_TO_ETHER;
    char ticker[MAX_TICKER_LEN] = "??? ";

    vault_address_ticker_t *currentVault = NULL;
    for (uint8_t i = 0; i < NUM_VAULT_ADDRESS_COLLECTION; i++) {
        currentVault = (vault_address_ticker_t *) PIC(&CONTRACT_ADDRESS_COLLECTION[i]);
        if (memcmp(currentVault->contract_address,
                   msg->pluginSharedRO->txContent->destination,
                   ADDRESS_LENGTH) == 0) {
            decimals = currentVault->decimals;
            strncpy(ticker, (char *) currentVault->vault_token_ticker, sizeof(ticker));
            break;
        }
    }

    amountToString(context->withdraw_shares_amount,
                   sizeof(context->withdraw_shares_amount),
                   decimals,
                   ticker,
                   msg->msg,
                   msg->msgLength);
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

    if (context->selectorIndex == DEPOSIT || context->selectorIndex == DEPOSIT_ETH ||
        context->selectorIndex == DEPOSIT_YIELD_TOKEN) {
        switch (msg->screenIndex) {
            case 0:
                set_vault_ui(msg);
                break;
            case 1:
                switch (context->selectorIndex) {
                    case DEPOSIT:
                    case DEPOSIT_YIELD_TOKEN:
                        set_deposit_ui(msg, context);
                        break;
                    default:
                        set_deposit_eth_ui(msg);
                        break;
                }
            // Keep this
            default:
                PRINTF("Received an invalid screenIndex\n");
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                return;
        }
    } else if (context->selectorIndex == INITIATE_WITHDRAWAL ||
               context->selectorIndex == INSTANT_WITHDRAW) {
        bool isInstant = context->selectorIndex == INSTANT_WITHDRAW;
        switch (msg->screenIndex) {
            case 0:
                set_vault_ui(msg);
                break;
            case 1:
                set_initiate_or_instant_withdraw_ui(msg, context, isInstant);
                break;
            // Keep this
            default:
                PRINTF("Received an invalid screenIndex\n");
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                return;
        }
    } else if (context->selectorIndex == COMPLETE_WITHDRAWAL) {
        switch (msg->screenIndex) {
            case 0:
                set_vault_ui(msg);
                break;
            // Keep this
            default:
                PRINTF("Received an invalid screenIndex\n");
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                return;
        }
    } else {
        PRINTF("Selector index: %d not supported\n", context->selectorIndex);
        msg->result = ETH_PLUGIN_RESULT_ERROR;
    }
}
