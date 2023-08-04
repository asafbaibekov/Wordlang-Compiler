#ifndef CONDITIONAL_STATEMENT_H
#define CONDITIONAL_STATEMENT_H

#include <stdlib.h>
#include <stdbool.h>

#include "ConditionalType.h"
#include "../../../wordlang.h"
#include "../../Symbol.h"
#include "../../CompiledFile.h"
#include "../Statement.h"
#include "../../Expressions/Expression.h"

#include "IfStatement.h"
#include "ElseStatement.h"

typedef struct Statement Statement;

typedef struct ConditionalStatement {
	ConditionalType type;
	void *data;
	struct ConditionalStatement *next;
} ConditionalStatement;

ConditionalStatement *create_conditional_statement(ConditionalType type, void *data);

ConditionalStatement *create_conditional_statement_list(ConditionalStatement *conditional_statement_list, ConditionalStatement *conditional_statement);

bool execute_conditional_statement(ConditionalStatement *conditional_statement);

bool execute_conditional_statement_list(ConditionalStatement *conditional_statement_list);

void print_conditional_statement(CompiledFile *compiled_file, ConditionalStatement *conditional_statement);

void print_conditional_statement_list(CompiledFile *compiled_file, ConditionalStatement *conditional_statement_list);

void destroy_conditional_statement(ConditionalStatement *conditional_statement);

void destroy_conditional_statement_list(ConditionalStatement *conditional_statement_list);

#endif // CONDITIONAL_STATEMENT_H
