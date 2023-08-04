#include "LiteralExpression.h"

LiteralExpression *create_literal_expression(int type, void *value) {
	LiteralExpression *literal_expression = malloc(sizeof(LiteralExpression));
	literal_expression->type = type;
	literal_expression->value = value;
	return literal_expression;
}

Symbol *evaluate_literal_expression(LiteralExpression *literal_expression) {
	return create_symbol(NULL, literal_expression->type, literal_expression->value);
}

void print_literal_expression(CompiledFile *compiled_file, LiteralExpression *literal_expression) {
	write_indents_to_compiled_file(compiled_file);
	compiled_file_println(compiled_file, "create_literal_expression(");
	compiled_file_increase_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	compiled_file_println(compiled_file, "%s, ", get_symbol_type_as_string(literal_expression->type));
	write_indents_to_compiled_file(compiled_file);
	switch (literal_expression->type) {
		case TYPE_INT: {
			compiled_file_println(compiled_file, "pointer_to_int(%d)", *((int *) literal_expression->value));
			break;
		} case TYPE_CHAR: {
			compiled_file_println(compiled_file, "pointer_to_char('%c')", *((char *) literal_expression->value));
			break;
		}
		case TYPE_WORD: {
			compiled_file_println(compiled_file, "pointer_to_word(\"%s\")", (char *) literal_expression->value);
			break;
		}
		case TYPE_SENTENCE: {
			char *sentence = (char *) literal_expression->value;
			int newline_count = 0;
			for (size_t i = 0; i < strlen(sentence); i++)
				if (sentence[i] == '\n')
					newline_count++;
			char *copied = malloc(strlen(sentence) + newline_count + 1);
			size_t j = 0;
			for (size_t i = 0; i < strlen(sentence); i++) {
				if (sentence[i] == '\n') {
					copied[j++] = '\\';
					copied[j++] = 'n';
				} else
					copied[j++] = sentence[i];
			}
			copied[j] = '\0';
			compiled_file_println(compiled_file, "pointer_to_sentence(\"%s\")", copied);
			free(copied);
			break;
		}
		default: {
			compiled_file_println(compiled_file, "NULL");
			break;
		}
	}
	compiled_file_decrease_indent(compiled_file);
	write_indents_to_compiled_file(compiled_file);
	compiled_file_print(compiled_file, ")");
}

void destroy_literal_expression(LiteralExpression *literal_expression) {
	free(literal_expression->value);
	free(literal_expression);
}