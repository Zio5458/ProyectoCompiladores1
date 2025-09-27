#include "lexer.hpp"
#include "parser.tab.h"

Lexer* g_scanner = nullptr;

extern "C" int yylex() {
  return g_scanner ? g_scanner->yylex() : 0;
}
