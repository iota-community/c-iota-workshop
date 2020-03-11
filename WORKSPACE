load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")

git_repository(
    name = "cclient",
    commit = "ae5a638f04f68f3580eea98bfce09f9fb745cbeb",
    remote = "https://github.com/iotaledger/iota.c.git",
)

git_repository(
    name = "org_iota_common",
    commit = "82818daf1ffa31b0f8a247ec51eee5cf68cb79ab",
    remote = "https://github.com/iotaledger/iota_common.git",
)

git_repository(
    name = "rules_iota",
    commit = "4fd742195c31b9e2bf859a68cd5de4b2fdba7086",
    remote = "https://github.com/iotaledger/rules_iota.git",
)

load("@rules_iota//:defs.bzl", "iota_deps")
iota_deps()
