#!/bin/bash
antlr4 ./ChameleonsLexer.g4 ./ChameleonsParser.g4 -Dlanguage=Cpp -visitor
