#include "LiteralExpression.h"

LiteralExpression *create_literal_expression(int type, void *value) {
	LiteralExpression *literal_expression = malloc(sizeof(LiteralExpression));
	literal_expression->type = type;
	literal_expression->value = value;
	return literal_expression;
}

Symbol *evaluate_literal_expression(LiteralExpression *literal_expression) {
	return create_symbol(NULL, literal_expression->type, literal_expression->value);
}

void print_literal_expression(CompiledFile *compiled_file, LiteralExpression *literal_expression) {

}

void destroy_literal_expression(LiteralExpression *literal_expression) {
	free(literal_expression->value);
	free(literal_expression);
}