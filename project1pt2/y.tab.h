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
     SEMICOLON = 266,
     DOCUWRITE = 267,
     OPENPARENT = 268,
     CLOSEPARENT = 269,
     COMMA = 270,
     WS = 271,
     DOT = 272,
     BR = 273,
     CUROPENBRAC = 274,
     CURCLOSEBRAC = 275,
     MINUS = 276,
     PLUS = 277,
     DIVIDE = 278,
     TIME = 279
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
#define SEMICOLON 266
#define DOCUWRITE 267
#define OPENPARENT 268
#define CLOSEPARENT 269
#define COMMA 270
#define WS 271
#define DOT 272
#define BR 273
#define CUROPENBRAC 274
#define CURCLOSEBRAC 275
#define MINUS 276
#define PLUS 277
#define DIVIDE 278
#define TIME 279




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1685 of yacc.c  */
#line 30 "miniscript.y"

	char * string_val;
	int int_val;



/* Line 1685 of yacc.c  */
#line 106 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


