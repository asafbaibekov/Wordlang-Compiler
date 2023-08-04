#include "InputStatement.h"

static char *readline() {
	size_t size = 64;
	char *str = malloc(size);
	size_t i = 0;
	char c = getchar();
	while (c == '\n') c = getchar();
	while (c != '\n' && c != EOF) {
		if (i == size) {
			size += 64;
			char *new_str = realloc(str, size);
			if (!new_str) {
				free(str);
				return NULL;
			}
			str = new_str;
		}
		str[i++] = c;
		c = getchar();
	}
	str[i] = '\0';
	char *new_str = realloc(str, i + 1);
	if (new_str)
		str = new_str;
	return str;
}

InputStatement *create_input_statement(SymbolTableStack **symbol_table_stack, char *identifier, Expression *expression) {
	InputStatement *input_statement = malloc(sizeof(InputStatement));
	input_statement->symbol_table_stack = symbol_table_stack;
	input_statement->identifier = identifier;
	input_statement->expression = expression;
	return input_statement;
}

void execute_input_statement(InputStatement *input_statement) {
	SymbolTableStack **symbol_table_stack = input_statement->symbol_table_stack;
	char *identifier = input_statement->identifier;
	Symbol *symbol = evaluate_expression(input_statement->expression);
	print_symbol_value(symbol);

	Symbol *symbol_in_table = find_identifier_in_symbol_table_stack(*symbol_table_stack, identifier);
	if (symbol_in_table == NULL)
		formatted_yyerror("Variable %s not declared", identifier);

	switch (symbol_in_table->type) {
		case TYPE_INT: {
			int *integer = malloc(sizeof(int));
			fscanf(stdin, "%d", integer);
			symbol_in_table->value = integer;
			break;
		}
		case TYPE_CHAR: {
			char *character = malloc(sizeof(char));
			fscanf(stdin, "%c", character);
			symbol_in_table->value = character;
			break;
		}
		case TYPE_WORD: {
			char *word = readline();
			if (strchr(word, ' ') != NULL) {
				free(word);
				formatted_yyerror("Word cannot contain space character");
			}
			symbol_in_table->value = word;
			break;
		}
		case TYPE_SENTENCE: {
			char *sentence = readline();
			sentence = realloc(sentence, sizeof(char) * (strlen(sentence) + 2));
			sentence[strlen(sentence)] = '\n';
			sentence[strlen(sentence) + 1] = '\0';
			symbol_in_table->value = sentence;
			break;
		}
	}
}

void print_input_statement(CompiledFile *compiled_file, InputStatement *input_statement) {

}

void destroy_input_statement(InputStatement *input_statement) {
	destroy_expression(input_statement->expression);
	free(input_statement);
}