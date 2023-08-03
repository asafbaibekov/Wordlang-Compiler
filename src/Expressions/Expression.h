#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <stdio.h>
#include <stdlib.h>
#include "../Symbol.h"

#include "ExpressionType.h"

#include "LiteralExpression.h"
#include "IdentifierExpression.h"
#include "UnaryExpression.h"
#include "BinaryExpression.h"

typedef struct Expression {
	ExpressionType type;
	void *data;
} Expression;

Expression *create_expression(ExpressionType type, void *data);

Symbol *evaluate_expression(Expression *expression);

void print_expression(FILE *file, Expression *expression);

void destroy_expression(Expression *expression);

#endif // EXPRESSION_H