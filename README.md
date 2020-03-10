# C IOTA workshop

**The CClient library used in this workshop is currently not designed to run on a microcontroller.
It runs on the ESP32 though. Take a look into [this blog article](https://blog.iota.org/running-the-iota-cclient-library-on-esp32-4a1a5191afad)
for more information.**

Some simple examples to get you started on developing with IOTA using C.

## Instructions
To build and run these examples you can use either CMake or Bazel.

### CMake

1. Clone this repository

```bash
git clone https://github.com/iota-community/c-iota-workshop.git
cd c-iota-workshop
```
    
2. Create a `build` directory in which to save the compiled library

```bash
mkdir build && cd build
```
    
3. Set the path in which to save the `lib` directory
    
```bash
cmake -DCMAKE_INSTALL_PREFIX=$PWD ..
```
    
4. Compile the code

```bash
make -j8
```

5. Execute the examples

```bash
./examples/iota_c_hello_world
./examples/iota_c_send_hello
./examples/iota_c_receive_hello
./examples/iota_c_generate_address
./examples/iota_c_check_balance
./examples/iota_c_send_tokens
```

### Bazel

1. [Install bazel](https://docs.bazel.build/versions/master/install.html)
2. Run one example

#### How to run an example

The example code is available in the ``example/`` folder.

You have to run the examples within bazel. Execute the following pattern in the root folder.
 
```bash
bazel run -c opt examples:[EXAMPLE_NAME]
```

Following examples are available:

```bash
hello_world
send_hello
receive_hello
generate_address
check_balances
send_tokens
```

You can run the hello_world example with this command
```bash
bazel run -c opt examples:hello_world
```

## Configuration

**DO NOT USE THE EXAMPLE SEEDS FOR PRODUCTION ENVIRONMENT!**

The configuration is available in iota_client_service/config.h
If you want to change the used seed or address, you need to change it
in every example. Each example uses different addresses and seeds.


## Contribution

PRs are welcome on master
