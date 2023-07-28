#ifndef BINARY_EXPRESSION_H
#define BINARY_EXPRESSION_H

#include <stdlib.h>
#include "../../bin/y.tab.h"
#include "../Symbol.h"
#include "../SymbolOperations.h"
#include "Expression.h"

typedef struct Expression Expression;

typedef struct BinaryExpression {
	Expression *left;
	int operator;
	Expression *right;
} BinaryExpression;

BinaryExpression *create_binary_expression(Expression *left, int operator, Expression *right);

Symbol *evaluate_binary_expression(BinaryExpression *binary_expression);

void destroy_binary_expression(BinaryExpression *binary_expression);

#endif // BINARY_EXPRESSION_H