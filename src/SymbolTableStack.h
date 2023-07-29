#ifndef SYMBOL_TABLE_STACK_H
#define SYMBOL_TABLE_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "Symbol.h"

typedef struct SymbolTableStack {
	Symbol *head;
	struct SymbolTableStack *next;
} SymbolTableStack;

void insert_symbol_to_symbol_table_stack(SymbolTableStack *symbol_table_stack, Symbol *symbol);

void print_symbol_table_stack(SymbolTableStack *symbol_table_stack);

Symbol *find_symbol_in_symbol_table_stack(SymbolTableStack *symbol_table_stack, char *name);

void push_symbol_table_stack(SymbolTableStack **symbol_table_stack);

void pop_symbol_table_stack(SymbolTableStack **symbol_table_stack);

void destroy_symbol_table_stack(SymbolTableStack **symbol_table_stack);

#endif // SYMBOL_TABLE_STACK_H