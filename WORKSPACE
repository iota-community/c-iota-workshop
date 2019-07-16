load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")

git_repository(
    name = "entangled",
    commit = "3fb1892f4941735ff7a51fb9d8fc3f10f289f90f",
    remote = "https://github.com/iotaledger/entangled.git",
)

git_repository(
    name = "rules_iota",
    commit = "1cb59eea62fd1d071de213a9aa46e61e8273472d",
    remote = "https://github.com/iotaledger/rules_iota.git",
)

load("@rules_iota//:defs.bzl", "iota_deps")
iota_deps()
