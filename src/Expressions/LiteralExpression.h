#ifndef LITERAL_EXPRESSION_H
#define LITERAL_EXPRESSION_H

#include <stdlib.h>
#include "../Symbol.h"

typedef struct LiteralExpression {
	int type;
	void *value;
} LiteralExpression;

LiteralExpression *create_literal_expression(int type, void *value);

Symbol *evaluate_literal_expression(LiteralExpression *literal_expression);

void destroy_literal_expression(LiteralExpression *literal_expression);

#endif // LITERAL_EXPRESSION_H