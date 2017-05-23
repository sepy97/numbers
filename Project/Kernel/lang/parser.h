/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     L_NUMBERLITERAL = 258,
     L_DOUBLELITERAL = 259,
     L_RATIONALLITERAL = 260,
     L_STRINGLITERAL = 261,
     L_IDENTIFIER = 262,
     L_FUNCTIONNAME = 263,
     L_FUNCTIONCALL = 264,
     L_FUNCTION = 265,
     L_PARAMETER = 266,
     L_COMMA = 267,
     L_MINUS = 268,
     L_PLUS = 269,
     L_REM = 270,
     L_MUL = 271,
     L_DIV = 272,
     L_POWER = 273,
     L_AMPERSAND = 274,
     L_PLUSPLUS = 275,
     L_MINUSMINUS = 276,
     L_OR = 277,
     L_AND = 278,
     L_NOT = 279,
     L_LBRACE = 280,
     L_RBRACE = 281,
     L_LBRACKET = 282,
     L_RBRACKET = 283,
     L_LPAREN = 284,
     L_RPAREN = 285,
     L_ASSIGN = 286,
     L_SEMI = 287,
     L_NEWLINE = 288,
     L_LE = 289,
     L_GE = 290,
     L_LT = 291,
     L_GT = 292,
     L_NE = 293,
     L_EQ = 294,
     L_INT = 295,
     L_DOUBLE = 296,
     L_RATIONAL = 297,
     L_STRING = 298,
     L_IF = 299,
     L_ELSE = 300,
     L_FOR = 301,
     L_WHILE = 302,
     L_RETURN = 303,
     L_INPUT = 304,
     L_OUTPUT = 305
   };
#endif
/* Tokens.  */
#define L_NUMBERLITERAL 258
#define L_DOUBLELITERAL 259
#define L_RATIONALLITERAL 260
#define L_STRINGLITERAL 261
#define L_IDENTIFIER 262
#define L_FUNCTIONNAME 263
#define L_FUNCTIONCALL 264
#define L_FUNCTION 265
#define L_PARAMETER 266
#define L_COMMA 267
#define L_MINUS 268
#define L_PLUS 269
#define L_REM 270
#define L_MUL 271
#define L_DIV 272
#define L_POWER 273
#define L_AMPERSAND 274
#define L_PLUSPLUS 275
#define L_MINUSMINUS 276
#define L_OR 277
#define L_AND 278
#define L_NOT 279
#define L_LBRACE 280
#define L_RBRACE 281
#define L_LBRACKET 282
#define L_RBRACKET 283
#define L_LPAREN 284
#define L_RPAREN 285
#define L_ASSIGN 286
#define L_SEMI 287
#define L_NEWLINE 288
#define L_LE 289
#define L_GE 290
#define L_LT 291
#define L_GT 292
#define L_NE 293
#define L_EQ 294
#define L_INT 295
#define L_DOUBLE 296
#define L_RATIONAL 297
#define L_STRING 298
#define L_IF 299
#define L_ELSE 300
#define L_FOR 301
#define L_WHILE 302
#define L_RETURN 303
#define L_INPUT 304
#define L_OUTPUT 305




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 55 "parser.y"
{tree *ptree; int icode;}
/* Line 1529 of yacc.c.  */
#line 151 "parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

