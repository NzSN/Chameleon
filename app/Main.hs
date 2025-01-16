module Main where

import qualified MyLib (someFunc)

data Tree a =
  Tree { l :: Tree a, r :: Tree a } | Node a

main :: IO ()
main = do
  putStrLn "Hello, Haskell!"
  MyLib.someFunc
