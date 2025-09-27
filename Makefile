# Compilador
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Archivos generados por Bison y Flex
BISON_FILE = parser.y
LEX_FILE   = lexer.l
BISON_OUTPUT = parser.tab.cpp
BISON_HEADER = parser.tab.hpp
LEX_OUTPUT  = lexer.yy.cpp

# Objetos
OBJS = main.o ast.o parser.tab.o lexer.yy.o

# Ejecutable
TARGET = mycompiler

all: $(TARGET)

# Compilar todo
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Bison
parser.tab.cpp parser.tab.hpp: $(BISON_FILE)
	bison -d -o parser.tab.cpp $(BISON_FILE)

# Flex
lexer.yy.cpp: $(LEX_FILE) parser.tab.hpp
	flex -o lexer.yy.cpp $(LEX_FILE)

# Compilar objetos
parser.tab.o: parser.tab.cpp
	$(CXX) $(CXXFLAGS) -c parser.tab.cpp

lexer.yy.o: lexer.yy.cpp
	$(CXX) $(CXXFLAGS) -c lexer.yy.cpp

ast.o: ast.cpp ast.hpp
	$(CXX) $(CXXFLAGS) -c ast.cpp

main.o: main.cpp ast.hpp parser.tab.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f $(OBJS) $(BISON_OUTPUT) $(BISON_HEADER) $(LEX_OUTPUT) $(TARGET)
