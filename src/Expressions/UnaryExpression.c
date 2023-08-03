#include "UnaryExpression.h"

static char *getOperator(int operator) {
	switch (operator) {
		case OPERATOR_MINUS:	return "-";
		case OPERATOR_NOT:		return "!";
		default:				return "";
	}
}

UnaryExpression *create_unary_expression(int operator, Expression *expression) {
	UnaryExpression *unary_expression = malloc(sizeof(UnaryExpression));
	unary_expression->operator = operator;
	unary_expression->expression = expression;
	return unary_expression;
}

Symbol *evaluate_unary_expression(UnaryExpression *unary_expression) {
	int operator = unary_expression->operator;
	Symbol *symbol = evaluate_expression(unary_expression->expression);

	if (symbol == NULL) return NULL;
	
	Symbol *result_symbol = perform_unary_operation(operator, symbol);
	if (result_symbol == NULL)
		formatted_yyerror("Invalid operation %s on type %s", getOperator(operator), get_symbol_type(symbol));
	return result_symbol;
}

void print_unary_expression(FILE *file, UnaryExpression *unary_expression) {

}

void destroy_unary_expression(UnaryExpression *unary_expression) {
	destroy_expression(unary_expression->expression);
	free(unary_expression);
}