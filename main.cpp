#include <iostream>
#include <cstdio>
#include "parser.tab.hpp"
#include "ast.hpp"

extern FILE* yyin;
extern Program* g_program;
int yyparse();
void yyerror(const char* s);

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo_fuente>\n";
        return 1;
    }

    FILE* f = fopen(argv[1], "r");
    if (!f) {
        std::cerr << "No se pudo abrir el archivo: " << argv[1] << "\n";
        return 1;
    }

    yyin = f;

    if (yyparse() == 0) {
        if (g_program) {
            g_program->print();
        } else {
            std::cerr << "No se generó el AST\n";
        }
    } else {
        std::cerr << "Errores de parseo\n";
    }

    fclose(f);
    return 0;
}

void yyerror(const char* s) {
    std::cerr << "Error de parseo: " << s << std::endl;
}
