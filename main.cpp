#include <iostream>
#include <cstdio>
#include "ast.hpp"
#include "parser.tab.hpp" 

extern int yyparse();
extern Program* g_program;
extern FILE* yyin;

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Uso: compiler <archivo.rs>\n";
    return 1;
  }

  yyin = std::fopen(argv[1], "r");
  if (!yyin) {
    std::cerr << "No se pudo abrir: " << argv[1] << "\n";
    return 1;
  }

  int ret = yyparse();

  if (ret == 0 && g_program) {
    g_program->print();
  }

  std::fclose(yyin);
  return ret;
}
