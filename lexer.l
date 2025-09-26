%option noyywrap reentrant bison-bridge nodefault yylineno

%{
#include "parser.hpp"
#include <cstdlib>
#include <cstring>
#include <cstdio>

#define YYSTYPE yylval
%}

/* Expresiones regulares */
WS       [ \t\r\f\v]+
COMMENT  \/\/[^\n]*\n
ID       [a-zA-Z_][a-zA-Z0-9_]* 
NUM      [0-9]+

%%

{WS}           ;
{COMMENT}      ;

/* Palabras clave */
"fn"           { return TOK_FN; }
"let"          { return TOK_LET; }
"if"           { return TOK_IF; }
"else"         { return TOK_ELSE; }
"return"       { return TOK_RETURN; }

/* Booleanos */
"true"         { yylval->boolean = true; return TOK_BOOL; }
"false"        { yylval->boolean = false; return TOK_BOOL; }

/* Tipos */
"i32"          { yylval->str = strdup("i32"); return TOK_TYPE; }
"bool"         { yylval->str = strdup("bool"); return TOK_TYPE; }

/* Operadores */
"->"           { return ARROW; }
"=="           { return EQ; }
"&&"           { return AND; }
"||"           { return OR; }
"<"            { return LT; }
">"            { return GT; }
"!"            { return NOT; }
"+"            { return PLUS; }
"-"            { return MINUS; }
"*"            { return MUL; }
"/"            { return DIV; }

/* Puntuación */
"("            { return LPAREN; }
")"            { return RPAREN; }
"{"            { return LBRACE; }
"}"            { return RBRACE; }
","            { return COMMA; }
";"            { return SEMI; }

/* Identificadores y números */
{NUM}          { yylval->num = atoll(yytext); return TOK_NUM; }
{ID}           { yylval->str = strdup(yytext); return TOK_ID; }

/* Saltos de línea ignorados */
\n             ;

/* Caracteres no reconocidos */
.              { return *yytext; }

%%
