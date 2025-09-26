#include <cstdio>
#include <iostream>
#include <memory>
#include "ast.hpp"
using namespace std

extern int yyparse(void* scanner);
extern int yylex_init(void** scanner);
extern int yylex_destroy(void* scanner);
extern FILE* yyin;
extern Program* g_program;

int main(int argc, char** argv){
  void* scanner = nullptr;
  yylex_init(&scanner);
  if(argc>1){ 
    yyin = fopen(argv[1], "r");
    if(!yyin){ perror("fopen");
        return 1;
        }
    }
  if(yyparse(scanner)==0 && g_program){
    g_program->print(cout);
    return 0;
    } else {
    cerr << "Hubo un error en el parseo" << endl;
    return 1;
  }
}