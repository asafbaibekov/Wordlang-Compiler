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

void print_literal_expression(LiteralExpression *literal_expression) {
	switch (literal_expression->type) {
		case TYPE_INT: {
			int integer = *((int *) literal_expression->value);
			printf("%d", integer * ((integer < 0) ? -1 : 1));
			break;
		}
		case TYPE_CHAR:
			printf("%c", *(char *) literal_expression->value);
			break;
		case TYPE_WORD:
		case TYPE_SENTENCE:
			printf("%s", (char *) literal_expression->value);
			break;
		case TYPE_BOOLEAN:
			printf("%s", *(int *) literal_expression->value ? "true" : "false");
			break;
	}
}

void destroy_literal_expression(LiteralExpression *literal_expression) {
	free(literal_expression->value);
	free(literal_expression);
}