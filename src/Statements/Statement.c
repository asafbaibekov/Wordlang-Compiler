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
		case LOOP_STATEMENT:
			execute_loop_statement(statement->data);
			break;
		case WHILE_STATEMENT:
			execute_while_statement(statement->data);
			break;
		case CONDITIONAL_STATEMENT:
			execute_conditional_statement_list(statement->data);
			break;
		case SCOPE_STATEMENT:
			execute_scope_statement(statement->data);
			break;
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

void print_statement(Statement *statement, int indent_level) {
	if (statement == NULL) return;
	for (int i = 0; i < indent_level; i++)
		printf("\t");
	switch (statement->type) {
		case LOOP_STATEMENT:
			print_loop_statement(statement->data, indent_level);
			break;
		case WHILE_STATEMENT:
			print_while_statement(statement->data, indent_level);
			break;
		case CONDITIONAL_STATEMENT:
			print_conditional_statement(statement->data, indent_level);
			break;
		case SCOPE_STATEMENT:
			print_scope_statement(statement->data, indent_level);
			break;
		case DECLARATION_STATEMENT:
			print_declaration_statement(statement->data, indent_level);
			break;
		case ASSIGNMENT_STATEMENT:
			print_assignment_statement(statement->data, indent_level);
			break;
		case OUTPUT_STATEMENT:
			print_output_statement(statement->data, indent_level);
			break;
		case INPUT_STATEMENT:
			print_input_statement(statement->data, indent_level);
			break;
		default:
			break;
	}
}

void print_statement_list(Statement *statement_list, int indent_level) {
	if (statement_list == NULL) return;
	print_statement_list(statement_list->next, indent_level);
	print_statement(statement_list, indent_level);
}

void destroy_statement(Statement *statement) {
	switch (statement->type) {
		case LOOP_STATEMENT:
			destroy_loop_statement(statement->data);
			break;
		case WHILE_STATEMENT:
			destroy_while_statement(statement->data);
			break;
		case CONDITIONAL_STATEMENT:
			destroy_conditional_statement(statement->data);
			break;
		case SCOPE_STATEMENT:
			destroy_scope_statement(statement->data);
			break;
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

void destroy_statement_list(Statement *statement_list) {
	if (statement_list == NULL) return;
	destroy_statement_list(statement_list->next);
	destroy_statement(statement_list);
}