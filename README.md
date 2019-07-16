#C IOTA workshop

**The CClient library used in this workshop is currently not designed to run on a microcontroller.
It runs on the ESP32 though. Take a look into [this blog article](https://blog.iota.org/running-the-iota-cclient-library-on-esp32-4a1a5191afad)
for more information.**

Some simple examples to get you started on developing with IOTA using C.

##Getting started

1. [Install bazel](https://docs.bazel.build/versions/master/install.html)
2. Run one example

###How to run an example

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

##Configuration

**DO NOT USE THE EXAMPLE SEEDS FOR PRODUCTION ENVIRONMENT!**

The configuration is available in iota_client_service/config.h
If you want to change the used seed or address, you need to change it
in every example. Each example uses different addresses and seeds.


##Contribution

PRs are welcome on master