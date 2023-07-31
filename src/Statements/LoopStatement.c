#include "LoopStatement.h"

LoopStatement *create_loop_statement(Expression *expression, Statement *statement) {
	LoopStatement *loop_statement = malloc(sizeof(LoopStatement));
	loop_statement->expression = expression;
	loop_statement->statement = statement;
	return loop_statement;
}

void execute_loop_statement(LoopStatement *loop_statement) {
	Expression *expression = loop_statement->expression;
	Statement *statement = loop_statement->statement;
	
	Symbol *symbol = evaluate_expression(expression);
	if (symbol->type != TYPE_INT)
		formatted_yyerror("Loop statement expression must evaluate to an int");

	int value = *((int *) symbol->value);
	for (int i = value; i > 0; i--)
		execute_statement_list(statement);
}

void print_loop_statement(LoopStatement *loop_statement, int indent_level) {
	for (int i = 0; i < indent_level; i++)
		printf("\t");
	printf("while (");
	print_expression(loop_statement->expression);
	printf(")\n");
	print_statement(loop_statement->statement, indent_level + 1);
}

void destroy_loop_statement(LoopStatement *loop_statement) {
	destroy_expression(loop_statement->expression);
	destroy_statement_list(loop_statement->statement);
	free(loop_statement);
}