load("//:bazel/repositories.bzl", "antlr4_repo")
load("//:bazel/repositories.bzl", "rapidcheck_repo")
load("//:bazel/repositories.bzl", "plog_repo")
load("//:bazel/repositories.bzl", "tree_sitter_repo")

# Antlr4
def _antlr4_dep_impl(_ctx):
    antlr4_repo()

antlr4_dep = module_extension(
    implementation = _antlr4_dep_impl,)

# RapidCheck
def _rapidcheck_dep_impl(_ctx):
    rapidcheck_repo()
rapidcheck_dep = module_extension(
    implementation = _rapidcheck_dep_impl)

# Plog
def _plog_dep_impl(_ctx):
    plog_repo()
plog_dep = module_extension(
    implementation = _plog_dep_impl)

# Tree-Sitter
def _treesitter_dep_impl(_ctx):
    tree_sitter_repo()
treesitter_dep = module_extension(
    implementation = _treesitter_dep_impl)
