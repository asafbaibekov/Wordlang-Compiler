#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bin/y.tab.h"

typedef struct Symbol {
	char *name;
	int type;
	void *value;
	struct Symbol *next;
} Symbol;

Symbol *create_symbol(char *name, int type, void *value);

Symbol *copy_symbol(Symbol *symbol);

void assign_type_to_symbol(Symbol *symbol, int type);

void assign_value_to_symbol(Symbol *symbol, void *value);

void print_symbol(Symbol *symbol);

void free_symbol(Symbol *symbol);

#endif // SYMBOL_H