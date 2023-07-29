#include "IdentifierExpression.h"

IdentifierExpression *create_identifier_expression(SymbolTableStack *symbol_table_stack, char *name) {
	IdentifierExpression *identifier_expression = malloc(sizeof(IdentifierExpression));
	identifier_expression->symbol_table_stack = symbol_table_stack;
	if (strlen(name) > 32)
		formatted_yyerror("Variable name too long: %s\n%s", name, "Should be less than or equal to 32 characters");
	identifier_expression->name = name;
	return identifier_expression;
}

Symbol *evaluate_identifier_expression(IdentifierExpression *identifier_expression) {
	SymbolTableStack *symbol_table_stack = identifier_expression->symbol_table_stack;
	char *name = identifier_expression->name;
	Symbol *symbol = find_symbol_in_symbol_table_stack(symbol_table_stack, name);
	if (symbol == NULL)
		formatted_yyerror("Variable %s not declared", name);
	return symbol;
}

void print_identifier_expression(IdentifierExpression *identifier_expression) {
	printf("%s", identifier_expression->name);
}

void destroy_identifier_expression(IdentifierExpression *identifier_expression) {
	free(identifier_expression->name);
	free(identifier_expression);
}