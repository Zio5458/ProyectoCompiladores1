%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <memory>
#include "ast.hpp"

using namespace std;

// Programa global (se puede omitir si se quiere encapsular)
Program* g_program = nullptr;

// Ajuste de yyerror para modo reentrant
int yyerror(yyscan_t scanner, const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
    return 0;
}

%}

%define api.pure full
%define parse.error verbose
%defines "parser.hpp"
%define api.value.type {union}

/* Tipos de valor del parser */
%union {
    long long num;
    bool boolean;
    char* str;
    Expr* expr;
    Stmt* stmt;
    Block* block;
    Param* param;
    Func* func;
    Program* program;
    std::vector<Expr*>* exprlist;
    std::vector<Param*>* paramlist;
}

/* Tokens con tipos de valor */
%token <str> TOK_ID TOK_TYPE
%token <num> TOK_NUM
%token <boolean> TOK_BOOL
%token TOK_FN TOK_LET TOK_IF TOK_ELSE TOK_RETURN
%token ARROW EQ AND OR LT GT NOT PLUS MINUS MUL DIV
%token LPAREN RPAREN LBRACE RBRACE COMMA SEMI

/* No terminales con tipos de valor */
%type <program> program
%type <func> function
%type <paramlist> param_list nonempty_params
%type <param> param
%type <block> block stmts
%type <stmt> stmt
%type <expr> expr term factor primary
%type <exprlist> arg_list nonempty_args
%type <str> opt_ret

%start program

%left OR
%left AND
%left EQ
%left LT GT
%left PLUS MINUS
%left MUL DIV
%right NOT

%%

program
    : /* empty */ { $$ = new Program(); g_program = $$; }
    | program function { $1->add($2); $$ = $1; }
    ;

function
    : TOK_FN TOK_ID LPAREN param_list RPAREN opt_ret block {
        auto f = new Func($2);
        for (auto p : *$4) f->addParam(p);
        delete $4;
        f->setRet($6 ? string($6) : string());
        free($6);
        f->setBody($7);
        $$ = f;
    }
    ;

opt_ret
    : /* empty */ { $$ = nullptr; }
    | ARROW TOK_TYPE { $$ = $2; }
    ;

param_list
    : /* empty */ { $$ = new vector<Param*>(); }
    | nonempty_params { $$ = $1; }
    ;

nonempty_params
    : param { $$ = new vector<Param*>(); $$->push_back($1); }
    | nonempty_params COMMA param { $1->push_back($3); $$ = $1; }
    ;

param
    : TOK_ID ':' TOK_TYPE { $$ = new Param($1, $3); }
    ;

block
    : LBRACE stmts RBRACE { $$ = $2; }
    ;

stmts
    : /* empty */ { $$ = new Block(); }
    | stmts stmt { $1->add($2); $$ = $1; }
    ;

stmt
    : TOK_LET TOK_ID '=' expr SEMI { $$ = new LetStmt($2, "infer", $4); }
    | TOK_RETURN expr SEMI { $$ = new ReturnStmt($2); }
    | TOK_RETURN SEMI { $$ = new ReturnStmt(nullptr); }
    | TOK_IF expr block TOK_ELSE block { $$ = new IfStmt($2, $3, $5); }
    | TOK_IF expr block { $$ = new IfStmt($2, $3, nullptr); }
    | expr SEMI { $$ = new ExprStmt($1); }
    ;

expr
    : expr OR term   { $$ = new Binary($1, "||", $3); }
    | expr AND term  { $$ = new Binary($1, "&&", $3); }
    | expr EQ term   { $$ = new Binary($1, "==", $3); }
    | expr LT term   { $$ = new Binary($1, "<", $3); }
    | expr GT term   { $$ = new Binary($1, ">", $3); }
    | term           { $$ = $1; }
    ;

term
    : term PLUS factor  { $$ = new Binary($1, "+", $3); }
    | term MINUS factor { $$ = new Binary($1, "-", $3); }
    | factor            { $$ = $1; }
    ;

factor
    : factor MUL primary { $$ = new Binary($1, "*", $3); }
    | factor DIV primary { $$ = new Binary($1, "/", $3); }
    | NOT factor         { $$ = new Unary("!", $2); }
    | primary            { $$ = $1; }
    ;

primary
    : TOK_NUM           { $$ = new Number($1); }
    | TOK_BOOL          { $$ = new BoolLit($1); }
    | TOK_ID LPAREN arg_list RPAREN {
        auto c = new Call($1);
        for (auto e : *$3) c->add(e);
        delete $3;
        $$ = c;
      }
    | TOK_ID            { $$ = new Identifier($1); }
    | LPAREN expr RPAREN { $$ = $2; }
    ;

arg_list
    : /* empty */ { $$ = new vector<Expr*>(); }
    | nonempty_args { $$ = $1; }
    ;

nonempty_args
    : expr { $$ = new vector<Expr*>(); $$->push_back($1); }
    | nonempty_args COMMA expr { $1->push_back($3); $$ = $1; }
    ;

%%
