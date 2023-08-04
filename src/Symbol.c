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

Symbol *create_symbol_list(char *name, int type, void *value, Symbol *next) {
	Symbol *symbol = create_symbol(name, type, value);
	symbol->next = next;
	return symbol;
}

void assign_type_to_symbol(Symbol *symbol, int type) {
	if (symbol == NULL) return;
	symbol->type = type;
	assign_type_to_symbol(symbol->next, type);
}

void assign_default_value_to_symbol(Symbol *symbol) {
	if (symbol == NULL) return;
	switch (symbol->type) {
		case TYPE_INT: {
			int *integer = (int *) malloc(sizeof(int));
			*integer = 0;
			assign_value_to_symbol(symbol, integer);
			break;
		} case TYPE_CHAR: {
			char *character = (char *) malloc(sizeof(char));
			*character = '\0';
			assign_value_to_symbol(symbol, character);
			break;
		} case TYPE_WORD: {
			char *word = strdup("");
			assign_value_to_symbol(symbol, word);
			break;
		} case TYPE_SENTENCE: {
			char *sentence = strdup("\n");
			assign_value_to_symbol(symbol, sentence);
			break;
		} case TYPE_BOOLEAN: {
			bool *boolean = (bool *) malloc(sizeof(bool));
			*boolean = false;
			assign_value_to_symbol(symbol, (int *) boolean);
			break;
		} default:
			break;
	}
	assign_default_value_to_symbol(symbol->next);
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
		case TYPE_BOOLEAN:	return "boolean";
		default:			return "no_type";
	}
}

bool get_symbol_value_as_bool(Symbol *symbol) {
	if (symbol == NULL) return false;
	switch (symbol->type) {
		case TYPE_INT:		return *((int *) symbol->value) != 0;
		case TYPE_CHAR:		return *((char *) symbol->value) != '\0';
		case TYPE_WORD:		return strlen((char *) symbol->value) > 0;
		case TYPE_SENTENCE: {
			char *sentence = (char *) symbol->value;
			size_t length = strlen(sentence);
			if (length == 1 && sentence[0] == '\n') return false;
			return length > 0;
		}
		case TYPE_BOOLEAN:	return *((bool *) symbol->value);
		default:			return false;
	}
}

void print_symbol_value(Symbol *symbol) {
	if (symbol == NULL) return;
	switch (symbol->type) {
		case TYPE_INT:		printf("%d", *((int *) symbol->value)); break;
		case TYPE_CHAR: 	printf("%c", *((char *) symbol->value)); break;
		case TYPE_WORD: 	printf("%s",  (char *) symbol->value); break;
		case TYPE_SENTENCE: printf("%s",  (char *) symbol->value); break;
		case TYPE_BOOLEAN:	printf("%s", *(bool *) symbol->value ? "true" : "false"); break;
		default: break;
	}
}

void print_symbol_list(CompiledFile *compiled_file, Symbol *symbol) {
	if (symbol == NULL) return;
	print_symbol_list(compiled_file, symbol->next);
	print_symbol(compiled_file, symbol);
}

void print_symbol(CompiledFile *compiled_file, Symbol *symbol) {
	if (symbol == NULL) return;
	char *name = symbol->name;
	char *type = get_symbol_type_as_string(symbol->type);
	write_indents_to_compiled_file(compiled_file);
	if (symbol->next == NULL) {
		compiled_file_print(compiled_file, "create_symbol(\"%s\", %s, NULL)", name, type);
		return;
	}
	compiled_file_println(compiled_file, "create_symbol_list(");
	compiled_file_increase_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	compiled_file_println(compiled_file, "\"%s\", %s, NULL,", name, type);
	print_symbol(compiled_file, symbol->next);
	compiled_file_println(compiled_file, "");
	compiled_file_decrease_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	compiled_file_print(compiled_file, ")");
}

void destroy_symbol(Symbol *symbol) {
	if (symbol == NULL) return;
	if (symbol->name != NULL) free(symbol->name);
	if (symbol->value != NULL) free(symbol->value);
	free(symbol);
}

void destroy_symbol_list(Symbol *symbol) {
	if (symbol == NULL) return;
	destroy_symbol_list(symbol->next);
	destroy_symbol(symbol);
}

void *pointer_to_int(int value) {
	int *integer = (int *) malloc(sizeof(int));
	*integer = value;
	return integer;
}

void *pointer_to_char(char value) {
	char *character = (char *) malloc(sizeof(char));
	*character = value;
	return character;
}

void *pointer_to_word(char *value) {
	return strdup(value);
}

void *pointer_to_sentence(char *value) {
	return strdup(value);
}

char *get_symbol_type_as_string(int type) {
	switch (type) {
		case TYPE_INT:		return "TYPE_INT";
		case TYPE_CHAR:		return "TYPE_CHAR";
		case TYPE_WORD:		return "TYPE_WORD";
		case TYPE_SENTENCE:	return "TYPE_SENTENCE";
		case TYPE_BOOLEAN:	return "TYPE_BOOLEAN";
		default:			return "0";
	}
}