#ifndef ELSE_STATEMENT_H
#define ELSE_STATEMENT_H

#include <stdlib.h>

#include "../../../wordlang.h"
#include "../../Symbol.h"
#include "../Statement.h"
#include "../../Expressions/Expression.h"

typedef struct Statement Statement;

typedef struct ElseStatement {
	Statement *statement;
} ElseStatement;

ElseStatement *create_else_statement(Statement *statement);

bool execute_else_statement(ElseStatement *else_statement);

void print_else_statement(ElseStatement *else_statement, int indent_level);

void destroy_else_statement(ElseStatement *else_statement);

#endif // ELSE_STATEMENT_H