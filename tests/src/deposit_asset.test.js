import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, genericTx, nano_models, SPECULOS_ADDRESS, txFromEtherscan } from './test.fixture';
import { ethers } from "ethers";
import { formatUnits, parseEther, parseUnits } from "ethers/lib/utils";


const contractAddr = "0xe63151a0ed4e5fafdc951d877102cf0977abd365";
const pluginName = "boilerplate";
const abi_path = `../${pluginName}/abis/` + contractAddr + '.json';
const abi = require(abi_path);

// This test is the default uniswap contract test.
// Test from replayed transaction: https://etherscan.io/tx/0x0160b3aec12fd08e6be0040616c7c38248efb4413168a3372fc4d2db0e5961bb
nano_models.forEach(function (model) {
  // test('[Nano ' + model.letter + '] Swap Exact Eth For Tokens with beneficiary', zemu(model, async (sim, eth) => {

  // // The rawTx of the tx up above is accessible through: https://etherscan.io/getRawTx?tx=0xb27a69cd3190ad0712da39f6b809ecc019ecbc319d3c17169853270226d18a8a
  // const serializedTx = txFromEtherscan("0x02f9015a0181d38459682f0085215d7c1e598302a4e9947a250d5630b4cf539739df2c5dacb4c659f2488d88016345785d8a0000b8e47ff36ab50000000000000000000000000000000000000000000000018b1dd9dc51b5a9f7000000000000000000000000000000000000000000000000000000000000008000000000000000000000000015557c8b7246c38ee71ea6dc69e4347f5dac210400000000000000000000000000000000000000000000000000000000615336100000000000000000000000000000000000000000000000000000000000000002000000000000000000000000c02aaa39b223fe8d0a0e5c4f27ead9083c756cc20000000000000000000000006b3595068778dd592e39a122f4f5a5cf09c90fe2c001a089c5ce4ce199f7d93ea1d54c08133fab9407d8de63a9885d59d8ce69a59573dda045f6a0e0d3288dfdfddc23ad0afb9577c4011801f598d581a46cd0b0e2bd0571");

  // const tx = eth.signTransaction(
  //   "44'/60'/0'/0",
  //   serializedTx,
  // );

  // const right_clicks = model.letter === 'S' ? 12 : 6;

  // // Wait for the application to actually load and parse the transaction
  // await waitForAppScreen(sim);
  // // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
  // await sim.navigateAndCompareSnapshots('.', model.name + '_swap_exact_eth_for_tokens_with_beneficiary', [right_clicks, 0]);

  // await tx;
  // }));
});

