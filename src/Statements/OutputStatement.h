#ifndef OUTPUT_STATEMENT_H
#define OUTPUT_STATEMENT_H

#include <stdlib.h>
#include "../Expressions/Expression.h"

typedef struct OutputStatement {
	Expression *expression;
} OutputStatement;

OutputStatement *create_output_statement(Expression *expression);

void execute_output_statement(OutputStatement *output_statement);

void print_output_statement(OutputStatement *output_statement, int indent_level);

void destroy_output_statement(OutputStatement *output_statement);

#endif // OUTPUT_STATEMENT_H