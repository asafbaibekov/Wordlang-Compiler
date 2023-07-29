#ifndef INPUT_STATEMENT_H
#define INPUT_STATEMENT_H

#include <stdlib.h>
#include "../Symbol.h"
#include "../SymbolTableStack.h"
#include "../Expressions/Expression.h"

typedef struct InputStatement {
	SymbolTableStack **symbol_table_stack;
	char *identifier;
	Expression *expression;
} InputStatement;

InputStatement *create_input_statement(SymbolTableStack **symbol_table_stack, char *identifier, Expression *expression);

void execute_input_statement(InputStatement *input_statement);

void print_input_statement(InputStatement *input_statement, int indent_level);

void destroy_input_statement(InputStatement *input_statement);

#endif // INPUT_STATEMENT_H