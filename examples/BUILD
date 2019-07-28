package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "hello_world",
    srcs = ["e01_hello_world.c"],
    copts = ["-DLOGGER_ENABLE"],
    linkopts = ["-pthread"],
    deps = [
        "//iota_client_service:config",
        "//iota_client_service:service",
        "@entangled//cclient/api",
    ],
)

cc_binary(
    name = "send_hello",
    srcs = ["e02_send_hello.c"],
    copts = ["-DLOGGER_ENABLE"],
    linkopts = ["-pthread", "-lm"],
    deps = [
        "//iota_client_service:config",
        "//iota_client_service:service",
        "@entangled//cclient/api",
        "@entangled//common/trinary:tryte_ascii",
    ],
)

cc_binary(
    name = "receive_hello",
    srcs = ["e03_receive_hello.c"],
    copts = ["-DLOGGER_ENABLE"],
    linkopts = ["-pthread"],
    deps = [
        "//iota_client_service:config",
        "//iota_client_service:service",
        "@entangled//cclient/api",
        "@entangled//common/trinary:tryte_ascii",
    ],
)

cc_binary(
    name = "generate_address",
    srcs = ["e04_generate_address.c"],
    copts = ["-DLOGGER_ENABLE"],
    linkopts = ["-pthread"],
    deps = [
        "//iota_client_service:config",
        "//iota_client_service:service",
        "@entangled//cclient/api",
        "@entangled//common/trinary:tryte_ascii",
    ],
)

cc_binary(
    name = "check_balances",
    srcs = ["e05_check_balance.c"],
    copts = ["-DLOGGER_ENABLE"],
    linkopts = ["-pthread"],
    deps = [
        "//iota_client_service:config",
        "//iota_client_service:service",
        "@entangled//cclient/api",
        "@entangled//common/trinary:tryte_ascii",
    ],
)

cc_binary(
    name = "send_tokens",
    srcs = ["e06_send_tokens.c"],
    copts = ["-DLOGGER_ENABLE"],
    linkopts = ["-pthread", "-lm"],
    deps = [
        "//iota_client_service:config",
        "//iota_client_service:service",
        "@entangled//cclient/api",
        "@entangled//common/trinary:tryte_ascii",
    ],
)
