package(default_visibility = ["//visibility:public"])

cc_library(
    name = "config",
    hdrs = [
        "config.h",
    ],
    deps = [
        "@entangled//cclient/api",
    ],
)

cc_library(
    name = "service",
    srcs = [
        "client_service.c",
    ],
    hdrs = [
        "client_service.h",
    ],
    deps = [
        ":config",
        "@entangled//cclient/api",
    ],
)
