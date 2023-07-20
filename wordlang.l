%{
#include "y.tab.h"
%}

%%

"word"					{											return TYPE_WORD;			}
"sentence"				{											return TYPE_SENTENCE;		}
"int"					{											return TYPE_INT;			}
"char"					{											return TYPE_CHAR;			}
"if"					{											return KEYWORD_IF;			}
"else"					{											return KEYWORD_ELSE;		}
"while"					{											return KEYWORD_WHILE;		}
"loop"					{											return KEYWORD_LOOP;		}
"input"					{											return KEYWORD_INPUT;		}
"output"				{											return KEYWORD_OUTPUT;		}
","						{											return SIGN_COMMA;			}
"="						{											return SIGN_ASSIGN;			}
"("						{											return SIGN_LPAREN;			}
")"						{											return SIGN_RPAREN;			}
"{"						{											return SIGN_LBRACE;			}
"}"						{											return SIGN_RBRACE;			}
";"						{											return SIGN_SEMICOLON;		}
"-"						{											return OPERATOR_MINUS;		}
"+"						{											return OPERATOR_PLUS;		}
"#"						{											return OPERATOR_CONCAT;		}
":"						{											return OPERATOR_INDEX;		}
"<"						{											return OPERATOR_LT;			}
">"						{											return OPERATOR_GT;			}
"<="					{											return OPERATOR_LE;			}
">="					{											return OPERATOR_GE;			}
"=="					{											return OPERATOR_EQ;			}
"!"						{											return OPERATOR_NOT;		}
[a-zA-Z_][a-zA-Z0-9_]*	{	yylval.string_val	= strdup(yytext);	return IDENTIFIER;			}
[0-9]+					{	yylval.int_val		= atoi(yytext);		return LITERAL_INTEGER;		}
'[^']*'					{	yylval.string_val	= strdup(yytext);	return LITERAL_CHAR;		}
\"[^\"]*\"				{	yylval.string_val	= strdup(yytext);	return LITERAL_WORD;		}
\^[^\^]*\^				{	yylval.string_val	= strdup(yytext);	return LITERAL_SENTENCE;	}
\/\/.*					{	/* ignore comments */												}
[ \t\n]					{	/* ignore whitespace */												}

%%

int yywrap() {
	return 1;
}