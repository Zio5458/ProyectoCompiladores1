#include <iostream>
#include <cstdio>
#include "ast.hpp"
#include "parser.tab.hpp" 
using namespace std;

extern int yyparse();
extern Program* g_program;
extern FILE* yyin;

int main(int argc, char** argv) {
  if (argc < 2) {
    cerr << "Uso: compiler <archivo.rs>\n";
    return 1;
  }

  yyin = fopen(argv[1], "r");
  if (!yyin) {
    cerr << "No se pudo abrir: " << argv[1] << "\n";
    return 1;
  }

  int ret = yyparse();

  if (ret == 0 && g_program) {
    g_program->print();
  }

  fclose(yyin);
  return ret;
}
