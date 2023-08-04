%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "../src/Symbol.h"
#include "../src/SymbolTableStack.h"
#include "../src/Statements/Statement.h"
#include "../src/Expressions/Expression.h"
#include "../src/CompiledFile.h"

extern int yylex();

extern FILE *yyin;

SymbolTableStack *symbol_table_stack = NULL;
CompiledFile *compiled_file = NULL;

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
	void *statement_val;
	void *expression_val;
}

%token TYPE_INT TYPE_CHAR TYPE_WORD TYPE_SENTENCE TYPE_BOOLEAN

%token SIGN_SEMICOLON SIGN_COMMA
%token KEYWORD_IF KEYWORD_ELSE KEYWORD_WHILE KEYWORD_LOOP KEYWORD_INPUT KEYWORD_OUTPUT
%token SIGN_ASSIGN SIGN_LPAREN SIGN_RPAREN SIGN_LBRACE SIGN_RBRACE
%token OPERATOR_MINUS OPERATOR_PLUS OPERATOR_CONCAT OPERATOR_INDEX OPERATOR_LT OPERATOR_GT OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE OPERATOR_NOT

%nonassoc ELSE
%nonassoc KEYWORD_ELSE

%token<int_val> LITERAL_INTEGER
%token<string_val> LITERAL_CHAR
%token<string_val> LITERAL_WORD LITERAL_SENTENCE
%token<string_val> IDENTIFIER

%type <int_val> type
%type <symbol_val> var_list

%type <expression_val> expression
%type <expression_val> literal
%type <expression_val> identifier
%type <expression_val> unary_expression
%type <expression_val> binary_expression
%type <expression_val> parentheses_expression

%type <statement_val> statement
%type <statement_val> statement_list
%type <statement_val> loop_statement
%type <statement_val> while_statement
%type <statement_val> conditional_statement
%type <statement_val> scope_statement
%type <statement_val> declaration_statement
%type <statement_val> assignment_statement
%type <statement_val> input_statement
%type <statement_val> output_statement

%left OPERATOR_LT
%left OPERATOR_LE
%left OPERATOR_GT
%left OPERATOR_GE
%left OPERATOR_EQ
%left OPERATOR_NE
%left OPERATOR_NOT
%left OPERATOR_PLUS
%left OPERATOR_MINUS
%left OPERATOR_CONCAT
%left OPERATOR_INDEX

%start program

%%

program:
		/* Empty program */
	|	statement_list {
			write_statement_list_to_compiled_file(compiled_file, $1);
		}
	;

statement_list:
		statement {
			$$ = $1;
		}
	|	statement_list statement {
			$$ = create_statement_list($2, $1);
		}
	;

statement:
		loop_statement
	|	while_statement
	|	conditional_statement
	|	scope_statement
	|	declaration_statement SIGN_SEMICOLON {
			$$ = $1;
		}
	|	assignment_statement SIGN_SEMICOLON {
			$$ = $1;
		}
	|	output_statement SIGN_SEMICOLON {
			$$ = $1;
		}
	|	input_statement SIGN_SEMICOLON {
			$$ = $1;
		}
	;

loop_statement:
		KEYWORD_LOOP parentheses_expression statement {
			LoopStatement *loop_statement = create_loop_statement($2, $3);
			$$ = create_statement(LOOP_STATEMENT, loop_statement);
		}
	;

while_statement:
		KEYWORD_WHILE parentheses_expression statement {
			WhileStatement *while_statement = create_while_statement($2, $3);
			$$ = create_statement(WHILE_STATEMENT, while_statement);
		}
	;

