%{
#include "parser.tab.hpp"
#include <cstdlib>
#include <cstring>

using namespace std;

#define YY_DECL int yylex(YYSTYPE* yylval)
%}

digit       [0-9]
alpha       [a-zA-Z_]
alphanum    [a-zA-Z0-9_]

%%

"fn"        { return TOK_FN; }
"let"       { return TOK_LET; }
"return"    { return TOK_RETURN; }
"if"        { return TOK_IF; }
"else"      { return TOK_ELSE; }
"while"     { return TOK_WHILE; }

"i32"       { yylval->str = strdup("i32"); return TOK_TYPE; }
"f64"       { yylval->str = strdup("f64"); return TOK_TYPE; }
"bool"      { yylval->str = strdup("bool"); return TOK_TYPE; }
"char"      { yylval->str = strdup("char"); return TOK_TYPE; }
"String"    { yylval->str = strdup("String"); return TOK_TYPE; }

"true"      { yylval->expr = new BoolLit(true); return TOK_BOOL; }
"false"     { yylval->expr = new BoolLit(false); return TOK_BOOL; }

{digit}+    { yylval->expr = new Number(atoi(yytext)); return TOK_NUM; }
{alpha}{alphanum}* { yylval->expr = new Identifier(strdup(yytext)); return TOK_ID; }

"&&"        { return TOK_AND; }
"||"        { return TOK_OR; }
"!"         { return TOK_NOT; }
"=="        { return TOK_EQ; }
"<"         { return TOK_LT; }
">"         { return TOK_GT; }
"+"         { return TOK_PLUS; }
"-"         { return TOK_MINUS; }
"*"         { return TOK_MUL; }
"/"         { return TOK_DIV; }

";"         { return TOK_SEMI; }
":"         { return TOK_COLON; }
","         { return TOK_COMMA; }
"("         { return TOK_LPAREN; }
")"         { return TOK_RPAREN; }
"{"         { return TOK_LBRACE; }
"}"         { return TOK_RBRACE; }
"->"        { return TOK_ARROW; }

[ \t\n\r]+  { /* Ignorar espacios y saltos de línea */ }

.           { fprintf(stderr, "Caracter inesperado: %s\n", yytext); exit(1); }

%%

int yywrap() { return 1; }
