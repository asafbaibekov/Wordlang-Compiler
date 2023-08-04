#include "CompiledFile.h"

static void write_headers(CompiledFile *compiled_file) {
	fprintf(compiled_file->file, "#include <stdio.h>\n");
	fprintf(compiled_file->file, "#include <stdlib.h>\n");
	fprintf(compiled_file->file, "#include <string.h>\n");
	fprintf(compiled_file->file, "#include <stdarg.h>\n");
	fprintf(compiled_file->file, "#include \"./src/Symbol.h\"\n");
	fprintf(compiled_file->file, "#include \"./src/SymbolTableStack.h\"\n");
	fprintf(compiled_file->file, "#include \"./src/Statements/Statement.h\"\n");
	fprintf(compiled_file->file, "#include \"./src/Expressions/Expression.h\"\n");
	fprintf(compiled_file->file, "\n\n");
	fprintf(compiled_file->file, "SymbolTableStack *symbol_table_stack = NULL;\n\n");
	fprintf(compiled_file->file, "void formatted_yyerror(const char *format, ...) {\n");
	fprintf(compiled_file->file, "\tva_list args;\n");
	fprintf(compiled_file->file, "\tva_start(args, format);\n");
	fprintf(compiled_file->file, "\tsize_t len = vsnprintf(NULL, 0, format, args);\n");
	fprintf(compiled_file->file, "\tchar *msg = (char *) malloc((len + 1) * sizeof(char));\n");
	fprintf(compiled_file->file, "\tvsprintf(msg, format, args);\n");
	fprintf(compiled_file->file, "\tva_end(args);\n");
	fprintf(compiled_file->file, "\tfprintf(stderr, \"Error: %%s\\n\", msg);\n");
	fprintf(compiled_file->file, "\tdestroy_symbol_table_stack(&symbol_table_stack);\n");
	fprintf(compiled_file->file, "\tfree(msg);\n");
	fprintf(compiled_file->file, "\texit(1);\n");
	fprintf(compiled_file->file, "}\n\n");
}

CompiledFile *create_compiled_file(char *path, char *filename) {
	CompiledFile *compiled_file = malloc(sizeof(CompiledFile));
	compiled_file->path = path;
	compiled_file->filename = filename;
	compiled_file->indent = 0;
	char *full_path = malloc(strlen(path) + strlen(filename) + 4);
	strcpy(full_path, path);
	strcat(full_path, "/");
	strcat(full_path, filename);
	strcat(full_path, ".c");
	compiled_file->file = fopen(full_path, "w");
	if (compiled_file->file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	write_headers(compiled_file);
	return compiled_file;
}

void write_statement_list_to_compiled_file(CompiledFile *compiled_file, Statement *statement_list) {
	fprintf(compiled_file->file, "int main(int argc, const char *argv[]) {\n");
	fprintf(compiled_file->file, 	"\tSymbolTableStack *symbol_table_stack = create_symbol_table_stack();\n");
	fprintf(compiled_file->file, 	"\tpush_symbol_table_stack(&symbol_table_stack);\n");
	
	fprintf(compiled_file->file, "\n");
	compiled_file_increase_indent(compiled_file);
	fprintf(compiled_file->file, "\tStatement *list = ");
	print_statement_list(compiled_file, statement_list);
	fprintf(compiled_file->file, ";\n");
	fprintf(compiled_file->file, "\texecute_statement_list(list);\n");

	fprintf(compiled_file->file, 	"\tdestroy_symbol_table_stack(&symbol_table_stack);\n");
	fprintf(compiled_file->file, "\treturn 0;\n");
	fprintf(compiled_file->file, "}\n");
}

void write_indents_to_compiled_file(CompiledFile *compiled_file) {
	for (int i = 0; i < compiled_file->indent; i++)
		fprintf(compiled_file->file, "\t");
}

void compiled_file_print(CompiledFile *compiled_file, char *format, ...) {
	va_list args;
	va_start(args, format);
	vfprintf(compiled_file->file, format, args);
	va_end(args);
}

void compiled_file_println(CompiledFile *compiled_file, char *format, ...) {
	va_list args;
	va_start(args, format);
	vfprintf(compiled_file->file, format, args);
	fprintf(compiled_file->file, "\n");
	va_end(args);
}

void compiled_file_increase_indent(CompiledFile *compiled_file) {
	compiled_file->indent++;
}

void compiled_file_decrease_indent(CompiledFile *compiled_file) {
	compiled_file->indent--;
}

void close_compiled_file(CompiledFile *compiled_file) {
	fclose(compiled_file->file);
}