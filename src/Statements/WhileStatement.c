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

void print_while_statement(CompiledFile *compiled_file, WhileStatement *while_statement) {
	compiled_file_println(compiled_file, "create_while_statement(");
	compiled_file_increase_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	print_expression(compiled_file, while_statement->expression);
	compiled_file_println(compiled_file, ",");
	write_indents_to_compiled_file(compiled_file);
	print_statement(compiled_file, while_statement->statement);
	compiled_file_println(compiled_file, "");
	compiled_file_decrease_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	compiled_file_print(compiled_file, ")");
}

void destroy_while_statement(WhileStatement *while_statement) {
	destroy_expression(while_statement->expression);
	destroy_statement(while_statement->statement);
	free(while_statement);
}
