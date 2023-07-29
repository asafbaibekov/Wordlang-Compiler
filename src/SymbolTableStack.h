#ifndef SYMBOL_TABLE_STACK_H
#define SYMBOL_TABLE_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Symbol.h"

typedef struct SymbolTableStack {
	Symbol *symbols;
	struct SymbolTableStack *top;
} SymbolTableStack;

SymbolTableStack *create_symbol_table_stack(void);

void push_symbol_table_stack(SymbolTableStack **symbol_table_stack);

void pop_symbol_table_stack(SymbolTableStack **symbol_table_stack);

void append_symbol_to_symbol_table_stack(SymbolTableStack **symbol_table_stack, Symbol *symbol);

Symbol *find_identifier_in_symbol_table_stack(SymbolTableStack *symbol_table_stack, char *identifier);

bool is_symbol_list_in_top_symbol_table(SymbolTableStack *symbol_table_stack, Symbol *symbol_list);

void destroy_symbol_table_stack(SymbolTableStack **symbol_table_stack);

#endif // SYMBOL_TABLE_STACK_H