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