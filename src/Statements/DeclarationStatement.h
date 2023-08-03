#ifndef DECLARATION_STATEMENT_H
#define DECLARATION_STATEMENT_H

#include <stdlib.h>
#include "../../bin/y.tab.h"
#include "../SymbolTableStack.h"
#include "../Symbol.h"

typedef struct DeclarationStatement {
	SymbolTableStack **symbol_table_stack;
	Symbol *symbol;
	int type;
} DeclarationStatement;

DeclarationStatement *create_declaration_statement(SymbolTableStack **symbol_table_stack, Symbol *symbol, int type);

void execute_declaration_statement(DeclarationStatement *declaration_statement);

void print_declaration_statement(FILE *file, DeclarationStatement *declaration_statement);

void destroy_declaration_statement(DeclarationStatement *declaration_statement);

#endif // DECLARATION_STATEMENT_H