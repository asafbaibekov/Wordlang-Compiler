#include "DeclarationStatement.h"

DeclarationStatement *create_declaration_statement(SymbolTableStack **symbol_table_stack, Symbol *symbol, int type) {
	DeclarationStatement *declaration_statement = malloc(sizeof(DeclarationStatement));
	declaration_statement->symbol_table_stack = symbol_table_stack;
	declaration_statement->symbol = symbol;
	declaration_statement->type = type;
	return declaration_statement;
}

void execute_declaration_statement(DeclarationStatement *declaration_statement) {
	SymbolTableStack **symbol_table_stack = declaration_statement->symbol_table_stack;
	Symbol *symbol = declaration_statement->symbol;

	if (strlen(symbol->name) > 32)
		formatted_yyerror("Variable name too long: %s\n%s", symbol->name, "Should be less than or equal to 32 characters");

	int type = declaration_statement->type;
	assign_type_to_symbol(symbol, type);
	insert_symbol_to_symbol_table_stack(*symbol_table_stack, symbol);
}

void destroy_declaration_statement(DeclarationStatement *declaration_statement) {
	free_symbol(declaration_statement->symbol);
	free(declaration_statement);
}