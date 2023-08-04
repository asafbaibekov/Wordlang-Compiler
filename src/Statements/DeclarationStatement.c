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

	bool is_symbol_found_on_top = is_symbol_list_in_top_symbol_table(*symbol_table_stack, symbol);
	if (is_symbol_found_on_top)
		formatted_yyerror("Variable %s already declared\n%s", symbol->name, "Cannot declare variable with same name twice");

	if (strlen(symbol->name) > 32)
		formatted_yyerror("Variable name too long: %s\n%s", symbol->name, "Should be less than or equal to 32 characters");

	int type = declaration_statement->type;
	assign_type_to_symbol(symbol, type);
	assign_default_value_to_symbol(symbol);
	append_symbol_to_symbol_table_stack(symbol_table_stack, symbol);
}

void print_declaration_statement(CompiledFile *compiled_file, DeclarationStatement *declaration_statement) {
	compiled_file_println(compiled_file, "create_declaration_statement(");
	compiled_file_increase_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	compiled_file_println(compiled_file, "&symbol_table_stack,");
	print_symbol(compiled_file, declaration_statement->symbol);
	compiled_file_println(compiled_file, ",");
	write_indents_to_compiled_file(compiled_file);
	compiled_file_println(compiled_file, "%s", get_symbol_type_as_string(declaration_statement->type));
	compiled_file_decrease_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	compiled_file_print(compiled_file, ")");
}

void destroy_declaration_statement(DeclarationStatement *declaration_statement) {
	destroy_symbol(declaration_statement->symbol);
	free(declaration_statement);
}