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

static size_t countWords(const char *str) {
	size_t wordCount = 0;
	int inWord = 0;
	while (*str) {
		if (*str == ' ' || *str == '\t' || *str == '\n') {
			inWord = 0;
		} else if (inWord == 0) {
			inWord = 1;
			wordCount++;
		}
		str++;
	}
	return wordCount;
}

static char *reverseString(const char *str) {
	if (str == NULL) return NULL;
	size_t length = strlen(str);
	char *reversedStr = (char *) malloc((length + 1) * sizeof(char));
	if (reversedStr == NULL) { printf("Error: Memory allocation failed\n"); exit(1); }
	size_t left = 0;
	size_t right = length - 1;
	while (left < length) {
		reversedStr[left] = str[right];
		left++;
		right--;
	}
	reversedStr[length] = '\0';
	return reversedStr;
}

static char *getWordAtReversedIndex(char *string, int index) {
	size_t number_of_words = countWords(string);
	if (index > number_of_words)
		return NULL;
	char *copy = reverseString(string);
	char *token = strdup(strtok(copy, " "));
	int currentIndex = 1;
	while (token != NULL) {
		if (index == currentIndex) {
			char *reversed = reverseString(token);
			free(token);
			free(copy);
			return reversed;
		}
		currentIndex++;
		free(token);
		token = strtok(NULL, " ");
		if (token != NULL)
			token = strdup(token);
	}
	free(copy);
	return NULL;
}

static char *getWordAtIndex(char *string, int index) {
	char *copy = strdup(string);
	char *word = strdup(strtok(copy, " "));
	while (index > 0 && word != NULL) {
		free(word);
		char *token = strtok(NULL, " ");
		word = (token != NULL) ? strdup(token) : NULL;
		index--;
	}
	free(copy);
	return (word != NULL) ? word : NULL;
}

Symbol *perform_unary_minus_operation(Symbol *symbol) {
	if (symbol->type == TYPE_INT) {
		int *integer = malloc(sizeof(int));
		*integer = -(*((int *) symbol->value));
		return create_symbol(NULL, TYPE_INT, integer);
	}
	return NULL;
}

Symbol *perform_unary_not_operation(Symbol *symbol) {
	if (symbol->type != TYPE_BOOLEAN) 
		return NULL;
	bool *boolean = malloc(sizeof(bool));
	*boolean = !(*((bool *) symbol->value));
	return create_symbol(NULL, TYPE_BOOLEAN, boolean);
}

Symbol *perform_binary_minus_operation(Symbol *symbol1, Symbol *symbol2) {
	if (symbol1->type == TYPE_INT && symbol2->type == TYPE_INT) {
		int *integer = malloc(sizeof(int));
		*integer = *((int *) symbol1->value) - *((int *) symbol2->value);
		return create_symbol(NULL, TYPE_INT, integer);
	}
	else if (symbol1->type == TYPE_CHAR && symbol2->type == TYPE_CHAR) {
		char *character = malloc(sizeof(char));
		*character = '\0';
		if (*((char *) symbol1->value) != *((char *) symbol2->value))
			*character = *((char *) symbol1->value);
		return create_symbol(NULL, TYPE_CHAR, character);
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
		char *sentence = malloc(sizeof(char) * (strlen(sentence1) + strlen(sentence2) + 1));
		strcpy(sentence, sentence1);
		strcat(sentence, sentence2);
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
		if (character2 != '\0')
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
		char *sentence = malloc(sizeof(char) * (strlen(word1) + strlen(sentence2) + 2));
		strcpy(sentence, word1);
		strcat(sentence, " ");
		strcat(sentence, sentence2);
		sentence[strlen(word1) + strlen(sentence2) + 1] = '\0';
		return create_symbol(NULL, TYPE_SENTENCE, sentence);
	}
	else if (symbol1->type == TYPE_SENTENCE && symbol2->type == TYPE_WORD) {
		char *sentence1 = strdup((char *) symbol1->value);
		char *word2 = (char *) symbol2->value;
		removeLastCharacter(&sentence1);
		char *sentence = malloc(sizeof(char) * (strlen(sentence1) + strlen(word2) + 3));
		strcpy(sentence, sentence1);
		strcat(sentence, " ");
		strcat(sentence, word2);
		sentence[strlen(sentence1) + strlen(word2) + 1] = '\n';
		sentence[strlen(sentence1) + strlen(word2) + 2] = '\0';
		free(sentence1);
		return create_symbol(NULL, TYPE_SENTENCE, sentence);
	}
	return NULL;
}

