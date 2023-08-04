#include "BinaryExpression.h"

static char *getOperator(int operator) {
	switch (operator) {
		case OPERATOR_MINUS:	return "-";
		case OPERATOR_PLUS:		return "+";
		case OPERATOR_CONCAT:	return "#";
		case OPERATOR_INDEX:	return ":";
		case OPERATOR_LT:		return "<";
		case OPERATOR_GT:		return ">";
		case OPERATOR_LE:		return "<=";
		case OPERATOR_GE:		return ">=";
		case OPERATOR_EQ:		return "==";
		case OPERATOR_NE:		return "!=";
		default:				return "";
	}
}

BinaryExpression *create_binary_expression(Expression *left, int operator, Expression *right) {
	BinaryExpression *binary_expression = malloc(sizeof(BinaryExpression));
	binary_expression->left = left;
	binary_expression->operator = operator;
	binary_expression->right = right;
	return binary_expression;
}

Symbol *evaluate_binary_expression(BinaryExpression *binary_expression) {
	Symbol *left_symbol = evaluate_expression(binary_expression->left);
	int operator = binary_expression->operator;
	Symbol *right_symbol = evaluate_expression(binary_expression->right);

	if (left_symbol == NULL || right_symbol == NULL) return NULL;

	Symbol *result_symbol = perform_binary_operation(left_symbol, operator, right_symbol);
	if (result_symbol == NULL)
		formatted_yyerror("Invalid operation on types %s %s %s", get_symbol_type(left_symbol), getOperator(operator), get_symbol_type(right_symbol));
	return result_symbol;
}

void print_binary_expression(CompiledFile *compiled_file, BinaryExpression *binary_expression) {
	write_indents_to_compiled_file(compiled_file);
	compiled_file_println(compiled_file, "create_binary_expression(");
	compiled_file_increase_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	print_expression(compiled_file, binary_expression->left);
	compiled_file_println(compiled_file, ",");
	write_indents_to_compiled_file(compiled_file);
	char *operator = NULL;
	switch (binary_expression->operator) {
		case OPERATOR_MINUS:	operator = "OPERATOR_MINUS";	break;
		case OPERATOR_PLUS:		operator = "OPERATOR_PLUS";		break;
		case OPERATOR_CONCAT:	operator = "OPERATOR_CONCAT";	break;
		case OPERATOR_INDEX:	operator = "OPERATOR_INDEX";	break;
		case OPERATOR_LT:		operator = "OPERATOR_LT";		break;
		case OPERATOR_GT:		operator = "OPERATOR_GT";		break;
		case OPERATOR_LE:		operator = "OPERATOR_LE";		break;
		case OPERATOR_GE:		operator = "OPERATOR_GE";		break;
		case OPERATOR_EQ:		operator = "OPERATOR_EQ";		break;
		case OPERATOR_NE:		operator = "OPERATOR_NE";		break;
		default:				operator = "";					break;
	}
	compiled_file_print(compiled_file, operator);
	compiled_file_println(compiled_file, ",");
	write_indents_to_compiled_file(compiled_file);
	print_expression(compiled_file, binary_expression->right);
	compiled_file_println(compiled_file, "");
	compiled_file_decrease_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	compiled_file_print(compiled_file, ")");
}

void destroy_binary_expression(BinaryExpression *binary_expression) {
	destroy_expression(binary_expression->left);
	destroy_expression(binary_expression->right);
	free(binary_expression);
}