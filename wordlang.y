%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "../src/Symbol.h"
#include "../src/SymbolTableStack.h"
#include "../src/SymbolOperations.h"

extern int yylex();

extern FILE *yyin;

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

%token TYPE_INT TYPE_CHAR TYPE_WORD TYPE_SENTENCE TYPE_BOOLEAN

%token SIGN_SEMICOLON SIGN_COMMA
%token KEYWORD_IF KEYWORD_ELSE KEYWORD_WHILE KEYWORD_LOOP KEYWORD_INPUT KEYWORD_OUTPUT
%token SIGN_ASSIGN SIGN_LPAREN SIGN_RPAREN SIGN_LBRACE SIGN_RBRACE
%token OPERATOR_MINUS OPERATOR_PLUS OPERATOR_CONCAT OPERATOR_INDEX OPERATOR_LT OPERATOR_GT OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE OPERATOR_NOT

%token<int_val> LITERAL_INTEGER
%token<string_val> LITERAL_CHAR
%token<string_val> LITERAL_WORD LITERAL_SENTENCE
%token<string_val> IDENTIFIER

%type <int_val> type
%type <symbol_val> var_list
%type <symbol_val> expression
%type <symbol_val> unary_expression
%type <symbol_val> binary_expression
%type <symbol_val> literal
%type <symbol_val> identifier

%left OPERATOR_PLUS
%left OPERATOR_MINUS
%left OPERATOR_CONCAT
%left OPERATOR_INDEX

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
	|	input_statement SIGN_SEMICOLON
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
	
input_statement:
	KEYWORD_INPUT expression IDENTIFIER {
		Symbol *symbol_in_table = find_symbol_in_symbol_table_stack(symbol_table_stack, $3);
		if (symbol_in_table == NULL)
			formatted_yyerror("Variable %s not declared", $3);
		Symbol *symbol = $2;
		print_symbol_value(symbol);
		if (symbol->name == NULL)
			free_symbol(symbol);
		perform_input_operation(&symbol_in_table);
	}
	;

output_statement:
		KEYWORD_OUTPUT expression {
			printf("Output: ");
			Symbol *symbol = $2;
			print_symbol_value(symbol);
			printf("\n");
		}
	;

expression:
		literal
	|	identifier
	|	unary_expression
	|	binary_expression
	|	SIGN_LPAREN expression SIGN_RPAREN {
			$$ = $2;
		}
	;

unary_expression:
		OPERATOR_MINUS expression {
			Symbol *symbol = $2;
			$$ = perform_unary_operation(OPERATOR_MINUS, symbol);
			if (symbol->name == NULL)
				free_symbol(symbol);
		}
	|	OPERATOR_NOT expression {
			Symbol *symbol = $2;
			$$ = perform_unary_operation(OPERATOR_NOT, symbol);
			if (symbol->name == NULL)
				free_symbol(symbol);
		}
	;

