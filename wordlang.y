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
	struct Symbol *next;
} Symbol;

Symbol *symbolTable = NULL;
Symbol *createSymbol(char* name, int type);
void addSymbol(Symbol **symbolTable, char *name, int type);
Symbol *lookupSymbol(Symbol *symbolTable, char *name);

%}

%union {
	int  int_val;
	char char_val;
	char *string_val;
}

%token EXIT
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
%type <string_val> var_list

%start program

%%

program: 
		/* Empty program */
	|	statement_list
	;

statement_list:
		statement SIGN_SEMICOLON
	|	statement_list statement SIGN_SEMICOLON
	;

statement:
		var_declaration
	;

var_declaration:
		type var_list
	;

type:
		TYPE_INT		{ $$ = TYPE_INT; }
	|	TYPE_CHAR		{ $$ = TYPE_CHAR; }
	|	TYPE_WORD		{ $$ = TYPE_WORD; }
	|	TYPE_SENTENCE	{ $$ = TYPE_SENTENCE; }
	;

var_list:
		IDENTIFIER
	|	IDENTIFIER SIGN_COMMA var_list
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

Symbol *createSymbol(char* name, int type) {
	Symbol *newSymbol = (Symbol *) malloc(sizeof(Symbol));
	newSymbol->name = strdup(name);
	newSymbol->type = type;
	newSymbol->next = NULL;
	return newSymbol;
}

void addSymbol(Symbol **symbolTable, char *name, int type) {
	Symbol *newSymbol = createSymbol(name, type);
	newSymbol->next = *symbolTable;
	*symbolTable = newSymbol;
}

Symbol *lookupSymbol(Symbol *symbolTable, char *name) {
	Symbol *current = symbolTable;
	while (current != NULL) {
		if (strcmp(current->name, name) == 0)
			return current;
		current = current->next;
	}
	return NULL;
}

int main() {
	yyparse();
	return 0;
}