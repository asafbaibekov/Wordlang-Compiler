#include "StatementType.h"

char *get_statement_type_as_string(StatementType type) {
	switch (type) {
		case LOOP_STATEMENT:		return "LOOP_STATEMENT";
		case WHILE_STATEMENT:		return "WHILE_STATEMENT";
		case CONDITIONAL_STATEMENT:	return "CONDITIONAL_STATEMENT";
		case SCOPE_STATEMENT:		return "SCOPE_STATEMENT";
		case DECLARATION_STATEMENT:	return "DECLARATION_STATEMENT";
		case ASSIGNMENT_STATEMENT:	return "ASSIGNMENT_STATEMENT";
		case OUTPUT_STATEMENT:		return "OUTPUT_STATEMENT";
		case INPUT_STATEMENT:		return "INPUT_STATEMENT";
		default:					return "UNKNOWN_STATEMENT";
	}
}