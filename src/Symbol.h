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

void assign_type_to_symbol(Symbol *symbol, int type);

void print_symbol(Symbol *symbol);

#endif // SYMBOL_H