binary_expression:
		expression OPERATOR_MINUS expression {
			Symbol *symbol1 = $1;
			Symbol *symbol2 = $3;
			Symbol *symbol3 = perform_binary_operation(symbol1, OPERATOR_MINUS, symbol2);
			if (symbol3 == NULL)
				formatted_yyerror("Invalid operation on types %s - %s", get_symbol_type(symbol1), get_symbol_type(symbol2));
			$$ = symbol3;
			if (symbol1->name == NULL)
				free_symbol(symbol1);
			if (symbol2->name == NULL)
				free_symbol(symbol2);
		}
	|	expression OPERATOR_PLUS expression {
			Symbol *symbol1 = $1;
			Symbol *symbol2 = $3;
			Symbol *symbol3 = perform_binary_operation(symbol1, OPERATOR_PLUS, symbol2);
			if (symbol3 == NULL)
				formatted_yyerror("Invalid operation on types %s + %s", get_symbol_type(symbol1), get_symbol_type(symbol2));
			$$ = symbol3;
			if (symbol1->name == NULL)
				free_symbol(symbol1);
			if (symbol2->name == NULL)
				free_symbol(symbol2);
		}
	|	expression OPERATOR_CONCAT expression {
			Symbol *symbol1 = $1;
			Symbol *symbol2 = $3;
			Symbol *symbol3 = perform_binary_operation(symbol1, OPERATOR_CONCAT, symbol2);
			if (symbol3 == NULL)
				formatted_yyerror("Invalid operation on types %s # %s", get_symbol_type(symbol1), get_symbol_type(symbol2));
			$$ = symbol3;
			if (symbol1->name == NULL)
				free_symbol(symbol1);
			if (symbol2->name == NULL)
				free_symbol(symbol2);
		}
	|	expression OPERATOR_INDEX expression {
			Symbol *symbol1 = $1;
			Symbol *symbol2 = $3;
			Symbol *symbol3 = perform_binary_operation(symbol1, OPERATOR_INDEX, symbol2);
			if (symbol3 == NULL)
				formatted_yyerror("Invalid operation on types %s : %s", get_symbol_type(symbol1), get_symbol_type(symbol2));
			$$ = symbol3;
			if (symbol1->name == NULL)
				free_symbol(symbol1);
			if (symbol2->name == NULL)
				free_symbol(symbol2);
		}
	|	expression OPERATOR_LT expression {
			Symbol *symbol1 = $1;
			Symbol *symbol2 = $3;
			Symbol *symbol3 = perform_binary_operation(symbol1, OPERATOR_LT, symbol2);
			if (symbol3 == NULL)
				formatted_yyerror("Invalid operation on types %s < %s", get_symbol_type(symbol1), get_symbol_type(symbol2));
			$$ = symbol3;
			if (symbol1->name == NULL)
				free_symbol(symbol1);
			if (symbol2->name == NULL)
				free_symbol(symbol2);
		}
	|	expression OPERATOR_LE expression {
			Symbol *symbol1 = $1;
			Symbol *symbol2 = $3;
			Symbol *symbol3 = perform_binary_operation(symbol1, OPERATOR_LE, symbol2);
			if (symbol3 == NULL)
				formatted_yyerror("Invalid operation on types %s <= %s", get_symbol_type(symbol1), get_symbol_type(symbol2));
			$$ = symbol3;
			if (symbol1->name == NULL)
				free_symbol(symbol1);
			if (symbol2->name == NULL)
				free_symbol(symbol2);
		}
	|	expression OPERATOR_GT expression {
			Symbol *symbol1 = $1;
			Symbol *symbol2 = $3;
			Symbol *symbol3 = perform_binary_operation(symbol1, OPERATOR_GT, symbol2);
			if (symbol3 == NULL)
				formatted_yyerror("Invalid operation on types %s > %s", get_symbol_type(symbol1), get_symbol_type(symbol2));
			$$ = symbol3;
			if (symbol1->name == NULL)
				free_symbol(symbol1);
			if (symbol2->name == NULL)
				free_symbol(symbol2);
		}
	|	expression OPERATOR_GE expression {
			Symbol *symbol1 = $1;
			Symbol *symbol2 = $3;
			Symbol *symbol3 = perform_binary_operation(symbol1, OPERATOR_GE, symbol2);
			if (symbol3 == NULL)
				formatted_yyerror("Invalid operation on types %s >= %s", get_symbol_type(symbol1), get_symbol_type(symbol2));
			$$ = symbol3;
			if (symbol1->name == NULL)
				free_symbol(symbol1);
			if (symbol2->name == NULL)
				free_symbol(symbol2);
		}
	|	expression OPERATOR_EQ expression {
			Symbol *symbol1 = $1;
			Symbol *symbol2 = $3;
			Symbol *symbol3 = perform_binary_operation(symbol1, OPERATOR_EQ, symbol2);
			if (symbol3 == NULL)
				formatted_yyerror("Invalid operation on types %s == %s", get_symbol_type(symbol1), get_symbol_type(symbol2));
			$$ = symbol3;
			if (symbol1->name == NULL)
				free_symbol(symbol1);
			if (symbol2->name == NULL)
				free_symbol(symbol2);
		}
	|	expression OPERATOR_NE expression {
			Symbol *symbol1 = $1;
			Symbol *symbol2 = $3;
			Symbol *symbol3 = perform_binary_operation(symbol1, OPERATOR_NE, symbol2);
			if (symbol3 == NULL)
				formatted_yyerror("Invalid operation on types %s != %s", get_symbol_type(symbol1), get_symbol_type(symbol2));
			$$ = symbol3;
			if (symbol1->name == NULL)
				free_symbol(symbol1);
			if (symbol2->name == NULL)
				free_symbol(symbol2);
		}
	;

literal:
		LITERAL_INTEGER {
			int *integer = malloc(sizeof(int));
			*integer = $1;
			$$ = create_symbol(NULL, TYPE_INT, integer);;
		}
	|	LITERAL_CHAR {
			if (strlen($1) > 3) {
				free($1);
				formatted_yyerror("Invalid character: %s", $1);
			}
			char *character = malloc(sizeof(char));
			*character = $1[1] == '\'' ? '\0' : $1[1];
			$$ = create_symbol(NULL, TYPE_CHAR, character);
			free($1);
		}
	|	LITERAL_WORD {
			size_t length = strlen($1);
			memmove($1, $1 + 1, length - 2);
			$1[length - 2] = '\0';
			if (strchr($1, ' ') != NULL) {
				free($1);
				formatted_yyerror("Invalid word: \"%s\"", $1);
			}
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
			if (strlen(symbol->name) > 32)
				formatted_yyerror("Variable name too long: %s\n%s", symbol->name, "Should be less than or equal to 32 characters");
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


int main(int argc, const char *argv[]) {
	push_symbol_table_stack(&symbol_table_stack);
	if (argc > 1) {
		FILE *input_file = fopen(argv[1], "r");
		if (input_file == NULL) { perror("Error opening file"); return 1; }
		yyin = input_file;
	}
	yyparse();
	destroy_symbol_table_stack(&symbol_table_stack);
	return 0;
}
