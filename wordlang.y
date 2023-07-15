%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();

void yyerror(char *msg) {
	fprintf(stderr, "Error: %s\n", msg);
}

char *typeToString(int type);

typedef struct Symbol {
	char *name;
	int type;
	void *value;
	struct Symbol *next;
} Symbol;

typedef struct SymbolTableStack {
	Symbol *top;
	struct SymbolTableStack *next;
} SymbolTableStack;

SymbolTableStack *symbol_table_stack = NULL;

Symbol *create_symbol(char *name, int type, void *value);

void assign_type_to_symbol(Symbol *symbol, int type);

void print_symbol(Symbol *symbol);

void insert_symbol(Symbol *symbol);

void print_symbol_table();

Symbol *find_symbol(char *name);

void push_symbol_table();

void pop_symbol_table();

void destroy_symbol_table_stack();
%}

%union {
	int  int_val;
	char char_val;
	char *string_val;
	void *symbol_val;
}

%token TYPE_INT TYPE_CHAR TYPE_WORD TYPE_SENTENCE

%token SIGN_SEMICOLON SIGN_COMMA
%token KEYWORD_IF KEYWORD_ELSE KEYWORD_WHILE KEYWORD_LOOP KEYWORD_INPUT KEYWORD_OUTPUT
%token SIGN_ASSIGN SIGN_LPAREN SIGN_RPAREN SIGN_LBRACE SIGN_RBRACE
%token OPERATOR_MINUS OPERATOR_PLUS OPERATOR_CONCAT OPERATOR_INDEX OPERATOR_LT OPERATOR_GT OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NOT

%token<int_val> LITERAL_INTEGER
%token<char_val> LITERAL_CHAR
%token<string_val> LITERAL_WORD LITERAL_SENTENCE
%token<string_val> IDENTIFIER

%type <int_val> type
%type <symbol_val> var_list

%start program

%%

program: 
		/* Empty program */
	|	statement_list
	;

statement_list:
		statement
	|	statement_list statement
	;

statement:
		var_declaration SIGN_SEMICOLON
	;

var_declaration:
		type var_list {
			Symbol *symbol = $2;
			assign_type_to_symbol(symbol, $1);
			print_symbol(symbol);
		}
	;

type:
		TYPE_INT		{ $$ = TYPE_INT; }
	|	TYPE_CHAR		{ $$ = TYPE_CHAR; }
	|	TYPE_WORD		{ $$ = TYPE_WORD; }
	|	TYPE_SENTENCE	{ $$ = TYPE_SENTENCE; }
	;

var_list:
		IDENTIFIER {
			$$ = create_symbol($1, 0, NULL);
		}
	|	IDENTIFIER SIGN_COMMA var_list {
			Symbol *symbol = create_symbol($1, 0, NULL);
			symbol->next = $3;
			$$ = symbol;
		}
	;

%%

char *typeToString(int type) {
	switch (type) {
		case TYPE_INT:		return "int";
		case TYPE_CHAR: 	return "char";
		case TYPE_WORD: 	return "word";
		case TYPE_SENTENCE:	return "sentence";
		default:			return "unknown";
	}
}

Symbol *create_symbol(char *name, int type, void *value) {
	Symbol *symbol = (Symbol *) malloc(sizeof(Symbol));
	if (name != NULL)	symbol->name = strdup(name);
	else				symbol->name = NULL;
	symbol->type = type;
	symbol->value = value;
	symbol->next = NULL;
	return symbol;
}

void assign_type_to_symbol(Symbol *symbol, int type) {
	if (symbol == NULL) return;
	symbol->type = type;
	assign_type_to_symbol(symbol->next, type);
}

void print_symbol(Symbol *symbol) {
	if (symbol == NULL) return;

	if (symbol->next != NULL) {
		print_symbol(symbol->next);
	}

	switch (symbol->type) {
		case TYPE_INT:		printf("int ");			break;
		case TYPE_CHAR:		printf("char ");		break;
		case TYPE_WORD:		printf("word ");		break;
		case TYPE_SENTENCE:	printf("sentence ");	break;
		default:			printf("no_type ");		break;
	}

	if (symbol->name != NULL)
		printf("%s", symbol->name);
	else
		printf("no_name");

	printf(" = ");

	
	if (symbol->value == NULL)
		printf("no_value");
	else
		switch (symbol->type) {
			case TYPE_INT:		printf("%d", *(int *) symbol->value	);	break;
			case TYPE_CHAR:		printf("%c", *(char *) symbol->value);	break;
			case TYPE_WORD:		printf("%s",  (char *) symbol->value);	break;
			case TYPE_SENTENCE:	printf("%s",  (char *) symbol->value);	break;
			default:			printf("unknown"					);	break;
		}
	printf(";\n");
}

void insert_symbol(Symbol *symbol) {
	if (symbol_table_stack->top != NULL)
		symbol->next = symbol_table_stack->top;
	symbol_table_stack->top = symbol;
}

void print_symbol_table() {
	SymbolTableStack *current_stack = symbol_table_stack;
	while (current_stack != NULL) {
		Symbol *current = current_stack->top;
		while (current != NULL) {
			print_symbol(current);
			current = current->next;
		}
		current_stack = current_stack->next;
	}
}

Symbol *find_symbol(char *name) {
	SymbolTableStack *current_stack = symbol_table_stack;
	while (current_stack != NULL) {
		Symbol *current = current_stack->top;
		while (current != NULL) {
			if (strcmp(current->name, name) == 0) {
				return current;
			}
			current = current->next;
		}
		current_stack = current_stack->next;
	}
	return NULL;
}

void push_symbol_table() {
	SymbolTableStack *new_node = (SymbolTableStack *) malloc(sizeof(SymbolTableStack));
	new_node->top = NULL;
	new_node->next = symbol_table_stack;
	symbol_table_stack = new_node;
}

void pop_symbol_table() {
	if (symbol_table_stack == NULL) return;
	
	SymbolTableStack *top_node = symbol_table_stack;
	symbol_table_stack = symbol_table_stack->next;
	
	Symbol *current = top_node->top;
	while (current != NULL) {
		Symbol *next = current->next;
		free(current->name);
		free(current);
		current = next;
	}
	free(top_node);
}

void destroy_symbol_table_stack() {
	while (symbol_table_stack != NULL) {
		pop_symbol_table();
	}
}

int main() {
	push_symbol_table();
	yyparse();
	destroy_symbol_table_stack();
	return 0;
}
