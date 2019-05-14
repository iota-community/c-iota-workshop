load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")

git_repository(
    name = "entangled",
    commit = "652d9f672fac64171490fcae73c9fcab4def11a6",
    remote = "https://github.com/iotaledger/entangled.git",
)

git_repository(
    name = "rules_iota",
    commit = "1cb59eea62fd1d071de213a9aa46e61e8273472d",
    remote = "https://github.com/iotaledger/rules_iota.git",
)

load("@rules_iota//:defs.bzl", "iota_deps")
iota_deps()