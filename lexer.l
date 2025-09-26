%{
  #include "parser.hpp"
  #include <cstring>
  #include <cstdlib>
  using namespace std;
  extern YYSTYPE yylval;
%}

%option noyywrap nodefault yylineno reentrant bison-bridge

WS       [ \t\r\f\v]+
COMMENT  \/\/[^{\n}]*\n
ID       [a-zA-Z_][a-zA-Z0-9_]*
NUM      [0-9]+

%%
{WS}           ;
{COMMENT}      ;
"fn"           { return TOK_FN; }
"let"          { return TOK_LET; }
"if"           { return TOK_IF; }
"else"         { return TOK_ELSE; }
"return"       { return TOK_RETURN; }
"true"         { yylval.boolean = true; return TOK_BOOL; }
"false"        { yylval.boolean = false; return TOK_BOOL; }
"i32"          { yylval.str = strdup("i32"); return TOK_TYPE; }
"bool"         { yylval.str = strdup("bool"); return TOK_TYPE; }

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
"("            { return LPAREN; }
")"            { return RPAREN; }
"{"            { return LBRACE; }
"}"            { return RBRACE; }
","            { return COMMA; }
";"            { return SEMI; }

{NUM}          { yylval.num = atoll(yytext); return TOK_NUM; }
{ID}           { yylval.str = strdup(yytext); return TOK_ID; }
\n             ;
.              { return *yytext; }
%%