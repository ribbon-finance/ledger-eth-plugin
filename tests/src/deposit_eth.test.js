import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, nano_models, txFromEtherscan } from './test.fixture';

// Test from replayed transaction: https://etherscan.io/tx/0xcb580b1de5c62e6894380e065b98f04dbf64e026940cecc321a3fe36c9e6ce57
nano_models.forEach(function (model) {
  test('[Nano ' + model.letter + '] Deposit ETH into Call Theta Vault', zemu(model, async (sim, eth) => {
    // The rawTx of the tx up above is accessible through: https://etherscan.io/getRawTx?tx=0xcb580b1de5c62e6894380e065b98f04dbf64e026940cecc321a3fe36c9e6ce57
    const serializedTx = txFromEtherscan("0x02f878010f8459682f008509e84346cd830176d39425751853eab4d0eb3652b5eb6ecb102a2789644b880501c3e57e17c02a84f6326fb3c001a0ba9460fbda132d6d5522ea93bfd62de398b05b5d319cabb03ff4c5ac1f3f1eada05dbf83dbafdff4286509a0bdd85e6e386023c1f70100fcb385a10cab920f71ba");
    console.log({
      serializedTx
    })
    const tx = eth.signTransaction(
      "44'/60'/0'/0",
      serializedTx,
    );

    const right_clicks = model.letter === 'S' ? 7 : 5;

    // Wait for the application to actually load and parse the transaction
    await waitForAppScreen(sim);
    // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
    await sim.navigateAndCompareSnapshots('.', model.name + '_deposit_eth', [right_clicks, 0]);

    await tx;
  }));
});

