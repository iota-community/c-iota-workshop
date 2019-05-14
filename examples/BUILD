package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "hello_world",
    srcs = ["e01_hello_world.c"],
    deps = [
        "@entangled//cclient/api",
    ],
    copts = ["-DLOGGER_ENABLE"],
    linkopts = ["-pthread"],
)

cc_binary(
    name = "send_hello",
    srcs = ["e02_send_hello.c"],
    deps = [
        "@entangled//cclient/api",
        "@entangled//common/trinary:tryte_ascii"
    ],
    copts = ["-DLOGGER_ENABLE"],
    linkopts = ["-pthread"],
)