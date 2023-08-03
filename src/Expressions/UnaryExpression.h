#ifndef UNARY_EXPRESSION_H
#define UNARY_EXPRESSION_H

#include <stdlib.h>
#include "../../bin/y.tab.h"
#include "../Symbol.h"
#include "../SymbolOperations.h"
#include "Expression.h"

typedef struct Expression Expression;

typedef struct UnaryExpression {
	int operator;
	Expression *expression;
} UnaryExpression;

UnaryExpression *create_unary_expression(int operator, Expression *expression);

Symbol *evaluate_unary_expression(UnaryExpression *unary_expression);

void print_unary_expression(FILE *file, UnaryExpression *unary_expression);

void destroy_unary_expression(UnaryExpression *unary_expression);

#endif // UNARY_EXPRESSION_H