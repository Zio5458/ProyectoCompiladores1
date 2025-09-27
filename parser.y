%code requires {
#include "ast.hpp"
#include <vector>
#include <string>
}

%union {
    Node* node;
    Expr* expr;
    Stmt* stmt;
    Block* block;
    Func* func;
    Program* program;
    Param* param;
    std::vector<Param*>* param_list;
    std::vector<std::string>* string_list;
    char* str;
    long num;
    bool boolean;
}

%code {
extern int yylex();
void yyerror(const char* s);
}

%token <str> TOK_ID TOK_TYPE
%token <num> TOK_NUM
%token <boolean> TOK_BOOL

%token TOK_FN TOK_LET TOK_RETURN TOK_IF TOK_ELSE TOK_WHILE
%token TOK_PLUS TOK_MINUS TOK_MUL TOK_DIV TOK_EQ TOK_LT TOK_GT
%token TOK_AND TOK_OR TOK_NOT
%token TOK_SEMI TOK_COLON TOK_COMMA TOK_LPAREN TOK_RPAREN TOK_LBRACE TOK_RBRACE TOK_ARROW

%type <program> program
%type <func> function
%type <block> block stmt_list
%type <stmt> stmt
%type <param_list> param_list param_list_opt
%type <param> param
%type <str> opt_ret
%type <expr> expr logic_and equality relational additive multiplicative unary primary

%%

program:
      %empty { $$ = new Program(); g_program = $$; }
    | program function { $1->add($2); $$ = $1; }
    ;

function:
    TOK_FN TOK_ID TOK_LPAREN param_list_opt TOK_RPAREN opt_ret block {
        // Crear la función
        Func* f = new Func($2);

        // Asignar parámetros (convertir Param* a nombres si Func::params es vector<string>)
        for (Param* p : *$4) {
            f->params.push_back(p->name); // asumiendo Param tiene 'name' como std::string
        }
        delete $4; // liberar vector temporal

        // Tipo de retorno
        f->ret_type = $6 ? std::string($6) : "void";

        // Asignar el bloque de código al unique_ptr
        f->body = std::unique_ptr<Block>($7);

        $$ = f;
    }
    ;


param_list_opt:
      %empty { $$ = new std::vector<Param*>(); }
    | param_list { $$ = $1; }
    ;

param_list:
      param { $$ = new std::vector<Param*>(); $$->push_back($1); }
    | param_list TOK_COMMA param { $1->push_back($3); $$ = $1; }
    ;

param:
    TOK_ID TOK_COLON TOK_TYPE { $$ = new Param($1, $3); }
    ;

opt_ret:
      %empty { $$ = nullptr; }
    | TOK_ARROW TOK_TYPE { $$ = $2; }
    ;

block:
    TOK_LBRACE stmt_list TOK_RBRACE { $$ = $2; }
    ;

stmt_list:
      stmt { Block* b = new Block(); b->add($1); $$ = b; }
    | stmt_list stmt { $1->add($2); $$ = $1; }
    ;

stmt:
      TOK_LET TOK_ID TOK_EQ expr TOK_SEMI { $$ = new LetStmt($2, $4); }
    | TOK_RETURN expr TOK_SEMI { $$ = new ReturnStmt($2); }
    | TOK_RETURN TOK_SEMI { $$ = new ReturnStmt(nullptr); }
    | TOK_IF expr block TOK_ELSE block { $$ = new IfStmt($2, $3, $5); }
    | TOK_IF expr block { $$ = new IfStmt($2, $3, nullptr); }
    | expr TOK_SEMI { $$ = new ExprStmt($1); }
    ;

expr:
      expr TOK_OR logic_and         { $$ = new Binary($1, "||", $3); }
    | logic_and
    ;

logic_and:
      logic_and TOK_AND equality    { $$ = new Binary($1, "&&", $3); }
    | equality
    ;

equality:
      equality TOK_EQ relational    { $$ = new Binary($1, "==", $3); }
    | relational
    ;

relational:
      relational TOK_LT additive    { $$ = new Binary($1, "<",  $3); }
    | relational TOK_GT additive    { $$ = new Binary($1, ">",  $3); }
    | additive
    ;

additive:
      additive TOK_PLUS multiplicative  { $$ = new Binary($1, "+", $3); }
    | additive TOK_MINUS multiplicative { $$ = new Binary($1, "-", $3); }
    | multiplicative
    ;

multiplicative:
      multiplicative TOK_MUL unary  { $$ = new Binary($1, "*", $3); }
    | multiplicative TOK_DIV unary  { $$ = new Binary($1, "/", $3); }
    | unary
    ;

unary:
      TOK_NOT unary                 { $$ = new Unary("!", $2); }
    | primary
    ;

primary:
      TOK_NUM                       { $$ = new Number($1); }
    | TOK_BOOL                      { $$ = new BoolLit($1); }
    | TOK_ID                        { $$ = new Identifier($1); }
    | TOK_LPAREN expr TOK_RPAREN    { $$ = $2; }
    ;


%%
