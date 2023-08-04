#include "ExpressionType.h"

char *get_expression_type_as_string(ExpressionType type) {
	switch (type) {
		case LITERAL_EXPRESSION:	return "LITERAL_EXPRESSION";
		case IDENTIFIER_EXPRESSION:	return "IDENTIFIER_EXPRESSION";
		case UNARY_EXPRESSION:		return "UNARY_EXPRESSION";
		case BINARY_EXPRESSION:		return "BINARY_EXPRESSION";
	}
}