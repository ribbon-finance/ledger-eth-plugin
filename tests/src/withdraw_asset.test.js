import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, nano_models, txFromEtherscan } from './test.fixture';

const withdrawVaults = [
  {
    name: "T-AAVE-C",
    initiateWithdraw: {
      // https://etherscan.io/tx/0xe0bb7d4f056a2243c8e44efc03c379b2d4e3ba7e361bc8ae1e7d649f8f2fd134
      rawTx: "0x02f892018205ad8459682f0085064f492f008301c2ad94e63151a0ed4e5fafdc951d877102cf0977abd36580a47e108d52000000000000000000000000000000000000000000000014fb4b448488f63306c001a0da09ea38166f6d406c88c1b395ba71b3519ef8003a99c78ac460091cdb17b4d6a02f624bf04e7d7d5acb24a9badc8e68884a1e32fae8c67ff24d99dd64f3271de9",
      rightClicks: {
        S: 7,
        X: 3
      }
    },
    instantWithdraw: {
      // https://etherscan.io/tx/0xaffd234459e82589db8dd157262e6c60475696026496984272f4c2818eb299af
      rawTx: "0x02f890011784773594008513509bcf728303b4dd94e63151a0ed4e5fafdc951d877102cf0977abd36580a42775d01c00000000000000000000000000000000000000000000001130307758c8005adfc080a09ded7c8d42729992b19ea156889fcb039582a1ce5cea579afee746251220cafea024e23cec888240e36f037416a3536f8d54b9d988cf39721d02b3ca6e6a409783",
      rightClicks: {
        S: 6,
        X: 3
      }
    },
    completeWithdraw: {
      // https://etherscan.io/tx/0x26fe42c9fc93bf4315e688b5883adb13c8bfecb09962503d6fc610c0bd255be0
      rawTx: "0x02f87001178459682f00850da14e413f8303f86994e63151a0ed4e5fafdc951d877102cf0977abd3658084f756fa21c001a02cf54155a006ca9390c3f49c892162fb8a3d768e89859f280df8b963e640c9cfa04021175a4b44284612f025c066cc6ac779df564fe2484136472b0f732aa4adba",
      rightClicks: {
        S: 6,
        X: 3
      }
    }
  },
  {
    name: "T-WBTC-C",
    initiateWithdraw: {
      // https://etherscan.io/tx/0xf4efe31e1aa9b3a06bb45d3d2f892228c15c87507b9b95d8b461390f5d3b3333
      rawTx: "0x02f89001728459682f008504939402ab83017e8a9465a833afdc250d9d38f8cd9bc2b1e3132db13b2f80a47e108d52000000000000000000000000000000000000000000000000000000000007da15c080a0269a65e900438ba189232e458cf8fa95849a12dd5c401e230e9c0101cb12903ba0125d18d3606e9575561a7ecfb026a211d2a8518009ef106ce3932632d1c3ed18",
      rightClicks: {
        S: 8,
        X: 5
      }
    },
    completeWithdraw: {
      // https://etherscan.io/tx/0x1ca77b7daa263cbb2a80152ae1da9200e4f689d30d5f4d806a68e7ba06d64046
      rawTx: "0x02f870012d8459682f008504e3b292008301b1d59465a833afdc250d9d38f8cd9bc2b1e3132db13b2f8084f756fa21c080a08831c4cacee18f7fcfe67c3317f3eb7bd9ff7b2c0b73f62cf04847f0c5dae763a038d4340246ebeafa04356b150e97c02d37cc22a11ee6ecbb0ef666572805044a",
      rightClicks: {
        S: 4,
        X: 2
      }
    }
  },
  {
    name: "T-APE-C",
    initiateWithdraw: {
      // https://etherscan.io/tx/0xa019cbc1d7c6fb40f37b09e85cb657aea2f305c0339b17a237d38fbcb0fbb148
      rawTx: "0x02f8910181968459682f00850f27b42a628301c2ad94c0cf10dd710aefb209d9dc67bc746510ffd98a5380a47e108d520000000000000000000000000000000000000000000000355ae763a613a54d43c080a0317b875b3cc7c04d7d5dbb6c62d6dd10c89db646977176214cf75e1353e5285da020ef066b97bc4745f87803f8beef4804aaeaa4587e5ac78887ec47a335dde823",
      rightClicks: {
        S: 9,
        X: 5
      }
    },
    completeWithdraw: {
      // https://etherscan.io/tx/0xe09c94bb678ce13f811426ab3a90233f7d96bf7fb81d95dda45e75c3aedeb1e8
      rawTx: "0x02f8720182043f8459682f00851a4027db0f830162aa94c0cf10dd710aefb209d9dc67bc746510ffd98a538084f756fa21c001a0c9d6cbb90fe6d6124a153942d3f56b93ea070f7aae8f584f5b89f8618405dbe2a03fea2eef1408de31e950d3ae96d37b72e199edb28fad25db4818494f737735a3",
      rightClicks: {
        S: 6,
        X: 4
      }
    }
  },
  {
    name: "T-yvUSDC-P-ETH",
    initiateWithdraw: {
      // https://etherscan.io/tx/0xaf4fab7418c0feaad7d94dc50334d941a62b5a59627a291af2274dc58877bb66
      rawTx: "0xf88946850c92a69c008301c29494cc323557c71c0d1d20a1861dc69c06c5f3cc962480a47e108d5200000000000000000000000000000000000000000000000000000077033d4aad26a0b99c5984e2bb26a27db4e1c4e55d88f56e551077f064700fb3ceaeb21ab21821a057c8d3e4591e6fc6d7a5ad9fbffe026c9a22153747f0ab20f2b71d118aca6f6a",
      rightClicks: {
        S: 6,
        X: 3
      }
    },
    completeWithdraw: {
      // https://etherscan.io/tx/0xa5e2b07c1ff61f4a7642873fba09876ce6c3584a5c4126ba81f709add227ed0e
      rawTx: "0x02f872018202de8459682f00851174aaeacb83026d2d94cc323557c71c0d1d20a1861dc69c06c5f3cc96248084f756fa21c001a0ffe31698a880bf99489515c1ec5df88dc7405c62776a236fc946d16a5b01809ba0129e8f7d94e080dacfe684fa03422653f2fd2caf9eead0bb787de7f6dc1e567e",
      rightClicks: {
        S: 6,
        X: 4
      }
    }
  },
  {
    name: "T-ETH-C",
    initiateWithdraw: {
      // https://etherscan.io/tx/0x826a86a286b984840f077863db5b204acec37faa22c35b87a2469f921a61fc5b
      rawTx: "0x02f89001178459682f008508255cef948301c2a19425751853eab4d0eb3652b5eb6ecb102a2789644b80a47e108d52000000000000000000000000000000000000000000000000069e9b658a7aa86ec001a0df453708cf585a8e6659eaeb6c09af2149db78da91e1633fd15afbbf0f4ecd30a0685e202835fdede2dd7f94820ab7f1108bb6e8d92eb8061bb6f7f45a2eb40614",
      rightClicks: {
        S: 9,
        X: 5
      }
    },
    completeWithdraw: {
      // https://etherscan.io/tx/0xd240b3ea6883e7e35b479043b69b49f3440cfc25a78e649af990b8fe86d7cb3f
      rawTx: "0x02f870013e8459682f0085083f0cfee183017daf9425751853eab4d0eb3652b5eb6ecb102a2789644b8084f756fa21c001a0fe0281bee978164facc5662eb422848777ba5db179c9ace51f77ec24bc498c8da04ef395cb2ac0159e445821d9ccf80dfccae1ce366cd8c6a769225305f217f965",
      rightClicks: {
        S: 6,
        X: 2
      }
    }
  },
  {
    name: "T-STETH-C",
    initiateWithdraw: {
      // https://etherscan.io/tx/0x2fb944af8dd7d30c01585f9f5b99df5591d007249dd8fc1a14af648532226864
      rawTx: "0x02f8910181c58459682f00850cc07d75368301c28b9453773e034d9784153471813dacaff53dbbb78e8c80a47e108d5200000000000000000000000000000000000000000000000001d343de4169a421c080a09e9ccb59ee46b299cfbdcc8bd592b47600fc09b9beab31f62aa414594c17e14da034d16d6362cb0a2a5436de5bdb4fc147dd7fb1cc2dd9a12f4cd4c12bc1e8261a",
      rightClicks: {
        S: 8,
        X: 5
      }
    },
    completeWithdraw: {
      // https://etherscan.io/tx/0x4ed59c74231358dac2fc2cf05aeb47122d6ae4241e371602e3531c2da1c29311
      rawTx: "0x02f8700102843dec1da08509a9b9d8fd83061a809453773e034d9784153471813dacaff53dbbb78e8c8084f756fa21c001a0334580f84e69e041df24d9000293fa7a4503ec01bb01f22301ecc40cad99ef7ea00a97e7a78cd123e68c489b193f837bb4932f0714db7e9450e5a59e88d37e6519",
      rightClicks: {
        S: 4,
        X: 4
      }
    }
  },
]

