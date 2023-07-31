#include "ElseStatement.h"

ElseStatement *create_else_statement(Statement *statement) {
	ElseStatement *else_statement = malloc(sizeof(ElseStatement));
	else_statement->statement = statement;
	return else_statement;
}

bool execute_else_statement(ElseStatement *else_statement) {
	execute_statement(else_statement->statement);
	return true;
}

void print_else_statement(ElseStatement *else_statement, int indent_level) {
	printf("else\n");
	print_statement(else_statement->statement, indent_level + 1);
}

void destroy_else_statement(ElseStatement *else_statement) {
	destroy_statement(else_statement->statement);
	free(else_statement);
}