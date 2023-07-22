#include "SymbolOperations.h"

static void removeLastCharacter(char **str) {
	if (str == NULL || *str == NULL) return;
	size_t len = strlen(*str);
	if (len == 0) return;
	char *newStr = (char *) malloc(len);
	if (newStr == NULL) {
		free(*str);
		*str = NULL;
		printf("Error: Out of memory\n");
		exit(1);
	}
	strncpy(newStr, *str, len - 1);
	newStr[len - 1] = '\0';
	free(*str);
	*str = newStr;
}

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

Symbol *perform_binary_concat_operation(Symbol *symbol1, Symbol *symbol2) {
	if (symbol1->type == TYPE_CHAR && symbol2->type == TYPE_CHAR) {
		char character1 = *((char *) symbol1->value);
		char character2 = *((char *) symbol2->value);
		if (character1 == ' ' || character2 == ' ') {
			char *sentence = malloc(sizeof(char) * 4);
			sentence[0] = character1;
			sentence[1] = character2;
			sentence[2] = '\n';
			sentence[3] = '\0';
			return create_symbol(NULL, TYPE_SENTENCE, sentence);
		} else {
			char *word = malloc(sizeof(char) * 3);
			word[0] = character1;
			word[1] = character2;
			word[2] = '\0';
			return create_symbol(NULL, TYPE_WORD, word);
		}
	}
	else if (symbol1->type == TYPE_WORD && symbol2->type == TYPE_WORD) {
		char *word1 = (char *) symbol1->value;
		char *word2 = (char *) symbol2->value;
		char *word = malloc(sizeof(char) * (strlen(word1) + strlen(word2) + 1));
		strcpy(word, word1);
		strcat(word, word2);
		word[strlen(word1) + strlen(word2)] = '\0';
		return create_symbol(NULL, TYPE_WORD, word);
	}
	else if (symbol1->type == TYPE_SENTENCE && symbol2->type == TYPE_SENTENCE) {
		char *sentence1 = strdup((char *) symbol1->value);
		char *sentence2 = (char *) symbol2->value;
		removeLastCharacter(&sentence1);
		char *sentence = malloc(sizeof(char) * (strlen(sentence1) + strlen(sentence2) + 2));
		strcpy(sentence, sentence1);
		strcat(sentence, sentence2);
		sentence[strlen(sentence1) + strlen(sentence2)] = '\n';
		sentence[strlen(sentence1) + strlen(sentence2) + 1] = '\0';
		free(sentence1);
		return create_symbol(NULL, TYPE_SENTENCE, sentence);
	}
	else if (symbol1->type == TYPE_CHAR && symbol2->type == TYPE_WORD) {
		char character1 = *((char *) symbol1->value);
		char *word2 = (char *) symbol2->value;
		if (character1 == ' ') {
			char *sentence = malloc(sizeof(char) * (strlen(word2) + 3));
			sentence[0] = character1;
			strcpy(sentence + 1, word2);
			sentence[strlen(word2) + 1] = '\n';
			sentence[strlen(word2) + 2] = '\0';
			return create_symbol(NULL, TYPE_SENTENCE, sentence);
		} else {
			char *word = malloc(sizeof(char) * (strlen(word2) + 2));
			word[0] = character1;
			strcpy(word + 1, word2);
			word[strlen(word2) + 1] = '\0';
			return create_symbol(NULL, TYPE_WORD, word);
		}
	}
	else if (symbol1->type == TYPE_WORD && symbol2->type == TYPE_CHAR) {
		char *word1 = (char *) symbol1->value;
		char character2 = *((char *) symbol2->value);
		if (character2 == ' ') {
			char *sentence = malloc(sizeof(char) * (strlen(word1) + 3));
			strcpy(sentence, word1);
			sentence[strlen(word1)] = character2;
			sentence[strlen(word1) + 1] = '\n';
			sentence[strlen(word1) + 2] = '\0';
			return create_symbol(NULL, TYPE_SENTENCE, sentence);
		} else {
			char *word = malloc(sizeof(char) * (strlen(word1) + 2));
			strcpy(word, word1);
			word[strlen(word1)] = character2;
			word[strlen(word1) + 1] = '\0';
			return create_symbol(NULL, TYPE_WORD, word);
		}
	}
	else if (symbol1->type == TYPE_CHAR && symbol2->type == TYPE_SENTENCE) {
		char character1 = *((char *) symbol1->value);
		char *sentence2 = (char *) symbol2->value;
		char *sentence = malloc(sizeof(char) * (strlen(sentence2) + 2));
		sentence[0] = character1;
		strcpy(sentence + 1, sentence2);
		sentence[strlen(sentence2) + 1] = '\0';
		return create_symbol(NULL, TYPE_SENTENCE, sentence);
	}
	else if (symbol1->type == TYPE_SENTENCE && symbol2->type == TYPE_CHAR) {
		char *sentence1 = strdup((char *) symbol1->value);
		char character2 = *((char *) symbol2->value);
		removeLastCharacter(&sentence1);
		char *sentence = malloc(sizeof(char) * (strlen(sentence1) + 3));
		strcpy(sentence, sentence1);
		sentence[strlen(sentence1)] = character2;
		sentence[strlen(sentence1) + 1] = '\n';
		sentence[strlen(sentence1) + 2] = '\0';
		free(sentence1);
		return create_symbol(NULL, TYPE_SENTENCE, sentence);
	}
	else if (symbol1->type == TYPE_WORD && symbol2->type == TYPE_SENTENCE) {
		char *word1 = (char *) symbol1->value;
		char *sentence2 = (char *) symbol2->value;
		char *sentence = malloc(sizeof(char) * (strlen(word1) + strlen(sentence2) + 1));
		strcpy(sentence, word1);
		strcat(sentence, sentence2);
		sentence[strlen(word1) + strlen(sentence2)] = '\0';
		return create_symbol(NULL, TYPE_SENTENCE, sentence);
	}
	else if (symbol1->type == TYPE_SENTENCE && symbol2->type == TYPE_WORD) {
		char *sentence1 = strdup((char *) symbol1->value);
		char *word2 = (char *) symbol2->value;
		removeLastCharacter(&sentence1);
		// end the result sentence with a \n
		char *sentence = malloc(sizeof(char) * (strlen(sentence1) + strlen(word2) + 2));
		strcpy(sentence, sentence1);
		strcat(sentence, word2);
		sentence[strlen(sentence1) + strlen(word2)] = '\n';
		sentence[strlen(sentence1) + strlen(word2) + 1] = '\0';
		free(sentence1);
		return create_symbol(NULL, TYPE_SENTENCE, sentence);
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
