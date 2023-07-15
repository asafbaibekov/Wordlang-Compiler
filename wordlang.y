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
%type <symbol_val> expression
%type <symbol_val> literal

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
	|	output_statement SIGN_SEMICOLON
	;

output_statement:
		KEYWORD_OUTPUT expression {
			printf("Output: ");
			Symbol *symbol = $2;
			switch (symbol->type) {
				case TYPE_INT:		printf("%d", *((int *) symbol->value)); break;
				case TYPE_CHAR: 	printf("%c", *((char *) symbol->value)); break;
				case TYPE_WORD: 	printf("%s",  (char *) symbol->value); break;
				case TYPE_SENTENCE: printf("%s",  (char *) symbol->value); break;
				default: break;
			}
			printf("\n");
		}
	;

expression:
		literal
	;

literal:
		LITERAL_INTEGER {
			int *integer = malloc(sizeof(int));
			*integer = $1;
			$$ = create_symbol(NULL, TYPE_CHAR, integer);;
		}
	|	LITERAL_CHAR {
			char *character = malloc(sizeof(char));
			*character = $1 == '\'' ? '\0' : $1;
			$$ = create_symbol(NULL, TYPE_CHAR, character);
		}
	|	LITERAL_WORD {
			size_t length = strlen($1);
			memmove($1, $1 + 1, length - 2);
			$1[length - 2] = '\0';
			$$ = create_symbol(NULL, TYPE_WORD, strdup($1));
		}
	|	LITERAL_SENTENCE {
			int length = strlen($1);
			memmove($1, $1 + 1, length - 2);
			$1[length - 2] = '\n';
			$1[length - 1] = '\0';
			$$ = create_symbol(NULL, TYPE_SENTENCE, strdup($1));
		}
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
