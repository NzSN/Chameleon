load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")


def antlr4_repo():
    http_archive(
        name = "antlr4_runtime",
        urls =["https://www.antlr.org/download/antlr4-cpp-runtime-4.13.1-source.zip"],
        build_file = "@//:bazel/external_builds/BUILD.antlr4_rumtime")

def rapidcheck_repo():
    new_git_repository(
        name = "rapidcheck",
        remote = "https://github.com/emil-e/rapidcheck.git",
        branch = "master",
        build_file = "@//:bazel/external_builds/BUILD.rapidcheck")

def plog_repo():
    new_git_repository(
        name = "plog",
        remote = "https://github.com/SergiusTheBest/plog.git",
        branch = "master",
        build_file = "@//:bazel/external_builds/BUILD.plog")

def tree_sitter_repo():
    new_git_repository(
        name = "tree_sitter",
        remote = "https://github.com/tree-sitter/tree-sitter.git",
        branch = "master",
        build_file = "@//:bazel/external_builds/BUILD.tree-sitter")

def oilpan_repo():
    git_repository(
        name = "oilpan",
        remote = "https://github.com/oilpan-gc/cppgc.git",
        branch = "main")