conditional_statement:
		KEYWORD_IF parentheses_expression statement %prec ELSE {
			Expression *expression = $2;
			Statement *statement = $3;
			IfStatement *if_statement = create_if_statement(expression, statement);
			ConditionalStatement *conditional_statement = create_conditional_statement(IF_CONDITIONAL, if_statement);
			$$ = create_statement(CONDITIONAL_STATEMENT, conditional_statement);
		}
	|	KEYWORD_IF parentheses_expression statement KEYWORD_ELSE statement {
			IfStatement *if_statement = create_if_statement($2, $3);
			ElseStatement *else_statement = create_else_statement($5);
			ConditionalStatement *if_conditional_statement = create_conditional_statement(IF_CONDITIONAL, if_statement);
			ConditionalStatement *else_conditional_statement = create_conditional_statement(ELSE_CONDITIONAL, else_statement);
			ConditionalStatement *conditional_statement_list = create_conditional_statement_list(else_conditional_statement, if_conditional_statement);
			$$ = create_statement(CONDITIONAL_STATEMENT, conditional_statement_list);
		}
	;

scope_statement:
		SIGN_LBRACE SIGN_RBRACE {
			ScopeStatement *scope_statement = create_scope_statement(&symbol_table_stack, NULL);
			$$ = create_statement(SCOPE_STATEMENT, scope_statement);
		}
	|	SIGN_LBRACE statement SIGN_RBRACE {
			ScopeStatement *scope_statement = create_scope_statement(&symbol_table_stack, $2);
			$$ = create_statement(SCOPE_STATEMENT, scope_statement);
		}
	|	SIGN_LBRACE statement_list statement SIGN_RBRACE {
			Statement *statement_list = $3;
			statement_list->next = $2;
			ScopeStatement *scope_statement = create_scope_statement(&symbol_table_stack, statement_list);
			$$ = create_statement(SCOPE_STATEMENT, scope_statement);
		}
	;

declaration_statement:
		type var_list {
			int type = $1;
			Symbol *symbol = $2;
			DeclarationStatement *declaration_statement = create_declaration_statement(&symbol_table_stack, symbol, type);
			$$ = create_statement(DECLARATION_STATEMENT, declaration_statement);
		}
	;

assignment_statement:
		IDENTIFIER SIGN_ASSIGN expression {
			char *identifier = $1;
			Expression *expression = $3;
			AssignmentStatement *assignment_statement = create_assignment_statement(&symbol_table_stack, identifier, expression);
			$$ = create_statement(ASSIGNMENT_STATEMENT, assignment_statement);
		}
	;
	
input_statement:
		KEYWORD_INPUT expression IDENTIFIER {
			Expression *expression = $2;
			char *identifier = $3;
			InputStatement *input_statement = create_input_statement(&symbol_table_stack, identifier, expression);
			$$ = create_statement(INPUT_STATEMENT, input_statement);
		}
	;

output_statement:
		KEYWORD_OUTPUT expression {
			Expression *expression = $2;
			OutputStatement *output_statement = create_output_statement(expression);
			$$ = create_statement(OUTPUT_STATEMENT, output_statement);
		}
	;

expression:
		literal
	|	unary_expression
	|	binary_expression
	|	identifier
	|	parentheses_expression
	;

parentheses_expression:
		SIGN_LPAREN expression SIGN_RPAREN {
			$$ = $2;
		}
	;

unary_expression:
		OPERATOR_MINUS expression {
			UnaryExpression *unary_expression = create_unary_expression(OPERATOR_MINUS, $2);
			$$ = create_expression(UNARY_EXPRESSION, unary_expression);
		}
	|	OPERATOR_NOT expression {
			UnaryExpression *unary_expression = create_unary_expression(OPERATOR_NOT, $2);
			$$ = create_expression(UNARY_EXPRESSION, unary_expression);
		}
	;