// ONLY TEST FOR NANOS FOR NOW
const models = [nano_models[0]]

for (let index = 0; index < models.length; index++) {
  const model = models[index];
  for (let i = 0; i < withdrawVaults.length; i++) {
    const {
      name,
      initiateWithdraw,
      instantWithdraw,
      completeWithdraw,
    } = withdrawVaults[i];

    // INSTANT WITHDRAWAL
    if (instantWithdraw) {
      test('[Nano ' + model.letter + '] Instant Withdraw ' + name, zemu(model, async (sim, eth) => {
        const serializedTx = txFromEtherscan(instantWithdraw.rawTx);
        const tx = eth.signTransaction(
          "44'/60'/0'/0",
          serializedTx,
        );

        const right_clicks = instantWithdraw.rightClicks[model.letter];

        // Wait for the application to actually load and parse the transaction
        await waitForAppScreen(sim);
        // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
        await sim.navigateAndCompareSnapshots('.', model.name + '_' + name + "_instant_withdraw", [right_clicks, 0]);

        await tx;
      }));
    }

    // INITIATE WITHDRAWAL
    test('[Nano ' + model.letter + '] Initiate Withdraw ' + name, zemu(model, async (sim, eth) => {
      const serializedTx = txFromEtherscan(initiateWithdraw.rawTx);
      const tx = eth.signTransaction(
        "44'/60'/0'/0",
        serializedTx,
      );

      const right_clicks = initiateWithdraw.rightClicks[model.letter];

      // Wait for the application to actually load and parse the transaction
      await waitForAppScreen(sim);
      // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
      await sim.navigateAndCompareSnapshots('.', model.name + '_' + name + "_initiate_withdraw", [right_clicks, 0]);

      await tx;
    }));

    // COMPLETE WITHDRAWAL
    const completeWithdrawTitle = "Complete Withdraw"
    const completeWithdrawSnapshot = "_complete_withdraw"

    test('[Nano ' + model.letter + '] ' + completeWithdrawTitle + ' ' + name, zemu(model, async (sim, eth) => {
      const serializedTx = txFromEtherscan(completeWithdraw.rawTx);
      const tx = eth.signTransaction(
        "44'/60'/0'/0",
        serializedTx,
      );

      const right_clicks = completeWithdraw.rightClicks[model.letter];

      // Wait for the application to actually load and parse the transaction
      await waitForAppScreen(sim);
      // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
      await sim.navigateAndCompareSnapshots('.', model.name + '_' + name + completeWithdrawSnapshot, [right_clicks, 0]);

      await tx;
    }));
  }
}

