#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../wordlang.h"

typedef struct Symbol {
	char *name;
	int type;
	void *value;
	struct Symbol *next;
} Symbol;

Symbol *create_symbol(char *name, int type, void *value);

Symbol *create_symbol_list(char *name, int type, void *value, Symbol *next);

void assign_type_to_symbol(Symbol *symbol, int type);

void assign_default_value_to_symbol(Symbol *symbol);

void assign_value_to_symbol(Symbol *symbol, void *value);

char *get_symbol_type(Symbol *symbol);

bool get_symbol_value_as_bool(Symbol *symbol);

void print_symbol_value(Symbol *symbol);

void print_symbol_list(FILE *file, Symbol *symbol);

void print_symbol(FILE *file, Symbol *symbol);

void destroy_symbol(Symbol *symbol);

void destroy_symbol_list(Symbol *symbol);

#endif // SYMBOL_H