#include "ScopeStatement.h"

ScopeStatement *create_scope_statement(SymbolTableStack **symbol_table_stack, Statement *statement_list) {
	ScopeStatement *scope_statement = malloc(sizeof(ScopeStatement));
	scope_statement->symbol_table_stack = symbol_table_stack;
	scope_statement->statement_list = statement_list;
	return scope_statement;
}

void execute_scope_statement(ScopeStatement *scope_statement) {
	SymbolTableStack **symbol_table_stack = scope_statement->symbol_table_stack;
	Statement *statement_list = scope_statement->statement_list;
	push_symbol_table_stack(symbol_table_stack);
	execute_statement_list(statement_list);
	pop_symbol_table_stack(symbol_table_stack);
}

void print_scope_statement(CompiledFile *compiled_file, ScopeStatement *scope_statement) {

}

void destroy_scope_statement(ScopeStatement *scope_statement) {
	destroy_statement_list(scope_statement->statement_list);
	free(scope_statement);
}