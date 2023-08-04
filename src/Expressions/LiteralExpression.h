#ifndef LITERAL_EXPRESSION_H
#define LITERAL_EXPRESSION_H

#include <stdlib.h>
#include "../../bin/y.tab.h"
#include "../Symbol.h"
#include "../CompiledFile.h"

typedef struct LiteralExpression {
	int type;
	void *value;
} LiteralExpression;

LiteralExpression *create_literal_expression(int type, void *value);

Symbol *evaluate_literal_expression(LiteralExpression *literal_expression);

void print_literal_expression(CompiledFile *compiled_file, LiteralExpression *literal_expression);

void destroy_literal_expression(LiteralExpression *literal_expression);

#endif // LITERAL_EXPRESSION_H