// Test from constructed transaction
// EDIT THIS: build your own test
nano_models.forEach(function (model) {
  // test('[Nano ' + model.letter + '] Swap Exact Eth For Tokens', zemu(model, async (sim, eth) => {
  //   const contract = new ethers.Contract(contractAddr, abi);

  //   // Constants used to create the transaction
  //   // EDIT THIS: Remove what you don't need
  //   const amountOutMin = parseUnits("28471151959593036279", 'wei');
  //   const WETH = "0xc02aaa39b223fe8d0a0e5c4f27ead9083c756cc2";
  //   const SUSHI = "0x6b3595068778dd592e39a122f4f5a5cf09c90fe2";
  //   const path = [WETH, SUSHI];
  //   const deadline = Number(1632843280);
  //   // We set beneficiary to the default address of the emulator, so it maches sender address
  //   const beneficiary = SPECULOS_ADDRESS;

  //   // EDIT THIS: adapt the signature to your method
  //   // signature: swapExactETHForTokens(uint amountOutMin, address[] calldata path, address to, uint deadline)
  //   // EDIT THIS: don't call `swapExactETHForTokens` but your own method and adapt the arguments.
  //   const { data } = await contract.populateTransaction.swapExactETHForTokens(amountOutMin, path, beneficiary, deadline);

  //   // Get the generic transaction template
  //   let unsignedTx = genericTx;
  //   // Modify `to` to make it interact with the contract
  //   unsignedTx.to = contractAddr;
  //   // Modify the attached data
  //   unsignedTx.data = data;
  //   // EDIT THIS: get rid of this if you don't wish to modify the `value` field.
  //   // Modify the number of ETH sent
  //   unsignedTx.value = parseEther("0.1");

  //   // Create serializedTx and remove the "0x" prefix
  //   const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);

  //   const tx = eth.signTransaction(
  //     "44'/60'/0'/0",
  //     serializedTx
  //   );

  //   const right_clicks = model.letter === 'S' ? 7 : 5;

  //   // Wait for the application to actually load and parse the transaction
  //   await waitForAppScreen(sim);
  //   // Navigate the display by pressing the right button 10 times, then pressing both buttons to accept the transaction.
  //   // EDIT THIS: modify `10` to fix the number of screens you are expecting to navigate through.
  //   await sim.navigateAndCompareSnapshots('.', model.name + '_swap_exact_eth_for_tokens', [right_clicks, 0]);

  //   await tx;
  // }));

  // test('[Nano ' + model.letter + '] Deposit AAVE into Theta Vault', zemu(model, async (sim, eth) => {
  //   const contract = new ethers.Contract(contractAddr, abi);

  //   // Constants used to create the transaction
  //   const aaveAmount = parseUnits("64", 18);

  //   const { data } = await contract.populateTransaction.deposit(aaveAmount);

  //   // Get the generic transaction template
  //   let unsignedTx = genericTx;
  //   // Modify `to` to make it interact with the contract
  //   unsignedTx.to = contractAddr;
  //   // Modify the attached data
  //   unsignedTx.data = data;

  //   // Create serializedTx and remove the "0x" prefix
  //   const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);

  //   const tx = eth.signTransaction(
  //     "44'/60'/0'/0",
  //     serializedTx
  //   );

  //   const right_clicks = model.letter === 'S' ? 7 : 5;

  //   // Wait for the application to actually load and parse the transaction
  //   await waitForAppScreen(sim);
  //   // Navigate the display by pressing the right button 10 times, then pressing both buttons to accept the transaction.
  //   // EDIT THIS: modify `10` to fix the number of screens you are expecting to navigate through.
  //   await sim.navigateAndCompareSnapshots('.', model.name + '_deposit', [right_clicks, 0]);

  //   await tx;
  // }));
});

// ONLY test for nano s
const model = nano_models[0];
const depositVaults = [
  {
    name: "T-AAVE-C",
    // https://etherscan.io/tx/0xc72cb565ec57db33a2bc689319c0872738c37cce5c92c3d71e7b776f13bf5987
    rawTx: "0x02f892018201c58459682f00850a22bc93d18303b62394e63151a0ed4e5fafdc951d877102cf0977abd36580a4b6b55f250000000000000000000000000000000000000000000000038252536bd64eebebc001a0096fe1ddb48a9e927cada2c03b9df35b6012f3fbff951025e44b5ac3ad5d77f1a04dcd0366fe2a03b52f180123a568bd2c48036875f90565094aad4995fe36efd1"
  },
  {
    name: "T-WBTC-C",
    // https://etherscan.io/tx/0xad4cc5484bdd68256ff7a987b85678886f0108a2fbe4f1f96f7b8786fd7c9213
    rawTx: "0x02f89001338459682f0085062e1ee4f483015c439465a833afdc250d9d38f8cd9bc2b1e3132db13b2f80a4b6b55f250000000000000000000000000000000000000000000000000000000000121731c001a0e4a295c678f181da338d48ae336a6e5d356524e61c95eb45021f17667c6ca7eaa07784b458b417f85a6326b803fb6af784b5d2f7ced9fa917dc5b2e80b022f5bb0"
  },
  {
    name: "T-APE-C",
    // https://etherscan.io/tx/0x12ebfdfbb543054a4d9b93d73de3e8e3bcc772a879b510f29a8e080c5607093b
    rawTx: "0x02f89001148459682f0085078c10e012830197b394c0cf10dd710aefb209d9dc67bc746510ffd98a5380a4b6b55f250000000000000000000000000000000000000000000004ee5d807432da1bd2e9c080a0017799d2d1e9680f532ccd0257e2ca54d1e020d6c84a9b27da7ce3b54b3c2d89a03d51ae1426f0b81ccead49fb47b498dfd8617339b3d3139e1c04545bdfde015b"
  },
  {
    name: "T-yvUSDC-P-ETH",
    // https://etherscan.io/tx/0x0c557ee26b4777a2c3c5e33863ca8fff16066976e15e10cbd6d1b04b2e971f3c
    rawTx: "0x02f89001318459682f008506fc23ac0083026b3e94cc323557c71c0d1d20a1861dc69c06c5f3cc962480a4b6b55f25000000000000000000000000000000000000000000000000000000174876e800c080a08931d39ce67a37f80a97b061b455c7a646defc2ba15bbfe8df56fe1f843c4445a034516babda81686b716b2efb9a783a7bea7ac34ccebdbbcd673658b09b33e0cf"
  },
]

