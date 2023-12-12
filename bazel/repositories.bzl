load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

def antlr4_repo():
    http_archive(
        name = "antlr4_runtime",
        urls =["https://www.antlr.org/download/antlr4-cpp-runtime-4.13.0-source.zip"],
        sha256 = "2e5db62acdca9adc3329c485c3b9ce3029e40d13cc9c3e74ced354e818cb63e9",
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
