/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "parser.y"

#include "ast.hpp"
#include <vector>
#include <string>
using namespace std;

#line 56 "parser.tab.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOK_ID = 258,                  /* TOK_ID  */
    TOK_TYPE = 259,                /* TOK_TYPE  */
    TOK_NUM = 260,                 /* TOK_NUM  */
    TOK_BOOL = 261,                /* TOK_BOOL  */
    TOK_FN = 262,                  /* TOK_FN  */
    TOK_LET = 263,                 /* TOK_LET  */
    TOK_RETURN = 264,              /* TOK_RETURN  */
    TOK_IF = 265,                  /* TOK_IF  */
    TOK_ELSE = 266,                /* TOK_ELSE  */
    TOK_WHILE = 267,               /* TOK_WHILE  */
    TOK_PLUS = 268,                /* TOK_PLUS  */
    TOK_MINUS = 269,               /* TOK_MINUS  */
    TOK_MUL = 270,                 /* TOK_MUL  */
    TOK_DIV = 271,                 /* TOK_DIV  */
    TOK_EQ = 272,                  /* TOK_EQ  */
    TOK_LT = 273,                  /* TOK_LT  */
    TOK_GT = 274,                  /* TOK_GT  */
    TOK_AND = 275,                 /* TOK_AND  */
    TOK_OR = 276,                  /* TOK_OR  */
    TOK_NOT = 277,                 /* TOK_NOT  */
    TOK_SEMI = 278,                /* TOK_SEMI  */
    TOK_COLON = 279,               /* TOK_COLON  */
    TOK_COMMA = 280,               /* TOK_COMMA  */
    TOK_LPAREN = 281,              /* TOK_LPAREN  */
    TOK_RPAREN = 282,              /* TOK_RPAREN  */
    TOK_LBRACE = 283,              /* TOK_LBRACE  */
    TOK_RBRACE = 284,              /* TOK_RBRACE  */
    TOK_ARROW = 285,               /* TOK_ARROW  */
    TOK_MOD = 286,                 /* TOK_MOD  */
    TOK_FOR = 287,                 /* TOK_FOR  */
    TOK_LOOP = 288,                /* TOK_LOOP  */
    TOK_BREAK = 289,               /* TOK_BREAK  */
    TOK_CONTINUE = 290             /* TOK_CONTINUE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 8 "parser.y"

    Node* node;
    Expr* expr;
    Stmt* stmt;
    Block* block;
    Func* func;
    Program* program;
    Param* param;
    vector<Param*>* param_list;
    vector<Expr*>* expr_list;
    vector<string>* string_list;
    char* str;
    long num;
    bool boolean;

#line 124 "parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */
