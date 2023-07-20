%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "../src/SymbolTableStack.h"
#include "../src/Symbol.h"

extern int yylex();

SymbolTableStack *symbol_table_stack = NULL;

void yyerror(char *msg) {
	fprintf(stderr, "Error: %s\n", msg);
	destroy_symbol_table_stack(&symbol_table_stack);
}

void formatted_yyerror(const char *format, ...) {
	va_list args;
	va_start(args, format);
	size_t len = vsnprintf(NULL, 0, format, args);
	char *msg = (char *) malloc((len + 1) * sizeof(char));
	vsprintf(msg, format, args);
	va_end(args);
	yyerror(msg);
	free(msg);
	exit(1);
}
%}

%union {
	int  int_val;
	char *string_val;
	void *symbol_val;
}

%token TYPE_INT TYPE_CHAR TYPE_WORD TYPE_SENTENCE

%token SIGN_SEMICOLON SIGN_COMMA
%token KEYWORD_IF KEYWORD_ELSE KEYWORD_WHILE KEYWORD_LOOP KEYWORD_INPUT KEYWORD_OUTPUT
%token SIGN_ASSIGN SIGN_LPAREN SIGN_RPAREN SIGN_LBRACE SIGN_RBRACE
%token OPERATOR_MINUS OPERATOR_PLUS OPERATOR_CONCAT OPERATOR_INDEX OPERATOR_LT OPERATOR_GT OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NOT

%token<int_val> LITERAL_INTEGER
%token<string_val> LITERAL_CHAR
%token<string_val> LITERAL_WORD LITERAL_SENTENCE
%token<string_val> IDENTIFIER

%type <int_val> type
%type <symbol_val> var_list
%type <symbol_val> expression
%type <symbol_val> literal
%type <symbol_val> identifier

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
	|	assignment_statement SIGN_SEMICOLON
	|	output_statement SIGN_SEMICOLON
	;

assignment_statement:
		IDENTIFIER SIGN_ASSIGN expression {
			Symbol *symbol_in_table = find_symbol_in_symbol_table_stack(symbol_table_stack, $1);
			if (symbol_in_table == NULL)
				formatted_yyerror("Variable %s not declared", $1);

			Symbol *literal_symbol = $3;
			if (symbol_in_table->type != literal_symbol->type)
				formatted_yyerror("Type mismatch");

			symbol_in_table->value = literal_symbol->value;
			free_symbol(literal_symbol);
		}
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
	|	identifier
	;

literal:
		LITERAL_INTEGER {
			int *integer = malloc(sizeof(int));
			*integer = $1;
			$$ = create_symbol(NULL, TYPE_INT, integer);;
		}
	|	LITERAL_CHAR {
			if (strlen($1) > 3)
				formatted_yyerror("Invalid character: %s", $1);
			char *character = malloc(sizeof(char));
			*character = $1[1] == '\'' ? '\0' : $1[1];
			$$ = create_symbol(NULL, TYPE_CHAR, character);
			free($1);
		}
	|	LITERAL_WORD {
			size_t length = strlen($1);
			memmove($1, $1 + 1, length - 2);
			$1[length - 2] = '\0';
			if (strchr($1, ' ') != NULL)
				formatted_yyerror("Invalid word: \"%s\"", $1);
			$$ = create_symbol(NULL, TYPE_WORD, strdup($1));
			free($1);
		}
	|	LITERAL_SENTENCE {
			int length = strlen($1);
			memmove($1, $1 + 1, length - 2);
			$1[length - 2] = '\n';
			$1[length - 1] = '\0';
			$$ = create_symbol(NULL, TYPE_SENTENCE, strdup($1));
			free($1);
		}
	;

identifier:
		IDENTIFIER {
			Symbol *symbol = find_symbol_in_symbol_table_stack(symbol_table_stack, $1);
			if (symbol == NULL)
				formatted_yyerror("Variable %s not declared", $1);
			$$ = symbol;
		}
	;

var_declaration:
		type var_list {
			Symbol *symbol = $2;
			assign_type_to_symbol(symbol, $1);
			insert_symbol_to_symbol_table_stack(&symbol_table_stack, symbol);
			free_symbol(symbol);
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
