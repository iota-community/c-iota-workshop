# C IOTA workshop

Some simple examples to get you started on developing with IOTA 1.5(Chrysalis) using C.

[Chrysalis Documentation](https://chrysalis.docs.iota.org/)
[IOTA C library documentation](https://iota-c-client.readthedocs.io/en/latest/index.html)

**DO NOT USE THE EXAMPLE SEEDS FOR PRODUCTION ENVIRONMENT!**

## Getting started

1. [Install CMake](https://cmake.org/install/)
2. Run one example

### Building examples

Project configuration

```
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=$PWD -DCryptoUse=mbedtls -DIOTA_TESTS=OFF -DIOTA_EXAMPLES=OFF ..
```

The example code is available in the ``example/`` folder, executable binaries are in the `build` folder.

```
make -j8
./build/e01_hello_world
```

Following examples are available:

* e01_hello_world
* e02_send_fetch_hello
* e03_fetch_message
* e04_generate_address **TODO**
* e05_check_balance **TODO**
* e06_send_tokens **TODO**


## Working with Visual Studio Code

This project has integrated with [Visual Studio Code IDE](https://code.visualstudio.com/), you can compile, debug, and run example through the IDE.

The configuration, `cmake.configureArgs`, is located in `.vscode/settings.json`

Please refer to [Get started with CMake Tools on Linux](https://code.visualstudio.com/docs/cpp/cmake-linux) for more details.

## Contribution

PRs are welcome on master