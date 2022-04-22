/*******************************************************************************
 *   Ethereum 2 Deposit Application
 *   (c) 2020 Ledger
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "os.h"
#include "cx.h"

#include "ribbon_plugin.h"

// for vaults that calls depositETH()
static const uint32_t DEPOSIT_ETH_SELECTOR = 0xf6326fb3;
// for vaults that calls deposit()
static const uint32_t DEPOSIT_SELECTOR = 0xb6b55f25;
// for vaults that calls depositYieldToken()
static const uint32_t DEPOSIT_YIELD_TOKEN_SELECTOR = 0x31807e42;

// withdrawals
static const uint32_t INITIATE_WITHDRAWAL_SELECTOR = 0x7e108d52;
static const uint32_t COMPLETE_WITHDRAWAL_SELECTOR = 0xf756fa21;
static const uint32_t COMPLETE_WITHDRAWAL_MIN_ETH_OUT_SELECTOR = 0x2087ed5c;

// Array of all the different boilerplate selectors. Make sure this follows the same order as the
// enum defined in `boilerplate_plugin.h`
// EDIT THIS: Use the names of the array declared above.
const uint32_t RIBBON_SELECTORS[NUM_SELECTORS] = {DEPOSIT_SELECTOR,
                                                  DEPOSIT_ETH_SELECTOR,
                                                  DEPOSIT_YIELD_TOKEN_SELECTOR,
                                                  INITIATE_WITHDRAWAL_SELECTOR,
                                                  COMPLETE_WITHDRAWAL_SELECTOR,
                                                  COMPLETE_WITHDRAWAL_MIN_ETH_OUT_SELECTOR};

const vault_address_ticker_t CONTRACT_ADDRESS_COLLECTION[NUM_VAULT_ADDRESS_COLLECTION] = {
    {{0xe6, 0x31, 0x51, 0xa0, 0xed, 0x4e, 0x5f, 0xaf, 0xdc, 0x95,
      0x1d, 0x87, 0x71, 0x02, 0xcf, 0x09, 0x77, 0xab, 0xd3, 0x65},
     "T-AAVE-C",
     "AAVE ",
     18,
     "rAAVE-THETA "},
    {{0x25, 0x75, 0x18, 0x53, 0xea, 0xb4, 0xd0, 0xeb, 0x36, 0x52,
      0xb5, 0xeb, 0x6e, 0xcb, 0x10, 0x2a, 0x27, 0x89, 0x64, 0x4b},
     "T-ETH-C",
     "ETH ",
     18,
     "rETH-THETA "},
    {{0x53, 0x77, 0x3e, 0x03, 0x4d, 0x97, 0x84, 0x15, 0x34, 0x71,
      0x81, 0x3d, 0xac, 0xaf, 0xf5, 0x3d, 0xbb, 0xb7, 0x8e, 0x8c},
     "T-STETH-C",
     "STETH ",
     18,
     "rstETH-THETA "},
    {{0xcc, 0x32, 0x35, 0x57, 0xc7, 0x1c, 0x0d, 0x1d, 0x20, 0xa1,
      0x86, 0x1d, 0xc6, 0x9c, 0x06, 0xc5, 0xf3, 0xcc, 0x96, 0x24},
     "T-yvUSDC-P-ETH",
     "USDC ",
     6,
     //  When the ticker is longer than this, make sure to change MAX_VAULT_TICKER_LEN
     "ryvUSDC-ETH-P-THETA "},
    {{0xc0, 0xcf, 0x10, 0xdd, 0x71, 0x0a, 0xef, 0xb2, 0x09, 0xd9,
      0xdc, 0x67, 0xbc, 0x74, 0x65, 0x10, 0xff, 0xd9, 0x8a, 0x53},
     "T-APE-C",
     "APE ",
     18,
     "rAPE-THETA "},
    {{0x65, 0xa8, 0x33, 0xaf, 0xdc, 0x25, 0x0d, 0x9d, 0x38, 0xf8,
      0xcd, 0x9b, 0xc2, 0xb1, 0xe3, 0x13, 0x2d, 0xb1, 0x3b, 0x2f},
     "T-WBTC-C",
     "WBTC ",
     8,
     "rBTC-THETA "}};

// Function to dispatch calls from the ethereum app.
void dispatch_plugin_calls(int message, void *parameters) {
    switch (message) {
        case ETH_PLUGIN_INIT_CONTRACT:
            handle_init_contract(parameters);
            break;
        case ETH_PLUGIN_PROVIDE_PARAMETER:
            handle_provide_parameter(parameters);
            break;
        case ETH_PLUGIN_FINALIZE:
            handle_finalize(parameters);
            break;
        case ETH_PLUGIN_PROVIDE_INFO:
            handle_provide_token(parameters);
            break;
        case ETH_PLUGIN_QUERY_CONTRACT_ID:
            handle_query_contract_id(parameters);
            break;
        case ETH_PLUGIN_QUERY_CONTRACT_UI:
            handle_query_contract_ui(parameters);
            break;
        default:
            PRINTF("Unhandled message %d\n", message);
            break;
    }
}

// Calls the ethereum app.
void call_app_ethereum() {
    unsigned int libcall_params[3];
    libcall_params[0] = (unsigned int) "Ethereum";
    libcall_params[1] = 0x100;
    libcall_params[2] = RUN_APPLICATION;
    os_lib_call((unsigned int *) &libcall_params);
}

// Weird low-level black magic. No need to edit this.
__attribute__((section(".boot"))) int main(int arg0) {
    // Exit critical section
    __asm volatile("cpsie i");

    // Ensure exception will work as planned
    os_boot();

    // Try catch block. Please read the docs for more information on how to use those!
    BEGIN_TRY {
        TRY {
            // Low-level black magic.
            check_api_level(CX_COMPAT_APILEVEL);

            // Check if we are called from the dashboard.
            if (!arg0) {
                // Called from dashboard, launch Ethereum app
                call_app_ethereum();
                return 0;
            } else {
                // Not called from dashboard: called from the ethereum app!
                const unsigned int *args = (const unsigned int *) arg0;

                // If `ETH_PLUGIN_CHECK_PRESENCE` is set, this means the caller is just trying to
                // know whether this app exists or not. We can skip `dispatch_plugin_calls`.
                if (args[0] != ETH_PLUGIN_CHECK_PRESENCE) {
                    dispatch_plugin_calls(args[0], (void *) args[1]);
                }

                // Call `os_lib_end`, go back to the ethereum app.
                os_lib_end();
            }
        }
        FINALLY {
        }
    }
    END_TRY;

    // Will not get reached.
    return 0;
}
