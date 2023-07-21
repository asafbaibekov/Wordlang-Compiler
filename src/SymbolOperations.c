#include "SymbolOperations.h"

Symbol *perform_unary_minus_operation(Symbol *symbol) {
	if (symbol->type == TYPE_INT) {
		int *integer = malloc(sizeof(int));
		*integer = -(*((int *) symbol->value));
		return create_symbol(NULL, TYPE_INT, integer);
	}
	return NULL;
}

Symbol *perform_binary_minus_operation(Symbol *symbol1, Symbol *symbol2) {
	if (symbol1->type == TYPE_INT && symbol2->type == TYPE_INT) {
		int *integer = malloc(sizeof(int));
		*integer = *((int *) symbol1->value) - *((int *) symbol2->value);
		return create_symbol(NULL, TYPE_INT, integer);
	}
	else if (symbol1->type == TYPE_SENTENCE && symbol2->type == TYPE_WORD) {
		char *sentence = strdup((char *) symbol1->value);
		char *word = (char *) symbol2->value;
		char *word_position = strstr(sentence, word);
		if (word_position != NULL) {
			memmove(word_position, word_position + strlen(word), strlen(word_position + strlen(word)) + 1);
			return create_symbol(NULL, TYPE_SENTENCE, sentence);
		}
		return create_symbol(NULL, TYPE_SENTENCE, sentence);
	}
	else if (symbol1->type == TYPE_SENTENCE && symbol2->type == TYPE_CHAR) {
		char *sentence = strdup((char *) symbol1->value);
		char *character = (char *) symbol2->value;
		char *character_position = strchr(sentence, *character);
		if (character_position != NULL) {
			memmove(character_position, character_position + 1, strlen(character_position + 1) + 1);
			return create_symbol(NULL, TYPE_SENTENCE, sentence);
		}
		return create_symbol(NULL, TYPE_SENTENCE, sentence);
	}
	else if (symbol1->type == TYPE_WORD && symbol2->type == TYPE_CHAR) {
		char *word = strdup((char *) symbol1->value);
		char *character = (char *) symbol2->value;
		char *character_position = strchr(word, *character);
		if (character_position != NULL) {
			memmove(character_position, character_position + 1, strlen(character_position + 1) + 1);
			return create_symbol(NULL, TYPE_WORD, word);
		}
		return create_symbol(NULL, TYPE_WORD, word);
	}
	return NULL;
}

Symbol *perform_binary_plus_operation(Symbol *symbol1, Symbol *symbol2) {
	if (symbol1->type == TYPE_INT && symbol2->type == TYPE_INT) {
		int *integer = malloc(sizeof(int));
		*integer = *((int *) symbol1->value) + *((int *) symbol2->value);
		return create_symbol(NULL, TYPE_INT, integer);
	}
	return NULL;
}

Symbol *perform_unary_operation(int OPERATION, Symbol *symbol) {
	if (symbol == NULL) return NULL;
	switch (OPERATION) {
		case OPERATOR_MINUS:
			return perform_unary_minus_operation(symbol);
		default:
			return NULL;
	}
}

Symbol *perform_binary_operation(Symbol *symbol1, int OPERATION, Symbol *symbol2) {
	if (symbol1 == NULL || symbol2 == NULL) return NULL;
	switch (OPERATION) {
		case OPERATOR_MINUS:
			return perform_binary_minus_operation(symbol1, symbol2);
		case OPERATOR_PLUS:
			return perform_binary_plus_operation(symbol1, symbol2);
		default:
			return NULL;
	}
}
