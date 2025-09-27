#pragma once
#include <istream>
#include <ostream>
#include <FlexLexer.h>
using namespace std;

class Lexer : public yyFlexLexer {
public:
  Lexer(istream* arg_yyin = nullptr, ostream* arg_yyout = nullptr);
  int yylex() override;
};

extern Lexer* g_scanner;
