TARGET = compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
#Archvios fuente
SRCS = main.cpp ast.cpp parser_support.cpp lexer.cpp parser.tab.cpp
OBJS = $(SRCS:.cpp=.o)

LEX_SRC = lexer.l
LEX_OUT = lexer.cpp
YACC_SRC = parser.y
YACC_CPP = parser.tab.cpp
YACC_HPP = parser.tab.hpp
all: $(TARGET)

#compiler.exe
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

#Bison
$(YACC_CPP) $(YACC_HPP): $(YACC_SRC)
	bison -d -o $(YACC_CPP) $(YACC_SRC)

#Flex
$(LEX_OUT): $(LEX_SRC)
	flex -o $@ $<

main.o parser_support.o: $(YACC_HPP)
lexer.o: $(YACC_HPP)

clean:
	rm -f $(OBJS) $(TARGET) $(LEX_OUT) $(YACC_CPP) $(YACC_HPP)

rebuild: clean all

.PHONY: all clean rebuild