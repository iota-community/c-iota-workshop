package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "hello_world",
    srcs = ["e01_hello_world.c", "config.h"],
    copts = ["-DLOGGER_ENABLE"],
    linkopts = ["-pthread"],
    deps = [
        "@cclient//cclient/api",
    ],
)

cc_binary(
    name = "send_hello",
    srcs = ["e02_send_hello.c", "config.h"],
    copts = ["-DLOGGER_ENABLE"],
    linkopts = ["-pthread", "-lm"],
    deps = [
        "@cclient//cclient/api",
    ],
)

cc_binary(
    name = "receive_hello",
    srcs = ["e03_receive_hello.c", "config.h"],
    copts = ["-DLOGGER_ENABLE"],
    linkopts = ["-pthread"],
    deps = [
        "@cclient//cclient/api",
    ],
)

cc_binary(
    name = "generate_address",
    srcs = ["e04_generate_address.c", "config.h"],
    copts = ["-DLOGGER_ENABLE"],
    linkopts = ["-pthread"],
    deps = [
        "@cclient//cclient/api",
    ],
)

cc_binary(
    name = "check_balances",
    srcs = ["e05_check_balance.c", "config.h"],
    copts = ["-DLOGGER_ENABLE"],
    linkopts = ["-pthread"],
    deps = [
        "@cclient//cclient/api",
    ],
)

cc_binary(
    name = "send_tokens",
    srcs = ["e06_send_tokens.c", "config.h"],
    copts = ["-DLOGGER_ENABLE"],
    linkopts = ["-pthread", "-lm"],
    deps = [
        "@cclient//cclient/api",
    ],
)
