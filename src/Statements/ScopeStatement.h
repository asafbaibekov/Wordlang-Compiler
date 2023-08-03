#ifndef SCOPE_STATEMENT_H
#define SCOPE_STATEMENT_H

#include <stdio.h>
#include <stdlib.h>

#include "../SymbolTableStack.h"
#include "Statement.h"

typedef struct Statement Statement;

typedef struct ScopeStatement {
	SymbolTableStack **symbol_table_stack;
	Statement *statement_list;
} ScopeStatement;

ScopeStatement *create_scope_statement(SymbolTableStack **symbol_table_stack, Statement *statement_list);

void execute_scope_statement(ScopeStatement *scope_statement);

void print_scope_statement(FILE *file, ScopeStatement *scope_statement);

void destroy_scope_statement(ScopeStatement *scope_statement);

#endif // SCOPE_STATEMENT_H