for (let i = 0; i < depositVaults.length; i++) {
  const { name, rawTx } = depositVaults[i];
  test('[Nano ' + model.letter + '] Deposit ' + name, zemu(model, async (sim, eth) => {
    const serializedTx = txFromEtherscan(rawTx);
    const tx = eth.signTransaction(
      "44'/60'/0'/0",
      serializedTx,
    );

    const right_clicks = model.letter === 'S' ? 9 : 5;

    // Wait for the application to actually load and parse the transaction
    await waitForAppScreen(sim);
    // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
    await sim.navigateAndCompareSnapshots('.', model.name + '_' + name + "_deposit", [right_clicks, 0]);

    await tx;
  }));
}

const depositETHVaults = [
  {
    name: "T-ETH-C",
    // https://etherscan.io/tx/0x5a7be6a721aded0f6bc4166a1fc4d743db5a3707abe04b8386312c40fba0a68f
    rawTx: "0x02f878010f8459682f008504356baebe830176d39425751853eab4d0eb3652b5eb6ecb102a2789644b881c4a8e71ff8941f184f6326fb3c080a0e4fbc53114cd2af57274686e2b4c212f1b2509b8a0d03c93a83ca962ecdc7412a00857072724e4fd09fb09c0b2275e6d13d32e444963f335b75f290c81d880e9fb"
  },
  {
    name: "T-STETH-C",
    // https://etherscan.io/tx/0xe93291af30fdfcd5ef846d05cfd1277229e796c17bd1502dde5ecf0d923e24a1
    rawTx: "0x02f87901028459682f008507b2caa39d830219f79453773e034d9784153471813dacaff53dbbb78e8c8901a055690d9db8000084f6326fb3c001a018053f82f5e38a41008a6f77cb9264be5c36b541666ee784211d835530aac50ba07656431291a386495f6698decce9589c5cff33e988a60a6ff61b27d448f66b02"
  },
]

for (let i = 0; i < depositETHVaults.length; i++) {
  const { name, rawTx } = depositETHVaults[i];
  test('[Nano ' + model.letter + '] DepositETH ' + name, zemu(model, async (sim, eth) => {
    const serializedTx = txFromEtherscan(rawTx);
    const tx = eth.signTransaction(
      "44'/60'/0'/0",
      serializedTx,
    );

    const right_clicks = model.letter === 'S' ? 9 : 5;

    // Wait for the application to actually load and parse the transaction
    await waitForAppScreen(sim);
    // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
    await sim.navigateAndCompareSnapshots('.', model.name + '_' + name + "_depositETH", [right_clicks, 0]);

    await tx;
  }));
}