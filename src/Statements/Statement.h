#ifndef STATEMENT_H
#define STATEMENT_H

#include <stdio.h>
#include <stdlib.h>

#include "StatementType.h"

#include "DeclarationStatement.h"
#include "AssignmentStatement.h"
#include "InputStatement.h"
#include "OutputStatement.h"

#include "../Symbol.h"
#include "../SymbolTableStack.h"

typedef struct Statement {
	StatementType type;
	void *data;
	struct Statement *next;
} Statement;

Statement *create_statement(StatementType type, void *data);

void execute_statement(Statement *statement);

void execute_statement_list(Statement *statement_list);

void destroy_statement(Statement *statement);

#endif // STATEMENT_H