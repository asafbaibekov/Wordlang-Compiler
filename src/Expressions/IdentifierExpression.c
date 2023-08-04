#include "IdentifierExpression.h"

IdentifierExpression *create_identifier_expression(SymbolTableStack **symbol_table_stack, char *name) {
	IdentifierExpression *identifier_expression = malloc(sizeof(IdentifierExpression));
	identifier_expression->symbol_table_stack = symbol_table_stack;
	if (strlen(name) > 32)
		formatted_yyerror("Variable name too long: %s\n%s", name, "Should be less than or equal to 32 characters");
	identifier_expression->name = name;
	return identifier_expression;
}

Symbol *evaluate_identifier_expression(IdentifierExpression *identifier_expression) {
	SymbolTableStack **symbol_table_stack = identifier_expression->symbol_table_stack;
	char *name = identifier_expression->name;
	Symbol *symbol = find_identifier_in_symbol_table_stack(*symbol_table_stack, name);
	if (symbol == NULL)
		formatted_yyerror("Variable %s not declared", name);
	return symbol;
}

void print_identifier_expression(CompiledFile *compiled_file, IdentifierExpression *identifier_expression) {
	write_indents_to_compiled_file(compiled_file);
	compiled_file_println(compiled_file, "create_identifier_expression(");
	compiled_file_increase_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	compiled_file_println(compiled_file, "&symbol_table_stack,");
	write_indents_to_compiled_file(compiled_file);
	compiled_file_println(compiled_file, "\"%s\"", identifier_expression->name);
	compiled_file_decrease_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	compiled_file_print(compiled_file, ")");
}

void destroy_identifier_expression(IdentifierExpression *identifier_expression) {
	free(identifier_expression->name);
	free(identifier_expression);
}