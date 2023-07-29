#include "OutputStatement.h"

OutputStatement *create_output_statement(Expression *expression) {
	OutputStatement *output_statement = malloc(sizeof(OutputStatement));
	output_statement->expression = expression;
	return output_statement;
}

void execute_output_statement(OutputStatement *output_statement) {
	Expression *expression = output_statement->expression;
	Symbol *symbol = evaluate_expression(expression);
	printf("Output: ");
	print_symbol_value(symbol);
	printf("\n");
}

void print_output_statement(OutputStatement *output_statement, int indent_level) {
	for (int i = 0; i < indent_level; i++)
		printf("\t");
	printf("output ");
	print_expression(output_statement->expression);
	printf(";\n");
}

void destroy_output_statement(OutputStatement *output_statement) {
	destroy_expression(output_statement->expression);
	free(output_statement);
}