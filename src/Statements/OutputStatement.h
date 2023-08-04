#ifndef OUTPUT_STATEMENT_H
#define OUTPUT_STATEMENT_H

#include <stdlib.h>
#include "../CompiledFile.h"
#include "../Expressions/Expression.h"

typedef struct OutputStatement {
	Expression *expression;
} OutputStatement;

OutputStatement *create_output_statement(Expression *expression);

void execute_output_statement(OutputStatement *output_statement);

void print_output_statement(CompiledFile *compiled_file, OutputStatement *output_statement);

void destroy_output_statement(OutputStatement *output_statement);

#endif // OUTPUT_STATEMENT_H