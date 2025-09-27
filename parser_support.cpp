#include <cstdio>
#include "parser.tab.hpp"


void yyerror(const char* s) {
  std::fprintf(stderr, "Parse error: %s\n", s);
}
