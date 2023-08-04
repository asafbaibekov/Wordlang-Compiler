#ifndef CONDITIONAL_TYPE_H
#define CONDITIONAL_TYPE_H

typedef enum ConditionalType {
	IF_CONDITIONAL,
	ELSE_CONDITIONAL
} ConditionalType;

char *get_conditional_type_as_string(ConditionalType type);

#endif // CONDITIONAL_TYPE_H