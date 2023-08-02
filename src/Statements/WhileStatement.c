#include "WhileStatement.h"

WhileStatement *create_while_statement(Expression *expression, Statement *statement) {
	WhileStatement *while_statement = malloc(sizeof(WhileStatement));
	while_statement->expression = expression;
	while_statement->statement = statement;
	return while_statement;
}

void execute_while_statement(WhileStatement *while_statement) {
	Expression *expression = while_statement->expression;
	Statement *statement = while_statement->statement;

	Symbol *symbol = evaluate_expression(expression);	
	bool value = get_symbol_value_as_bool(symbol);
	while (value) {
		execute_statement_list(statement);
		symbol = evaluate_expression(expression);
		value = get_symbol_value_as_bool(symbol);
	}
}

void print_while_statement(WhileStatement *while_statement, int indent_level) {
	for (int i = 0; i < indent_level; i++)
		printf("\t");
	printf("while (");
	print_expression(while_statement->expression);
	printf(")\n");
	print_statement(while_statement->statement, indent_level + 1);
}

void destroy_while_statement(WhileStatement *while_statement) {
	destroy_expression(while_statement->expression);
	destroy_statement(while_statement->statement);
	free(while_statement);
}