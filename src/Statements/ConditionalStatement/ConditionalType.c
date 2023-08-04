#include "ConditionalType.h"

char *get_conditional_type_as_string(ConditionalType type) {
	switch (type) {
		case IF_CONDITIONAL:	return "IF_CONDITIONAL";
		case ELSE_CONDITIONAL:	return "ELSE_CONDITIONAL";
		default: return "";
	}
}