#pragma once
#include <istream>
#include <ostream>
#include <FlexLexer.h>

class Lexer : public yyFlexLexer {
public:
  Lexer(std::istream* arg_yyin = nullptr, std::ostream* arg_yyout = nullptr);
  int yylex() override;
};

extern Lexer* g_scanner;
