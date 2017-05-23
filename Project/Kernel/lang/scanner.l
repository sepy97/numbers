%{
#include "scanner.h"
#include "tree.h"
#include "parser.h"

int	  lex_iconst;
double  lex_dconst;
int	   lex_lineno;

%}

%x str
        char lex_sconst[MAX_STR_CONST];
        char *lex_sconst_ptr;

ID       [a-zA-Z][a-zA-Z_0-9]*


%%

\"      lex_sconst_ptr = lex_sconst; BEGIN(str);

<str>\"        { /* saw closing quote - all done */
        BEGIN(INITIAL);
        *lex_sconst_ptr = '\0';
        /* return string constant token type and
         * value to parser
         */
        }
        return L_STRINGLITERAL;

<str>\n        {
        /* error - unterminated string constant */
        /* generate error message */
        }

<str>\\[0-7]{1,3} {
        /* octal escape sequence */
        int result;

        (void) sscanf( yytext + 1, "%o", &result );

        if ( result > 0xff )
                /* error, constant is out-of-bounds */

        *lex_sconst_ptr++ = result;
        }

<str>\\[0-9]+ {
        /* generate error - bad escape sequence; something
         * like '\48' or '\0777777'
         */
        }

<str>\\n  *lex_sconst_ptr++ = '\n';
<str>\\t  *lex_sconst_ptr++ = '\t';
<str>\\r  *lex_sconst_ptr++ = '\r';
<str>\\b  *lex_sconst_ptr++ = '\b';
<str>\\f  *lex_sconst_ptr++ = '\f';

<str>\\(.|\n)  *lex_sconst_ptr++ = yytext[1];

<str>[^\\\n\"]+        {
        char *yptr = yytext;

        while ( *yptr )
                *lex_sconst_ptr++ = *yptr++;
        }


[0-9]+        lex_iconst = atoi( yytext ); return L_NUMBERLITERAL;

"++" return L_PLUSPLUS;
"+"	 return L_PLUS;
"--"  return L_MINUSMINUS;
"-"   return L_MINUS;
"/"	return L_DIV;
"*" return L_MUL;
"%" return L_REM;
","   return L_COMMA;
"&&"  return L_AND;
"&"   return L_AMPERSAND;
"!"   return L_NOT;
"||"  return L_OR;
"{"   return L_LBRACE;
"}"   return L_RBRACE;
"["  return L_LBRACKET;
"]"  return L_RBRACKET;
"("  return L_LPAREN;
")"  return L_RPAREN;
"="   return L_ASSIGN;
";"   return L_SEMI;
"=="  return L_EQ;
"!="  return L_NE;
">"   return L_GT;
">="  return L_GE;
"<"   return L_LT;
"<="  return L_LE;
"^"   return L_POWER;

		
"return"	return L_RETURN;
"int"	return L_INT;
"double" return L_DOUBLE;
"string" return L_STRING;
"if"		return L_IF;
"for"		return L_FOR;
"while"	return L_WHILE;
"else"		return L_ELSE;
"output"	return L_OUTPUT;
"input"		return L_INPUT;

{ID}		strncpy(lex_sconst, yytext, MAX_STR_CONST); if (strcmp(lex_sconst, "return") == 0) return L_RETURN; return L_IDENTIFIER;


"\n"		lex_lineno++; return L_NEWLINE; 
"\r"
"\t"
" "

%%



