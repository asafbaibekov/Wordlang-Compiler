#include "IfStatement.h"

IfStatement *create_if_statement(Expression *expression, Statement *statement) {
	IfStatement *if_statement = malloc(sizeof(IfStatement));
	if_statement->expression = expression;
	if_statement->statement = statement;
	return if_statement;
}

bool execute_if_statement(IfStatement *if_statement) {
	Expression *expression = if_statement->expression;
	Statement *statement = if_statement->statement;

	Symbol *symbol = evaluate_expression(expression);
	bool value = get_symbol_value_as_bool(symbol);
	if (value)
		execute_statement_list(statement);
	return value;
}

void print_if_statement(IfStatement *if_statement, int indent_level) {
	for (int i = 0; i < indent_level; i++)
		printf("\t");
	printf("if (");
	print_expression(if_statement->expression);
	printf(")\n");
	print_statement(if_statement->statement, indent_level + 1);
}

void destroy_if_statement(IfStatement *if_statement) {
	destroy_expression(if_statement->expression);
	destroy_statement(if_statement->statement);
	free(if_statement);
}