#ifndef IF_STATEMENT_H
#define IF_STATEMENT_H

#include <stdlib.h>
#include <stdbool.h>
#include "../../../wordlang.h"
#include "../../Symbol.h"
#include "../../CompiledFile.h"
#include "../Statement.h"
#include "../../Expressions/Expression.h"

typedef struct Statement Statement;

typedef struct IfStatement {
	Expression *expression;
	Statement *statement;
} IfStatement;

IfStatement *create_if_statement(Expression *expression, Statement *statement);

bool execute_if_statement(IfStatement *if_statement);

void print_if_statement(CompiledFile *compiled_file, IfStatement *if_statement);

void destroy_if_statement(IfStatement *if_statement);

#endif // IF_STATEMENT_H