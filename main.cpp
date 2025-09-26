#include <cstdio>
#include <iostream>
#include "parser.hpp"
#include "ast.hpp"
#include "lexer.hpp"

extern Program* g_program;

int main() {
    // Abrir archivo de entrada
    FILE* f = fopen("test.txt", "r");
    if (!f) {
        std::cerr << "No se pudo abrir test.txt\n";
        return 1;
    }

    // Inicializar scanner reentrant
    yyscan_t scanner;
    if (yylex_init(&scanner)) {
        std::cerr << "Error al inicializar el scanner\n";
        fclose(f);
        return 1;
    }

    // Crear buffer y activarlo
    YY_BUFFER_STATE buf = yy_create_buffer(f, YY_BUF_SIZE, scanner);
    yy_switch_to_buffer(buf);

    // Parsear
    if (yyparse(scanner) == 0) {
        if (g_program) {
            g_program->print(std::cout);
        }
    } else {
        std::cerr << "Error de parsing\n";
    }

    // Limpiar
    yy_delete_buffer(buf, scanner);
    yylex_destroy(scanner);
    fclose(f);

    return 0;
}
