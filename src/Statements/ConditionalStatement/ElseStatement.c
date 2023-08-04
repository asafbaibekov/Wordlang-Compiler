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

void print_else_statement(CompiledFile *compiled_file, ElseStatement *else_statement) {

}

void destroy_else_statement(ElseStatement *else_statement) {
	destroy_statement(else_statement->statement);
	free(else_statement);
}