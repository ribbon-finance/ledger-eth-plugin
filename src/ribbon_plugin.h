#pragma once

#include "eth_internals.h"
#include "eth_plugin_interface.h"
#include <string.h>

// Number of selectors defined in this plugin. Should match the enum `selector_t`.
#define NUM_SELECTORS 7

// Name of the plugin.
#define PLUGIN_NAME "Ribbon Finance"

#define NUM_VAULT_ADDRESS_COLLECTION 7
#define MAX_VAULT_TICKER_LEN         20
typedef struct vault_address_ticker {
    uint8_t contract_address[ADDRESS_LENGTH];
    char vault_ticker[MAX_VAULT_TICKER_LEN];
    char asset_ticker[MAX_TICKER_LEN];
    uint8_t decimals;
    char vault_token_ticker[MAX_VAULT_TICKER_LEN];
} vault_address_ticker_t;
extern const vault_address_ticker_t CONTRACT_ADDRESS_COLLECTION[NUM_VAULT_ADDRESS_COLLECTION];

// Enumeration of the different selectors possible.
// Should follow the exact same order as the array declared in main.c
// EDIT THIS: Change the naming (`selector_t`), and add your selector names.
// ===== SELECTORS =====
typedef enum {
    DEPOSIT = 0,
    DEPOSIT_ETH,
    DEPOSIT_YIELD_TOKEN,
    INSTANT_WITHDRAW,
    INSTANT_WITHDRAW_STETH,
    INITIATE_WITHDRAWAL,
    COMPLETE_WITHDRAWAL,
} selector_t;

// ===== DATA =====
// Enumeration used to parse the smart contract data.
typedef enum {
    PATH_OFFSET,
    PATH_LENGTH,
    UNEXPECTED_PARAMETER,
    DEPOSIT_AMOUNT,
    WITHDRAW_NUM_SHARES
} parameter;

extern const uint32_t RIBBON_SELECTORS[NUM_SELECTORS];

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
// EDIT THIS: This struct is used by your plugin to save the parameters you parse. You
// will need to adapt this struct to your plugin.
typedef struct context_t {
    // For Ribbon Theta vault.
    uint8_t deposit_amount[INT256_LENGTH];
    char vaultName[MAX_VAULT_TICKER_LEN];
    uint8_t asset_token[ADDRESS_LENGTH];

    // Withdraw
    uint8_t withdraw_shares_amount[INT256_LENGTH];

    // For parsing data.
    uint8_t next_param;  // Set to be the next param we expect to parse.
    bool skip_remaining_params; // If true, don't process any other params

    // For both parsing and display.
    selector_t selectorIndex;
} context_t;

// Piece of code that will check that the above structure is not bigger than 5 * 32. Do not remove
// this check.
_Static_assert(sizeof(context_t) <= 5 * 32, "Structure of parameters too big.");

void handle_provide_parameter(void *parameters);
void handle_query_contract_ui(void *parameters);
void handle_init_contract(void *parameters);
void handle_finalize(void *parameters);
void handle_provide_token(void *parameters);
void handle_query_contract_id(void *parameters);