#include "Statement.h"

Statement *create_statement(StatementType type, void *data) {
	Statement *statement = malloc(sizeof(Statement));
	statement->type = type;
	statement->data = data;
	statement->next = NULL;
	return statement;
}

void execute_statement(Statement *statement) {
	switch (statement->type) {
		case DECLARATION_STATEMENT:
			execute_declaration_statement(statement->data);
			break;
		case ASSIGNMENT_STATEMENT:
			execute_assignment_statement(statement->data);
			break;
		case OUTPUT_STATEMENT:
			execute_output_statement(statement->data);
			break;
		case INPUT_STATEMENT:
			execute_input_statement(statement->data);
			break;
		default:
			break;
	}
}

void execute_statement_list(Statement *statement_list) {
	if (statement_list == NULL) { return; }
	execute_statement_list(statement_list->next);
	execute_statement(statement_list);
}

void destroy_statement(Statement *statement) {
	switch (statement->type) {
		case DECLARATION_STATEMENT:
			destroy_declaration_statement(statement->data);
			break;
		case ASSIGNMENT_STATEMENT:
			destroy_assignment_statement(statement->data);
			break;
		case OUTPUT_STATEMENT:
			destroy_output_statement(statement->data);
			break;
		case INPUT_STATEMENT:
			destroy_input_statement(statement->data);
			break;
		default:
			break;
	}
	free(statement);
}