Symbol *perform_binary_index_operation(Symbol *symbol1, Symbol *symbol2) {
	if (symbol1->type != TYPE_CHAR && symbol1->type != TYPE_WORD && symbol1->type != TYPE_SENTENCE) return NULL;

	if (symbol2->type != TYPE_INT) return NULL;
	int index = *((int *) symbol2->value);

	switch (symbol1->type) {
		case TYPE_CHAR: {
			char *character = malloc(sizeof(char));
			*character = (index == 0) ? *((char *) symbol1->value) : '\0';
			return create_symbol(NULL, TYPE_CHAR, character);
		}
		case TYPE_WORD: {
			char *word = strdup((char *) symbol1->value);
			size_t wordLength = strlen(word);
			char *character = malloc(sizeof(char));
			if (index >= 0)
				*character = (index < wordLength) ? word[index] : '\0';
			else {
				*character = (index >= -wordLength) ? word[wordLength + index] : '\0';
			}
			free(word);
			return create_symbol(NULL, TYPE_CHAR, character);
		}
		case TYPE_SENTENCE: {
			char *sentence = strdup((char *) symbol1->value);
			removeLastCharacter(&sentence);
			char *word = NULL;
			if (index >= 0) {
				word = getWordAtIndex(sentence, index);
			} else {
				word = getWordAtReversedIndex(sentence, -index);
			}
			free(sentence);
			if (word == NULL)
				return create_symbol(NULL, TYPE_WORD, strdup(""));
			return create_symbol(NULL, TYPE_WORD, word);
		}
		default: {
			return NULL;
		}
	}
}

Symbol *perform_binary_lt_operation(Symbol *symbol1, Symbol *symbol2) {
	bool *boolean = malloc(sizeof(bool));
	if (symbol1->type == TYPE_INT && symbol2->type == TYPE_INT)
		*boolean = *((int *) symbol1->value) < *((int *) symbol2->value);
	else if (symbol1->type == TYPE_CHAR && symbol2->type == TYPE_CHAR)
		*boolean = *((char *) symbol1->value) < *((char *) symbol2->value);
	else if (symbol1->type == TYPE_WORD && symbol2->type == TYPE_WORD)
		*boolean = strcmp((char *) symbol1->value, (char *) symbol2->value) < 0;
	else if (symbol1->type == TYPE_SENTENCE && symbol2->type == TYPE_SENTENCE)
		*boolean = strcmp((char *) symbol1->value, (char *) symbol2->value) < 0;
	else {
		free(boolean);
		return NULL;
	}
	return create_symbol(NULL, TYPE_BOOLEAN, boolean);
}

Symbol *perform_binary_le_operation(Symbol *symbol1, Symbol *symbol2) {
	bool *boolean = malloc(sizeof(bool));
	if (symbol1->type == TYPE_INT && symbol2->type == TYPE_INT)
		*boolean = *((int *) symbol1->value) <= *((int *) symbol2->value);
	else if (symbol1->type == TYPE_CHAR && symbol2->type == TYPE_CHAR)
		*boolean = *((char *) symbol1->value) <= *((char *) symbol2->value);
	else if (symbol1->type == TYPE_WORD && symbol2->type == TYPE_WORD)
		*boolean = strcmp((char *) symbol1->value, (char *) symbol2->value) <= 0;
	else if (symbol1->type == TYPE_SENTENCE && symbol2->type == TYPE_SENTENCE)
		*boolean = strcmp((char *) symbol1->value, (char *) symbol2->value) <= 0;
	else {
		free(boolean);
		return NULL;
	}
	return create_symbol(NULL, TYPE_BOOLEAN, boolean);
}

Symbol *perform_binary_gt_operation(Symbol *symbol1, Symbol *symbol2) {
	bool *boolean = malloc(sizeof(bool));
	if (symbol1->type == TYPE_INT && symbol2->type == TYPE_INT)
		*boolean = *((int *) symbol1->value) > *((int *) symbol2->value);
	else if (symbol1->type == TYPE_CHAR && symbol2->type == TYPE_CHAR)
		*boolean = *((char *) symbol1->value) > *((char *) symbol2->value);
	else if (symbol1->type == TYPE_WORD && symbol2->type == TYPE_WORD)
		*boolean = strcmp((char *) symbol1->value, (char *) symbol2->value) > 0;
	else if (symbol1->type == TYPE_SENTENCE && symbol2->type == TYPE_SENTENCE)
		*boolean = strcmp((char *) symbol1->value, (char *) symbol2->value) > 0;
	else {
		free(boolean);
		return NULL;
	}
	return create_symbol(NULL, TYPE_BOOLEAN, boolean);
}

