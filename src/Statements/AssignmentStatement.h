#ifndef ASSIGNMENT_STATEMENT_H
#define ASSIGNMENT_STATEMENT_H

#include <stdlib.h>
#include "../../wordlang.h"
#include "../Expressions/Expression.h"
#include "../SymbolTableStack.h"

typedef struct AssignmentStatement {
	SymbolTableStack **symbol_table_stack;
	char *identifier;
	Expression *expression;
} AssignmentStatement;

AssignmentStatement *create_assignment_statement(SymbolTableStack **symbol_table_stack, char *identifier, Expression *expression);

void execute_assignment_statement(AssignmentStatement *assignment_statement);

void print_assignment_statement(AssignmentStatement *assignment_statement, int indent_level);

void destroy_assignment_statement(AssignmentStatement *assignment_statement);

#endif // ASSIGNMENT_STATEMENT_H