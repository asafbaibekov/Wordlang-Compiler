CC = gcc
LEX = lex
YACC = bison

SOURCE_FOLDER = ./src/
COMPILATION_FOLDER = ./bin/

LEX_FILE = wordlang.l
YACC_FILE = wordlang.y
TARGET = $(COMPILATION_FOLDER)wordlang
LEX_OUTPUT = $(COMPILATION_FOLDER)lex.yy.c
YACC_OUTPUT = $(COMPILATION_FOLDER)y.tab.c
YACC_OUTPUT_H = $(COMPILATION_FOLDER)y.tab.h

SOURCE_FILES =	$(SOURCE_FOLDER)Symbol.c \
				$(SOURCE_FOLDER)SymbolOperations.c \
				$(SOURCE_FOLDER)SymbolTableStack.c \
				$(SOURCE_FOLDER)Statements/AssignmentStatement.c \
				$(SOURCE_FOLDER)Statements/DeclarationStatement.c \
				$(SOURCE_FOLDER)Statements/InputStatement.c \
				$(SOURCE_FOLDER)Statements/OutputStatement.c \
				$(SOURCE_FOLDER)Statements/ScopeStatement.c \
				$(SOURCE_FOLDER)Statements/ConditionalStatement/IfStatement.c \
				$(SOURCE_FOLDER)Statements/ConditionalStatement/ElseStatement.c \
				$(SOURCE_FOLDER)Statements/ConditionalStatement/ConditionalStatement.c \
				$(SOURCE_FOLDER)Statements/Statement.c \
				$(SOURCE_FOLDER)Expressions/LiteralExpression.c \
				$(SOURCE_FOLDER)Expressions/IdentifierExpression.c \
				$(SOURCE_FOLDER)Expressions/UnaryExpression.c \
				$(SOURCE_FOLDER)Expressions/BinaryExpression.c \
				$(SOURCE_FOLDER)Expressions/Expression.c

OUTPUT_FILE = $(TARGET)

all: $(TARGET)

$(TARGET): $(YACC_OUTPUT) $(LEX_OUTPUT) $(SOURCE_FILES)
	$(CC) -o $(OUTPUT_FILE) $(SOURCE_FILES) $(YACC_OUTPUT) $(LEX_OUTPUT)

$(LEX_OUTPUT): $(LEX_FILE) $(YACC_OUTPUT)
	$(LEX) -o $(LEX_OUTPUT) $(LEX_FILE)

$(YACC_OUTPUT): $(YACC_FILE)
	$(YACC) -v -o $(YACC_OUTPUT) -d $(YACC_FILE)

$(shell mkdir -p $(COMPILATION_FOLDER))

run:
	$(OUTPUT_FILE)

clean:
	rm -rf $(COMPILATION_FOLDER)