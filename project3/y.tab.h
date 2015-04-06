/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
   2009, 2010 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
     ID = 258,
     QQUO = 259,
     NUM = 260,
     SCRIPTYPE = 261,
     SLASHSCRIPT = 262,
     NEWLINE = 263,
     VAR = 264,
     EQUAL = 265,
     COLON = 266,
     SEMICOLON = 267,
     DOCUWRITE = 268,
     OPENPARENT = 269,
     CLOSEPARENT = 270,
     COMMA = 271,
     WS = 272,
     DOT = 273,
     CUROPENBRAC = 274,
     CURCLOSEBRAC = 275,
     PLUS = 276,
     MINUS = 277,
     TIME = 278,
     DIVIDE = 279,
     IF = 280,
     ELSE = 281,
     LESS = 282,
     GREAT = 283,
     LESSEQUAL = 284,
     GREATEQUAL = 285,
     EQEQUAL = 286,
     NOTEQUAL = 287,
     ANDAND = 288,
     OROR = 289,
     EXCLAMATION = 290,
     OPENBRAC = 291,
     CLOSEBRAC = 292,
     ELSEIF = 293
   };
#endif
/* Tokens.  */
#define ID 258
#define QQUO 259
#define NUM 260
#define SCRIPTYPE 261
#define SLASHSCRIPT 262
#define NEWLINE 263
#define VAR 264
#define EQUAL 265
#define COLON 266
#define SEMICOLON 267
#define DOCUWRITE 268
#define OPENPARENT 269
#define CLOSEPARENT 270
#define COMMA 271
#define WS 272
#define DOT 273
#define CUROPENBRAC 274
#define CURCLOSEBRAC 275
#define PLUS 276
#define MINUS 277
#define TIME 278
#define DIVIDE 279
#define IF 280
#define ELSE 281
#define LESS 282
#define GREAT 283
#define LESSEQUAL 284
#define GREATEQUAL 285
#define EQEQUAL 286
#define NOTEQUAL 287
#define ANDAND 288
#define OROR 289
#define EXCLAMATION 290
#define OPENBRAC 291
#define CLOSEBRAC 292
#define ELSEIF 293




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1685 of yacc.c  */
#line 63 "miniscript.y"

	char *string_val;
	int int_val;
	Expression *expr_val;
	Variable * var_val;
	Block * block_val;



/* Line 1685 of yacc.c  */
#line 137 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


