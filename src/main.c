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

#include "boilerplate_plugin.h"

// List of selectors supported by this plugin.
// EDIT THIS: Adapt the variable names and change the `0x` values to match your selectors.
static const uint32_t SWAP_EXACT_ETH_FOR_TOKENS_SELECTOR = 0x7ff36ab5;
// for vaults that calls depositETH()
static const uint32_t DEPOSIT_ETH_SELECTOR = 0xf6326fb3;
// for vaults that calls deposit()
static const uint32_t DEPOSIT_SELECTOR = 0xb6b55f25;

// Array of all the different boilerplate selectors. Make sure this follows the same order as the
// enum defined in `boilerplate_plugin.h`
// EDIT THIS: Use the names of the array declared above.
const uint32_t BOILERPLATE_SELECTORS[NUM_SELECTORS] = {SWAP_EXACT_ETH_FOR_TOKENS_SELECTOR,
                                                       DEPOSIT_SELECTOR,
                                                       DEPOSIT_ETH_SELECTOR};

const vault_address_ticker_t CONTRACT_ADDRESS_COLLECTION[NUM_VAULT_ADDRESS_COLLECTION] = {
    {{0xe6, 0x31, 0x51, 0xA0, 0xEd, 0x4e, 0x5f, 0xaf, 0xdc, 0x95,
      0x1D, 0x87, 0x71, 0x02, 0xcf, 0x09, 0x77, 0xAb, 0xd3, 0x65},
    "T-AAVE-C",
    {0x7F, 0xc6, 0x65, 0x00, 0xc8, 0x4A, 0x76, 0xAd, 0x7e, 0x9c,
      0x93, 0x43, 0x7b, 0xFc, 0x5A, 0xc3, 0x3E, 0x2D, 0xDa, 0xE9},
     "AAVE ",
     18},
    {{0x53, 0x77, 0x3E, 0x03, 0x4d, 0x97, 0x84, 0x15, 0x34, 0x71, 
      0x81, 0x3d, 0xac, 0xAF, 0xF5, 0x3d, 0xBB, 0xB7, 0x8E, 0x8c},
    "T-STETH-C",
    {0xae, 0x7a, 0xb9, 0x65, 0x20, 0xDE, 0x3A, 0x18, 0xE5, 0xe1,
      0x11, 0xB5, 0xEa, 0xAb, 0x09, 0x53, 0x12, 0xD7, 0xfE, 0x84},
     "STETH ",
     18},
    {{0xCc, 0x32, 0x35, 0x57, 0xc7, 0x1C, 0x0D, 0x1D, 0x20, 0xa1,
      0x86, 0x1D, 0xc6, 0x9c, 0x06, 0xC5, 0xf3, 0xcC, 0x96, 0x24},
    "T-yvUSDC-P-ETH",
    {0xA0, 0xb8, 0x69, 0x91, 0xc6, 0x21, 0x8b, 0x36, 0xc1, 0xd1,
      0x9D, 0x4a, 0x2e, 0x9E, 0xb0, 0xcE, 0x36, 0x06, 0xeB, 0x48},
     "USDC ",
     6},
    {{0xc0, 0xcF, 0x10, 0xDd, 0x71, 0x0a, 0xef, 0xb2, 0x09, 0xD9,
      0xdc, 0x67, 0xbc, 0x74, 0x65, 0x10, 0xff, 0xd9, 0x8A, 0x53},
    "T-APE-C",
    {0x4d, 0x22, 0x44, 0x52, 0x80, 0x1A, 0xCE, 0xd8, 0xB2, 0xF0,
      0xae, 0xbE, 0x15, 0x53, 0x79, 0xbb, 0x5D, 0x59, 0x43, 0x81},
     "AAPE ",
     18},
    {{0x65, 0xa8, 0x33, 0xaf, 0xDc, 0x25, 0x0D, 0x9d, 0x38, 0xf8,
      0xCD, 0x9b, 0xC2, 0xB1, 0xE3, 0x13, 0x2d, 0xB1, 0x3B, 0x2F},
    "T-WBTC-C",
    {0x22, 0x60, 0xFA, 0xC5, 0xE5, 0x54, 0x2a, 0x77, 0x3A, 0xa4,
      0x4f, 0xBC, 0xfe, 0xDf, 0x7C, 0x19, 0x3b, 0xc2, 0xC5, 0x99},
     "WBTC ",
     8}};

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
