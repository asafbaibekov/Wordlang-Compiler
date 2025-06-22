#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "./Statements/StatementType.h"

typedef struct CompiledFile {
	char *path;
	char *filename;
	int indent;
	FILE *file;
} CompiledFile;

typedef struct Statement Statement;

void print_statement_list(CompiledFile *compiled_file, Statement *statement_list);

CompiledFile *create_compiled_file(char *path, char *filename);

void write_statement_list_to_compiled_file(CompiledFile *compiled_file, Statement *statement_list);

void write_indents_to_compiled_file(CompiledFile *compiled_file);

void compiled_file_print(CompiledFile *compiled_file, char *format, ...);

void compiled_file_println(CompiledFile *compiled_file, char *format, ...);

void compiled_file_increase_indent(CompiledFile *compiled_file);

void compiled_file_decrease_indent(CompiledFile *compiled_file);

void close_compiled_file(CompiledFile *compiled_file);

#endif // FILE_WRITER_H