Symbol *perform_binary_ge_operation(Symbol *symbol1, Symbol *symbol2) {
	bool *boolean = malloc(sizeof(bool));
	if (symbol1->type == TYPE_INT && symbol2->type == TYPE_INT)
		*boolean = *((int *) symbol1->value) >= *((int *) symbol2->value);
	else if (symbol1->type == TYPE_CHAR && symbol2->type == TYPE_CHAR)
		*boolean = *((char *) symbol1->value) >= *((char *) symbol2->value);
	else if (symbol1->type == TYPE_WORD && symbol2->type == TYPE_WORD)
		*boolean = strcmp((char *) symbol1->value, (char *) symbol2->value) >= 0;
	else if (symbol1->type == TYPE_SENTENCE && symbol2->type == TYPE_SENTENCE)
		*boolean = strcmp((char *) symbol1->value, (char *) symbol2->value) >= 0;
	else {
		free(boolean);
		return NULL;
	}
	return create_symbol(NULL, TYPE_BOOLEAN, boolean);
}

Symbol *perform_binary_eq_operation(Symbol *symbol1, Symbol *symbol2) {
	bool *boolean = malloc(sizeof(bool));
	if (symbol1->type == TYPE_INT && symbol2->type == TYPE_INT)
		*boolean = *((int *) symbol1->value) == *((int *) symbol2->value);
	else if (symbol1->type == TYPE_CHAR && symbol2->type == TYPE_CHAR)
		*boolean = *((char *) symbol1->value) == *((char *) symbol2->value);
	else if (symbol1->type == TYPE_WORD && symbol2->type == TYPE_WORD)
		*boolean = strcmp((char *) symbol1->value, (char *) symbol2->value) == 0;
	else if (symbol1->type == TYPE_SENTENCE && symbol2->type == TYPE_SENTENCE)
		*boolean = strcmp((char *) symbol1->value, (char *) symbol2->value) == 0;
	else {
		free(boolean);
		return NULL;
	}
	return create_symbol(NULL, TYPE_BOOLEAN, boolean);
}

Symbol *perform_binary_ne_operation(Symbol *symbol1, Symbol *symbol2) {
	bool *boolean = malloc(sizeof(bool));
	if (symbol1->type == TYPE_INT && symbol2->type == TYPE_INT)
		*boolean = *((int *) symbol1->value) != *((int *) symbol2->value);
	else if (symbol1->type == TYPE_CHAR && symbol2->type == TYPE_CHAR)
		*boolean = *((char *) symbol1->value) != *((char *) symbol2->value);
	else if (symbol1->type == TYPE_WORD && symbol2->type == TYPE_WORD)
		*boolean = strcmp((char *) symbol1->value, (char *) symbol2->value) != 0;
	else if (symbol1->type == TYPE_SENTENCE && symbol2->type == TYPE_SENTENCE)
		*boolean = strcmp((char *) symbol1->value, (char *) symbol2->value) != 0;
	else {
		free(boolean);
		return NULL;
	}
	return create_symbol(NULL, TYPE_BOOLEAN, boolean);
}

Symbol *perform_unary_operation(int OPERATION, Symbol *symbol) {
	if (symbol == NULL) return NULL;
	switch (OPERATION) {
		case OPERATOR_MINUS:
			return perform_unary_minus_operation(symbol);
		case OPERATOR_NOT:
			return perform_unary_not_operation(symbol);
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
		case OPERATOR_CONCAT:
			return perform_binary_concat_operation(symbol1, symbol2);
		case OPERATOR_INDEX:
			return perform_binary_index_operation(symbol1, symbol2);
		case OPERATOR_LT:
			return perform_binary_lt_operation(symbol1, symbol2);
		case OPERATOR_LE:
			return perform_binary_le_operation(symbol1, symbol2);
		case OPERATOR_GT:
			return perform_binary_gt_operation(symbol1, symbol2);
		case OPERATOR_GE:
			return perform_binary_ge_operation(symbol1, symbol2);
		case OPERATOR_EQ:
			return perform_binary_eq_operation(symbol1, symbol2);
		case OPERATOR_NE:
			return perform_binary_ne_operation(symbol1, symbol2);
		default:
			return NULL;
	}
}
