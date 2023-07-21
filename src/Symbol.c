#include "Symbol.h"

Symbol *create_symbol(char *name, int type, void *value) {
	Symbol *symbol = (Symbol *) malloc(sizeof(Symbol));
	if (name != NULL)	symbol->name = strdup(name);
	else				symbol->name = NULL;
	symbol->type = type;
	symbol->value = value;
	symbol->next = NULL;
	return symbol;
}

Symbol *copy_symbol(Symbol *symbol) {
	if (symbol == NULL) return NULL;
	Symbol *new_symbol = create_symbol(symbol->name, symbol->type, symbol->value);
	new_symbol->next = NULL;
	return new_symbol;
}

void assign_type_to_symbol(Symbol *symbol, int type) {
	if (symbol == NULL) return;
	symbol->type = type;
	assign_type_to_symbol(symbol->next, type);
}

void assign_value_to_symbol(Symbol *symbol, void *value) {
	if (symbol == NULL) return;
	symbol->value = value;
}

char *get_symbol_type(Symbol *symbol) {
	if (symbol == NULL) return NULL;
	switch (symbol->type) {
		case TYPE_INT:		return "int";
		case TYPE_CHAR:		return "char";
		case TYPE_WORD:		return "word";
		case TYPE_SENTENCE:	return "sentence";
		default:			return "no_type";
	}
}

void print_symbol(Symbol *symbol) {
	if (symbol == NULL) return;
	
	switch (symbol->type) {
		case TYPE_INT:		printf("int ");			break;
		case TYPE_CHAR:		printf("char ");		break;
		case TYPE_WORD:		printf("word ");		break;
		case TYPE_SENTENCE:	printf("sentence ");	break;
		default:			printf("no_type ");		break;
	}

	if (symbol->name != NULL)
		printf("%s", symbol->name);
	else
		printf("no_name");

	printf(" = ");

	
	if (symbol->value == NULL)
		printf("no_value");
	else
		switch (symbol->type) {
			case TYPE_INT:		printf("%d", *(int *) symbol->value	);	break;
			case TYPE_CHAR:		printf("%c", *(char *) symbol->value);	break;
			case TYPE_WORD:		printf("%s",  (char *) symbol->value);	break;
			case TYPE_SENTENCE:	printf("%s",  (char *) symbol->value);	break;
			default:			printf("unknown"					);	break;
		}
	printf(";\n");
}

void free_symbol(Symbol *symbol) {
	if (symbol == NULL) return;
	free(symbol->name);
	free(symbol);
}