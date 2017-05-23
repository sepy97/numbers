%token L_NUMBERLITERAL
%token L_DOUBLELITERAL
%token L_RATIONALLITERAL
%token L_STRINGLITERAL

%token L_IDENTIFIER
%token L_FUNCTIONNAME
%token L_FUNCTIONCALL
%token L_FUNCTION
%token L_PARAMETER
%left  L_COMMA
%left  L_PLUS L_MINUS
%left  L_DIV L_MUL L_REM
%right  L_POWER
%token L_AMPERSAND
%token L_PLUSPLUS
%token L_MINUSMINUS
%left  L_OR
%left  L_AND
%left  L_NOT


%token L_LBRACE
%token L_RBRACE
%token L_LBRACKET
%token L_RBRACKET
%token L_LPAREN
%token L_RPAREN
%token L_ASSIGN
%token L_SEMI
%token L_NEWLINE
%token L_COMMA
%left  L_EQ L_NE L_GT L_LT L_GE L_LE

%token L_INT
%token L_DOUBLE
%token L_RATIONAL
%token L_STRING

%token L_IF
%token L_ELSE
%token L_FOR
%token L_WHILE
%token L_RETURN
%token L_INPUT
%token L_OUTPUT


%start operator_list
%{
#include "scanner.h"
#include "tree.h"
%}

%union {tree *ptree; int icode;}

%type <ptree> expression term function_id 
%type <ptree> identifier argument_list 
%type <ptree> operator operator_list
%type <ptree> assign_operator input_operator output_operator


%%

operator_list:
	operator { $$ = $1; }
	| operator_list operator {$$ = tree_add(L_COMMA, $1, $2, NULL, "COMMA"); }
	;

identifier:
	L_IDENTIFIER { $$ = tree_identifier(lex_sconst); }
        ;
	
operator:
	   L_SEMI { $$ = NULL; }
        |  L_NEWLINE { $$ = NULL; }
	|  expression L_NEWLINE { $$ = $1; }
	|  assign_operator L_NEWLINE {$$ = $1; }
	|  input_operator L_NEWLINE {$$ = $1; }
	|  output_operator L_NEWLINE {$$ = $1; }
	;

assign_operator:
	   identifier L_ASSIGN expression { $$ = tree_add(L_ASSIGN, $1, $3, NULL, "ASSIGN"); }
	;

expression:
	  expression L_MUL expression { $$ = tree_add(L_MUL, $1, $3, NULL, "MUL"); }
	| expression L_DIV expression { $$ = tree_add(L_DIV, $1, $3, NULL, "DIV"); }
	| expression L_REM expression { $$ = tree_add(L_REM, $1, $3, NULL, "REM"); }
	| expression L_PLUS expression { $$ = tree_add(L_PLUS, $1, $3, NULL, "PLUS"); }
	| expression L_MINUS expression { $$ = tree_add(L_MINUS, $1, $3, NULL, "MINUS"); }
        | expression L_POWER expression { $$ = tree_add(L_POWER, $1, $3, NULL, "POWER"); }
	| expression L_LT expression { $$ = tree_add(L_LT, $1, $3, NULL, "LT"); }
	| expression L_LE expression { $$ = tree_add(L_LE, $1, $3, NULL, "LE"); }
	| expression L_GE expression { $$ = tree_add(L_GE, $1, $3, NULL, "GE"); }
	| expression L_GT expression { $$ = tree_add(L_GT, $1, $3, NULL, "GT"); }
	| expression L_EQ expression { $$ = tree_add(L_EQ, $1, $3, NULL, "EQ"); }
	| expression L_NE expression { $$ = tree_add(L_NE, $1, $3, NULL, "NE"); }
	| expression L_COMMA expression { $$ = tree_add(L_COMMA, $1, $3, NULL, "COMMA"); }

	| expression L_AND expression { $$ = tree_add(L_AND, $1, $3, NULL, "AND"); }
	| expression L_OR expression { $$ = tree_add(L_OR, $1, $3, NULL, "OR"); }
        | L_LPAREN expression L_RPAREN { $$ = $2; }
	| term { $$ = $1; }
	;

term:
	  term L_PLUSPLUS { $$ = tree_add(L_PLUSPLUS, $1, NULL, NULL, "PLUSPLUS"); }
	| term L_MINUSMINUS { $$ = tree_add(L_MINUSMINUS, $1, NULL, NULL, "MINUSMINUS"); }
	| L_PLUSPLUS term { $$ = tree_add(L_PLUSPLUS, $2, NULL, NULL, "PLUSPLUS"); }
	| L_MINUSMINUS term { $$ = tree_add(L_MINUSMINUS, $2, NULL, NULL, "MINUSMINUS"); }
	| L_MINUS term { $$ = tree_add(L_MINUS, $2, NULL, NULL, "UMINUS"); }
	| L_NOT term { $$ = tree_not($2); }
	| function_id L_RPAREN { $$ = tree_function_name($1); }
	| L_IDENTIFIER { $$ = tree_identifier(lex_sconst); }
	| L_NUMBERLITERAL { $$ = tree_int_const(lex_iconst); }
        | L_RATIONALLITERAL { $$ = tree_rational_const(lex_sconst); }
	| L_DOUBLELITERAL { $$ = tree_double_const(lex_dconst); }
	| L_STRINGLITERAL { $$ = tree_string_const(lex_sconst); }
	;

function_id:
	L_IDENTIFIER { $$ = tree_identifier(lex_sconst) } L_LPAREN argument_list { $$ = tree_function_call($$, $4); }
	;

argument_list:
	  expression {$$ = $1; }
	 | argument_list L_COMMA expression {$$ = tree_add(L_COMMA, $1, NULL, NULL, "COMMA"); }
	 | { $$ = NULL; }
	 ;
	 
input_operator:
	   L_INPUT argument_list 
	  ;
	  
output_operator:
	   L_OUTPUT argument_list 
	  ;
	  	 
