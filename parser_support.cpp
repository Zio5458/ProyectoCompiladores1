#include <cstdio>
#include "parser.tab.hpp"
using namespace std;


void yyerror(const char* s) {
  fprintf(stderr, "Parse error: %s\n", s);
}
