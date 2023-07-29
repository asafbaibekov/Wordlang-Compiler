#include "SymbolTableStack.h"

SymbolTableStack *create_symbol_table_stack() {
	SymbolTableStack *symbol_table_stack = (SymbolTableStack *) malloc(sizeof(SymbolTableStack));
	symbol_table_stack->symbols = NULL;
	symbol_table_stack->top = NULL;
	return symbol_table_stack;
}

void push_symbol_table_stack(SymbolTableStack **symbol_table_stack) {
	SymbolTableStack *new_symbol_table_stack = create_symbol_table_stack();
	new_symbol_table_stack->top = *symbol_table_stack;
	*symbol_table_stack = new_symbol_table_stack;
}

void pop_symbol_table_stack(SymbolTableStack **symbol_table_stack) {
	SymbolTableStack *temp = *symbol_table_stack;
	*symbol_table_stack = (*symbol_table_stack)->top;
	destroy_symbol_list(temp->symbols);
	free(temp);
}

void append_symbol_to_symbol_table_stack(SymbolTableStack **symbol_table_stack, Symbol *symbol) {
	if (symbol_table_stack == NULL) return;
	if (*symbol_table_stack == NULL) return;
	if (symbol == NULL) return;
	Symbol *current = (*symbol_table_stack)->symbols;
	if (current == NULL) {
		(*symbol_table_stack)->symbols = symbol;
		return;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = symbol;
}

Symbol *find_identifier_in_symbol_table_stack(SymbolTableStack *symbol_table_stack, char *identifier) {
	if (symbol_table_stack == NULL) return NULL;
	if (identifier == NULL) return NULL;
	Symbol *current = symbol_table_stack->symbols;
	while (current != NULL) {
		if (strcmp(current->name, identifier) == 0)
			return current;
		current = current->next;
	}
	return find_identifier_in_symbol_table_stack(symbol_table_stack->top, identifier);
}

bool is_symbol_list_in_top_symbol_table(SymbolTableStack *symbol_table_stack, Symbol *symbol_list) {
	if (symbol_table_stack == NULL) return false;
	if (symbol_list == NULL) return false;
	Symbol *current_symbol_list = symbol_list;
	Symbol *current_symbol_list_of_symbol_table_top_stack = symbol_table_stack->symbols;
	while (current_symbol_list != NULL) {
		while (current_symbol_list_of_symbol_table_top_stack != NULL) {
			if (strcmp(current_symbol_list->name, current_symbol_list_of_symbol_table_top_stack->name) == 0)
				return true;
			current_symbol_list_of_symbol_table_top_stack = current_symbol_list_of_symbol_table_top_stack->next;
		}
		current_symbol_list = current_symbol_list->next;
	}
	return false;
}

void destroy_symbol_table_stack(SymbolTableStack **symbol_table_stack) {
	if (symbol_table_stack == NULL) return;
	if (*symbol_table_stack == NULL) return;
	SymbolTableStack *current = *symbol_table_stack;
	while (current != NULL) {
		SymbolTableStack *temp = current;
		current = current->top;
		destroy_symbol_list(temp->symbols);
		free(temp);
	}
	*symbol_table_stack = NULL;
}