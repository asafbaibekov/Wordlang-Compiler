#include "AssignmentStatement.h"

static char *get_type_name(int type) {
	switch (type) {
		case TYPE_INT:		return "int";
		case TYPE_CHAR: 	return "char";
		case TYPE_WORD: 	return "word";
		case TYPE_SENTENCE:	return "sentence";
		case TYPE_BOOLEAN:	return "boolean";
		default:			return "unknown";
	}
}

AssignmentStatement *create_assignment_statement(SymbolTableStack **symbol_table_stack, char *identifier, Expression *expression) {
	AssignmentStatement *assignment_statement = malloc(sizeof(AssignmentStatement));
	assignment_statement->symbol_table_stack = symbol_table_stack;
	assignment_statement->identifier = strdup(identifier);
	assignment_statement->expression = expression;
	return assignment_statement;
}

void execute_assignment_statement(AssignmentStatement *assignment_statement) {
	SymbolTableStack **symbol_table_stack = assignment_statement->symbol_table_stack;
	char *identifier = assignment_statement->identifier;
	Expression *expression = assignment_statement->expression;

	Symbol *symbol_in_table = find_identifier_in_symbol_table_stack(*symbol_table_stack, identifier);
	if (symbol_in_table == NULL)
		formatted_yyerror("Variable %s not declared", identifier);

	Symbol *symbol = evaluate_expression(expression);

	if (symbol_in_table->type != symbol->type)
		formatted_yyerror("Type mismatch, cannot assign %s <- %s", get_type_name(symbol_in_table->type), get_type_name(symbol->type));
	
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

void print_assignment_statement(AssignmentStatement *assignment_statement, int indent_level) {
	for (int i = 0; i < indent_level; i++)
		printf("\t");
	printf("%s = ", assignment_statement->identifier);
	print_expression(assignment_statement->expression);
	printf(";\n");
}

void destroy_assignment_statement(AssignmentStatement *assignment_statement) {
	destroy_expression(assignment_statement->expression);
	free(assignment_statement->identifier);
	free(assignment_statement);
}