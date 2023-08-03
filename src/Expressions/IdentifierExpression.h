#ifndef IDENTIFIER_EXPRESSION_H
#define IDENTIFIER_EXPRESSION_H

#include <stdlib.h>
#include "../Symbol.h"
#include "../SymbolTableStack.h"

typedef struct IdentifierExpression {
	SymbolTableStack **symbol_table_stack;
	char *name;
} IdentifierExpression;

IdentifierExpression *create_identifier_expression(SymbolTableStack **symbol_table_stack, char *name);

Symbol *evaluate_identifier_expression(IdentifierExpression *identifier_expression);

void print_identifier_expression(FILE *file, IdentifierExpression *identifier_expression);

void destroy_identifier_expression(IdentifierExpression *identifier_expression);

#endif // IDENTIFIER_EXPRESSION_H