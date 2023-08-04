#include "IfStatement.h"

IfStatement *create_if_statement(Expression *expression, Statement *statement) {
	IfStatement *if_statement = malloc(sizeof(IfStatement));
	if_statement->expression = expression;
	if_statement->statement = statement;
	return if_statement;
}

bool execute_if_statement(IfStatement *if_statement) {
	Expression *expression = if_statement->expression;
	Statement *statement = if_statement->statement;

	Symbol *symbol = evaluate_expression(expression);
	bool value = get_symbol_value_as_bool(symbol);
	if (value)
		execute_statement_list(statement);
	return value;
}

void print_if_statement(CompiledFile *compiled_file, IfStatement *if_statement) {
	compiled_file_println(compiled_file, "create_if_statement(");
	compiled_file_increase_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	print_expression(compiled_file, if_statement->expression);
	compiled_file_println(compiled_file, ",");
	write_indents_to_compiled_file(compiled_file);
	print_statement(compiled_file, if_statement->statement);
	compiled_file_println(compiled_file, "");
	compiled_file_decrease_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	compiled_file_print(compiled_file, ")");
}

void destroy_if_statement(IfStatement *if_statement) {
	destroy_expression(if_statement->expression);
	destroy_statement(if_statement->statement);
	free(if_statement);
}