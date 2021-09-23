# C IOTA workshop

Some simple examples to get you started on developing with IOTA 1.5(Chrysalis) using C.

[Chrysalis Documentation](https://chrysalis.docs.iota.org/)
[IOTA C library documentation](https://iota-c-client.readthedocs.io/en/latest/index.html)

## Getting started

1. [Install CMake](https://cmake.org/install/)
2. Run one example

### building examples

```
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=$PWD -DCryptoUse=mbedtls -DIOTA_TESTS=OFF -DIOTA_EXAMPLES=OFF ..
make -j8
```

### How to run an example

The example code is available in the ``example/`` folder.

The executable binary is in the `build` folder.

```
./build/e01_hello_world
```

Following examples are available:

* e01_hello_world
* e02_send_fetch_hello
* e03_fetch_message

## Configuration

**DO NOT USE THE EXAMPLE SEEDS FOR PRODUCTION ENVIRONMENT!**

The configuration is available in iota_client_service/config.h
If you want to change the used seed or address, you need to change it
in every example. Each example uses different addresses and seeds.


## Contribution

PRs are welcome on master