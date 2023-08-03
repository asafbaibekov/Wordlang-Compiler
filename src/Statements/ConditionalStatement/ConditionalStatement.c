#include "ConditionalStatement.h"

ConditionalStatement *create_conditional_statement(ConditionalType type, void *data) {
	ConditionalStatement *conditional_statement = malloc(sizeof(ConditionalStatement));
	conditional_statement->type = type;
	conditional_statement->data = data;
	return conditional_statement;
}

bool execute_conditional_statement(ConditionalStatement *conditional_statement) {
	ConditionalType type = conditional_statement->type;
	switch (type) {
		case IF_CONDITIONAL:
			return execute_if_statement(conditional_statement->data);
		case ELSE_CONDITIONAL:
			return execute_else_statement(conditional_statement->data);
		default:
			return false;
	}
}

bool execute_conditional_statement_list(ConditionalStatement *conditional_statement_list) {
	if (conditional_statement_list == NULL) return false;
	bool isExecuted = execute_conditional_statement_list(conditional_statement_list->next);
	if (isExecuted) return true;
	return execute_conditional_statement(conditional_statement_list);
}

void print_conditional_statement(FILE *file, ConditionalStatement *conditional_statement) {

}

void print_conditional_statement_list(FILE *file, ConditionalStatement *conditional_statement_list) {

}

void destroy_conditional_statement(ConditionalStatement *conditional_statement) {
	ConditionalType type = conditional_statement->type;
	switch (type) {
		case IF_CONDITIONAL:
			destroy_if_statement(conditional_statement->data);
			break;
		case ELSE_CONDITIONAL:
			destroy_else_statement(conditional_statement->data);
			break;
		default:
			break;
	}
	free(conditional_statement);
}

void destroy_conditional_statement_list(ConditionalStatement *conditional_statement_list) {
	if (conditional_statement_list == NULL) return;
	destroy_conditional_statement_list(conditional_statement_list->next);
	destroy_conditional_statement(conditional_statement_list);
}