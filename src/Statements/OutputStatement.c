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

void print_output_statement(CompiledFile *compiled_file, OutputStatement *output_statement) {
	compiled_file_println(compiled_file, "create_output_statement(");
	compiled_file_increase_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	print_expression(compiled_file, output_statement->expression);
	compiled_file_println(compiled_file, "");
	compiled_file_decrease_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	compiled_file_print(compiled_file, ")");
}

void destroy_output_statement(OutputStatement *output_statement) {
	destroy_expression(output_statement->expression);
	free(output_statement);
}