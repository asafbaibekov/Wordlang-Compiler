#ifndef LOOP_STATEMENT_H
#define LOOP_STATEMENT_H

#include <stdlib.h>
#include <stdbool.h>
#include "../../wordlang.h"
#include "../Symbol.h"
#include "../CompiledFile.h"
#include "Statement.h"
#include "../Expressions/Expression.h"

typedef struct Statement Statement;

typedef struct LoopStatement {
	Expression *expression;
	Statement *statement;
} LoopStatement;

LoopStatement *create_loop_statement(Expression *expression, Statement *statement);

void execute_loop_statement(LoopStatement *loop_statement);

void print_loop_statement(CompiledFile *compiled_file, LoopStatement *loop_statement);

void destroy_loop_statement(LoopStatement *loop_statement);

#endif // LOOP_STATEMENT_H