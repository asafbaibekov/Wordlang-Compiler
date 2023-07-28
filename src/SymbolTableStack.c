#include "SymbolTableStack.h"

void insert_symbol_to_symbol_table_stack(SymbolTableStack *symbol_table_stack, Symbol *symbol) {
	while (symbol != NULL) {
		Symbol *existing_symbol = find_symbol_in_symbol_table_stack(symbol_table_stack, symbol->name);
		if (existing_symbol != NULL) {
			printf("Error: Variable %s already exists in the symbol table\n", symbol->name);
			destroy_symbol_table_stack(&symbol_table_stack);
			free_symbol(symbol);
			exit(1);
		} else {
			Symbol *new_symbol = copy_symbol(symbol);
			new_symbol->next = symbol_table_stack->head;
			symbol_table_stack->head = new_symbol;
		}
		symbol = symbol->next;
	}
}

void print_symbol_table_stack(SymbolTableStack *symbol_table_stack) {
	while (symbol_table_stack != NULL) {
		print_symbol_list(symbol_table_stack->head);
		symbol_table_stack = symbol_table_stack->next;
	}
}

Symbol *find_symbol_in_symbol_table_stack(SymbolTableStack *symbol_table_stack, char *name) {
	SymbolTableStack *currentStack = symbol_table_stack;
	while (currentStack != NULL) {
		Symbol *currentSymbol = currentStack->head;
		while (currentSymbol != NULL) {
			if (strcmp(currentSymbol->name, name) == 0)
				return currentSymbol;
			currentSymbol = currentSymbol->next;
		}
		currentStack = currentStack->next;
	}
	return NULL;
}

void push_symbol_table_stack(SymbolTableStack **symbol_table_stack) {
	SymbolTableStack *new_node = (SymbolTableStack *) malloc(sizeof(SymbolTableStack));
	new_node->head = NULL;
	new_node->next = *symbol_table_stack;
	*symbol_table_stack = new_node;
}

void pop_symbol_table(SymbolTableStack **symbol_table_stack) {
	if (*symbol_table_stack == NULL) return;
	
	SymbolTableStack *head_node = *symbol_table_stack;
	*symbol_table_stack = (*symbol_table_stack)->next;
	
	Symbol *current = head_node->head;
	while (current != NULL) {
		Symbol *next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	free(head_node);
}

void destroy_symbol_table_stack(SymbolTableStack **symbol_table_stack) {
	while (*symbol_table_stack != NULL) {
		pop_symbol_table(symbol_table_stack);
	}
}