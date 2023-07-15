%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/SymbolTableStack.h"
#include "../src/Symbol.h"

extern int yylex();

void yyerror(char *msg) {
	fprintf(stderr, "Error: %s\n", msg);
}

SymbolTableStack *symbol_table_stack = NULL;
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

int main() {
	push_symbol_table_stack(&symbol_table_stack);
	yyparse();
	destroy_symbol_table_stack(&symbol_table_stack);
	return 0;
}
