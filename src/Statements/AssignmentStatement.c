#include "AssignmentStatement.h"

AssignmentStatement *create_assignment_statement(SymbolTableStack *symbol_table_stack, char *identifier, Expression *expression) {
	AssignmentStatement *assignment_statement = malloc(sizeof(AssignmentStatement));
	assignment_statement->symbol_table_stack = symbol_table_stack;
	assignment_statement->identifier = strdup(identifier);
	assignment_statement->expression = expression;
	return assignment_statement;
}

void execute_assignment_statement(AssignmentStatement *assignment_statement) {
	SymbolTableStack *symbol_table_stack = assignment_statement->symbol_table_stack;
	char *identifier = assignment_statement->identifier;
	
	Symbol *symbol_in_table = find_symbol_in_symbol_table_stack(symbol_table_stack, identifier);
	if (symbol_in_table == NULL)
		formatted_yyerror("Variable %s not declared", identifier);

	Expression *expression = assignment_statement->expression;
	Symbol *symbol = evaluate_expression(expression);

	if (symbol_in_table->type != symbol->type)
		formatted_yyerror("Type mismatch");
	
	switch (symbol->type) {
		case TYPE_INT:
			assign_value_to_symbol(symbol_in_table, malloc(sizeof(int)));
			*((int *) symbol_in_table->value) = *((int *) symbol->value);
			break;
		case TYPE_CHAR: 
			assign_value_to_symbol(symbol_in_table, malloc(sizeof(char)));
			*((char *) symbol_in_table->value) = *((char *) symbol->value);
			break;
		case TYPE_WORD:
			assign_value_to_symbol(symbol_in_table, strdup((char *) symbol->value));
			break;
		case TYPE_SENTENCE:
			assign_value_to_symbol(symbol_in_table, strdup((char *) symbol->value));
			break;
		case TYPE_BOOLEAN:
			assign_value_to_symbol(symbol_in_table, malloc(sizeof(bool)));
			*((bool *) symbol_in_table->value) = *((bool *) symbol->value);
			break;
		default:
			break;
	}
}

void destroy_assignment_statement(AssignmentStatement *assignment_statement) {
	destroy_expression(assignment_statement->expression);
	free(assignment_statement->identifier);
	free(assignment_statement);
}