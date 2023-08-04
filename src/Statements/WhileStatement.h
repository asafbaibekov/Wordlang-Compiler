#ifndef WHILE_STATEMENT_H
#define WHILE_STATEMENT_H

#include <stdlib.h>
#include <stdbool.h>
#include "../../wordlang.h"
#include "../Symbol.h"
#include "../CompiledFile.h"
#include "Statement.h"
#include "../Expressions/Expression.h"

typedef struct Statement Statement;

typedef struct WhileStatement {
	Expression *expression;
	Statement *statement;
} WhileStatement;

WhileStatement *create_while_statement(Expression *expression, Statement *statement);

void execute_while_statement(WhileStatement *while_statement);

void print_while_statement(CompiledFile *compiled_file, WhileStatement *while_statement);

void destroy_while_statement(WhileStatement *while_statement);

#endif // WHILE_STATEMENT_H