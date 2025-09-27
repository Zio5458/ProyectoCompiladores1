%option noyywrap nodefault yylineno
%{
  #include <cstdlib>
  #include <cstring>
  #include <string>
  #include "parser.tab.hpp"

  extern YYSTYPE yylval;

  static char* dup_cstr(const char* s) {
    if (!s) return nullptr;
    size_t n = std::strlen(s) + 1;
    char* p = static_cast<char*>(std::malloc(n));
    if (p) std::memcpy(p, s, n);
    return p;
  }
%}

WS        [ \t\r]+
ID        [A-Za-z_][A-Za-z0-9_]*
NUM       [0-9]+
BOOLTRUE  "true"
BOOLFALSE "false"
ARROW     "->"

%x CMT

%%

{WS}                            
\n                              
"//".*                          
"/*"                            { BEGIN(CMT); }
<CMT>"*/"                       { BEGIN(INITIAL); }
<CMT>\n                         
<CMT>.                          

"fn"                            { return TOK_FN; }
"let"                           { return TOK_LET; }
"return"                        { return TOK_RETURN; }
"if"                            { return TOK_IF; }
"else"                          { return TOK_ELSE; }
"while"                         { return TOK_WHILE; }

"i32"|"f64"|"bool"|"char"|"str" { yylval.str = dup_cstr(yytext); return TOK_TYPE; }

{BOOLTRUE}                      { yylval.boolean = true;  return TOK_BOOL; }
{BOOLFALSE}                     { yylval.boolean = false; return TOK_BOOL; }

{NUM}                           { yylval.num = std::strtol(yytext, nullptr, 10); return TOK_NUM; }

{ID}                            { yylval.str = dup_cstr(yytext); return TOK_ID; }

"&&"                            { return TOK_AND; }
"||"                            { return TOK_OR;  }
"!"                             { return TOK_NOT; }
"=="                            { return TOK_EQ; }
"<"                             { return TOK_LT; }
">"                             { return TOK_GT; }
"+"                             { return TOK_PLUS; }
"-"                             { return TOK_MINUS; }
"*"                             { return TOK_MUL; }
"/"                             { return TOK_DIV; }
"="                             { return TOK_EQ; }

";"                             { return TOK_SEMI; }
":"                             { return TOK_COLON; }
","                             { return TOK_COMMA; }
"("                             { return TOK_LPAREN; }
")"                             { return TOK_RPAREN; }
"{"                             { return TOK_LBRACE; }
"}"                             { return TOK_RBRACE; }
{ARROW}                         { return TOK_ARROW; }

.                               
<<EOF>>                         { return 0; }