binary_expression:
		expression OPERATOR_MINUS expression {
			BinaryExpression *binary_expression = create_binary_expression($1, OPERATOR_MINUS, $3);
			$$ = create_expression(BINARY_EXPRESSION, binary_expression);
		}
	|	expression OPERATOR_PLUS expression {
			BinaryExpression *binary_expression = create_binary_expression($1, OPERATOR_PLUS, $3);
			$$ = create_expression(BINARY_EXPRESSION, binary_expression);
		}
	|	expression OPERATOR_CONCAT expression {
			BinaryExpression *binary_expression = create_binary_expression($1, OPERATOR_CONCAT, $3);
			$$ = create_expression(BINARY_EXPRESSION, binary_expression);
		}
	|	expression OPERATOR_INDEX expression {
			BinaryExpression *binary_expression = create_binary_expression($1, OPERATOR_INDEX, $3);
			$$ = create_expression(BINARY_EXPRESSION, binary_expression);
		}
	|	expression OPERATOR_LT expression {
			BinaryExpression *binary_expression = create_binary_expression($1, OPERATOR_LT, $3);
			$$ = create_expression(BINARY_EXPRESSION, binary_expression);
		}
	|	expression OPERATOR_LE expression {
			BinaryExpression *binary_expression = create_binary_expression($1, OPERATOR_LE, $3);
			$$ = create_expression(BINARY_EXPRESSION, binary_expression);
		}
	|	expression OPERATOR_GT expression {
			BinaryExpression *binary_expression = create_binary_expression($1, OPERATOR_GT, $3);
			$$ = create_expression(BINARY_EXPRESSION, binary_expression);
		}
	|	expression OPERATOR_GE expression {
			BinaryExpression *binary_expression = create_binary_expression($1, OPERATOR_GE, $3);
			$$ = create_expression(BINARY_EXPRESSION, binary_expression);
		}
	|	expression OPERATOR_EQ expression {
			BinaryExpression *binary_expression = create_binary_expression($1, OPERATOR_EQ, $3);
			$$ = create_expression(BINARY_EXPRESSION, binary_expression);
		}
	|	expression OPERATOR_NE expression {
			BinaryExpression *binary_expression = create_binary_expression($1, OPERATOR_NE, $3);
			$$ = create_expression(BINARY_EXPRESSION, binary_expression);
		}
	;

literal:
		LITERAL_INTEGER {
			int *integer = malloc(sizeof(int));
			*integer = $1;
			LiteralExpression *literal_expression = create_literal_expression(TYPE_INT, integer);
			$$ = create_expression(LITERAL_EXPRESSION, literal_expression);
		}
	|	LITERAL_CHAR {
			if (strlen($1) > 3) {
				free($1);
				formatted_yyerror("Invalid character: %s", $1);
			}
			char *character = malloc(sizeof(char));
			*character = $1[1] == '\'' ? '\0' : $1[1];
			LiteralExpression *literal_expression = create_literal_expression(TYPE_CHAR, character);
			$$ = create_expression(LITERAL_EXPRESSION, literal_expression);
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
			LiteralExpression *literal_expression = create_literal_expression(TYPE_WORD, strdup($1));
			$$ = create_expression(LITERAL_EXPRESSION, literal_expression);
			free($1);
		}
	|	LITERAL_SENTENCE {
			size_t length = strlen($1);
			memmove($1, $1 + 1, length - 2);
			$1[length - 2] = '\n';
			$1[length - 1] = '\0';
			LiteralExpression *literal_expression = create_literal_expression(TYPE_SENTENCE, strdup($1));
			$$ = create_expression(LITERAL_EXPRESSION, literal_expression);
			free($1);
		}
	;

identifier:
		IDENTIFIER {
			char *identifier = $1;
			IdentifierExpression *identifier_expression = create_identifier_expression(&symbol_table_stack, identifier);
			$$ = create_expression(IDENTIFIER_EXPRESSION, identifier_expression);
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
			$$ = create_symbol_list($1, 0, NULL, $3);
		}
	;

%%


int main(int argc, const char *argv[]) {
	compiled_file = create_compiled_file("./", "main");
	push_symbol_table_stack(&symbol_table_stack);
	if (argc > 1) {
		FILE *input_file = fopen(argv[1], "r");
		if (input_file == NULL) { perror("Error opening file"); return 1; }
		yyin = input_file;
	}
	yyparse();
	destroy_symbol_table_stack(&symbol_table_stack);
	close_compiled_file(compiled_file);
	return 0;
}
