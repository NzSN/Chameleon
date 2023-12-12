#include <gtest/gtest.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <tree_sitter/api.h>

extern "C" {

TSLanguage *tree_sitter_json();
TSLanguage *tree_sitter_wgsl();

}

TEST(TreeSitter, WGSL_Failed) {
 // Create a parser.
  TSParser *parser = ts_parser_new();

  // Set the parser's language (WGSL in this case).
  ts_parser_set_language(parser, tree_sitter_wgsl());

  const char* source_code = "a = ??";
  TSTree *tree = ts_parser_parse_string(
    parser,
    NULL,
    source_code,
    strlen(source_code));

  TSNode root_node = ts_tree_root_node(tree);
  EXPECT_TRUE(ts_node_has_error(root_node));
}


TEST(TreeSitter, WGSL) {
 // Create a parser.
  TSParser *parser = ts_parser_new();

  // Set the parser's language (WGSL in this case).
  ts_parser_set_language(parser, tree_sitter_wgsl());

  const char* source_code =
    "struct Uniforms { "
    "  modelViewProjectionMatrix: mat4x4<f32>,"
    "  maxStorableFragments: u32,"
    "  targetWidth: u32 "
    "};";
  TSTree *tree = ts_parser_parse_string(
    parser,
    NULL,
    source_code,
    strlen(source_code));

  TSNode root_node = ts_tree_root_node(tree);
  EXPECT_TRUE(!ts_node_has_error(root_node));
}


TEST(TreeSitter, Intro) {
 // Create a parser.
  TSParser *parser = ts_parser_new();

  // Set the parser's language (JSON in this case).
  ts_parser_set_language(parser, tree_sitter_json());

  // Build a syntax tree based on source code stored in a string.
  const char *source_code = "[1, null]";
  TSTree *tree = ts_parser_parse_string(
    parser,
    NULL,
    source_code,
    strlen(source_code)
  );

  // Get the root node of the syntax tree.
  TSNode root_node = ts_tree_root_node(tree);

  // Get some child nodes.
  TSNode array_node = ts_node_named_child(root_node, 0);
  TSNode number_node = ts_node_named_child(array_node, 0);

  // Check that the nodes have the expected types.
  assert(strcmp(ts_node_type(root_node), "document") == 0);
  assert(strcmp(ts_node_type(array_node), "array") == 0);
  assert(strcmp(ts_node_type(number_node), "number") == 0);

  // Check that the nodes have the expected child counts.
  assert(ts_node_child_count(root_node) == 1);
  assert(ts_node_child_count(array_node) == 5);
  assert(ts_node_named_child_count(array_node) == 2);
  assert(ts_node_child_count(number_node) == 0);

  // Free all of the heap-allocated memory.
  ts_tree_delete(tree);
  ts_parser_delete(parser);
}
