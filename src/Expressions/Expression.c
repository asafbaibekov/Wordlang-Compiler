#include "Expression.h"

Expression *create_expression(ExpressionType type, void *data) {
	Expression *expression = malloc(sizeof(Expression));
	expression->type = type;
	expression->data = data;
	return expression;
}

Symbol *evaluate_expression(Expression *expression) {
	switch (expression->type) {
		case LITERAL_EXPRESSION:
			return evaluate_literal_expression(expression->data);
		case IDENTIFIER_EXPRESSION:
			return evaluate_identifier_expression(expression->data);
		case UNARY_EXPRESSION:
			return evaluate_unary_expression(expression->data);
		case BINARY_EXPRESSION:
			return evaluate_binary_expression(expression->data);
		default:
			return NULL;
	}
}

void print_expression(CompiledFile *compiled_file, Expression *expression) {
	compiled_file_println(compiled_file, "create_expression(");
	compiled_file_increase_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	compiled_file_println(compiled_file, "%s,", get_expression_type_as_string(expression->type));
	switch (expression->type) {
		case LITERAL_EXPRESSION:
			print_literal_expression(compiled_file, expression->data);
			break;
		case IDENTIFIER_EXPRESSION:
			print_identifier_expression(compiled_file, expression->data);
			break;
		case UNARY_EXPRESSION:
			print_unary_expression(compiled_file, expression->data);
			break;
		case BINARY_EXPRESSION:
			print_binary_expression(compiled_file, expression->data);
			break;
	}
	compiled_file_println(compiled_file, "");
	compiled_file_decrease_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	compiled_file_print(compiled_file, ")");
}

void destroy_expression(Expression *expression) {
	switch (expression->type) {
		case LITERAL_EXPRESSION:
			destroy_literal_expression(expression->data);
			break;
		case IDENTIFIER_EXPRESSION:
			destroy_identifier_expression(expression->data);
			break;
		case UNARY_EXPRESSION:
			destroy_unary_expression(expression->data);
			break;
		case BINARY_EXPRESSION:
			destroy_binary_expression(expression->data);
			break;
	}
	free(expression);
}