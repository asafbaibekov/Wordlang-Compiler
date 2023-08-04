#ifndef EXPRESSION_TYPE_H
#define EXPRESSION_TYPE_H

typedef enum ExpressionType {
	LITERAL_EXPRESSION,
	IDENTIFIER_EXPRESSION,
	UNARY_EXPRESSION,
	BINARY_EXPRESSION
} ExpressionType;

char *get_expression_type_as_string(ExpressionType type);

#endif // EXPRESSION_TYPE_H