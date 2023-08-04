#include "ConditionalStatement.h"

ConditionalStatement *create_conditional_statement(ConditionalType type, void *data) {
	ConditionalStatement *conditional_statement = malloc(sizeof(ConditionalStatement));
	conditional_statement->type = type;
	conditional_statement->data = data;
	return conditional_statement;
}

ConditionalStatement *create_conditional_statement_list(ConditionalStatement *conditional_statement_list, ConditionalStatement *conditional_statement) {
	conditional_statement_list->next = conditional_statement;
	return conditional_statement_list;
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

void print_conditional_statement(CompiledFile *compiled_file, ConditionalStatement *conditional_statement) {
	if (conditional_statement == NULL) return;
	if (conditional_statement->next != NULL) {
		compiled_file_println(compiled_file, "create_conditional_statement_list(");
		compiled_file_increase_indent(compiled_file);
		write_indents_to_compiled_file(compiled_file);
	}
	compiled_file_println(compiled_file, "create_conditional_statement(");
	compiled_file_increase_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	compiled_file_println(compiled_file, "%s,", get_conditional_type_as_string(conditional_statement->type));
	write_indents_to_compiled_file(compiled_file);
	switch (conditional_statement->type) {
		case IF_CONDITIONAL:
			print_if_statement(compiled_file, conditional_statement->data);
			break;
		case ELSE_CONDITIONAL:
			print_else_statement(compiled_file, conditional_statement->data);
			break;
	}
	compiled_file_println(compiled_file, "");
	compiled_file_decrease_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	compiled_file_print(compiled_file, ")");
	if (conditional_statement->next != NULL)
		compiled_file_print(compiled_file, ",");
}

void print_conditional_statement_list(CompiledFile *compiled_file, ConditionalStatement *conditional_statement_list) {
	if (conditional_statement_list == NULL) return;
	write_indents_to_compiled_file(compiled_file);
	print_conditional_statement(compiled_file, conditional_statement_list);
	compiled_file_println(compiled_file, "");
	print_conditional_statement_list(compiled_file, conditional_statement_list->next);
	if (conditional_statement_list->next == NULL) return;
	if (conditional_statement_list->next->next != NULL)
		compiled_file_println(compiled_file, "");
	compiled_file_decrease_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	compiled_file_print(compiled_file, ")");
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