#ifndef STATEMENT_H
#define STATEMENT_H

#include <stdio.h>
#include <stdlib.h>

#include "StatementType.h"

#include "LoopStatement.h"
#include "WhileStatement.h"
#include "ConditionalStatement/ConditionalStatement.h"
#include "ScopeStatement.h"
#include "DeclarationStatement.h"
#include "AssignmentStatement.h"
#include "InputStatement.h"
#include "OutputStatement.h"

#include "../Symbol.h"
#include "../CompiledFile.h"
#include "../SymbolTableStack.h"

typedef struct Statement {
	StatementType type;
	void *data;
	struct Statement *next;
} Statement;

Statement *create_statement(StatementType type, void *data);

Statement *create_statement_list(Statement *statement_list, Statement *statement);

void execute_statement(Statement *statement);

void execute_statement_list(Statement *statement_list);

void print_statement(CompiledFile *compiled_file, Statement *statement);

void print_statement_list(CompiledFile *compiled_file, Statement *statement_list);

void destroy_statement(Statement *statement);

void destroy_statement_list(Statement *statement_list);

#endif // STATEMENT_H