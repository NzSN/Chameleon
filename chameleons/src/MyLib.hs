{-# LANGUAGE LambdaCase #-}

module MyLib (someFunc) where

import qualified TreeSitter.Node as TN
import qualified TreeSitter.Tree as TT
import qualified TreeSitter.Cursor as TC
import qualified TreeSitter.Parser as TParser
import TreeSitter.TypeScript (tree_sitter_typescript)
import qualified Data.ByteString.Char8 as BL
import Foreign (Ptr, Storable (peek,poke), malloc, free)
import Foreign.C.String
import Control.Exception.Extra (assertIO)
import TreeSitter.Node (Node(nodeTSNode))

tree_traverse :: Ptr TC.Cursor  -> IO ()
tree_traverse cursor = do
  node_ptr <- malloc
  succeed <- TC.ts_tree_cursor_current_node_p cursor node_ptr
  assertIO succeed

  node <- peek node_ptr
  msg <- peekCString $ TN.nodeType node

  putStrLn msg

  TC.ts_tree_cursor_goto_first_child cursor
    >>= \case
    True -> tree_traverse cursor
    False -> do
      TC.ts_tree_cursor_goto_next_sibling cursor
        >>= \case
          True -> tree_traverse cursor
          False -> return ()

  free node_ptr

someFunc :: IO ()
someFunc = do
  parser <- TParser.ts_parser_new
  succeed <- TParser.ts_parser_set_language parser tree_sitter_typescript
  assertIO succeed

  TParser.withParseTree parser (BL.pack "function main() { return 0; }") $ \tree -> do
    TT.withRootNode tree $ \node_ptr -> do
      node <- peek node_ptr
      tsnode_ptr <- malloc

      poke tsnode_ptr (nodeTSNode node)
      TC.withCursor tsnode_ptr $ \cursor_p -> tree_traverse cursor_p

      free tsnode_ptr
