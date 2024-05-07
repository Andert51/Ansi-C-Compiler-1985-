/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 12 "ansic.y"

	/* Codigo en C: */
// Bibliotecas de C++ para diferentes usos.
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <list>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h> // Para exit(0)

using namespace std; // Se reuiere std para las librerias siguientes

extern void yyerror(const char* s);
extern int column;
extern int yylex();
extern FILE* yyin;

#include "symtab.h" // Para tabla de simbolos
#include "genlib.h" // Para la generacion de codigo intermedio



enum ASSIGN_TYPES {

	EQ_ASSIGN_OP = 1,
	MUL_ASSIGN_OP,
	DIV_ASSIGN_OP,
	MOD_ASSIGN_OP,
	ADD_ASSIGN_OP,
	SUB_ASSIGN_OP,
	LEFT_ASSIGN_OP,
	RIGHT_ASSIGN_OP,
	AND_ASSIGN_OP,
	XOR_ASSIGN_OP,
	OR_ASSIGN_OP

};

enum OP_TYPES{

	PLUS_OP = 1,
	ADDR_OP,
	MINUS_OP,
	DEREF_OP,
	ONESCOMP_OP,
	NOT_OP

};

// Sobrecarga de funciones para bloque de datos
void setval(symrec* s, int val){
	*(int*)(datablock+s->offset) = val; //datablock es un bloque de datos para almacenar valor de variables
}

void setval(symrec* s, float val){
	*(float*)(datablock + s->offset) = val;
}

void setval(symrec* s, double val){
	*(double*)(datablock + s->offset) = val;
}

void setval(symrec* s, char val){
	*(char*)(datablock + s->offset) = val;
}

void setval(symrec* s, long val){
	*(long*)(datablock + s->offset) = val;
}

void setval(symrec* s, char* val ){
	strcpy((char*)(datablock + s->offset), val); // Copiar cadena en bloque de datos
}

void tological(VAR_DATA *sym){ // Verificar si es una expresion logica, si no lo es, generar codigo para compararla con 0
	if(sym->truelist == nullptr || sym->falselist == nullptr){

		std::string* name = newtemp(); // Nueva variable temporal
		symrec *s0;
		if(isfloat(sym->typ)){
			s0 = putsym(name, FVAL | CONST_SPEC);
			setval(s0, 0.0f);
		}
		else{
			s0 = putsym(name, INTVAL | CONST_SPEC);
			setval(s0, 0);
		}
		sym->truelist = makelist(nextinstr);
		gencode(IF_NE_IR, sym->var, s0, nullptr);
		sym->falselist = makelist(nextinstr);
		gencode(GOTO_IR);

	}

}



#line 173 "ansic.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    CONSTANT = 259,                /* CONSTANT  */
    STRING_LITERAL = 260,          /* STRING_LITERAL  */
    SIZEOF = 261,                  /* SIZEOF  */
    PTR_OP = 262,                  /* PTR_OP  */
    INC_OP = 263,                  /* INC_OP  */
    DEC_OP = 264,                  /* DEC_OP  */
    LEFT_OP = 265,                 /* LEFT_OP  */
    RIGHT_OP = 266,                /* RIGHT_OP  */
    LE_OP = 267,                   /* LE_OP  */
    GE_OP = 268,                   /* GE_OP  */
    EQ_OP = 269,                   /* EQ_OP  */
    NE_OP = 270,                   /* NE_OP  */
    AND_OP = 271,                  /* AND_OP  */
    OR_OP = 272,                   /* OR_OP  */
    MUL_ASSIGN = 273,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 274,              /* DIV_ASSIGN  */
    MOD_ASSIGN = 275,              /* MOD_ASSIGN  */
    ADD_ASSIGN = 276,              /* ADD_ASSIGN  */
    SUB_ASSIGN = 277,              /* SUB_ASSIGN  */
    LEFT_ASSIGN = 278,             /* LEFT_ASSIGN  */
    RIGHT_ASSIGN = 279,            /* RIGHT_ASSIGN  */
    AND_ASSIGN = 280,              /* AND_ASSIGN  */
    XOR_ASSIGN = 281,              /* XOR_ASSIGN  */
    OR_ASSIGN = 282,               /* OR_ASSIGN  */
    TYPE_NAME = 283,               /* TYPE_NAME  */
    TYPEDEF = 284,                 /* TYPEDEF  */
    EXTERN = 285,                  /* EXTERN  */
    STATIC = 286,                  /* STATIC  */
    AUTO = 287,                    /* AUTO  */
    REGISTER = 288,                /* REGISTER  */
    CHAR = 289,                    /* CHAR  */
    SHORT = 290,                   /* SHORT  */
    INT = 291,                     /* INT  */
    LONG = 292,                    /* LONG  */
    SIGNED = 293,                  /* SIGNED  */
    UNSIGNED = 294,                /* UNSIGNED  */
    FLOAT = 295,                   /* FLOAT  */
    DOUBLE = 296,                  /* DOUBLE  */
    CONST = 297,                   /* CONST  */
    VOLATILE = 298,                /* VOLATILE  */
    VOID = 299,                    /* VOID  */
    STRUCT = 300,                  /* STRUCT  */
    UNION = 301,                   /* UNION  */
    ENUM = 302,                    /* ENUM  */
    ELLIPSIS = 303,                /* ELLIPSIS  */
    CASE = 304,                    /* CASE  */
    DEFAULT = 305,                 /* DEFAULT  */
    IF = 306,                      /* IF  */
    ELSE = 307,                    /* ELSE  */
    SWITCH = 308,                  /* SWITCH  */
    WHILE = 309,                   /* WHILE  */
    DO = 310,                      /* DO  */
    FOR = 311,                     /* FOR  */
    GOTO = 312,                    /* GOTO  */
    CONTINUE = 313,                /* CONTINUE  */
    BREAK = 314,                   /* BREAK  */
    RETURN = 315,                  /* RETURN  */
    NOELSE = 316                   /* NOELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 114 "ansic.y"
 // Directiva union que contiene la union de los atributos requeridos por los Tokens

    struct { // Estructura que contiene los atributos de diferentes tokens 
		union { // Todas esas variables ocupan el mismo espacio de RAM por ser union, solo una de esas se usara en un momento determinado para una variable determianda
        	int ival;
        	double dval;
			float fval;
			char cval;
		};

		int valtype; // Contiene el tipo de la constante
    };

    char* name;
    char* sval; // Los strings en c son char* char[]
	int typesp;
	int scsp;
	int typeq;
	VAR_DATA* id_data; // Datos de identificador
	VAR_DATA sym; // Para poner datos sobre una variable ya declarada
	std::list<VAR_DATA*>* idlist;
	std::list<int>* splist;
	int asop;

	struct{
		int typq; // Calificador de tipo
		int level; // Nivel de puntero, *, **, etc
	} pstruct;

	std::list<VAR_DATA*>* symlist;
	int typ;
	std::list<int>* sqlist;
	int instr;

	struct{
		std::list<int>* breaklist; // Para salto fuera de un switch
		std::list<int>* nextlist; // Para salto a siguiente instruccion
		std::list<int>* continuelist; // Para salto a siguiente inicio de ciclo
		std::list<GOTO_DATA*>* gotolist; // Para salto de GOTO
		std::list<CASE_DATA*>* caselist; // Para saltos a los case de un switch
	} lists;
	int op;
	

#line 329 "ansic.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_CONSTANT = 4,                   /* CONSTANT  */
  YYSYMBOL_STRING_LITERAL = 5,             /* STRING_LITERAL  */
  YYSYMBOL_SIZEOF = 6,                     /* SIZEOF  */
  YYSYMBOL_PTR_OP = 7,                     /* PTR_OP  */
  YYSYMBOL_INC_OP = 8,                     /* INC_OP  */
  YYSYMBOL_DEC_OP = 9,                     /* DEC_OP  */
  YYSYMBOL_LEFT_OP = 10,                   /* LEFT_OP  */
  YYSYMBOL_RIGHT_OP = 11,                  /* RIGHT_OP  */
  YYSYMBOL_LE_OP = 12,                     /* LE_OP  */
  YYSYMBOL_GE_OP = 13,                     /* GE_OP  */
  YYSYMBOL_EQ_OP = 14,                     /* EQ_OP  */
  YYSYMBOL_NE_OP = 15,                     /* NE_OP  */
  YYSYMBOL_AND_OP = 16,                    /* AND_OP  */
  YYSYMBOL_OR_OP = 17,                     /* OR_OP  */
  YYSYMBOL_MUL_ASSIGN = 18,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 19,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 20,                /* MOD_ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 21,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 22,                /* SUB_ASSIGN  */
  YYSYMBOL_LEFT_ASSIGN = 23,               /* LEFT_ASSIGN  */
  YYSYMBOL_RIGHT_ASSIGN = 24,              /* RIGHT_ASSIGN  */
  YYSYMBOL_AND_ASSIGN = 25,                /* AND_ASSIGN  */
  YYSYMBOL_XOR_ASSIGN = 26,                /* XOR_ASSIGN  */
  YYSYMBOL_OR_ASSIGN = 27,                 /* OR_ASSIGN  */
  YYSYMBOL_TYPE_NAME = 28,                 /* TYPE_NAME  */
  YYSYMBOL_TYPEDEF = 29,                   /* TYPEDEF  */
  YYSYMBOL_EXTERN = 30,                    /* EXTERN  */
  YYSYMBOL_STATIC = 31,                    /* STATIC  */
  YYSYMBOL_AUTO = 32,                      /* AUTO  */
  YYSYMBOL_REGISTER = 33,                  /* REGISTER  */
  YYSYMBOL_CHAR = 34,                      /* CHAR  */
  YYSYMBOL_SHORT = 35,                     /* SHORT  */
  YYSYMBOL_INT = 36,                       /* INT  */
  YYSYMBOL_LONG = 37,                      /* LONG  */
  YYSYMBOL_SIGNED = 38,                    /* SIGNED  */
  YYSYMBOL_UNSIGNED = 39,                  /* UNSIGNED  */
  YYSYMBOL_FLOAT = 40,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 41,                    /* DOUBLE  */
  YYSYMBOL_CONST = 42,                     /* CONST  */
  YYSYMBOL_VOLATILE = 43,                  /* VOLATILE  */
  YYSYMBOL_VOID = 44,                      /* VOID  */
  YYSYMBOL_STRUCT = 45,                    /* STRUCT  */
  YYSYMBOL_UNION = 46,                     /* UNION  */
  YYSYMBOL_ENUM = 47,                      /* ENUM  */
  YYSYMBOL_ELLIPSIS = 48,                  /* ELLIPSIS  */
  YYSYMBOL_CASE = 49,                      /* CASE  */
  YYSYMBOL_DEFAULT = 50,                   /* DEFAULT  */
  YYSYMBOL_IF = 51,                        /* IF  */
  YYSYMBOL_ELSE = 52,                      /* ELSE  */
  YYSYMBOL_SWITCH = 53,                    /* SWITCH  */
  YYSYMBOL_WHILE = 54,                     /* WHILE  */
  YYSYMBOL_DO = 55,                        /* DO  */
  YYSYMBOL_FOR = 56,                       /* FOR  */
  YYSYMBOL_GOTO = 57,                      /* GOTO  */
  YYSYMBOL_CONTINUE = 58,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 59,                     /* BREAK  */
  YYSYMBOL_RETURN = 60,                    /* RETURN  */
  YYSYMBOL_NOELSE = 61,                    /* NOELSE  */
  YYSYMBOL_62_ = 62,                       /* '('  */
  YYSYMBOL_63_ = 63,                       /* ')'  */
  YYSYMBOL_64_ = 64,                       /* '['  */
  YYSYMBOL_65_ = 65,                       /* ']'  */
  YYSYMBOL_66_ = 66,                       /* '.'  */
  YYSYMBOL_67_ = 67,                       /* ','  */
  YYSYMBOL_68_ = 68,                       /* '&'  */
  YYSYMBOL_69_ = 69,                       /* '*'  */
  YYSYMBOL_70_ = 70,                       /* '+'  */
  YYSYMBOL_71_ = 71,                       /* '-'  */
  YYSYMBOL_72_ = 72,                       /* '~'  */
  YYSYMBOL_73_ = 73,                       /* '!'  */
  YYSYMBOL_74_ = 74,                       /* '/'  */
  YYSYMBOL_75_ = 75,                       /* '%'  */
  YYSYMBOL_76_ = 76,                       /* '<'  */
  YYSYMBOL_77_ = 77,                       /* '>'  */
  YYSYMBOL_78_ = 78,                       /* '^'  */
  YYSYMBOL_79_ = 79,                       /* '|'  */
  YYSYMBOL_80_ = 80,                       /* '?'  */
  YYSYMBOL_81_ = 81,                       /* ':'  */
  YYSYMBOL_82_ = 82,                       /* '='  */
  YYSYMBOL_83_ = 83,                       /* ';'  */
  YYSYMBOL_84_ = 84,                       /* '{'  */
  YYSYMBOL_85_ = 85,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 86,                  /* $accept  */
  YYSYMBOL_primary_expression = 87,        /* primary_expression  */
  YYSYMBOL_postfix_expression = 88,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 89,  /* argument_expression_list  */
  YYSYMBOL_unary_expression = 90,          /* unary_expression  */
  YYSYMBOL_unary_operator = 91,            /* unary_operator  */
  YYSYMBOL_cast_expression = 92,           /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 93, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 94,       /* additive_expression  */
  YYSYMBOL_shift_expression = 95,          /* shift_expression  */
  YYSYMBOL_relational_expression = 96,     /* relational_expression  */
  YYSYMBOL_equality_expression = 97,       /* equality_expression  */
  YYSYMBOL_and_expression = 98,            /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 99,   /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 100,  /* inclusive_or_expression  */
  YYSYMBOL_N = 101,                        /* N  */
  YYSYMBOL_logical_and_expression = 102,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 103,    /* logical_or_expression  */
  YYSYMBOL_M = 104,                        /* M  */
  YYSYMBOL_conditional_expression = 105,   /* conditional_expression  */
  YYSYMBOL_106_1 = 106,                    /* $@1  */
  YYSYMBOL_107_2 = 107,                    /* $@2  */
  YYSYMBOL_assignment_expression = 108,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 109,      /* assignment_operator  */
  YYSYMBOL_expression = 110,               /* expression  */
  YYSYMBOL_constant_expression = 111,      /* constant_expression  */
  YYSYMBOL_declaration = 112,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 113,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 114,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 115,          /* init_declarator  */
  YYSYMBOL_storage_class_specifier = 116,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 117,           /* type_specifier  */
  YYSYMBOL_struct_or_union_specifier = 118, /* struct_or_union_specifier  */
  YYSYMBOL_struct_or_union = 119,          /* struct_or_union  */
  YYSYMBOL_struct_declaration_list = 120,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 121,       /* struct_declaration  */
  YYSYMBOL_specifier_qualifier_list = 122, /* specifier_qualifier_list  */
  YYSYMBOL_struct_declarator_list = 123,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 124,        /* struct_declarator  */
  YYSYMBOL_enum_specifier = 125,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 126,          /* enumerator_list  */
  YYSYMBOL_enumerator = 127,               /* enumerator  */
  YYSYMBOL_type_qualifier = 128,           /* type_qualifier  */
  YYSYMBOL_declarator = 129,               /* declarator  */
  YYSYMBOL_direct_declarator = 130,        /* direct_declarator  */
  YYSYMBOL_pointer = 131,                  /* pointer  */
  YYSYMBOL_type_qualifier_list = 132,      /* type_qualifier_list  */
  YYSYMBOL_parameter_type_list = 133,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 134,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 135,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 136,          /* identifier_list  */
  YYSYMBOL_type_name = 137,                /* type_name  */
  YYSYMBOL_abstract_declarator = 138,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 139, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 140,              /* initializer  */
  YYSYMBOL_initializer_list = 141,         /* initializer_list  */
  YYSYMBOL_P = 142,                        /* P  */
  YYSYMBOL_statement = 143,                /* statement  */
  YYSYMBOL_144_3 = 144,                    /* $@3  */
  YYSYMBOL_labeled_statement = 145,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 146,       /* compound_statement  */
  YYSYMBOL_declaration_list = 147,         /* declaration_list  */
  YYSYMBOL_statement_list = 148,           /* statement_list  */
  YYSYMBOL_expression_statement = 149,     /* expression_statement  */
  YYSYMBOL_logic_expression = 150,         /* logic_expression  */
  YYSYMBOL_selection_statement = 151,      /* selection_statement  */
  YYSYMBOL_logic_expression_statement = 152, /* logic_expression_statement  */
  YYSYMBOL_iteration_statement = 153,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 154,           /* jump_statement  */
  YYSYMBOL_translation_unit = 155,         /* translation_unit  */
  YYSYMBOL_external_declaration = 156,     /* external_declaration  */
  YYSYMBOL_function_definition = 157,      /* function_definition  */
  YYSYMBOL_158_4 = 158,                    /* $@4  */
  YYSYMBOL_159_5 = 159                     /* $@5  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 231 "ansic.y"

 	//extern int yylex(YYSTYPE * yylval_param, YYLTYPE * yylloc_param);	

#line 518 "ansic.tab.c"


#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  60
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1247

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  222
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  380

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   316


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    73,     2,     2,     2,    75,    68,     2,
      62,    63,    69,    70,    67,    71,    66,    74,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    81,    83,
      76,    82,    77,    80,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    64,     2,    65,    78,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    84,    79,    85,    72,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   245,   245,   260,   296,   309,   316,   320,   375,   384,
     400,   404,   408,   421,   438,   448,   458,   462,   470,   478,
     530,   540,   553,   557,   561,   565,   569,   573,   580,   593,
     623,   627,   651,   675,   702,   706,   730,   757,   761,   791,
     824,   828,   845,   862,   879,   899,   903,   920,   940,   944,
     970,   974,  1000,  1004,  1030,  1037,  1041,  1052,  1056,  1067,
    1076,  1080,  1102,  1080,  1125,  1129,  1205,  1209,  1213,  1217,
    1221,  1225,  1229,  1233,  1237,  1241,  1245,  1252,  1256,  1263,
    1270,  1274,  1308,  1314,  1319,  1325,  1330,  1336,  1344,  1351,
    1359,  1364,  1373,  1377,  1381,  1385,  1389,  1396,  1400,  1404,
    1408,  1412,  1416,  1420,  1424,  1428,  1432,  1436,  1440,  1446,
    1450,  1454,  1461,  1465,  1472,  1476,  1483,  1490,  1495,  1501,
    1506,  1515,  1519,  1526,  1530,  1534,  1541,  1545,  1549,  1556,
    1560,  1567,  1571,  1578,  1582,  1589,  1595,  1616,  1626,  1630,
    1646,  1655,  1662,  1667,  1676,  1681,  1686,  1691,  1700,  1706,
    1715,  1719,  1726,  1734,  1744,  1754,  1758,  1765,  1775,  1787,
    1791,  1798,  1802,  1806,  1813,  1817,  1821,  1825,  1829,  1833,
    1837,  1841,  1845,  1852,  1856,  1860,  1867,  1871,  1877,  1884,
    1889,  1889,  1899,  1907,  1912,  1917,  1925,  1934,  1947,  1957,
    1964,  1968,  1975,  1982,  1986,  1993,  1997,  2011,  2016,  2023,
    2031,  2040,  2050,  2090,  2108,  2121,  2133,  2146,  2164,  2173,
    2182,  2191,  2200,  2234,  2238,  2244,  2248,  2255,  2259,  2259,
    2280,  2284,  2284
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "CONSTANT", "STRING_LITERAL", "SIZEOF", "PTR_OP", "INC_OP", "DEC_OP",
  "LEFT_OP", "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP",
  "OR_OP", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN",
  "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN",
  "OR_ASSIGN", "TYPE_NAME", "TYPEDEF", "EXTERN", "STATIC", "AUTO",
  "REGISTER", "CHAR", "SHORT", "INT", "LONG", "SIGNED", "UNSIGNED",
  "FLOAT", "DOUBLE", "CONST", "VOLATILE", "VOID", "STRUCT", "UNION",
  "ENUM", "ELLIPSIS", "CASE", "DEFAULT", "IF", "ELSE", "SWITCH", "WHILE",
  "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN", "NOELSE", "'('",
  "')'", "'['", "']'", "'.'", "','", "'&'", "'*'", "'+'", "'-'", "'~'",
  "'!'", "'/'", "'%'", "'<'", "'>'", "'^'", "'|'", "'?'", "':'", "'='",
  "';'", "'{'", "'}'", "$accept", "primary_expression",
  "postfix_expression", "argument_expression_list", "unary_expression",
  "unary_operator", "cast_expression", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "N", "logical_and_expression",
  "logical_or_expression", "M", "conditional_expression", "$@1", "$@2",
  "assignment_expression", "assignment_operator", "expression",
  "constant_expression", "declaration", "declaration_specifiers",
  "init_declarator_list", "init_declarator", "storage_class_specifier",
  "type_specifier", "struct_or_union_specifier", "struct_or_union",
  "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "type_qualifier", "declarator", "direct_declarator", "pointer",
  "type_qualifier_list", "parameter_type_list", "parameter_list",
  "parameter_declaration", "identifier_list", "type_name",
  "abstract_declarator", "direct_abstract_declarator", "initializer",
  "initializer_list", "P", "statement", "$@3", "labeled_statement",
  "compound_statement", "declaration_list", "statement_list",
  "expression_statement", "logic_expression", "selection_statement",
  "logic_expression_statement", "iteration_statement", "jump_statement",
  "translation_unit", "external_declaration", "function_definition", "$@4",
  "$@5", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-280)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-219)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     871,  -280,  -280,  -280,  -280,  -280,  -280,  -280,  -280,  -280,
    -280,  -280,  -280,  -280,  -280,  -280,  -280,  -280,  -280,  -280,
    -280,     9,    61,    -8,  -280,    49,  1200,  1200,  -280,    21,
    -280,  1200,  1200,   -18,    23,   781,  -280,  -280,   -51,    40,
     -13,  -280,  -280,    -8,  -280,   -25,  -280,  1024,  -280,  -280,
     -31,   998,  -280,  -280,    49,  1044,   -21,   916,   586,   -18,
    -280,  -280,    40,    -6,   -20,  -280,  -280,  -280,  -280,    61,
    -280,   444,  1044,   -21,   998,   998,   946,  -280,    38,   998,
     107,   300,  -280,  -280,  -280,  -280,  -280,    53,   109,   116,
    -280,    64,  -280,  -280,  -280,   681,   707,   707,   565,  -280,
    -280,  -280,  -280,  -280,  -280,  -280,  -280,   126,  -280,   728,
    -280,    15,    54,   152,    90,   218,   141,   166,   173,   204,
      -3,  -280,   193,   -12,   728,    40,  -280,  -280,   444,   812,
    -280,  -280,  -280,  -280,  -280,   966,  -280,  -280,  -280,   728,
      16,  -280,   183,  -280,   189,   728,   192,   198,   206,  -280,
    -280,   207,   272,   195,   196,   492,  -280,  -280,  -280,    92,
    -280,  -280,  -280,   371,   191,  -280,  -280,  -280,  -280,   826,
     610,  -280,    94,  -280,   161,  -280,  1179,  -280,   277,   565,
    -280,   728,  -280,  -280,   106,   172,   219,   280,  -280,  -280,
     636,   728,   281,  -280,   728,   728,   728,   728,   728,   728,
     728,   728,   728,   728,   728,   728,   728,   728,   728,   728,
    -280,  -280,   205,  -280,  -280,  -280,  -280,  -280,   -10,  -280,
    -280,  -280,  -280,  -280,  -280,  -280,  -280,  -280,  -280,  -280,
     728,  -280,  -280,    38,  -280,   728,  -280,   208,  -280,   728,
     728,   224,   476,   515,   209,  -280,  -280,  -280,   101,   728,
    -280,   -21,  -280,   202,  -280,   476,  -280,   225,   227,  -280,
     226,   161,  1143,   657,  -280,  -280,  -280,   232,  -280,  1101,
     187,  -280,   728,  -280,  -280,   148,  -280,   188,  -280,  -280,
    -280,  -280,    15,    15,    54,    54,   152,   152,   152,   152,
      90,    90,   218,   141,   166,   728,   728,  -280,   389,  -280,
    -280,  -280,  -280,   476,  -280,   476,   229,   234,   179,   728,
     244,  -280,  -280,  -280,  -280,  -280,  -280,  -280,  -280,  -280,
    -280,  -280,   236,  -280,   235,  -280,  -280,  -280,   728,  -280,
     173,   204,   728,  -280,  -280,  -280,   476,  -280,  -280,  -280,
     238,  -280,   515,  -280,  -280,  -280,    47,  -280,   476,   476,
    -280,   248,   249,  -280,  -280,   261,  -280,   476,   728,   728,
     253,  -280,  -280,  -280,   254,   180,   476,  -280,  -280,   237,
    -280,  -280,   728,   476,  -280,  -280,  -280,  -280,   476,  -280
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   137,   108,    92,    93,    94,    95,    96,    98,    99,
     100,   101,   104,   105,   102,   103,   133,   134,    97,   112,
     113,     0,     0,   144,   216,     0,    82,    84,   106,     0,
     107,    86,   221,   136,     0,     0,   213,   215,   128,     0,
       0,   148,   146,   145,    80,     0,    88,    90,    83,    85,
     111,     0,    87,   193,     0,     0,     0,     0,     0,   135,
       1,   214,     0,   131,     0,   129,   138,   149,   147,     0,
      81,     0,     0,     0,     0,   118,     0,   114,     0,   120,
      90,   178,   194,   220,   222,   157,   143,   156,     0,   150,
     152,     0,     2,     3,     4,     0,     0,     0,     0,   140,
      22,    23,    24,    25,    26,    27,     6,    16,    28,     0,
      30,    34,    37,    40,    45,    48,    50,    52,    55,    57,
      60,    79,     0,     0,     0,     0,   126,    89,     0,    28,
      64,   173,    91,   217,   219,     0,   117,   110,   115,     0,
       0,   121,   123,   119,     2,     0,     0,     0,     0,    54,
      54,     0,     0,     0,     0,     0,   197,   189,    77,     0,
     180,   195,   179,   178,    54,   182,   183,   184,   185,     0,
       0,   154,   161,   155,   162,   141,     0,   142,     0,     0,
      20,     0,    17,    18,     0,   159,     0,     0,    12,    13,
       0,     0,     0,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      54,    54,     0,   139,   127,   132,   130,   176,     0,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    66,
       0,   109,   124,     0,   116,     0,    54,     0,    54,     0,
       0,     0,   178,     0,     0,   209,   210,   211,     0,     0,
     198,     0,   191,    54,   190,   178,   169,     0,     0,   165,
       0,   163,     0,     0,   151,   153,   158,     0,     5,     0,
     161,   160,     0,    11,     8,     0,    14,     0,    10,    31,
      32,    33,    35,    36,    38,    39,    43,    44,    41,    42,
      46,    47,    49,    51,    53,     0,     0,    54,     0,   174,
      65,   122,   125,   178,    54,   178,   199,     0,     0,     0,
       0,    54,   208,   212,    78,   181,   192,   196,   170,   164,
     166,   171,     0,   167,     0,    21,    29,     9,     0,     7,
      56,    58,     0,   175,   177,   186,   178,   188,    54,    59,
       0,    54,     0,   172,   168,    15,     0,   187,   178,   178,
      54,     0,    54,    54,    62,   200,   202,   178,     0,     0,
       0,    59,    59,   204,     0,     0,   178,    54,    54,     0,
      59,   206,     0,   178,   205,    54,    63,   201,   178,   207
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -280,  -280,  -280,  -280,   -58,  -280,   -86,    59,    62,    -7,
      60,   112,   114,   115,    30,  -140,    31,  -280,  -131,   -57,
    -280,  -280,   -69,  -280,   -87,   -44,    19,     5,  -280,   257,
    -280,   128,  -280,  -280,   274,   -49,   -50,  -280,   119,  -280,
     299,   239,   142,    -9,   -17,   -15,  -280,   -54,  -280,   190,
    -280,   184,   -65,  -154,  -122,  -280,  -280,   -55,  -280,  -280,
     -52,   -32,   215,  -236,  -279,  -280,  -280,  -280,  -280,  -280,
     330,  -280,  -280,  -280
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,   106,   107,   275,   129,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   255,   119,   120,   349,   130,
     212,   361,   158,   230,   159,   122,    53,    54,    45,    46,
      26,    27,    28,    29,    76,    77,    78,   140,   141,    30,
      64,    65,    31,    32,    33,    34,    43,   257,    89,    90,
      91,   186,   258,   174,   132,   218,   160,   161,   251,   162,
      83,    55,   164,   165,   307,   166,   353,   167,   168,    35,
      36,    37,    73,    56
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     108,   121,   131,    88,    84,    25,   217,   311,    42,   241,
     242,   184,    38,    40,   211,    72,    47,    59,   261,    24,
     133,   134,   173,   193,    50,   136,     1,   138,    68,   143,
     340,    48,    49,    62,    16,    17,    52,   180,   182,   183,
      25,     1,    69,    63,    57,    80,    58,   125,   185,   163,
      66,   108,     1,    74,    24,   125,     1,   298,    70,   131,
      80,    23,    87,    81,     1,   126,   108,   121,   248,   142,
     295,   296,   172,   214,    82,   299,   124,   -61,   171,   364,
     215,   108,   121,   233,   194,    22,   138,   108,   121,   195,
     196,    82,   184,    39,   184,   232,   303,     1,   305,   234,
      22,   237,   201,   202,   277,    51,   352,    23,   279,   280,
     281,    22,   108,   121,   249,   169,   261,   170,    23,   139,
     271,   276,    23,    22,   197,   198,   260,   177,   354,   185,
      23,   178,    44,   187,   188,   189,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   306,   308,   172,    59,   169,   332,   170,   249,
      40,   300,   199,   200,   336,    41,   203,   204,   249,   268,
     270,   342,   175,   249,    87,   250,   334,   108,   121,    75,
     314,    87,    82,   176,   313,    67,   326,   310,   190,    71,
     191,   302,   192,    79,   286,   287,   288,   289,   348,   315,
     317,   351,    75,    75,    75,   108,   121,    75,   322,   207,
     357,   327,   359,   360,   108,   328,    79,    79,    79,   324,
     210,    79,   306,   262,   142,   263,    75,   372,   373,   131,
     367,   368,   205,   206,   269,   378,   170,   108,   108,   375,
      79,    23,   339,   370,   208,   346,   249,   249,   335,   269,
     337,   170,   209,   329,   270,   249,   282,   283,   213,   345,
     239,   284,   285,    75,   235,   290,   291,    87,   240,   243,
     236,   306,   365,   238,    87,   244,   254,    79,   245,   246,
     266,   347,   272,   273,   278,   297,   309,   316,   318,   304,
     319,   320,   312,   355,   356,   325,   249,   338,   341,   343,
     344,   350,   363,   144,    93,    94,    95,    75,    96,    97,
     358,   371,  -203,   362,   108,   376,   366,   369,   377,   292,
     374,    79,   293,   379,   294,   330,   127,   331,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,   135,   145,
     146,   147,   301,   148,   149,   150,   151,   152,   153,   154,
     155,   123,    98,   267,   216,    61,   265,     0,   100,   101,
     102,   103,   104,   105,   144,    93,    94,    95,   253,    96,
      97,     0,     0,   156,     0,   157,     0,     0,     0,     0,
       0,     0,    92,    93,    94,    95,     0,    96,    97,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     0,
     145,   146,   147,     0,   148,   149,   150,   151,   152,   153,
     154,   155,     0,    98,     0,     0,     0,     0,     0,   100,
     101,   102,   103,   104,   105,     0,     0,    92,    93,    94,
      95,    98,    96,    97,   156,     0,   252,   100,   101,   102,
     103,   104,   105,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   128,   333,     0,     0,     0,     0,   144,
      93,    94,    95,     0,    96,    97,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    92,    93,    94,    95,     0,
      96,    97,     0,     0,     0,     0,    98,     0,     0,     0,
       0,     0,   100,   101,   102,   103,   104,   105,    92,    93,
      94,    95,     0,    96,    97,   145,   146,   147,   128,   148,
     149,   150,   151,   152,   153,   154,   155,     0,    98,     0,
       0,     0,     0,     0,   100,   101,   102,   103,   104,   105,
       0,     0,     0,     0,    98,     0,     0,     0,     0,   156,
     100,   101,   102,   103,   104,   105,     0,     0,    92,    93,
      94,    95,     0,    96,    97,   247,     0,    98,     0,     0,
       0,     0,     0,   100,   101,   102,   103,   104,   105,    92,
      93,    94,    95,     2,    96,    97,     0,     0,   156,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    92,    93,    94,    95,     0,    96,    97,
       0,     0,     0,     0,     0,     0,     0,    98,     0,     0,
       0,     0,     0,   100,   101,   102,   103,   104,   105,    92,
      93,    94,    95,     0,    96,    97,     0,     0,    98,     0,
       0,    99,     0,     0,   100,   101,   102,   103,   104,   105,
      92,    93,    94,    95,     0,    96,    97,     0,     0,     0,
       0,     0,    98,     0,     0,   259,     0,     0,   100,   101,
     102,   103,   104,   105,    92,    93,    94,    95,     0,    96,
      97,     0,     0,     0,     0,     0,     0,     0,    98,   274,
       0,     0,     0,     0,   100,   101,   102,   103,   104,   105,
      92,    93,    94,    95,     0,    96,    97,     0,     0,    98,
       0,     0,   323,     0,     0,   100,   101,   102,   103,   104,
     105,    92,    93,    94,    95,     0,    96,    97,     0,     0,
       0,     0,     0,   179,     0,     0,     0,     0,     0,   100,
     101,   102,   103,   104,   105,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   181,
       0,     0,     0,     0,     0,   100,   101,   102,   103,   104,
     105,    60,     0,     0,     1,     0,     0,     0,     0,     0,
      98,     0,     0,     0,     0,     0,   100,   101,   102,   103,
     104,   105,     0,     0,     0,     0,     0,     0,     0,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     1,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
       0,     0,     0,    22,     0,     0,     0,     0,     0,     0,
      23,     0,     0,     0,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     1,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   169,   256,
     170,     0,     0,     0,   229,    23,     0,     0,     0,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    85,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    22,     0,     0,     0,     0,     0,     0,
      23,     0,     0,     0,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     0,     0,     0,     0,    86,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     2,     0,     0,     0,     0,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     2,     0,     0,     0,
       0,   137,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     0,     0,     0,     0,
       0,   231,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    71,     0,  -218,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    81,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   269,   256,   170,     0,     0,     0,     0,
      23,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   321,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,   264,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21
};

static const yytype_int16 yycheck[] =
{
      58,    58,    71,    57,    56,     0,   128,   243,    23,   149,
     150,    98,     3,    22,    17,    47,    25,    34,   172,     0,
      72,    73,    87,   109,     3,    75,     3,    76,    43,    79,
     309,    26,    27,    84,    42,    43,    31,    95,    96,    97,
      35,     3,    67,     3,    62,    54,    64,    67,    98,    81,
      63,   109,     3,    84,    35,    67,     3,    67,    83,   128,
      69,    69,    57,    84,     3,    85,   124,   124,   155,    78,
     210,   211,    87,    85,    55,    85,    82,    80,    87,   358,
     124,   139,   139,    67,    69,    62,   135,   145,   145,    74,
      75,    72,   179,    84,   181,   139,   236,     3,   238,    83,
      62,   145,    12,    13,   191,    84,   342,    69,   194,   195,
     196,    62,   170,   170,    67,    62,   270,    64,    69,    81,
     185,   190,    69,    62,    70,    71,   170,    63,    81,   179,
      69,    67,    83,     7,     8,     9,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   239,   240,   169,   172,    62,   297,    64,    67,
     169,   230,    10,    11,   304,    23,    76,    77,    67,    63,
     185,   311,    63,    67,   169,    83,   298,   235,   235,    51,
     249,   176,   163,    67,    83,    43,   272,   242,    62,    82,
      64,   235,    66,    51,   201,   202,   203,   204,   338,   251,
     255,   341,    74,    75,    76,   263,   263,    79,   262,    68,
     350,    63,   352,   353,   272,    67,    74,    75,    76,   263,
      16,    79,   309,    62,   233,    64,    98,   367,   368,   298,
     361,   362,    14,    15,    62,   375,    64,   295,   296,   370,
      98,    69,    63,    63,    78,   332,    67,    67,   303,    62,
     305,    64,    79,    65,   269,    67,   197,   198,    65,   328,
      62,   199,   200,   135,    81,   205,   206,   262,    62,    62,
      81,   358,   359,    81,   269,     3,    85,   135,    83,    83,
       3,   336,    63,     3,     3,    80,    62,    85,    63,    81,
      63,    65,    83,   348,   349,    63,    67,    63,    54,    63,
      65,    63,   357,     3,     4,     5,     6,   179,     8,     9,
      62,   366,    63,    52,   372,   372,    63,    63,   373,   207,
      83,   179,   208,   378,   209,   295,    69,   296,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    74,    49,
      50,    51,   233,    53,    54,    55,    56,    57,    58,    59,
      60,    62,    62,   179,   125,    35,   176,    -1,    68,    69,
      70,    71,    72,    73,     3,     4,     5,     6,   163,     8,
       9,    -1,    -1,    83,    -1,    85,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,    -1,     8,     9,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      49,    50,    51,    -1,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    -1,    -1,     3,     4,     5,
       6,    62,     8,     9,    83,    -1,    85,    68,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,    -1,
       8,     9,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,     3,     4,
       5,     6,    -1,     8,     9,    49,    50,    51,    84,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    83,
      68,    69,    70,    71,    72,    73,    -1,    -1,     3,     4,
       5,     6,    -1,     8,     9,    83,    -1,    62,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,     3,
       4,     5,     6,    28,     8,     9,    -1,    -1,    83,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    62,    -1,
      -1,    65,    -1,    -1,    68,    69,    70,    71,    72,    73,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    -1,    65,    -1,    -1,    68,    69,
      70,    71,    72,    73,     3,     4,     5,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    62,
      -1,    -1,    65,    -1,    -1,    68,    69,    70,    71,    72,
      73,     3,     4,     5,     6,    -1,     8,     9,    -1,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,     0,    -1,    -1,     3,    -1,    -1,    -1,    -1,    -1,
      62,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,     3,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    -1,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,     3,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,
      64,    -1,    -1,    -1,    82,    69,    -1,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,     3,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    -1,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    63,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    28,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    85,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    -1,    -1,    -1,    -1,
      -1,    85,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    63,    64,    -1,    -1,    -1,    -1,
      69,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    62,    69,   112,   113,   116,   117,   118,   119,
     125,   128,   129,   130,   131,   155,   156,   157,     3,    84,
     129,   128,   131,   132,    83,   114,   115,   129,   113,   113,
       3,    84,   113,   112,   113,   147,   159,    62,    64,   130,
       0,   156,    84,     3,   126,   127,    63,   128,   131,    67,
      83,    82,   147,   158,    84,   117,   120,   121,   122,   128,
     129,    84,   112,   146,   146,     3,    63,   113,   133,   134,
     135,   136,     3,     4,     5,     6,     8,     9,    62,    65,
      68,    69,    70,    71,    72,    73,    87,    88,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   102,
     103,   105,   111,   126,    82,    67,    85,   115,    84,    90,
     105,   108,   140,   146,   146,   120,   122,    85,   121,    81,
     123,   124,   129,   122,     3,    49,    50,    51,    53,    54,
      55,    56,    57,    58,    59,    60,    83,    85,   108,   110,
     142,   143,   145,   147,   148,   149,   151,   153,   154,    62,
      64,   129,   131,   138,   139,    63,    67,    63,    67,    62,
      90,    62,    90,    90,   110,   122,   137,     7,     8,     9,
      62,    64,    66,    92,    69,    74,    75,    70,    71,    10,
      11,    12,    13,    76,    77,    14,    15,    68,    78,    79,
      16,    17,   106,    65,    85,   111,   127,   140,   141,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    82,
     109,    85,   111,    67,    83,    81,    81,   111,    81,    62,
      62,   101,   101,    62,     3,    83,    83,    83,   110,    67,
      83,   144,    85,   148,    85,   101,    63,   133,   138,    65,
     111,   139,    62,    64,    48,   135,     3,   137,    63,    62,
     131,   138,    63,     3,    63,    89,   108,   110,     3,    92,
      92,    92,    93,    93,    94,    94,    95,    95,    95,    95,
      96,    96,    97,    98,    99,   101,   101,    80,    67,    85,
     108,   124,   111,   101,    81,   101,   110,   150,   110,    62,
     143,   149,    83,    83,   108,   146,    85,   143,    63,    63,
      65,    63,   133,    65,   111,    63,    92,    63,    67,    65,
     100,   102,   101,    85,   140,   143,   101,   143,    63,    63,
     150,    54,   101,    63,    65,   108,   110,   143,   101,   104,
      63,   101,   149,   152,    81,   143,   143,   101,    62,   101,
     101,   107,    52,   143,   150,   110,    63,   104,   104,    63,
      63,   143,   101,   101,    83,   104,   105,   143,   101,   143
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    87,    87,    87,    88,    88,    88,    88,
      88,    88,    88,    88,    89,    89,    90,    90,    90,    90,
      90,    90,    91,    91,    91,    91,    91,    91,    92,    92,
      93,    93,    93,    93,    94,    94,    94,    95,    95,    95,
      96,    96,    96,    96,    96,    97,    97,    97,    98,    98,
      99,    99,   100,   100,   101,   102,   102,   103,   103,   104,
     105,   106,   107,   105,   108,   108,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   110,   110,   111,
     112,   112,   113,   113,   113,   113,   113,   113,   114,   114,
     115,   115,   116,   116,   116,   116,   116,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   118,
     118,   118,   119,   119,   120,   120,   121,   122,   122,   122,
     122,   123,   123,   124,   124,   124,   125,   125,   125,   126,
     126,   127,   127,   128,   128,   129,   129,   130,   130,   130,
     130,   130,   130,   130,   131,   131,   131,   131,   132,   132,
     133,   133,   134,   134,   135,   135,   135,   136,   136,   137,
     137,   138,   138,   138,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   140,   140,   140,   141,   141,   142,   143,
     144,   143,   143,   143,   143,   143,   145,   145,   145,   146,
     146,   146,   146,   147,   147,   148,   148,   149,   149,   150,
     151,   151,   151,   152,   153,   153,   153,   153,   154,   154,
     154,   154,   154,   155,   155,   156,   156,   157,   158,   157,
     157,   159,   157
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     4,     3,     4,
       3,     3,     2,     2,     1,     3,     1,     2,     2,     2,
       2,     4,     1,     1,     1,     1,     1,     1,     1,     4,
       1,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       1,     3,     1,     3,     0,     1,     4,     1,     4,     0,
       1,     0,     0,    10,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       2,     3,     1,     2,     1,     2,     1,     2,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       4,     2,     1,     1,     1,     2,     3,     2,     1,     2,
       1,     1,     3,     1,     2,     3,     4,     5,     2,     1,
       3,     1,     3,     1,     1,     2,     1,     1,     3,     4,
       3,     4,     4,     3,     1,     2,     2,     3,     1,     2,
       1,     3,     1,     3,     2,     2,     1,     1,     3,     1,
       2,     1,     1,     2,     3,     2,     3,     3,     4,     2,
       3,     3,     4,     1,     3,     4,     1,     3,     0,     1,
       0,     3,     1,     1,     1,     1,     4,     5,     4,     2,
       3,     3,     4,     1,     2,     1,     3,     1,     2,     1,
       6,    10,     6,     1,     7,     9,     8,    11,     3,     2,
       2,     2,     3,     1,     2,     1,     1,     4,     0,     4,
       3,     0,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* primary_expression: IDENTIFIER  */
#line 245 "ansic.y"
                                        {	printf("primary_expression: IDENTIFIER\n");
								std::string *name = new std::string((yyvsp[0].name));
								symrec *s = getsym(name);
								if(s == nullptr){
									printf("Variable %s ", (yyvsp[0].name));
									yyerror("not declared");
								}
								//std::cout << "<" << *name << ">" << std::endl;
								(yyval.sym).name = name;
								(yyval.sym).var = s;
								(yyval.sym).typ = s->typ;
								(yyval.sym).dimlist = s->dimlist;
								(yyval.sym).plevel = 0;
							}
#line 1951 "ansic.tab.c"
    break;

  case 3: /* primary_expression: CONSTANT  */
#line 260 "ansic.y"
                                                {	printf("primary_expression: CONSTANT\n"); // Lleva atributo sym porque ira en la tabla de simbolos
								int typ = (yyvsp[0].valtype); // sintaxis para leer esa variable de la union, leer el tipo de la variable
								std::string *name;
								symrec* s;
								switch (typ){ // Para las constantes se usa un @ y un numero para diferenciar las constantes de las variables declaradas

									case DOUBLEVAL:
										name = newtemp(); // Crear nueva variable temporal // Le da un nombre temporal por defecto
										s = putsym(name, DOUBLEVAL | CONST_SPEC); // Se pone la constante en la tabla de simbolos y se agrega atributo CONST por constante y/o el tipo, en este caso DOUBLEVAL y name para indicar su nombre
										setval(s, (yyvsp[0].dval));// Para obtener el atributo 
										(yyval.sym).val.doubleval = (yyvsp[0].dval); // val esta en la esctructura VAR_DATA , es el valor inicial, que es a su vez estructura VALUE
										(yyval.sym).name = name;
										(yyval.sym).var = s; // Puntero hacia la variable
										(yyval.sym).typ = s->typ; // Para guardar el tipo
										break;
									case INTVAL:
										name = newtemp();
										s = putsym(name, INTVAL | CONST_SPEC);
										setval(s, (yyvsp[0].ival));
										(yyval.sym).val.intval = (yyvsp[0].ival);
										(yyval.sym).name = name;
										(yyval.sym).var = s;
										(yyval.sym).typ = s->typ;
										break;
									case CHARVAL:
										name = newtemp();
										s = putsym(name, CHARVAL | CONST_SPEC);
										setval(s, (yyvsp[0].cval));
										(yyval.sym).val.charval = (yyvsp[0].cval);
										(yyval.sym).name = name;
										(yyval.sym).var = s;
										(yyval.sym).typ = s->typ;
										break;
								}
							}
#line 1991 "ansic.tab.c"
    break;

  case 4: /* primary_expression: STRING_LITERAL  */
#line 296 "ansic.y"
                                        {	printf("primary_expression: STRING_LITERAL\n"); // Literales cadena
								std::string *name; //Para nombre de una variable temporal
								symrec* s; //Para variable o constante en la tabla de simbolos
								name = newtemp(); // Crear variable temporal
								s = putsym(name, STRVAL | CONST_SPEC); //Declarar constante cadena en tabla de simbolos
								s->size = strlen((yyvsp[0].sval)) + 1; // Poner atributo size de la cadena, calcular longitud, +1 para caracter nulo
								setval(s, (yyvsp[0].sval)); // Copiar cadena en bloque de datos, copiar byte por byte usando la funcion
								data_location(s->size); // Ajustar posicion libre en bloque dde datos, ajusta el bloque de datos para que tome en cuanta el tamaño de la variable
								(yyval.sym).var = s; // Asignar en atributos var la constante cadena de la tabla de simbolos
								(yyval.sym).typ = s->typ; // Asignar en atributo typ el tipo de la constante cadena
								(yyval.sym).name = new string(s->name); // Asignar en atributo name el nombre de la constante cadena
							}
#line 2008 "ansic.tab.c"
    break;

  case 5: /* primary_expression: '(' expression ')'  */
#line 309 "ansic.y"
                                {	printf("primary_expression: '(' expression ')'\n");
								(yyval.sym) = (yyvsp[-1].sym);
							}
#line 2016 "ansic.tab.c"
    break;

  case 6: /* postfix_expression: primary_expression  */
#line 316 "ansic.y"
                                                                                                {	printf("postfix_expression: primary_expression\n");
																(yyval.sym) = (yyvsp[0].sym); // Heredar el attributo de la var de la izquierda $ $ a la var de la derecha $ 1
															}
#line 2024 "ansic.tab.c"
    break;

  case 7: /* postfix_expression: postfix_expression '[' expression ']'  */
#line 320 "ansic.y"
                                                                                {	printf("postfix_expression: postfix_expression '[' expression ']'\n");
																if((yyvsp[-3].sym).var == NULL){
																	yyerror("Error: Array name must be specified");
																}
																if(!isintegral((yyvsp[-1].sym).typ)){
																	yyerror("Array subscript must be integral typ\n");
																}
																// plevel es el numero de subindices del arreglo se inicializan a cero en regla de primary_expression
																//cout << "\tplevel = " << $ 1.plevel << endl;
																if((yyvsp[-3].sym).plevel > 0){
																	/* Para el caso a[i][j]
																		postfix_expression = a[i]
																		expression = j
																	i (esta en bytes) se multilpica por N
																	j se multiplica por sizeof(type)
																	nuevo i = i*N + j*sizeof(type)
																	N es la dimension del subindice j
																	*/
																	std::string *name = newtemp(); // s0 = sizeof(type)
																	symrec *s0 = putsym(name, INTVAL | CONST_SPEC);
																	setval(s0, getsizeof((yyvsp[-3].sym).typ));
																	name = newtemp(); //s1 = N
																	symrec *s1 = putsym(name, INTVAL | CONST_SPEC);
																	setval(s1, getrdim((yyvsp[-3].sym).dimlist, (yyvsp[-3].sym).plevel - 1));
																	name = newtemp(); //s2 = j*sizeof(type)
																	symrec *s2 = putsym(name, INTVAL | VAR_SPEC);
																	gencode(MULT_IR, (yyvsp[-1].sym).var, s0, s2);
																	name = newtemp(); //s3 = i*N
																	symrec *s3 = putsym(name, INTVAL | VAR_SPEC);
																	gencode(MULT_IR, (yyvsp[-3].sym).var2, s1, s3);
																	name = newtemp(); //s4 = i*N + j*sizeof(type)
																	symrec *s4 = putsym(name, INTVAL | VAR_SPEC);
																	gencode(ADD_IR, s3, s2, s4);
																	(yyvsp[-3].sym).var2 = s4; //nuevo i = i*N + j*sizeof(type)															
																} 
																else {
																	/* Para el caso a[i]
																	postfix_expression = a
																	expression = i
																	i se multiplica por sizeof(type)
																	nuevo i = i*sizeof(type) */
																	std::string *name = newtemp(); // s1 = sizeof(type)
																	symrec *s1 = putsym(name, INTVAL | CONST_SPEC);
																	setval(s1, getsizeof((yyvsp[-3].sym).typ));
																	name = newtemp(); //s2 = i*sizeof(type)
																	symrec *s2 = putsym(name, INTVAL | VAR_SPEC);
																	gencode(MULT_IR, (yyvsp[-1].sym).var, s1, s2);
																	(yyvsp[-3].sym).var2 = s2; //nuevo i = i*sizeof(type)
																}
																// PENDIENTE A MODIFICAR
																(yyval.sym) = (yyvsp[-3].sym);
																(yyval.sym).typ |= ARRAY_SPEC; // agregar atributo spec por si no lo tiene
																(yyval.sym).plevel++; // Incrementar numero de subinidices;
															}
#line 2083 "ansic.tab.c"
    break;

  case 8: /* postfix_expression: postfix_expression '(' ')'  */
#line 375 "ansic.y"
                                                                                        {	printf("postfix_expression: postfix_expression '(' ')'\n");
																std::string *name = newtemp();
																symrec *s = putsym(name, (yyvsp[-2].sym).typ & 0x1f);
																gencode(CALL_IR, (yyvsp[-2].sym).var, NULL, s);
																(yyval.sym).var = s;
																(yyval.sym).typ = s->typ;
																(yyval.sym).name = name;
															}
#line 2096 "ansic.tab.c"
    break;

  case 9: /* postfix_expression: postfix_expression '(' argument_expression_list ')'  */
#line 384 "ansic.y"
                                                                {	printf("postfix_expression: postfix_expression '(' argument_expression_list ')'\n");
																std::list<VAR_DATA*>::reverse_iterator it;
																for(it = (yyvsp[-1].sym).arglist->rbegin(); it != (yyvsp[-1].sym).arglist->rend(); it++){
																	gencode(PARAM_IR, (*it)->var, nullptr, nullptr);
																}
																std::string *name = newtemp();
																symrec *s = putsym(name, (yyvsp[-3].sym).typ & 0x1f);
																symrec *s3 = new symrec();
																s3->name = "";
																s3->offset = (yyvsp[-1].sym).arglist->size();
																gencode(CALL_IR, (yyvsp[-3].sym).var, s3, s);
																(yyval.sym).var = s;
																(yyval.sym).typ = s->typ;
																(yyval.sym).name = name;
															}
#line 2116 "ansic.tab.c"
    break;

  case 10: /* postfix_expression: postfix_expression '.' IDENTIFIER  */
#line 400 "ansic.y"
                                                                                        {	printf("postfix_expression: postfix_expression '.' IDENTIFIER\n");
																;
															}
#line 2124 "ansic.tab.c"
    break;

  case 11: /* postfix_expression: postfix_expression PTR_OP IDENTIFIER  */
#line 404 "ansic.y"
                                                                                {	printf("postfix_expression: postfix_expression PTR_OP IDENTIFIER\n");
																;
															}
#line 2132 "ansic.tab.c"
    break;

  case 12: /* postfix_expression: postfix_expression INC_OP  */
#line 408 "ansic.y"
                                                                                                {	printf("postfix_expression: postfix_expression INC_OP\n");
																if(!isvar((yyvsp[-1].sym).typ)){
																	yyerror("Error: Increment operator requires a variable");
																}
																std::string *name = newtemp();
																symrec *s = putsym(name, (yyvsp[-1].sym).typ & 0x1f);
																gencode(STORE_IR, (yyvsp[-1].sym).var, NULL, s);
																gencode(INC_IR, (yyvsp[-1].sym).var, NULL, (yyvsp[-1].sym).var);
																(yyval.sym).var = s;
																(yyval.sym).typ = s->typ;
																(yyval.sym).name = name;
															}
#line 2149 "ansic.tab.c"
    break;

  case 13: /* postfix_expression: postfix_expression DEC_OP  */
#line 421 "ansic.y"
                                                                                                {	printf("postfix_expression: postfix_expression DEC_OP\n");
																if(!isvar((yyvsp[-1].sym).typ)){
																	yyerror("Error: Decrement operator requires a variable");
																}
																std::string *name = newtemp();
																symrec *s = putsym(name, (yyvsp[-1].sym).typ & 0x1f);
																gencode(STORE_IR, (yyvsp[-1].sym).var, NULL, s);
																// PENDIENTE A MODIFICAR
																gencode(DEC_IR, (yyvsp[-1].sym).var, NULL, (yyvsp[-1].sym).var);
																(yyval.sym).var = s;
																(yyval.sym).typ = s->typ;
																(yyval.sym).name = name;
															}
#line 2167 "ansic.tab.c"
    break;

  case 14: /* argument_expression_list: assignment_expression  */
#line 438 "ansic.y"
                                                                                                {	printf("argument_expression_list: assignment_expression\n");
																std::list<VAR_DATA*> *newlist = new std::list<VAR_DATA*>();
																VAR_DATA *newstruct = new VAR_DATA();
																*newstruct = (yyvsp[0].sym);
																newlist->push_back(newstruct);
																(yyval.sym).name = new std::string();
																(yyval.sym).typ = 0;
																(yyval.sym).arglist = newlist;
															}
#line 2181 "ansic.tab.c"
    break;

  case 15: /* argument_expression_list: argument_expression_list ',' assignment_expression  */
#line 448 "ansic.y"
                                                                {	printf("argument_expression_list: argument_expression_list ',' assignment_expression\n");
																VAR_DATA *newstruct = new VAR_DATA();
																*newstruct = (yyvsp[0].sym);
																(yyval.sym) = (yyvsp[-2].sym);
																(yyval.sym).arglist->push_back(newstruct);
															}
#line 2192 "ansic.tab.c"
    break;

  case 16: /* unary_expression: postfix_expression  */
#line 458 "ansic.y"
                                                        {	printf("unary_expression: postfix_expression\n");
											(yyval.sym) = (yyvsp[0].sym);
										}
#line 2200 "ansic.tab.c"
    break;

  case 17: /* unary_expression: INC_OP unary_expression  */
#line 462 "ansic.y"
                                                        {	printf("unary_expression: INC_OP unary_expression\n");
											if(!isvar((yyvsp[0].sym).typ)){
												yyerror("Error: Increment operator requires a variable");
											}
											gencode(INC_IR, (yyvsp[0].sym).var, NULL, (yyvsp[0].sym).var);
											(yyval.sym) = (yyvsp[0].sym);
										}
#line 2212 "ansic.tab.c"
    break;

  case 18: /* unary_expression: DEC_OP unary_expression  */
#line 470 "ansic.y"
                                                        {	printf("unary_expression: DEC_OP unary_expression\n");
											if(!isvar((yyvsp[0].sym).typ)){
												yyerror("Error: Decrement operator requires a variable");
											}
											gencode(DEC_IR, (yyvsp[0].sym).var, NULL, (yyvsp[0].sym).var);
											(yyval.sym) = (yyvsp[0].sym);
										}
#line 2224 "ansic.tab.c"
    break;

  case 19: /* unary_expression: unary_operator cast_expression  */
#line 478 "ansic.y"
                                                {	printf("unary_expression: unary_operator cast_expression\n");
											std::string *name;
											symrec *s;
											name = newtemp();
											// Para cada operador unario
											switch((yyvsp[-1].op)){
												case PLUS_OP:
													name = (yyvsp[0].sym).name;
													s = (yyvsp[0].sym).var;
													(yyval.sym).typ = (yyvsp[0].sym).typ;
													break;
												case ADDR_OP:
													name = newtemp();
													s = putsym(name, INTVAL);
													gencode(ADDRESS_IR, (yyvsp[0].sym).var, nullptr, s);
													(yyval.sym).typ = INTVAL;
													break;
												case DEREF_OP:
													name = newtemp();
													if(!ispointer((yyvsp[0].sym).typ)){
														yyerror("Error: OPERAND MUST BE A POINTER\n");
													}
													s = putsym(name, (yyvsp[0].sym).typ & ~POINTER_SPEC);
													gencode(DEREF_IR, (yyvsp[0].sym).var, nullptr, s);
													(yyval.sym).typ = (yyvsp[0].sym).typ;
													break;
												case MINUS_OP:
													name = newtemp();
													s = putsym(name, (yyvsp[0].sym).typ);
													gencode(MINUS_IR, (yyvsp[0].sym).var, nullptr, s);
													(yyval.sym).typ = (yyvsp[0].sym).typ;
													break;
												case ONESCOMP_OP:
													name = newtemp();
													s = putsym(name, INTVAL);
													gencode(ONECOMP_IR, (yyvsp[0].sym).var, nullptr, s);
													(yyval.sym).typ = INTVAL;
													break;
												case NOT_OP:
													name = newtemp();
													//s = putsym(name, INTVAL);
													gencode(NOT_IR, (yyvsp[0].sym).var, nullptr, s);
													tological(&((yyvsp[0].sym)));
													(yyval.sym).truelist = (yyvsp[0].sym).falselist;
													(yyval.sym).falselist = (yyvsp[0].sym).falselist;
													(yyval.sym).typ = INTVAL;
													break;
											}
												(yyval.sym).name = name;
												(yyval.sym).var = s;											
										}
#line 2280 "ansic.tab.c"
    break;

  case 20: /* unary_expression: SIZEOF unary_expression  */
#line 530 "ansic.y"
                                                        {	printf("unary_expression: SIZEOF unary_expression\n");
											std::string *name = newtemp();
											symrec *s = putsym(name, INTVAL | CONST_SPEC);
											int sz = getsizeof((yyvsp[0].sym).typ);
											setval(s, sz);
											(yyval.sym).var = s;
											(yyval.sym).typ = s->typ;
											(yyval.sym).name = name;
										}
#line 2294 "ansic.tab.c"
    break;

  case 21: /* unary_expression: SIZEOF '(' type_name ')'  */
#line 540 "ansic.y"
                                                        {	printf("unary_expression: SIZEOF '(' type_name ')'\n");
											std::string *name = newtemp();
											symrec *s = putsym(name, INTVAL | CONST_SPEC);
											int sz = getsizeof((yyvsp[-1].typ));
											setval(s, sz);
											(yyval.sym).var = s;
											(yyval.sym).typ = s->typ;
											(yyval.sym).name = name;
										}
#line 2308 "ansic.tab.c"
    break;

  case 22: /* unary_operator: '&'  */
#line 553 "ansic.y"
                {	printf("unary_operator: '&'\n");
				(yyval.op) = ADDR_OP;
			}
#line 2316 "ansic.tab.c"
    break;

  case 23: /* unary_operator: '*'  */
#line 557 "ansic.y"
                {	printf("unary_operator: '*'\n");
				(yyval.op) = DEREF_OP;
			}
#line 2324 "ansic.tab.c"
    break;

  case 24: /* unary_operator: '+'  */
#line 561 "ansic.y"
                {	printf("unary_operator: '+'\n");
				(yyval.op) = PLUS_OP;
			}
#line 2332 "ansic.tab.c"
    break;

  case 25: /* unary_operator: '-'  */
#line 565 "ansic.y"
                {	printf("unary_operator: '-'\n");
				(yyval.op) = MINUS_OP;
			}
#line 2340 "ansic.tab.c"
    break;

  case 26: /* unary_operator: '~'  */
#line 569 "ansic.y"
                {	printf("unary_operator: '~'\n");
				(yyval.op) = ONESCOMP_OP;
			}
#line 2348 "ansic.tab.c"
    break;

  case 27: /* unary_operator: '!'  */
#line 573 "ansic.y"
                {	printf("unary_operator: '!'\n");
				(yyval.op) = NOT_OP;
			}
#line 2356 "ansic.tab.c"
    break;

  case 28: /* cast_expression: unary_expression  */
#line 580 "ansic.y"
                                                                        {	printf("cast_expression: unary_expression\n");
												(yyval.sym) = (yyvsp[0].sym);
												if(isarray((yyvsp[0].sym).typ)){
													
													string *name = newtemp();
													symrec *s = putsym(name, (yyvsp[0].sym).typ & ~ARRAY_SPEC);
													gencode(LOADA_IR, (yyvsp[0].sym).var, (yyvsp[0].sym).var2, s);
													(yyval.sym).name = name;
													(yyval.sym).typ = s->typ;
													(yyval.sym).var = s;
												}
											}
#line 2373 "ansic.tab.c"
    break;

  case 29: /* cast_expression: '(' type_name ')' cast_expression  */
#line 593 "ansic.y"
                                                        {	printf("cast_expression: '(' type_name ')' cast_expression\n");
												std::string* name = newtemp();
												symrec *s;
												int typ = (yyvsp[-2].typ) & 0x1f;
												switch(typ){
													case CHARVAL:
														s = putsym(name, CHARVAL | VAR_SPEC);
														gencode(CHAR_IR, (yyvsp[0].sym).var, NULL, s);
														break;
													case INTVAL:
														s = putsym(name, INTVAL | VAR_SPEC);
														gencode(INT_IR, (yyvsp[0].sym).var, NULL, s);
														break;
													case FVAL:
														s = putsym(name, FVAL | VAR_SPEC);
														gencode(FLOAT_IR, (yyvsp[0].sym).var, NULL, s);
														break;
													case DOUBLEVAL:
														s = putsym(name, FVAL | VAR_SPEC);
														gencode(DOUBLE_IR, (yyvsp[0].sym).var, NULL, s);
														break;
												}
												(yyval.sym).name = name;
												(yyval.sym).typ = s->typ;
												(yyval.sym).var = s;
											}
#line 2404 "ansic.tab.c"
    break;

  case 30: /* multiplicative_expression: cast_expression  */
#line 623 "ansic.y"
                                                                                        {	printf("multiplicative_expression: cast_expression\n");
														(yyval.sym) = (yyvsp[0].sym);
													}
#line 2412 "ansic.tab.c"
    break;

  case 31: /* multiplicative_expression: multiplicative_expression '*' cast_expression  */
#line 627 "ansic.y"
                                                        {	printf("multiplicative_expression: multiplicative_expression '*' cast_expression\n");
														int typ = gettype((yyvsp[-2].sym).typ, (yyvsp[0].sym).typ) & 0x1f;
														std::string* name = newtemp();
														symrec *s;
														s = putsym(name, typ | VAR_SPEC);
														if(((yyvsp[-2].sym).typ & 0x1f) == ((yyvsp[0].sym).typ & 0x1f)){
															gencode(MULT_IR, (yyvsp[-2].sym).var, (yyvsp[0].sym).var, s);
														}
														else{
															symrec* s2;
															if(((yyvsp[-2].sym).typ & 0x1f) == typ){
																s2 = genconv(typ, (yyvsp[0].sym).var);
																gencode(MULT_IR, (yyvsp[-2].sym).var, s2, s);
															}
															else{
																s2 = genconv(typ, (yyvsp[-2].sym).var);
																gencode(MULT_IR, s2, (yyvsp[0].sym).var, s);
															}
														}
														(yyval.sym).var = s;
														(yyval.sym).typ = s->typ;
														(yyval.sym).name = name;
													}
#line 2440 "ansic.tab.c"
    break;

  case 32: /* multiplicative_expression: multiplicative_expression '/' cast_expression  */
#line 651 "ansic.y"
                                                        {	printf("multiplicative_expression: multiplicative_expression '/' cast_expression\n");
														int typ = gettype((yyvsp[-2].sym).typ, (yyvsp[0].sym).typ) & 0x1f;
														std::string* name = newtemp();
														symrec *s;
														s = putsym(name, typ | VAR_SPEC);
														if(((yyvsp[-2].sym).typ & 0x1f) == ((yyvsp[0].sym).typ & 0x1f)){
															gencode(DIV_IR, (yyvsp[-2].sym).var, (yyvsp[0].sym).var, s);
														}
														else{
															symrec* s2;
															if(((yyvsp[-2].sym).typ & 0x1f) == typ){
																s2 = genconv(typ, (yyvsp[0].sym).var);
																gencode(DIV_IR, (yyvsp[-2].sym).var, s2, s);
															}
															else{
																s2 = genconv(typ, (yyvsp[-2].sym).var);
																gencode(DIV_IR, s2, (yyvsp[0].sym).var, s);
															}
														}
														(yyval.sym).var = s;
														(yyval.sym).typ = s->typ;
														(yyval.sym).name = name;
													}
#line 2468 "ansic.tab.c"
    break;

  case 33: /* multiplicative_expression: multiplicative_expression '%' cast_expression  */
#line 675 "ansic.y"
                                                        {	printf("multiplicative_expression: multiplicative_expression 'percent' cast_expression\n");
														int typ = gettype((yyvsp[-2].sym).typ, (yyvsp[0].sym).typ) & 0x1f;
														std::string* name = newtemp();
														symrec *s;
														s = putsym(name, typ | VAR_SPEC);
														if(((yyvsp[-2].sym).typ & 0x1f) == ((yyvsp[0].sym).typ & 0x1f)){
															gencode(MOD_IR, (yyvsp[-2].sym).var, (yyvsp[0].sym).var, s);
														}
														else{
															symrec* s2;
															if(((yyvsp[-2].sym).typ & 0x1f) == typ){
																s2 = genconv(typ, (yyvsp[0].sym).var);
																gencode(MOD_IR, (yyvsp[-2].sym).var, s2, s);
															}
															else{
																s2 = genconv(typ, (yyvsp[-2].sym).var);
																gencode(MOD_IR, s2, (yyvsp[0].sym).var, s);
															}
														}
														(yyval.sym).var = s;
														(yyval.sym).typ = s->typ;
														(yyval.sym).name = name;
													}
#line 2496 "ansic.tab.c"
    break;

  case 34: /* additive_expression: multiplicative_expression  */
#line 702 "ansic.y"
                                                                                        {	printf("additive_expression: multiplicative_expression\n");
															(yyval.sym) = (yyvsp[0].sym);
														}
#line 2504 "ansic.tab.c"
    break;

  case 35: /* additive_expression: additive_expression '+' multiplicative_expression  */
#line 706 "ansic.y"
                                                                {	printf("additive_expression: additive_expression '+' multiplicative_expression\n");
															int typ = gettype((yyvsp[-2].sym).typ, (yyvsp[0].sym).typ) & 0x1f;
															std::string* name = newtemp();
															symrec *s;
															s = putsym(name, typ | VAR_SPEC);
															if(((yyvsp[-2].sym).typ & 0x1f) == ((yyvsp[0].sym).typ & 0x1f)){
																gencode(ADD_IR, (yyvsp[-2].sym).var, (yyvsp[0].sym).var, s);
															}
															else{
																symrec* s2;
																if(((yyvsp[-2].sym).typ & 0x1f) == typ){
																	s2 = genconv(typ, (yyvsp[0].sym).var);
																	gencode(ADD_IR, (yyvsp[-2].sym).var, s2, s);
																}
																else{
																	s2 = genconv(typ, (yyvsp[-2].sym).var);
																	gencode(ADD_IR, s2, (yyvsp[0].sym).var, s);
																}
															}
															(yyval.sym).var = s;
															(yyval.sym).typ = s->typ;
															(yyval.sym).name = name;
														}
#line 2532 "ansic.tab.c"
    break;

  case 36: /* additive_expression: additive_expression '-' multiplicative_expression  */
#line 730 "ansic.y"
                                                                {	printf("additive_expression: additive_expression '-' multiplicative_expression\n");
															int typ = gettype((yyvsp[-2].sym).typ, (yyvsp[0].sym).typ) & 0x1f;
															std::string* name = newtemp();
															symrec *s;
															s = putsym(name, typ | VAR_SPEC);
															if(((yyvsp[-2].sym).typ & 0x1f) == ((yyvsp[0].sym).typ & 0x1f)){
																gencode(SUB_IR, (yyvsp[-2].sym).var, (yyvsp[0].sym).var, s);
															}
															else{
																symrec* s2;
																if(((yyvsp[-2].sym).typ & 0x1f) == typ){
																	s2 = genconv(typ, (yyvsp[0].sym).var);
																	gencode(SUB_IR, (yyvsp[-2].sym).var, s2, s);
																}
																else{
																	s2 = genconv(typ, (yyvsp[-2].sym).var);
																	gencode(SUB_IR, s2, (yyvsp[0].sym).var, s);
																}
															}
															(yyval.sym).var = s;
															(yyval.sym).typ = s->typ;
															(yyval.sym).name = name;
														}
#line 2560 "ansic.tab.c"
    break;

  case 37: /* shift_expression: additive_expression  */
#line 757 "ansic.y"
                                                                                {	printf("shift_expression: additive_expression\n");
														(yyval.sym) = (yyvsp[0].sym);
													}
#line 2568 "ansic.tab.c"
    break;

  case 38: /* shift_expression: shift_expression LEFT_OP additive_expression  */
#line 761 "ansic.y"
                                                        {	printf("shift_expression: shift_expression LEFT_OP additive_expression\n");
														int typ = gettype((yyvsp[-2].sym).typ, (yyvsp[0].sym).typ) & 0x1f;
														if(!isintegral((yyvsp[-2].sym).typ & 0x1f)){
															yyerror("Left hand side of left shift operator must be integer\n");
														}
														if(!isintegral((yyvsp[0].sym).typ & 0x1f)){
															yyerror("Right hand side of left shift operator must be integer\n");
														}
														std::string* name = newtemp();
														symrec *s;
														s = putsym(name, typ | VAR_SPEC);
														if(((yyvsp[-2].sym).typ & 0x1f) == ((yyvsp[0].sym).typ & 0x1f)){
															gencode(LSHIFT_IR, (yyvsp[-2].sym).var, (yyvsp[0].sym).var, s);
														}
														else{
															symrec* s2;
															if(((yyvsp[-2].sym).typ & 0x1f) == typ){
																s2 = genconv(typ, (yyvsp[0].sym).var);
																gencode(LSHIFT_IR, (yyvsp[-2].sym).var, s2, s);
															}
															else{
																s2 = genconv(typ, (yyvsp[-2].sym).var);
																gencode(LSHIFT_IR, s2, (yyvsp[0].sym).var, s);
															}
														}
														(yyval.sym).var = s;
														(yyval.sym).typ = s->typ;
														(yyval.sym).name = name;
													}
#line 2602 "ansic.tab.c"
    break;

  case 39: /* shift_expression: shift_expression RIGHT_OP additive_expression  */
#line 791 "ansic.y"
                                                        {	printf("shift_expression: shift_expression RIGHT_OP additive_expression\n");
														int typ = gettype((yyvsp[-2].sym).typ, (yyvsp[0].sym).typ) & 0x1f;
														if(!isintegral((yyvsp[-2].sym).typ & 0x1f)){
															yyerror("Left hand side of right shift operator must be integer\n");
														}
														if(!isintegral((yyvsp[0].sym).typ & 0x1f)){
															yyerror("Right hand side of right shift operator must be integer\n");
														}
														std::string* name = newtemp();
														symrec *s;
														s = putsym(name, typ | VAR_SPEC);
														if(((yyvsp[-2].sym).typ & 0x1f) == ((yyvsp[0].sym).typ & 0x1f)){
															gencode(RSHIFT_IR, (yyvsp[-2].sym).var, (yyvsp[0].sym).var, s);
														}
														else{
															symrec* s2;
															if(((yyvsp[-2].sym).typ & 0x1f) == typ){
																s2 = genconv(typ, (yyvsp[0].sym).var);
																gencode(RSHIFT_IR, (yyvsp[-2].sym).var, s2, s);
															}
															else{
																s2 = genconv(typ, (yyvsp[-2].sym).var);
																gencode(RSHIFT_IR, s2, (yyvsp[0].sym).var, s);
															}
														}
														(yyval.sym).var = s;
														(yyval.sym).typ = s->typ;
														(yyval.sym).name = name;
													}
#line 2636 "ansic.tab.c"
    break;

  case 40: /* relational_expression: shift_expression  */
#line 824 "ansic.y"
                                                                                        {	printf("relational_expression: shift_expression\n");
														(yyval.sym) = (yyvsp[0].sym);
													}
#line 2644 "ansic.tab.c"
    break;

  case 41: /* relational_expression: relational_expression '<' shift_expression  */
#line 828 "ansic.y"
                                                        {	printf("relational_expression: relational_expression '<' shift_expression\n");
														int typ = gettype((yyvsp[-2].sym).typ, (yyvsp[0].sym).typ) & 0x1f;
															symrec *s1 = (yyvsp[-2].sym).var, *s2 = (yyvsp[0].sym).var;
															if(((yyvsp[-2].sym).typ & 0x1f) != ((yyvsp[0].sym).typ & 0x1f)){
																if(((yyvsp[-2].sym).typ & 0x1f) == typ){
																	s2 = genconv(typ, (yyvsp[0].sym).var);
																}
																else{ // Conversion del segundo operando
																	s1 = genconv(typ, (yyvsp[-2].sym).var);
																}
															}
															(yyval.sym).truelist = makelist(nextinstr);
															gencode(IF_LT_IR, s1, s2, nullptr);
															(yyval.sym).falselist = makelist(nextinstr);
															gencode(GOTO_IR);
													}
#line 2665 "ansic.tab.c"
    break;

  case 42: /* relational_expression: relational_expression '>' shift_expression  */
#line 845 "ansic.y"
                                                        {	printf("relational_expression: relational_expression '>' shift_expression\n");
														int typ = gettype((yyvsp[-2].sym).typ, (yyvsp[0].sym).typ) & 0x1f;
															symrec *s1 = (yyvsp[-2].sym).var, *s2 = (yyvsp[0].sym).var;
															if(((yyvsp[-2].sym).typ & 0x1f) != ((yyvsp[0].sym).typ & 0x1f)){
																if(((yyvsp[-2].sym).typ & 0x1f) == typ){
																	s2 = genconv(typ, (yyvsp[0].sym).var);
																}
																else{ // Conversion del segundo operando
																	s1 = genconv(typ, (yyvsp[-2].sym).var);
																}
															}
															(yyval.sym).truelist = makelist(nextinstr);
															gencode(IF_GT_IR, s1, s2, nullptr);
															(yyval.sym).falselist = makelist(nextinstr);
															gencode(GOTO_IR);
													}
#line 2686 "ansic.tab.c"
    break;

  case 43: /* relational_expression: relational_expression LE_OP shift_expression  */
#line 862 "ansic.y"
                                                        {	printf("relational_expression: relational_expression LE_OP shift_expression\n");
														int typ = gettype((yyvsp[-2].sym).typ, (yyvsp[0].sym).typ) & 0x1f;
															symrec *s1 = (yyvsp[-2].sym).var, *s2 = (yyvsp[0].sym).var;
															if(((yyvsp[-2].sym).typ & 0x1f) != ((yyvsp[0].sym).typ & 0x1f)){
																if(((yyvsp[-2].sym).typ & 0x1f) == typ){
																	s2 = genconv(typ, (yyvsp[0].sym).var);
																}
																else{ // Conversion del segundo operando
																	s1 = genconv(typ, (yyvsp[-2].sym).var);
																}
															}
															(yyval.sym).truelist = makelist(nextinstr);
															gencode(IF_LE_IR, s1, s2, nullptr);
															(yyval.sym).falselist = makelist(nextinstr);
															gencode(GOTO_IR);
													}
#line 2707 "ansic.tab.c"
    break;

  case 44: /* relational_expression: relational_expression GE_OP shift_expression  */
#line 879 "ansic.y"
                                                        {	printf("relational_expression: relational_expression GE_OP shift_expression\n");
														int typ = gettype((yyvsp[-2].sym).typ, (yyvsp[0].sym).typ) & 0x1f;
															symrec *s1 = (yyvsp[-2].sym).var, *s2 = (yyvsp[0].sym).var;
															if(((yyvsp[-2].sym).typ & 0x1f) != ((yyvsp[0].sym).typ & 0x1f)){
																if(((yyvsp[-2].sym).typ & 0x1f) == typ){
																	s2 = genconv(typ, (yyvsp[0].sym).var);
																}
																else{ // Conversion del segundo operando
																	s1 = genconv(typ, (yyvsp[-2].sym).var);
																}
															}
															(yyval.sym).truelist = makelist(nextinstr);
															gencode(IF_GE_IR, s1, s2, nullptr);
															(yyval.sym).falselist = makelist(nextinstr);
															gencode(GOTO_IR);
													}
#line 2728 "ansic.tab.c"
    break;

  case 45: /* equality_expression: relational_expression  */
#line 899 "ansic.y"
                                                                                        {	printf("equality_expression: relational_expression\n");
															(yyval.sym) = (yyvsp[0].sym);
														}
#line 2736 "ansic.tab.c"
    break;

  case 46: /* equality_expression: equality_expression EQ_OP relational_expression  */
#line 903 "ansic.y"
                                                                {	printf("equality_expression: equality_expression EQ_OP relational_expression\n");
															int typ = gettype((yyvsp[-2].sym).typ, (yyvsp[0].sym).typ) & 0x1f;
															symrec *s1 = (yyvsp[-2].sym).var, *s2 = (yyvsp[0].sym).var;
															if(((yyvsp[-2].sym).typ & 0x1f) != ((yyvsp[0].sym).typ & 0x1f)){
																if(((yyvsp[-2].sym).typ & 0x1f) == typ){
																	s2 = genconv(typ, (yyvsp[0].sym).var);
																}
																else{ // Conversion del segundo operando
																	s1 = genconv(typ, (yyvsp[-2].sym).var);
																}
															}
															(yyval.sym).truelist = makelist(nextinstr);
															gencode(IF_EQ_IR, s1, s2, nullptr);
															(yyval.sym).falselist = makelist(nextinstr);
															gencode(GOTO_IR);
														}
#line 2757 "ansic.tab.c"
    break;

  case 47: /* equality_expression: equality_expression NE_OP relational_expression  */
#line 920 "ansic.y"
                                                                {	printf("equality_expression: equality_expression NE_OP relational_expression\n");
															int typ = gettype((yyvsp[-2].sym).typ, (yyvsp[0].sym).typ) & 0x1f;
															symrec* s1 = (yyvsp[-2].sym).var, *s2 = (yyvsp[0].sym).var;
															if(((yyvsp[-2].sym).typ & 0x1f) != ((yyvsp[0].sym).typ & 0x1f)){
																if(((yyvsp[-2].sym),typ & 0x1f) == typ){
																	s2 = genconv(typ, (yyvsp[0].sym).var);
																}
																else{
																	s1 = genconv(typ, (yyvsp[-2].sym).var);
																}
															}
															(yyval.sym).truelist = makelist(nextinstr);
															gencode(IF_NE_IR, s1, s2, nullptr);
															(yyval.sym).falselist = makelist(nextinstr);
															gencode(GOTO_IR);
														}
#line 2778 "ansic.tab.c"
    break;

  case 48: /* and_expression: equality_expression  */
#line 940 "ansic.y"
                                                                        {	printf("and_expression: equality_expression\n");
													(yyval.sym) = (yyvsp[0].sym);
												}
#line 2786 "ansic.tab.c"
    break;

  case 49: /* and_expression: and_expression '&' equality_expression  */
#line 944 "ansic.y"
                                                        {	printf("and_expression: and_expression '&' equality_expression\n");
													int typ = gettype((yyvsp[-2].sym).typ, (yyvsp[0].sym).typ) & 0x1f;
													std::string* name = newtemp();
													symrec *s = putsym(name, typ);
													if(((yyvsp[-2].sym).typ & 0x1f) == ((yyvsp[0].sym).typ & 0x1f)){
														gencode(AND_IR, (yyvsp[-2].sym).var, (yyvsp[0].sym).var, s);
													}
													else{
														symrec* s2;
														if(((yyvsp[-2].sym).typ & 0x1f) == typ){
															s2 = genconv(typ, (yyvsp[0].sym).var);
															gencode(AND_IR, (yyvsp[-2].sym).var, s2, s);
														}
														else{
															s2 = genconv(typ, (yyvsp[-2].sym).var);
															gencode(AND_IR, s2, (yyvsp[0].sym).var, s);
														}
													}
													(yyval.sym).var = s;
													(yyval.sym).typ = s->typ;
													(yyval.sym).name = name;
												}
#line 2813 "ansic.tab.c"
    break;

  case 50: /* exclusive_or_expression: and_expression  */
#line 970 "ansic.y"
                                                                                        {	printf("exclusive_or_expression: and_expression\n");
														(yyval.sym) = (yyvsp[0].sym);
													}
#line 2821 "ansic.tab.c"
    break;

  case 51: /* exclusive_or_expression: exclusive_or_expression '^' and_expression  */
#line 974 "ansic.y"
                                                        {	printf("exclusive_or_expression: exclusive_or_expression '^' and_expression\n");
														int typ = gettype((yyvsp[-2].sym).typ, (yyvsp[0].sym).typ) & 0x1f;
														std::string* name = newtemp();
														symrec *s = putsym(name, typ);
														if(((yyvsp[-2].sym).typ & 0x1f) == ((yyvsp[0].sym).typ & 0x1f)){
															gencode(XOR_IR, (yyvsp[-2].sym).var, (yyvsp[0].sym).var, s);
														}
														else{
															symrec* s2;
															if(((yyvsp[-2].sym).typ & 0x1f) == typ){
																s2 = genconv(typ, (yyvsp[0].sym).var);
																gencode(XOR_IR, (yyvsp[-2].sym).var, s2, s);
															}
															else{
																s2 = genconv(typ, (yyvsp[-2].sym).var);
																gencode(XOR_IR, s2, (yyvsp[0].sym).var, s);
															}
														}
														(yyval.sym).var = s;
														(yyval.sym).typ = s->typ;
														(yyval.sym).name = name;
													}
#line 2848 "ansic.tab.c"
    break;

  case 52: /* inclusive_or_expression: exclusive_or_expression  */
#line 1000 "ansic.y"
                                                                                                {	printf("inclusive_or_expression: exclusive_or_expression\n");
																(yyval.sym) = (yyvsp[0].sym);
															}
#line 2856 "ansic.tab.c"
    break;

  case 53: /* inclusive_or_expression: inclusive_or_expression '|' exclusive_or_expression  */
#line 1004 "ansic.y"
                                                                {	printf("inclusive_or_expression: inclusive_or_expression '|' exclusive_or_expression\n");
																int typ = gettype((yyvsp[-2].sym).typ, (yyvsp[0].sym).typ) & 0x1f;
																std::string* name = newtemp();
																symrec* s = putsym(name, typ);
																if(((yyvsp[-2].sym).typ & 0x1f) == ((yyvsp[0].sym).typ & 0x1f)){
																	gencode(OR_IR, (yyvsp[-2].sym).var, (yyvsp[0].sym).var, s);
																}
																else{
																	symrec* s2;
																	if(((yyvsp[-2].sym).typ & 0x1f) == typ){
																		s2 = genconv(typ, (yyvsp[0].sym).var);
																		gencode(OR_IR, (yyvsp[-2].sym).var, s2, s);
																	}
																	else{
																		s2 = genconv(typ, (yyvsp[-2].sym).var);
																		gencode(OR_IR, s2, (yyvsp[0].sym).var, s);
																	}
																}
																(yyval.sym).var = s;
																(yyval.sym).typ = s->typ;
																(yyval.sym).name = name;
															}
#line 2883 "ansic.tab.c"
    break;

  case 54: /* N: %empty  */
#line 1030 "ansic.y"
                                        {	// Esta regla sirve para capturar direccion de siguiente instruccion de IR
							(yyval.instr) = nextinstr;
						}
#line 2891 "ansic.tab.c"
    break;

  case 55: /* logical_and_expression: inclusive_or_expression  */
#line 1037 "ansic.y"
                                                                                                        {	printf("logical_and_expression: inclusive_or_expression\n");
																	(yyval.sym) = (yyvsp[0].sym);
																}
#line 2899 "ansic.tab.c"
    break;

  case 56: /* logical_and_expression: logical_and_expression AND_OP N inclusive_or_expression  */
#line 1041 "ansic.y"
                                                                        {	printf("logical_and_expression: logical_and_expression AND_OP inclusive_or_expression\n");
																	backpatch((yyvsp[-3].sym).truelist, (yyvsp[-1].instr));
																	(yyval.sym).truelist = (yyvsp[0].sym).truelist;
																	(yyval.sym).falselist = (yyvsp[-3].sym).falselist;
																	(yyval.sym).falselist->merge(*((yyvsp[0].sym).falselist));
																	(yyval.sym).typ = INTVAL; // Un valor logico es entero
																}
#line 2911 "ansic.tab.c"
    break;

  case 57: /* logical_or_expression: logical_and_expression  */
#line 1052 "ansic.y"
                                                                                                {	printf("logical_or_expression: logical_and_expression\n");
																(yyval.sym) = (yyvsp[0].sym);
															}
#line 2919 "ansic.tab.c"
    break;

  case 58: /* logical_or_expression: logical_or_expression OR_OP N logical_and_expression  */
#line 1056 "ansic.y"
                                                                {	printf("logical_or_expression: logical_or_expression OR_OP logical_and_expression\n");
																backpatch((yyvsp[-3].sym).falselist, (yyvsp[-1].instr));
																(yyval.sym).falselist = (yyvsp[0].sym).falselist;
																(yyval.sym).truelist = (yyvsp[-3].sym).truelist;
																(yyval.sym).truelist->merge(*((yyvsp[0].sym).truelist));
																(yyval.sym).typ = INTVAL; // Un valor logico es entero
															}
#line 2931 "ansic.tab.c"
    break;

  case 59: /* M: %empty  */
#line 1067 "ansic.y"
                                {	// Agregar direccion de siguiente instruccion de IR en atributo nextlist y generar instruccion de salto pendiente
						(yyval.lists).nextlist = makelist(nextinstr);
						gencode(GOTO_IR);
					}
#line 2940 "ansic.tab.c"
    break;

  case 60: /* conditional_expression: logical_or_expression  */
#line 1076 "ansic.y"
                                                                                                                                {	printf("conditional_expression: logical_or_expression\n");
																				(yyval.sym) = (yyvsp[0].sym);
																			}
#line 2948 "ansic.tab.c"
    break;

  case 61: /* $@1: %empty  */
#line 1080 "ansic.y"
                                                                                                                        {	
																			// Verificar si logical_or_expression es logica si no lo es,
																			//generar codigo para comparar con 0
																			if((yyvsp[0].sym).truelist == nullptr || (yyvsp[0].sym).falselist == nullptr){ 
																				std::string* name = newtemp();
																				symrec* s0;
																				if(isfloat((yyvsp[0].sym).typ)){
																					s0 = putsym(name, FVAL | CONST_SPEC);
																					setval(s0, 0.0f);
																				}
																				else{
																					s0 = putsym(name, INTVAL | CONST_SPEC);
																					setval(s0, 0);
																				}
																				(yyvsp[0].sym).truelist = makelist(nextinstr);
																				gencode(IF_NE_IR, (yyvsp[0].sym).var, s0, nullptr);
																				(yyvsp[0].sym).falselist = makelist(nextinstr);
																				gencode(GOTO_IR);
																			}

																		}
#line 2974 "ansic.tab.c"
    break;

  case 62: /* $@2: %empty  */
#line 1102 "ansic.y"
                                                                                                                        {	
																			std::string* name = newtemp();
																			symrec* s = putsym(name, (yyvsp[-1].sym).typ & ~CONST_SPEC | VAR_SPEC);
																			gencode(STORE_IR, (yyvsp[-1].sym).var, NULL, s);
																			(yyvsp[-1].sym).var = s;
																			(yyvsp[-1].sym).typ = s->typ;
																		}
#line 2986 "ansic.tab.c"
    break;

  case 63: /* conditional_expression: logical_or_expression $@1 '?' N expression ':' $@2 M N conditional_expression  */
#line 1110 "ansic.y"
                                                                                                                        {
																			printf("conditional_expression: logical_or_expression '?' expression ':' conditional_expression\n");
																			gencode(STORE_IR, (yyvsp[0].sym).var, NULL, (yyvsp[-5].sym).var);
																			(yyval.sym).var = (yyvsp[-5].sym).var;
																			(yyval.sym).typ = (yyvsp[-5].sym).typ;
																			backpatch((yyvsp[-9].sym).truelist, (yyvsp[-6].instr));
																			backpatch((yyvsp[-9].sym).falselist, (yyvsp[-1].instr));
																			backpatch((yyvsp[-2].lists).nextlist, nextinstr);
																			(yyval.sym).truelist = nullptr;
																			(yyval.sym).falselist = nullptr;
																		}
#line 3002 "ansic.tab.c"
    break;

  case 64: /* assignment_expression: conditional_expression  */
#line 1125 "ansic.y"
                                                                                                                {	printf("assignment_expression: conditional_expression\n");
																		(yyval.sym) = (yyvsp[0].sym);
																	}
#line 3010 "ansic.tab.c"
    break;

  case 65: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 1129 "ansic.y"
                                                                        {	printf("assignment_expression: unary_expression assignment_operator assignment_expression\n");
																		string *name;
																		symrec *s, *s2, *s3;
																		if((yyvsp[0].sym).truelist || (yyvsp[0].sym).falselist){
																			std::string *name = newtemp();
																			symrec *s1, *s0;
																			s0 = putsym(name, INTVAL | CONST_SPEC);
																			*(int*)(datablock + s0->offset) = 0; // Valor logico 0
																			name = newtemp();
																			s1 = putsym(name, INTVAL | CONST_SPEC);
																			*(int*)(datablock + s1->offset) = 1; // Valor logico 1
																			name = newtemp();
																			(yyvsp[0].sym).var = putsym(name, INTVAL | VAR_SPEC);
																			(yyvsp[0].sym).typ = INTVAL | VAR_SPEC;
																			(yyvsp[0].sym).name = name;
																			backpatch((yyvsp[0].sym).truelist, nextinstr);
																			gencode(STORE_IR, s1, nullptr, (yyvsp[0].sym).var);
																			gencode(GOTO_IR, nullptr, nullptr, nextinstr + 2);
																			backpatch((yyvsp[0].sym).falselist, nextinstr);
																			gencode(STORE_IR, s0, nullptr, (yyvsp[0].sym).var);
																		}
																		switch((yyvsp[-1].asop)){
																			case EQ_ASSIGN_OP:
																				if(!isarray((yyvsp[-2].sym).typ)){
																					if(((yyvsp[0].sym).typ & 0x1f) == ((yyvsp[-2].sym).typ & 0x1f)){
																						gencode(STORE_IR, (yyvsp[0].sym).var, nullptr, (yyvsp[-2].sym).var);
																					}
																					else{
																						s3 = genconv((yyvsp[-2].sym).typ, (yyvsp[0].sym).var);
																						gencode(STORE_IR, s3, nullptr, (yyvsp[-2].sym).var);
																					}
																				} else {
																					if(((yyvsp[0].sym).typ & 0x1f) == ((yyvsp[-2].sym).typ & 0x1f))
																						gencode(STOREA_IR, (yyvsp[0].sym).var, (yyvsp[-2].sym).var2, (yyvsp[-2].sym).var);
																					else{
																						s3 = genconv((yyvsp[-2].sym).typ, (yyvsp[0].sym).var);
																						gencode(STOREA_IR, s3, (yyvsp[-2].sym).var2, (yyvsp[-2].sym).var);
																					}
																				}
																				break;
																			case MUL_ASSIGN_OP:
																				genassign(MULT_IR, &(yyvsp[-2].sym), &(yyvsp[0].sym));
																				break;
																			case DIV_ASSIGN_OP:
																				genassign(DIV_IR, &(yyvsp[-2].sym), &(yyvsp[0].sym));
																				break;
																			case MOD_ASSIGN_OP:
																				genassign(MOD_IR, &(yyvsp[-2].sym), &(yyvsp[0].sym));
																				break;
																			case ADD_ASSIGN_OP:
																				genassign(ADD_IR, &(yyvsp[-2].sym), &(yyvsp[0].sym));
																				break;
																			case SUB_ASSIGN_OP:
																				genassign(SUB_IR, &(yyvsp[-2].sym), &(yyvsp[0].sym));
																				break;
																			case LEFT_ASSIGN_OP:
																				genassign(LSHIFT_IR, &(yyvsp[-2].sym), &(yyvsp[0].sym));
																				break;
																			case RIGHT_ASSIGN_OP:
																				genassign(RSHIFT_IR, &(yyvsp[-2].sym), &(yyvsp[0].sym));
																				break;
																			case AND_ASSIGN_OP:
																				genassign(AND_IR, &(yyvsp[-2].sym), &(yyvsp[0].sym));
																				break;
																			case XOR_ASSIGN_OP:
																				genassign(XOR_IR, &(yyvsp[-2].sym), &(yyvsp[0].sym));
																				break;
																			case OR_ASSIGN_OP:
																				genassign(OR_IR, &(yyvsp[-2].sym), &(yyvsp[0].sym));
																				break;
																		}
																	}
#line 3087 "ansic.tab.c"
    break;

  case 66: /* assignment_operator: '='  */
#line 1205 "ansic.y"
                                {	printf("assignment_operator: '='\n");
						(yyval.asop) = EQ_ASSIGN_OP;
					}
#line 3095 "ansic.tab.c"
    break;

  case 67: /* assignment_operator: MUL_ASSIGN  */
#line 1209 "ansic.y"
                        {	printf("assignment_operator: MUL_ASSIGN\n");
						(yyval.asop) = MUL_ASSIGN_OP;
					}
#line 3103 "ansic.tab.c"
    break;

  case 68: /* assignment_operator: DIV_ASSIGN  */
#line 1213 "ansic.y"
                        {	printf("assignment_operator: DIV_ASSIGN\n");
						(yyval.asop) = DIV_ASSIGN_OP;
					}
#line 3111 "ansic.tab.c"
    break;

  case 69: /* assignment_operator: MOD_ASSIGN  */
#line 1217 "ansic.y"
                        {	printf("assignment_operator: MOD_ASSIGN\n");
						(yyval.asop) = MOD_ASSIGN_OP;
					}
#line 3119 "ansic.tab.c"
    break;

  case 70: /* assignment_operator: ADD_ASSIGN  */
#line 1221 "ansic.y"
                        {	printf("assignment_operator: ADD_ASSIGN\n");
						(yyval.asop) = ADD_ASSIGN_OP;
					}
#line 3127 "ansic.tab.c"
    break;

  case 71: /* assignment_operator: SUB_ASSIGN  */
#line 1225 "ansic.y"
                        {	printf("assignment_operator: SUB_ASSIGN\n");
						(yyval.asop) = SUB_ASSIGN_OP;
					}
#line 3135 "ansic.tab.c"
    break;

  case 72: /* assignment_operator: LEFT_ASSIGN  */
#line 1229 "ansic.y"
                        {	printf("assignment_operator: LEFT_ASSIGN\n");
						(yyval.asop) = LEFT_ASSIGN_OP;
					}
#line 3143 "ansic.tab.c"
    break;

  case 73: /* assignment_operator: RIGHT_ASSIGN  */
#line 1233 "ansic.y"
                        {	printf("assignment_operator: RIGHT_ASSIGN\n");
						(yyval.asop) = RIGHT_ASSIGN_OP;
					}
#line 3151 "ansic.tab.c"
    break;

  case 74: /* assignment_operator: AND_ASSIGN  */
#line 1237 "ansic.y"
                        {	printf("assignment_operator: AND_ASSIGN\n");
						(yyval.asop) = AND_ASSIGN_OP;
					}
#line 3159 "ansic.tab.c"
    break;

  case 75: /* assignment_operator: XOR_ASSIGN  */
#line 1241 "ansic.y"
                        {	printf("assignment_operator: XOR_ASSIGN\n");
						(yyval.asop) = XOR_ASSIGN_OP;
					}
#line 3167 "ansic.tab.c"
    break;

  case 76: /* assignment_operator: OR_ASSIGN  */
#line 1245 "ansic.y"
                                {	printf("assignment_operator: OR_ASSIGN\n");
						(yyval.asop) = OR_ASSIGN_OP;
					}
#line 3175 "ansic.tab.c"
    break;

  case 77: /* expression: assignment_expression  */
#line 1252 "ansic.y"
                                                                {	printf("expression: assignment_expression\n");
												(yyval.sym) = (yyvsp[0].sym);
											}
#line 3183 "ansic.tab.c"
    break;

  case 78: /* expression: expression ',' assignment_expression  */
#line 1256 "ansic.y"
                                                {	printf("expression: expression ',' assignment_expression\n");
												;
											}
#line 3191 "ansic.tab.c"
    break;

  case 79: /* constant_expression: conditional_expression  */
#line 1263 "ansic.y"
                                        {	printf("constant_expression: conditional_expression\n");
									(yyval.sym) = (yyvsp[0].sym);
								}
#line 3199 "ansic.tab.c"
    break;

  case 80: /* declaration: declaration_specifiers ';'  */
#line 1270 "ansic.y"
                                                                                {	printf("declaration: declaration_specifiers ';'\n");
															;
														}
#line 3207 "ansic.tab.c"
    break;

  case 81: /* declaration: declaration_specifiers init_declarator_list ';'  */
#line 1274 "ansic.y"
                                                                {	printf("declaration: declaration_specifiers init_declarator_list ';'\n");
															int typ = get_type((yyvsp[-2].splist));
															symrec* s; // Variable que apunta a una estructura symrec
															std::list<VAR_DATA*>::iterator it;
															for(it = (yyvsp[-1].idlist)->begin(); it != (yyvsp[-1].idlist)->end(); it ++){
																std::cout << "Name:" << *(*it)->name << std::endl; //depuracion
																if(isarray((*it)->typ)){
																	installarray((*it)->name, typ | VAR_SPEC | ((*it)->typ & ~0x1F), (*it)->dimlist);//Funcion para crear codigo ensamblador para arreglos
																	// Se le pasa el nombre, el tipo, el bit para identificar que es variable, y se le pasa un arreglo de punteros y remover bits, tambien se le pasa la lista de dimensiones asi queda el tipo integro y se declara el arreglo
																}
																else if(isfunction((*it)->typ)){
																	s = install((*it)->name, typ | FUNC_SPEC | ((*it)->typ & ~0x1F));  // Para quitar algunos bits y dejar las variables adecuadas a los tipos, usa complemento A1 ~0x1f, operacion and de bits bitwise
																	// El & ~0x1F es para aislar bits y quitarlos, dejando integro el tipo
																}
																else {
																	s = install((*it)->name, typ | VAR_SPEC | ((*it)->typ & ~0x1F)); // Son 31 en hexadecimal que se adecua en los tipos de datos permitidos, son los bits menos arriba de 32, 6 byte, la funcion regresa un puntero
																	if((*it)->init){
																		if(currscope > 0){ // Verificar que sea una variable local, ambito actual
																			gencode(STORE_IR, (*it)->var, nullptr, s); // Generacion de codigo intermedio
																		}
																		else{
																			initvar(s, (*it)->var); // Poner valor inicial en el bloque de datos
																		}

																		}
																	
																	}
															}

														}
#line 3242 "ansic.tab.c"
    break;

  case 82: /* declaration_specifiers: storage_class_specifier  */
#line 1308 "ansic.y"
                                                                                        {	printf("declaration_specifiers: storage_class_specifier\n");
															std::list<int>* newlist = new std::list<int>; // Lista de enteros
															newlist->push_back((yyvsp[0].scsp)); // Poner primer atributo del no terminal en la cima de la lista
															(yyval.splist) = newlist; // Se le asigna a la regla declaration_specifier
														}
#line 3252 "ansic.tab.c"
    break;

  case 83: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 1314 "ansic.y"
                                                                {	printf("declaration_specifiers: storage_class_specifier declaration_specifiers\n");
															(yyval.splist) = (yyvsp[0].splist);
															(yyval.splist)->push_back((yyvsp[-1].scsp));
														}
#line 3261 "ansic.tab.c"
    break;

  case 84: /* declaration_specifiers: type_specifier  */
#line 1319 "ansic.y"
                                                                                                {	printf("declaration_specifiers: type_specifier\n");
															std::list<int>* newlist = new std::list<int>; // Lista de enteros
															newlist->push_back((yyvsp[0].typesp)); // Poner primer atributo del no terminal en la cima de la lista
															(yyval.splist) = newlist; // Se le asigna a la regla declaration_specifier
														}
#line 3271 "ansic.tab.c"
    break;

  case 85: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 1325 "ansic.y"
                                                                        {	printf("declaration_specifiers: type_specifier declaration_specifiers\n");
															(yyval.splist)->push_back((yyvsp[-1].typesp));
															(yyval.splist) = (yyvsp[0].splist);
														}
#line 3280 "ansic.tab.c"
    break;

  case 86: /* declaration_specifiers: type_qualifier  */
#line 1330 "ansic.y"
                                                                                                {	printf("declaration_specifiers: type_qualifier\n");
															std::list<int>* newlist = new std::list<int>; // Lista de enteros
															newlist->push_back((yyvsp[0].typeq)); // Poner primer atributo del no terminal en la cima de la lista
															(yyval.splist) = newlist; // Se le asigna a la regla declaration_specifier
														}
#line 3290 "ansic.tab.c"
    break;

  case 87: /* declaration_specifiers: type_qualifier declaration_specifiers  */
#line 1336 "ansic.y"
                                                                        {	printf("declaration_specifiers: type_qualifier declaration_specifiers\n");
															(yyval.splist)->push_back((yyvsp[-1].typeq));
															(yyval.splist) = (yyvsp[0].splist);
														}
#line 3299 "ansic.tab.c"
    break;

  case 88: /* init_declarator_list: init_declarator  */
#line 1344 "ansic.y"
                                                                                {	printf("init_declarator_list: init_declarator\n");
													std::list<VAR_DATA*>* ptr = new std::list<VAR_DATA*>;
													//VAR_DATA *newstruct = $ 1 //$ 1 ya es una estructura VAR_DATA entonces no es necesario
													ptr->push_back((yyvsp[0].id_data)); 
													(yyval.idlist) = ptr;
												}
#line 3310 "ansic.tab.c"
    break;

  case 89: /* init_declarator_list: init_declarator_list ',' init_declarator  */
#line 1351 "ansic.y"
                                                        {	printf("init_declarator_list: init_declarator_list ',' init_declarator\n");
													(yyvsp[-2].idlist)->push_back((yyvsp[0].id_data));
													(yyval.idlist) = (yyvsp[-2].idlist);
												}
#line 3319 "ansic.tab.c"
    break;

  case 90: /* init_declarator: declarator  */
#line 1359 "ansic.y"
                                                        {	printf("init_declarator: declarator\n");
										(yyval.id_data) = (yyvsp[0].id_data);
										(yyval.id_data)->init = 0; // Variable no inicializada
									}
#line 3328 "ansic.tab.c"
    break;

  case 91: /* init_declarator: declarator '=' initializer  */
#line 1364 "ansic.y"
                                        {	printf("init_declarator: declarator '=' initializer\n");
										(yyval.id_data) = (yyvsp[-2].id_data);
										(yyval.id_data)->init = 1; // Variable inicializada
										(yyval.id_data)->var = (yyvsp[0].sym).var;
									}
#line 3338 "ansic.tab.c"
    break;

  case 92: /* storage_class_specifier: TYPEDEF  */
#line 1373 "ansic.y"
                        {	printf("storage_class_specifier: TYPEDEF\n");
					(yyval.scsp) = TYPEDEF_SPEC;
				}
#line 3346 "ansic.tab.c"
    break;

  case 93: /* storage_class_specifier: EXTERN  */
#line 1377 "ansic.y"
                        {	printf("storage_class_specifier: EXTERN\n");
					(yyval.scsp) = EXTERN_SPEC;
				}
#line 3354 "ansic.tab.c"
    break;

  case 94: /* storage_class_specifier: STATIC  */
#line 1381 "ansic.y"
                        {	printf("storage_class_specifier: STATIC\n");
					(yyval.scsp) = STATIC_SPEC;
				}
#line 3362 "ansic.tab.c"
    break;

  case 95: /* storage_class_specifier: AUTO  */
#line 1385 "ansic.y"
                        {	printf("storage_class_specifier: AUTO\n");
					(yyval.scsp) = AUTO_SPEC;
				}
#line 3370 "ansic.tab.c"
    break;

  case 96: /* storage_class_specifier: REGISTER  */
#line 1389 "ansic.y"
                        {	printf("storage_class_specifier: REGISTER\n");
					(yyval.scsp) = REGISTER_SPEC;
				}
#line 3378 "ansic.tab.c"
    break;

  case 97: /* type_specifier: VOID  */
#line 1396 "ansic.y"
                                                        {	printf("type_specifier: VOID\n");
									(yyval.typesp) = VOID_SPEC;
								}
#line 3386 "ansic.tab.c"
    break;

  case 98: /* type_specifier: CHAR  */
#line 1400 "ansic.y"
                                                        {	printf("type_specifier: CHAR\n");
									(yyval.typesp) = CHAR_SPEC;
								}
#line 3394 "ansic.tab.c"
    break;

  case 99: /* type_specifier: SHORT  */
#line 1404 "ansic.y"
                                                        {	printf("type_specifier: SHORT\n");
									(yyval.typesp) = SHORT_SPEC;
								}
#line 3402 "ansic.tab.c"
    break;

  case 100: /* type_specifier: INT  */
#line 1408 "ansic.y"
                                                        {	printf("type_specifier: INT\n");
									(yyval.typesp) = INT_SPEC;
								}
#line 3410 "ansic.tab.c"
    break;

  case 101: /* type_specifier: LONG  */
#line 1412 "ansic.y"
                                                        {	printf("type_specifier: LONG\n");
									(yyval.typesp) = LONG_SPEC;
								}
#line 3418 "ansic.tab.c"
    break;

  case 102: /* type_specifier: FLOAT  */
#line 1416 "ansic.y"
                                                        {	printf("type_specifier: FLOAT\n");
									(yyval.typesp) = FLOAT_SPEC;
								}
#line 3426 "ansic.tab.c"
    break;

  case 103: /* type_specifier: DOUBLE  */
#line 1420 "ansic.y"
                                                        {	printf("type_specifier: DOUBLE\n");
									(yyval.typesp) = DOUBLE_SPEC;
								}
#line 3434 "ansic.tab.c"
    break;

  case 104: /* type_specifier: SIGNED  */
#line 1424 "ansic.y"
                                                        {	printf("type_specifier: SIGNED\n");
									(yyval.typesp) = SIGNED_SPEC;
								}
#line 3442 "ansic.tab.c"
    break;

  case 105: /* type_specifier: UNSIGNED  */
#line 1428 "ansic.y"
                                                        {	printf("type_specifier: UNSIGNED\n");
									(yyval.typesp) = UNSIGNED_SPEC;
								}
#line 3450 "ansic.tab.c"
    break;

  case 106: /* type_specifier: struct_or_union_specifier  */
#line 1432 "ansic.y"
                                        {	printf("type_specifier: struct_or_union_specifier\n");
									;
								}
#line 3458 "ansic.tab.c"
    break;

  case 107: /* type_specifier: enum_specifier  */
#line 1436 "ansic.y"
                                                {	printf("type_specifier: enum_specifier\n");
									;
								}
#line 3466 "ansic.tab.c"
    break;

  case 108: /* type_specifier: TYPE_NAME  */
#line 1440 "ansic.y"
                                                        {	printf("type_specifier: TYPE_NAME\n");
									(yyval.typesp) = TYPENAME_SPEC;
								}
#line 3474 "ansic.tab.c"
    break;

  case 109: /* struct_or_union_specifier: struct_or_union IDENTIFIER '{' struct_declaration_list '}'  */
#line 1446 "ansic.y"
                                                                        {	printf("struct_or_union_specifier: struct_or_union IDENTIFIER '{' struct_declaration_list '}'\n");
																		;
																	}
#line 3482 "ansic.tab.c"
    break;

  case 110: /* struct_or_union_specifier: struct_or_union '{' struct_declaration_list '}'  */
#line 1450 "ansic.y"
                                                                                        {	printf("struct_or_union_specifier: struct_or_union '{' struct_declaration_list '}'\n");
																		;
																	}
#line 3490 "ansic.tab.c"
    break;

  case 111: /* struct_or_union_specifier: struct_or_union IDENTIFIER  */
#line 1454 "ansic.y"
                                                                                                        {	printf("struct_or_union_specifier: struct_or_union IDENTIFIER\n");
																		;
																	}
#line 3498 "ansic.tab.c"
    break;

  case 112: /* struct_or_union: STRUCT  */
#line 1461 "ansic.y"
                        {	printf("struct_or_union: STRUCT\n");
					;
				}
#line 3506 "ansic.tab.c"
    break;

  case 113: /* struct_or_union: UNION  */
#line 1465 "ansic.y"
                        {	printf("struct_or_union: UNION\n");
					;
				}
#line 3514 "ansic.tab.c"
    break;

  case 114: /* struct_declaration_list: struct_declaration  */
#line 1472 "ansic.y"
                                                                                {	printf("struct_declaration_list: struct_declaration\n");
														;
													}
#line 3522 "ansic.tab.c"
    break;

  case 115: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 1476 "ansic.y"
                                                        {	printf("struct_declaration_list: struct_declaration_list struct_declaration\n");
														;
													}
#line 3530 "ansic.tab.c"
    break;

  case 116: /* struct_declaration: specifier_qualifier_list struct_declarator_list ';'  */
#line 1483 "ansic.y"
                                                                {	printf("struct_declaration: specifier_qualifier_list struct_declarator_list ';'\n");
																;
															}
#line 3538 "ansic.tab.c"
    break;

  case 117: /* specifier_qualifier_list: type_specifier specifier_qualifier_list  */
#line 1490 "ansic.y"
                                                        {	printf("specifier_qualifier_list: type_specifier specifier_qualifier_list\n");
													(yyvsp[0].sqlist)->push_back((yyvsp[-1].typesp));
													(yyval.sqlist) = (yyvsp[0].sqlist);
												}
#line 3547 "ansic.tab.c"
    break;

  case 118: /* specifier_qualifier_list: type_specifier  */
#line 1495 "ansic.y"
                                                                                {	printf("specifier_qualifier_list: type_specifier\n");
													std::list<int>* newlist = new std::list<int>();
													newlist->push_back((yyvsp[0].typesp));
													(yyval.sqlist) = newlist;
												}
#line 3557 "ansic.tab.c"
    break;

  case 119: /* specifier_qualifier_list: type_qualifier specifier_qualifier_list  */
#line 1501 "ansic.y"
                                                        {	printf("specifier_qualifier_list: type_qualifier specifier_qualifier_list\n");
													(yyvsp[0].sqlist)->push_back((yyvsp[-1].typeq));
													(yyval.sqlist) = (yyvsp[0].sqlist);
												}
#line 3566 "ansic.tab.c"
    break;

  case 120: /* specifier_qualifier_list: type_qualifier  */
#line 1506 "ansic.y"
                                                                                {	printf("specifier_qualifier_list: type_qualifier\n");
													std::list<int>* newlist = new std::list<int>();
													newlist->push_back((yyvsp[0].typeq));
													(yyval.sqlist) = newlist;
												}
#line 3576 "ansic.tab.c"
    break;

  case 121: /* struct_declarator_list: struct_declarator  */
#line 1515 "ansic.y"
                                                                                        {	printf("struct_declarator_list: struct_declarator\n");
														;
													}
#line 3584 "ansic.tab.c"
    break;

  case 122: /* struct_declarator_list: struct_declarator_list ',' struct_declarator  */
#line 1519 "ansic.y"
                                                        {	printf("struct_declarator_list: struct_declarator_list ',' struct_declarator\n");
														;
													}
#line 3592 "ansic.tab.c"
    break;

  case 123: /* struct_declarator: declarator  */
#line 1526 "ansic.y"
                                                                        {	printf("struct_declarator: declarator\n");
												;
											}
#line 3600 "ansic.tab.c"
    break;

  case 124: /* struct_declarator: ':' constant_expression  */
#line 1530 "ansic.y"
                                                                {	printf("struct_declarator: ':' constant_expression\n");
												;
											}
#line 3608 "ansic.tab.c"
    break;

  case 125: /* struct_declarator: declarator ':' constant_expression  */
#line 1534 "ansic.y"
                                                {	printf("struct_declarator: declarator ':' constant_expression\n");
												;
											}
#line 3616 "ansic.tab.c"
    break;

  case 126: /* enum_specifier: ENUM '{' enumerator_list '}'  */
#line 1541 "ansic.y"
                                                                {	printf("enum_specifier: ENUM '{' enumerator_list '}'\n");
													;
												}
#line 3624 "ansic.tab.c"
    break;

  case 127: /* enum_specifier: ENUM IDENTIFIER '{' enumerator_list '}'  */
#line 1545 "ansic.y"
                                                        {	printf("enum_specifier: ENUM IDENTIFIER '{' enumerator_list '}'\n");
													;
												}
#line 3632 "ansic.tab.c"
    break;

  case 128: /* enum_specifier: ENUM IDENTIFIER  */
#line 1549 "ansic.y"
                                                                                {	printf("enum_specifier: ENUM IDENTIFIER\n");
													;
												}
#line 3640 "ansic.tab.c"
    break;

  case 129: /* enumerator_list: enumerator  */
#line 1556 "ansic.y"
                                                                {	printf("enumerator_list: enumerator\n");
											;
										}
#line 3648 "ansic.tab.c"
    break;

  case 130: /* enumerator_list: enumerator_list ',' enumerator  */
#line 1560 "ansic.y"
                                                {	printf("enumerator_list: enumerator_list ',' enumerator\n");
											;
										}
#line 3656 "ansic.tab.c"
    break;

  case 131: /* enumerator: IDENTIFIER  */
#line 1567 "ansic.y"
                                                                        {	printf("enumerator: IDENTIFIER\n");
												;
											}
#line 3664 "ansic.tab.c"
    break;

  case 132: /* enumerator: IDENTIFIER '=' constant_expression  */
#line 1571 "ansic.y"
                                                {	printf("enumerator: IDENTIFIER '=' constant_expression\n");
												;
											}
#line 3672 "ansic.tab.c"
    break;

  case 133: /* type_qualifier: CONST  */
#line 1578 "ansic.y"
                                        {	printf("type_qualifier: CONST\n");
							(yyval.typeq) = CONST_SPEC;
						}
#line 3680 "ansic.tab.c"
    break;

  case 134: /* type_qualifier: VOLATILE  */
#line 1582 "ansic.y"
                                        {	printf("type_qualifier: VOLATILE\n");
							(yyval.typeq) = VOLATILE_SPEC;
						}
#line 3688 "ansic.tab.c"
    break;

  case 135: /* declarator: pointer direct_declarator  */
#line 1589 "ansic.y"
                                                {	printf("declarator: pointer direct_declarator\n");
										(yyval.id_data) = (yyvsp[0].id_data);
										(yyval.id_data)->plevel = (yyvsp[-1].pstruct).level;
										(yyval.id_data)->typ |= POINTER_SPEC | (yyvsp[-1].pstruct).typq;
									}
#line 3698 "ansic.tab.c"
    break;

  case 136: /* declarator: direct_declarator  */
#line 1595 "ansic.y"
                                                        {	printf("declarator: direct_declarator\n");
										(yyval.id_data) = (yyvsp[0].id_data);
										if(isarray((yyval.id_data)->typ)){
											if(allzero((yyval.id_data)->dimlist)){
												(yyval.id_data)->typ &= ~ARRAY_SPEC;
											}
											//Arreglos sin dimensiones son punteros
											if(allzero((yyval.id_data)->dimlist)){
												(yyval.id_data)->typ &= ~ARRAY_SPEC;
												(yyval.id_data)->typ |= POINTER_SPEC;
											}
											else{
												if(product((yyval.id_data)->dimlist) == 0)
													yyerror("Array dimensions must be specified!");
											}
										}
									}
#line 3720 "ansic.tab.c"
    break;

  case 137: /* direct_declarator: IDENTIFIER  */
#line 1616 "ansic.y"
                                                                                        {	printf("direct_declarator: IDENTIFIER\n");
														VAR_DATA *newsym = new VAR_DATA();
														string* namestr = new string ((yyvsp[0].name)); // El nombre es el atributo id del token IDENTIFIER
														//cout << "name = " << *name << endl; //depuracion
														(yyval.id_data) = newsym;
														(yyval.id_data)->name = namestr; //char* = cadena de c, string cadena de C++
														(yyval.id_data)->dimlist = nullptr;
														(yyval.id_data)->typ = 0;
													}
#line 3734 "ansic.tab.c"
    break;

  case 138: /* direct_declarator: '(' declarator ')'  */
#line 1626 "ansic.y"
                                                                                {	printf("direct_declarator: '(' declarator ')'\n");
														;
													}
#line 3742 "ansic.tab.c"
    break;

  case 139: /* direct_declarator: direct_declarator '[' constant_expression ']'  */
#line 1630 "ansic.y"
                                                        {	printf("direct_declarator: direct_declarator '[' constant_expression ']'\n"); // Arreglo con dimensiones
														if(!isintegral((yyvsp[-1].sym).typ)){
															yyerror("Array dimensions must be integral");
														}
														if(!isconstant((yyvsp[-1].sym).typ)){
															yyerror("Array dimensions must be constant");	
														}
														(yyval.id_data) = (yyvsp[-3].id_data); //Herencia/Propagacion de atributo del primero
														if((yyval.id_data)->dimlist == nullptr){
															(yyval.id_data)->dimlist = new std::list<int>;
														}
														(yyval.id_data)->dimlist->push_back((yyvsp[-1].sym).val.intval);
														(yyval.id_data)->typ |= ARRAY_SPEC; // Agregar un bit
														
													}
#line 3762 "ansic.tab.c"
    break;

  case 140: /* direct_declarator: direct_declarator '[' ']'  */
#line 1646 "ansic.y"
                                                                                {	printf("direct_declarator: direct_declarator '[' ']'\n"); // Arreglo sin dimensiones, como en la ultima de un arreglo bidimensional
														(yyval.id_data) = (yyvsp[-2].id_data); //Herencia/Propagacion de atributo del primero
														if((yyval.id_data)->dimlist == nullptr){
															(yyval.id_data)->dimlist = new std::list<int>;
														}
														(yyval.id_data)->dimlist->push_back(0); // Agregar 0 a la lista
														(yyval.id_data)->typ |= ARRAY_SPEC; // Agregar un bit
													}
#line 3775 "ansic.tab.c"
    break;

  case 141: /* direct_declarator: direct_declarator '(' parameter_type_list ')'  */
#line 1655 "ansic.y"
                                                        {	printf("direct_declarator: direct_declarator '(' parameter_type_list ')'\n");
														(yyval.id_data) = (yyvsp[-3].id_data);
														(yyval.id_data)->typ |= FUNC_SPEC;
														(yyval.id_data)->arglist = (yyvsp[-1].idlist);
														(yyval.id_data)->init = 0;
													}
#line 3786 "ansic.tab.c"
    break;

  case 142: /* direct_declarator: direct_declarator '(' identifier_list ')'  */
#line 1662 "ansic.y"
                                                                {	printf("direct_declarator: direct_declarator '(' identifier_list ')'\n");
														(yyval.id_data) = (yyvsp[-3].id_data);
														(yyval.id_data)->typ |= FUNC_SPEC;
													}
#line 3795 "ansic.tab.c"
    break;

  case 143: /* direct_declarator: direct_declarator '(' ')'  */
#line 1667 "ansic.y"
                                                                                {	printf("direct_declarator: direct_declarator '(' ')'\n");
														(yyval.id_data) = (yyvsp[-2].id_data);
														(yyval.id_data)->typ |= FUNC_SPEC;
														(yyval.id_data)->init = 0;
													}
#line 3805 "ansic.tab.c"
    break;

  case 144: /* pointer: '*'  */
#line 1676 "ansic.y"
                                                                        {	printf("pointer: '*'\n");
											(yyval.pstruct).typq = POINTER_SPEC; // Atributo sintetizado
											(yyval.pstruct).level = 1;
										}
#line 3814 "ansic.tab.c"
    break;

  case 145: /* pointer: '*' type_qualifier_list  */
#line 1681 "ansic.y"
                                                        {	printf("pointer: '*' type_qualifier_list\n");
											(yyval.pstruct).typq = get_type((yyvsp[0].splist)) | POINTER_SPEC;
											(yyval.pstruct).level = 1;
										}
#line 3823 "ansic.tab.c"
    break;

  case 146: /* pointer: '*' pointer  */
#line 1686 "ansic.y"
                                                                {	printf("pointer: '*' pointer\n");
											(yyval.pstruct) = (yyvsp[0].pstruct);
											(yyval.pstruct).level++;
										}
#line 3832 "ansic.tab.c"
    break;

  case 147: /* pointer: '*' type_qualifier_list pointer  */
#line 1691 "ansic.y"
                                                {	printf("pointer: '*' type_qualifier_list pointer\n");
											(yyval.pstruct) = (yyvsp[0].pstruct);
											(yyval.pstruct).typq = get_type((yyvsp[-1].splist));
											(yyval.pstruct).level++;
										}
#line 3842 "ansic.tab.c"
    break;

  case 148: /* type_qualifier_list: type_qualifier  */
#line 1700 "ansic.y"
                                                                        {	printf("type_qualifier_list: type_qualifier\n");
												std::list<int>* newlist = new list<int>();
												newlist->push_back((yyvsp[0].typeq));
												(yyval.splist) = newlist;
											}
#line 3852 "ansic.tab.c"
    break;

  case 149: /* type_qualifier_list: type_qualifier_list type_qualifier  */
#line 1706 "ansic.y"
                                                {	printf("type_qualifier_list: type_qualifier_list type_qualifier\n");
												(yyval.splist) = (yyvsp[-1].splist);
												(yyval.splist)->push_back((yyvsp[0].typeq));
											}
#line 3861 "ansic.tab.c"
    break;

  case 150: /* parameter_type_list: parameter_list  */
#line 1715 "ansic.y"
                                                        {	printf("parameter_type_list: parameter_list\n");
										(yyval.idlist) = (yyvsp[0].idlist);
									}
#line 3869 "ansic.tab.c"
    break;

  case 151: /* parameter_type_list: parameter_list ',' ELLIPSIS  */
#line 1719 "ansic.y"
                                        {	printf("parameter_type_list: parameter_list ',' ELLIPSIS\n");
										(yyval.idlist) = (yyvsp[-2].idlist);
									}
#line 3877 "ansic.tab.c"
    break;

  case 152: /* parameter_list: parameter_declaration  */
#line 1726 "ansic.y"
                                                                        {	printf("parameter_list: parameter_declaration\n");
													std::list<VAR_DATA*>* newlist = new std::list<VAR_DATA*>;
													VAR_DATA* newstruct = new VAR_DATA();
													*newstruct = (yyvsp[0].sym);
													newlist->push_back(newstruct);
													(yyval.idlist) = newlist;
												}
#line 3889 "ansic.tab.c"
    break;

  case 153: /* parameter_list: parameter_list ',' parameter_declaration  */
#line 1734 "ansic.y"
                                                        {	printf("parameter_list: parameter_list ',' parameter_declaration\n");
													(yyval.idlist) = (yyvsp[-2].idlist);
													VAR_DATA *newstruct = new VAR_DATA();
													*newstruct = (yyvsp[0].sym);
													(yyval.idlist)->push_back(newstruct);
												}
#line 3900 "ansic.tab.c"
    break;

  case 154: /* parameter_declaration: declaration_specifiers declarator  */
#line 1744 "ansic.y"
                                                                        {	printf("parameter_declaration: declaration_specifiers declarator\n");
														(yyval.sym).name = (yyvsp[0].id_data)->name;
														if(!isarray((yyvsp[0].id_data)->typ)){
															(yyval.sym).typ = get_type((yyvsp[-1].splist));
														}
														else{
															(yyval.sym).typ = get_type((yyvsp[-1].splist)) | ARRAY_SPEC;
														}
													}
#line 3914 "ansic.tab.c"
    break;

  case 155: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 1754 "ansic.y"
                                                        {	printf("parameter_declaration: declaration_specifiers abstract_declarator\n");
														;
													}
#line 3922 "ansic.tab.c"
    break;

  case 156: /* parameter_declaration: declaration_specifiers  */
#line 1758 "ansic.y"
                                                                                {	printf("parameter_declaration: declaration_specifiers\n");
														;
													}
#line 3930 "ansic.tab.c"
    break;

  case 157: /* identifier_list: IDENTIFIER  */
#line 1765 "ansic.y"
                                                                {	printf("identifier_list: IDENTIFIER\n");
											std::list<VAR_DATA*>* newlist = new std::list<VAR_DATA*>();
											VAR_DATA* newsym = new VAR_DATA();
											newsym->name = new std::string((yyvsp[0].name));
											newsym->dimlist = NULL;
											newsym->typ = 0;
											newlist->push_back(newsym);
											(yyval.symlist) = newlist;
										}
#line 3944 "ansic.tab.c"
    break;

  case 158: /* identifier_list: identifier_list ',' IDENTIFIER  */
#line 1775 "ansic.y"
                                                {	printf("identifier_list: identifier_list ',' IDENTIFIER\n");
											VAR_DATA* newsym = new VAR_DATA();
											newsym->name = new std::string((yyvsp[0].name));
											newsym->dimlist = NULL;
											newsym->typ = 0;
											(yyval.symlist) = (yyvsp[-2].symlist);
											(yyval.symlist)->push_back(newsym);
										}
#line 3957 "ansic.tab.c"
    break;

  case 159: /* type_name: specifier_qualifier_list  */
#line 1787 "ansic.y"
                                                                                {	printf("type_name: specifier_qualifier_list\n");
														(yyval.typ) = get_type((yyvsp[0].sqlist));
													}
#line 3965 "ansic.tab.c"
    break;

  case 160: /* type_name: specifier_qualifier_list abstract_declarator  */
#line 1791 "ansic.y"
                                                        {	printf("type_name: specifier_qualifier_list abstract_declarator\n");
														(yyval.typ) = get_type((yyvsp[-1].sqlist));
													}
#line 3973 "ansic.tab.c"
    break;

  case 161: /* abstract_declarator: pointer  */
#line 1798 "ansic.y"
                                                                                {	printf("abstract_declarator: pointer\n");
												;
											}
#line 3981 "ansic.tab.c"
    break;

  case 162: /* abstract_declarator: direct_abstract_declarator  */
#line 1802 "ansic.y"
                                                        {	printf("abstract_declarator: direct_abstract_declarator\n");
												;
											}
#line 3989 "ansic.tab.c"
    break;

  case 163: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 1806 "ansic.y"
                                                {	printf("abstract_declarator: pointer direct_abstract_declarator\n");
												;
											}
#line 3997 "ansic.tab.c"
    break;

  case 164: /* direct_abstract_declarator: '(' abstract_declarator ')'  */
#line 1813 "ansic.y"
                                                                                                {	printf("direct_abstract_declarator: '(' abstract_declarator ')'\n");
																	;
																}
#line 4005 "ansic.tab.c"
    break;

  case 165: /* direct_abstract_declarator: '[' ']'  */
#line 1817 "ansic.y"
                                                                                                                        {	printf("direct_abstract_declarator: '[' ']'\n");
																	;
																}
#line 4013 "ansic.tab.c"
    break;

  case 166: /* direct_abstract_declarator: '[' constant_expression ']'  */
#line 1821 "ansic.y"
                                                                                                {	printf("direct_abstract_declarator: '[' constant_expression ']'\n");
																	;
																}
#line 4021 "ansic.tab.c"
    break;

  case 167: /* direct_abstract_declarator: direct_abstract_declarator '[' ']'  */
#line 1825 "ansic.y"
                                                                                        {	printf("direct_abstract_declarator: direct_abstract_declarator '[' ']'\n");
																	;
																}
#line 4029 "ansic.tab.c"
    break;

  case 168: /* direct_abstract_declarator: direct_abstract_declarator '[' constant_expression ']'  */
#line 1829 "ansic.y"
                                                                        {	printf("direct_abstract_declarator: direct_abstract_declarator '[' constant_expression ']'\n");
																	;
																}
#line 4037 "ansic.tab.c"
    break;

  case 169: /* direct_abstract_declarator: '(' ')'  */
#line 1833 "ansic.y"
                                                                                                                        {	printf("direct_abstract_declarator: '(' ')'\n");
																	;
																}
#line 4045 "ansic.tab.c"
    break;

  case 170: /* direct_abstract_declarator: '(' parameter_type_list ')'  */
#line 1837 "ansic.y"
                                                                                                {	printf("direct_abstract_declarator: '(' parameter_type_list ')'\n");
																	;
																}
#line 4053 "ansic.tab.c"
    break;

  case 171: /* direct_abstract_declarator: direct_abstract_declarator '(' ')'  */
#line 1841 "ansic.y"
                                                                                        {	printf("direct_abstract_declarator: direct_abstract_declarator '(' ')'\n");
																	;
																}
#line 4061 "ansic.tab.c"
    break;

  case 172: /* direct_abstract_declarator: direct_abstract_declarator '(' parameter_type_list ')'  */
#line 1845 "ansic.y"
                                                                        {	printf("direct_abstract_declarator: direct_abstract_declarator '(' parameter_type_list ')'\n");
																	;
																}
#line 4069 "ansic.tab.c"
    break;

  case 173: /* initializer: assignment_expression  */
#line 1852 "ansic.y"
                                                {	printf("initializer: assignment_expression\n");
										(yyval.sym) = (yyvsp[0].sym);
									}
#line 4077 "ansic.tab.c"
    break;

  case 174: /* initializer: '{' initializer_list '}'  */
#line 1856 "ansic.y"
                                                {	printf("initializer: '{' initializer_list '}'\n");
										;
									}
#line 4085 "ansic.tab.c"
    break;

  case 175: /* initializer: '{' initializer_list ',' '}'  */
#line 1860 "ansic.y"
                                        {	printf("initializer: '{' initializer_list ',' '}'\n");
										;
									}
#line 4093 "ansic.tab.c"
    break;

  case 176: /* initializer_list: initializer  */
#line 1867 "ansic.y"
                                                                {	printf("initializer_list: initializer\n");
											;
										}
#line 4101 "ansic.tab.c"
    break;

  case 177: /* initializer_list: initializer_list ',' initializer  */
#line 1871 "ansic.y"
                                                {	printf("initializer_list: initializer_list ',' initializer\n");
											;
										}
#line 4109 "ansic.tab.c"
    break;

  case 178: /* P: %empty  */
#line 1877 "ansic.y"
                        {

				}
#line 4117 "ansic.tab.c"
    break;

  case 179: /* statement: labeled_statement  */
#line 1884 "ansic.y"
                                        {	printf("statement: labeled_statement\n");
								(yyval.lists) = (yyvsp[0].lists);
								(yyval.lists).nextlist = NULL;
							}
#line 4126 "ansic.tab.c"
    break;

  case 180: /* $@3: %empty  */
#line 1889 "ansic.y"
                                                        {
								enter_scope();
							}
#line 4134 "ansic.tab.c"
    break;

  case 181: /* statement: P $@3 compound_statement  */
#line 1893 "ansic.y"
                                        {	printf("statement: compound_statement\n");
	 							printlocalvars();
								exit_scope();
								(yyval.lists) = (yyvsp[0].lists);	
							}
#line 4144 "ansic.tab.c"
    break;

  case 182: /* statement: expression_statement  */
#line 1899 "ansic.y"
                                {	printf("statement: expression_statement\n");
								(yyval.lists).nextlist = merge((yyvsp[0].sym).truelist, (yyvsp[0].sym).falselist);
								(yyval.lists).breaklist = NULL;
								(yyval.lists).continuelist = NULL;
								(yyval.lists).gotolist = NULL;
								(yyval.lists).caselist = NULL;
							}
#line 4156 "ansic.tab.c"
    break;

  case 183: /* statement: selection_statement  */
#line 1907 "ansic.y"
                                {	printf("statement: selection_statement\n");
								(yyval.lists) = (yyvsp[0].lists);
								(yyval.lists).caselist = NULL;
							}
#line 4165 "ansic.tab.c"
    break;

  case 184: /* statement: iteration_statement  */
#line 1912 "ansic.y"
                                {	printf("statement: iteration_statement\n");
								(yyval.lists) = (yyvsp[0].lists);
								(yyval.lists).caselist = NULL;
							}
#line 4174 "ansic.tab.c"
    break;

  case 185: /* statement: jump_statement  */
#line 1917 "ansic.y"
                                        {	printf("statement: jump_statement\n");
								(yyval.lists) = (yyvsp[0].lists);
								(yyval.lists).caselist = NULL;
							}
#line 4183 "ansic.tab.c"
    break;

  case 186: /* labeled_statement: IDENTIFIER ':' N statement  */
#line 1925 "ansic.y"
                                                                        {	printf("labeled_statement: IDENTIFIER ':' statement\n");
														putlab(new string((yyvsp[-3].name)), (yyvsp[-1].instr));
														(yyval.lists).nextlist = NULL;
														(yyval.lists).breaklist = NULL;
														(yyval.lists).continuelist = NULL;
														(yyval.lists).gotolist = NULL;
														(yyval.lists).caselist = NULL;
												}
#line 4196 "ansic.tab.c"
    break;

  case 187: /* labeled_statement: CASE constant_expression ':' N statement  */
#line 1934 "ansic.y"
                                                        {	printf("labeled_statement: CASE constant_expression ':' statement\n");
													(yyval.lists).breaklist = (yyvsp[0].lists).breaklist;
													(yyval.lists).continuelist = (yyvsp[0].lists).continuelist;
													(yyval.lists).gotolist = (yyvsp[0].lists).gotolist;
													if(!isconstant((yyvsp[-3].sym).typ)){
														yyerror("Error: CASE expression must be constant\n");
													}
													if(!isintegral((yyvsp[-3].sym).typ)){
														yyerror("Error: CASE expression must be integral constant\n");
													}
													(yyval.lists).caselist = makecaselist((yyvsp[-3].sym).val, (yyvsp[-3].sym).typ, (yyvsp[-1].instr));
												}
#line 4213 "ansic.tab.c"
    break;

  case 188: /* labeled_statement: DEFAULT ':' N statement  */
#line 1947 "ansic.y"
                                                                        {	printf("labeled_statement: DEFAULT ':' statement\n");
													(yyval.lists).breaklist = (yyvsp[0].lists).breaklist;
													(yyval.lists).continuelist = (yyvsp[0].lists).continuelist;
													(yyval.lists).gotolist = (yyvsp[0].lists).gotolist;
													(yyval.lists).caselist = makecaselist((yyvsp[-1].instr));
												}
#line 4224 "ansic.tab.c"
    break;

  case 189: /* compound_statement: '{' '}'  */
#line 1957 "ansic.y"
                                                                                        {	printf("compound_statement: '{' '}'\n");
													(yyval.lists).breaklist = NULL;
													(yyval.lists).continuelist = NULL;
													(yyval.lists).gotolist = NULL;
													(yyval.lists).nextlist = NULL;
												}
#line 4235 "ansic.tab.c"
    break;

  case 190: /* compound_statement: '{' statement_list '}'  */
#line 1964 "ansic.y"
                                                                        {	printf("compound_statement: '{' statement_list '}'\n");
													(yyval.lists) = (yyvsp[-1].lists);
												}
#line 4243 "ansic.tab.c"
    break;

  case 191: /* compound_statement: '{' declaration_list '}'  */
#line 1968 "ansic.y"
                                                                        {	printf("compound_statement: '{' declaration_list '}'\n");
													(yyval.lists).breaklist = NULL;
													(yyval.lists).continuelist = NULL;
													(yyval.lists).gotolist = NULL;
													(yyval.lists).nextlist = NULL;
												}
#line 4254 "ansic.tab.c"
    break;

  case 192: /* compound_statement: '{' declaration_list statement_list '}'  */
#line 1975 "ansic.y"
                                                        {	printf("compound_statement: '{' declaration_list statement_list '}'\n");
													(yyval.lists) = (yyvsp[-1].lists);
												}
#line 4262 "ansic.tab.c"
    break;

  case 193: /* declaration_list: declaration  */
#line 1982 "ansic.y"
                                                        {	printf("declaration_list: declaration\n");
										;
									}
#line 4270 "ansic.tab.c"
    break;

  case 194: /* declaration_list: declaration_list declaration  */
#line 1986 "ansic.y"
                                        {	printf("declaration_list: declaration_list declaration\n");
										;
									}
#line 4278 "ansic.tab.c"
    break;

  case 195: /* statement_list: statement  */
#line 1993 "ansic.y"
                                                                {	printf("statement_list: statement\n");
										(yyval.lists) = (yyvsp[0].lists);
									}
#line 4286 "ansic.tab.c"
    break;

  case 196: /* statement_list: statement_list N statement  */
#line 1998 "ansic.y"
                                                        {	printf("statement_list: statement_list statement\n");
	  									backpatch((yyvsp[-2].lists).nextlist, (yyvsp[-1].instr));
										(yyval.lists) = (yyvsp[-2].lists);
										(yyval.lists).nextlist = (yyvsp[0].lists).nextlist;
										(yyval.lists).breaklist = merge((yyvsp[-2].lists).breaklist, (yyvsp[0].lists).breaklist);
										(yyval.lists).continuelist = merge((yyvsp[-2].lists).continuelist, (yyvsp[0].lists).continuelist);
										(yyval.lists).gotolist = merge((yyvsp[-2].lists).gotolist, (yyvsp[0].lists).gotolist);
										(yyval.lists).caselist = merge((yyvsp[-2].lists).caselist, (yyvsp[0].lists).caselist);
									}
#line 4300 "ansic.tab.c"
    break;

  case 197: /* expression_statement: ';'  */
#line 2011 "ansic.y"
                                        {	printf("expression_statement: ';'\n");
							(yyval.sym).truelist = nullptr;
							(yyval.sym).falselist = nullptr;
						}
#line 4309 "ansic.tab.c"
    break;

  case 198: /* expression_statement: expression ';'  */
#line 2016 "ansic.y"
                                {	printf("expression_statement: expression ';'\n");
							(yyval.sym) = (yyvsp[-1].sym);
						}
#line 4317 "ansic.tab.c"
    break;

  case 199: /* logic_expression: expression  */
#line 2023 "ansic.y"
                                                {
									tological(&((yyvsp[0].sym)));
									(yyval.sym) = (yyvsp[0].sym);
								}
#line 4326 "ansic.tab.c"
    break;

  case 200: /* selection_statement: IF '(' logic_expression ')' N statement  */
#line 2032 "ansic.y"
                                                                                                        {	printf("selection_statement: IF '(' expression ')' statement NOELSE\n");
																	backpatch((yyvsp[-3].sym).truelist, (yyvsp[-1].instr));
																	(yyval.lists).nextlist = merge((yyvsp[-3].sym).falselist, (yyvsp[0].lists).nextlist);
																	(yyval.lists).breaklist = (yyvsp[0].lists).breaklist;
																	(yyval.lists).continuelist = (yyvsp[0].lists).continuelist;
																	(yyval.lists).gotolist = (yyvsp[0].lists).gotolist;
																}
#line 4338 "ansic.tab.c"
    break;

  case 201: /* selection_statement: IF '(' logic_expression ')' N statement ELSE M N statement  */
#line 2041 "ansic.y"
                                                                                                {	printf("selection_statement: IF '(' expression ')' statement ELSE statement\n");
																	backpatch((yyvsp[-7].sym).truelist, (yyvsp[-5].instr));
																	backpatch((yyvsp[-7].sym).falselist, (yyvsp[-1].instr));
																	(yyval.lists).nextlist = merge((yyvsp[-4].lists).nextlist, (yyvsp[-2].lists).nextlist, (yyvsp[0].lists).nextlist);
																	(yyval.lists).breaklist = merge((yyvsp[-4].lists).breaklist, (yyvsp[0].lists).breaklist);
																	(yyval.lists).continuelist = merge((yyvsp[-4].lists).continuelist, (yyvsp[0].lists).continuelist);
																	(yyval.lists).gotolist = merge((yyvsp[-4].lists).gotolist, (yyvsp[0].lists).gotolist);
																}
#line 4351 "ansic.tab.c"
    break;

  case 202: /* selection_statement: SWITCH '(' expression ')' M statement  */
#line 2051 "ansic.y"
                                                                                                                {	printf("selection_statement: SWITCH '(' expression ')' statement\n");
																	if(!isintegral((yyvsp[-3].sym).typ)){
																		yyerror("Error: switch expression must be integreal\n");
																	}
																	(yyvsp[0].lists).breaklist = merge((yyvsp[0].lists).breaklist, makelist(nextinstr));
																	gencode(GOTO_IR);
																	backpatch((yyvsp[-1].lists).nextlist, nextinstr);
																	std::list<CASE_DATA*>::iterator it;
																	if((yyvsp[0].lists).caselist != NULL){
																		for(it = (yyvsp[0].lists).caselist->begin(); it != (yyvsp[0].lists).caselist->end(); it++){
																			int addr = (*it)->addr;
																			int typ = (*it)->typ;
																			if(typ == VOIDVAL){
																				gencode(GOTO_IR, addr);
																			}
																			else { 
																				std::string *name = newtemp();
																				symrec *s = putsym(name, INTVAL | CONST_SPEC);
																				symrec *s1 = (yyvsp[-3].sym).var;
																				*(int*)((char*)datablock + s1->offset) = (*it)->val.intval;
																				if(isconstant((yyvsp[-3].sym).typ)){
																					name = newtemp();
																					s1 = putsym(name, INTVAL | CONST_SPEC);
																					*(int*)((char*)datablock + s->offset) = (yyvsp[-3].sym).val.intval;
																				}
																				gencode(IF_EQ_IR, s1, s, addr);
																			}
																		}
																	}
																	backpatch((yyvsp[0].lists).breaklist, nextinstr);
																	(yyval.lists).breaklist = NULL;
																	(yyval.lists).continuelist = (yyvsp[0].lists).continuelist;
																	(yyval.lists).gotolist = (yyvsp[0].lists).gotolist;
																	(yyval.lists).nextlist = NULL;
															}
#line 4391 "ansic.tab.c"
    break;

  case 203: /* logic_expression_statement: expression_statement  */
#line 2090 "ansic.y"
                                                                                                {
																(yyval.sym) = (yyvsp[0].sym);
																// Verificar si una expresion es comparacion u operacion logica
																if((yyvsp[0].sym).truelist == nullptr || (yyvsp[0].sym).falselist == nullptr){
																	std::string *name = newtemp();
																	symrec *s0;
																	s0 = putsym(name, INTVAL | CONST_SPEC);
																	*(int*)(datablock + s0->offset) = 0;
																	(yyval.sym).truelist = makelist(nextinstr);
																	gencode(IF_NE_IR, (yyvsp[0].sym).var, s0, nullptr);
																	(yyval.sym).falselist = makelist(nextinstr);
																	gencode(GOTO_IR);
																}
															}
#line 4410 "ansic.tab.c"
    break;

  case 204: /* iteration_statement: WHILE N '(' logic_expression ')' N statement  */
#line 2108 "ansic.y"
                                                                                                                        {	printf("iteration_statement: WHILE '(' expression ')' statement\n");
																						backpatch((yyvsp[0].lists).nextlist, (yyvsp[-5].instr));
																						backpatch((yyvsp[0].lists).continuelist , (yyvsp[-5].instr));
																						backpatch((yyvsp[-3].sym).truelist, (yyvsp[-1].instr));
																						(yyval.lists).nextlist = (yyvsp[-3].sym).falselist;
																						gencode(GOTO_IR, (yyvsp[-5].instr));
																						backpatch((yyvsp[0].lists).breaklist, nextinstr);
																						(yyval.lists).breaklist = NULL;
																						(yyval.lists).continuelist = NULL;
																						(yyval.lists).gotolist = (yyvsp[0].lists).gotolist;
																						
																					}
#line 4427 "ansic.tab.c"
    break;

  case 205: /* iteration_statement: DO N statement WHILE N '(' logic_expression ')' ';'  */
#line 2122 "ansic.y"
                                                                                                                                                {	printf("iteration_statement: DO statement WHILE '(' expression ')' ';'\n");
																						backpatch((yyvsp[-2].sym).truelist, (yyvsp[-7].instr));
																						backpatch((yyvsp[-6].lists).nextlist, (yyvsp[-4].instr));
																						backpatch((yyvsp[-6].lists).continuelist, (yyvsp[-4].instr));
																						backpatch((yyvsp[-6].lists).breaklist, nextinstr);
																						(yyval.lists).breaklist = NULL;
																						(yyval.lists).continuelist = NULL;
																						(yyval.lists).nextlist = (yyvsp[-2].sym).falselist;
																						(yyval.lists).gotolist = (yyvsp[-6].lists).gotolist;
																					}
#line 4442 "ansic.tab.c"
    break;

  case 206: /* iteration_statement: FOR '(' expression_statement N logic_expression_statement N ')' statement  */
#line 2134 "ansic.y"
                                                                                                                        {	printf("iteration_statement: FOR '(' expression_statement expression_statement ')' statement\n");
																						backpatch((yyvsp[-3].sym).truelist, (yyvsp[-2].instr));
																						backpatch((yyvsp[0].lists).nextlist, (yyvsp[-4].instr));
																						backpatch((yyvsp[0].lists).continuelist, (yyvsp[-4].instr));
																						(yyval.lists).nextlist = (yyvsp[-3].sym).falselist;
																						gencode(GOTO_IR, (yyvsp[-4].instr));
																						backpatch((yyvsp[0].lists).breaklist, nextinstr);
																						(yyval.lists).breaklist = NULL;
																						(yyval.lists).continuelist = NULL;
																						(yyval.lists).gotolist = (yyvsp[0].lists).gotolist;
																					}
#line 4458 "ansic.tab.c"
    break;

  case 207: /* iteration_statement: FOR '(' expression_statement N expression_statement N expression ')' M N statement  */
#line 2148 "ansic.y"
                                                                                                                                                        {	printf("iteration_statement: FOR '(' expression_statement expression_statement expression ')' statement\n");
																						backpatch((yyvsp[-6].sym).truelist, (yyvsp[-1].instr));
																						backpatch((yyvsp[0].lists).nextlist, (yyvsp[-5].instr));
																						backpatch((yyvsp[0].lists).continuelist, (yyvsp[-5].instr));
																						backpatch((yyvsp[-2].lists).nextlist, (yyvsp[-7].instr));
																						(yyval.lists).nextlist = (yyvsp[-6].sym).falselist;
																						gencode(GOTO_IR, (yyvsp[-5].instr));
																						backpatch((yyvsp[0].lists).breaklist, nextinstr);
																						(yyval.lists).breaklist = NULL;
																						(yyval.lists).continuelist = NULL;
																						(yyval.lists).gotolist = (yyvsp[0].lists).gotolist;
																					}
#line 4475 "ansic.tab.c"
    break;

  case 208: /* jump_statement: GOTO IDENTIFIER ';'  */
#line 2164 "ansic.y"
                                        {	printf("jump_statement: GOTO IDENTIFIER ';'\n");
									(yyval.lists).continuelist = NULL;
									(yyval.lists).breaklist = NULL;
									(yyval.lists).nextlist = NULL;
									(yyval.lists).caselist = NULL;
									(yyval.lists).gotolist = makelist(new string((yyvsp[-1].name)), nextinstr);
									gencode(GOTO_IR);
								}
#line 4488 "ansic.tab.c"
    break;

  case 209: /* jump_statement: CONTINUE ';'  */
#line 2173 "ansic.y"
                                                {	printf("jump_statement: CONTINUE ';'\n");
									(yyval.lists).breaklist = NULL;
									(yyval.lists).nextlist = NULL;
									(yyval.lists).caselist = NULL;
									(yyval.lists).gotolist = NULL;
									(yyval.lists).continuelist = makelist(nextinstr);
									gencode(GOTO_IR);
								}
#line 4501 "ansic.tab.c"
    break;

  case 210: /* jump_statement: BREAK ';'  */
#line 2182 "ansic.y"
                                                        {	printf("jump_statement: BREAK ';'\n");
									(yyval.lists).nextlist = NULL;
									(yyval.lists).continuelist = NULL;
									(yyval.lists).caselist = NULL;
									(yyval.lists).gotolist = NULL;
									(yyval.lists).breaklist = makelist(nextinstr);
									gencode(GOTO_IR);
								}
#line 4514 "ansic.tab.c"
    break;

  case 211: /* jump_statement: RETURN ';'  */
#line 2191 "ansic.y"
                                                {	printf("jump_statement: RETURN ';'\n");
									(yyval.lists).breaklist = NULL;
									(yyval.lists).nextlist = NULL;
									(yyval.lists).continuelist = NULL;
									(yyval.lists).caselist = NULL;
									(yyval.lists).gotolist = NULL;
									gencode(RET_IR);
								}
#line 4527 "ansic.tab.c"
    break;

  case 212: /* jump_statement: RETURN expression ';'  */
#line 2200 "ansic.y"
                                        {	printf("jump_statement: RETURN expression ';'\n");
									// Verificar si hay saltos truelist/falselist en expresion
									// si los hay, es porque contiene operaciones logicas
									// entonces calcular su valor logico 0 o 1
									if((yyvsp[-1].sym).truelist || (yyvsp[-1].sym).falselist){
											std::string *name = newtemp();
											symrec *s1, *s0;
											s0 = putsym(name, INTVAL | CONST_SPEC);
											setval(s0, 0);
											name = newtemp();
											s1 = putsym(name, INTVAL | CONST_SPEC);
											setval(s1, 1);
											name = newtemp();
											(yyvsp[-1].sym).var = putsym(name, INTVAL | VAR_SPEC);
											(yyvsp[-1].sym).typ = INTVAL | VAR_SPEC;
											(yyvsp[-1].sym).name = name;
											backpatch((yyvsp[-1].sym).truelist, nextinstr);
											gencode(STORE_IR, s1, nullptr, (yyvsp[-1].sym).var);
											gencode(GOTO_IR, nullptr, nullptr, nextinstr + 2);
											backpatch((yyvsp[-1].sym).falselist, nextinstr);
											gencode(STORE_IR, s0, nullptr, (yyvsp[-1].sym).var);
									}

									(yyval.lists).breaklist = NULL;
									(yyval.lists).nextlist = NULL;
									(yyval.lists).continuelist = NULL;
									(yyval.lists).caselist = NULL;
									(yyval.lists).gotolist = NULL;
									gencode(RET_IR, (yyvsp[-1].sym).var, nullptr, nullptr);
									
								}
#line 4563 "ansic.tab.c"
    break;

  case 213: /* translation_unit: external_declaration  */
#line 2234 "ansic.y"
                                                                        {	printf("translation_unit: external_declaration\n");
													;
												}
#line 4571 "ansic.tab.c"
    break;

  case 214: /* translation_unit: translation_unit external_declaration  */
#line 2238 "ansic.y"
                                                        {	printf("translation_unit: translation_unit external_declaration\n");
													;
												}
#line 4579 "ansic.tab.c"
    break;

  case 215: /* external_declaration: function_definition  */
#line 2244 "ansic.y"
                                {	printf("external_declaration: function_definition\n");
								;
							}
#line 4587 "ansic.tab.c"
    break;

  case 216: /* external_declaration: declaration  */
#line 2248 "ansic.y"
                                        {	printf("external_declaration: declaration\n");
								;
							}
#line 4595 "ansic.tab.c"
    break;

  case 217: /* function_definition: declaration_specifiers declarator declaration_list compound_statement  */
#line 2255 "ansic.y"
                                                                                        {	printf("function_definition: declaration_specifiers declarator declaration_list compound_statement\n");
	
																				}
#line 4603 "ansic.tab.c"
    break;

  case 218: /* $@4: %empty  */
#line 2259 "ansic.y"
                                                                                                                        {
																					int typ = get_type((yyvsp[-1].splist)) | (yyvsp[0].id_data)->typ; // Agregar bits extras para por ejemplo punteros
																					curr_func = getlocalsym((yyvsp[0].id_data)->name);
																					if(curr_func == nullptr){
																						curr_func = putsym((yyvsp[0].id_data)->name, typ | FUNC_SPEC);
																					}	
																					gencode(PROC_IR, curr_func);
																					localsyms = new symboltable();
																					enter_scope();
																					installarg((yyvsp[0].id_data)->arglist);
																					lab_table.clear(); // Limpiar tabla de etiquetas
																					setargs();
																				}
#line 4621 "ansic.tab.c"
    break;

  case 219: /* function_definition: declaration_specifiers declarator $@4 compound_statement  */
#line 2273 "ansic.y"
                                                                                                                                        {	printf("function_definition: declaration_specifiers declarator compound_statement\n");
																					printlocalvars();
																					exit_scope();
																					curr_func->func_desc.sym_table = localsyms;
																					gencode(ENDPROC_IR, curr_func);
																				}
#line 4632 "ansic.tab.c"
    break;

  case 220: /* function_definition: declarator declaration_list compound_statement  */
#line 2280 "ansic.y"
                                                                                                                {	printf("function_definition: declarator declaration_list compound_statement\n");
																					;
																				}
#line 4640 "ansic.tab.c"
    break;

  case 221: /* $@5: %empty  */
#line 2284 "ansic.y"
                                                                                                                                                {	// Acciones de mitad de regla
																					int typ = INTVAL | (yyvsp[0].id_data)->typ; // Agregar bits extras para por ejemplo punteros
																					curr_func = getlocalsym((yyvsp[0].id_data)->name);
																					if(curr_func == nullptr){
																						curr_func = putsym((yyvsp[0].id_data)->name, typ | FUNC_SPEC);
																					}		
																					gencode(PROC_IR, curr_func);																			
																					localsyms = new symboltable();
																					enter_scope(); // Iniciar un nuevo ambito local de variables
																					installarg((yyvsp[0].id_data)->arglist);
																					lab_table.clear(); // Limpiar tabla de etiquetas
																					setargs(); // Agregar atributo ARG_SPEC a variables

																				}
#line 4659 "ansic.tab.c"
    break;

  case 222: /* function_definition: declarator $@5 compound_statement  */
#line 2299 "ansic.y"
                                                                                                                                        {	printf("function_definition: declarator compound_statement\n");
																					printlocalvars();
																					exit_scope();
																					curr_func->func_desc.sym_table = localsyms;
																					gencode(ENDPROC_IR, curr_func);
																				}
#line 4670 "ansic.tab.c"
    break;


#line 4674 "ansic.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 2308 "ansic.y"


/* Seccion de Codigo Suplementario */

#include <stdio.h>

extern char yytext[]; // Usualmente no se necesita porque es parte del analizador lexico
extern int column; // Ambas variables para columnas y lineas son externas porque estan declaradas en otro archivo
extern int lineno; 

void yyerror(const char* s) {

	fflush(stdout); 
    fprintf(stderr, "\nSyntax error: %s\n", s);
	fprintf(stderr, "Line %d: %s\n", lineno + 1, yytext); // Imprimir toda la línea
   	fprintf(stderr, "%*s^\n", column + 6, ""); // Ajusta el espacio para que la flecha apunte a la columna del error
	exit(1);

} 


int main(int argc, char* argv[]) {

    printf("\nANSI C (1985) Compiler v ALPHA 0.9.5 by Andres Torres\n"); // Sintactic Analyzer

    if (argc < 2) { // Es decir que espera al menos dos prompts [0] y [1], si es menor a eso sale
        printf("Usage: %s <\"file to compile\">\n", argv[0]);
		printf("Compiler requires two arguments. Procces exit with failure e(1)\n" );
        exit(1);

    } else {

		// Capturar error de nulidad
        yyin = fopen(argv[1], "rt"); // El archivo a abrir en lectura de texto rt esta en argv[1]
        if (yyin == NULL) {
            printf("Error: Couldn't open file %s\n", argv[1]);
            exit(1);
        }

		std::string fname; // Para guardar nombre de archivo compilandose
		sym_table = new symboltable(); // Crear tabla de simbolos globales
		yyin = fopen(argv[1], "rt");
		fname = argv[1]; // Para usarlo al crear codigo ensamblador .asm assembly y darsela al ejecutable
		yyparse(); // Analisis sintactico + Analisis lexico
		printvars(); // Imprime variables, tablas de simbolos
		print_icode(); // Imprime el codigo intermedio
		print_code(fname); // Imprime el codigo de ensamblador
		printf("Succesful Compilation. Compiler exits with succes e(0)\n"); // En consola de Linux si aparecen acentos
		return 0;
       
    }

    return 0;
}

//Compilacion:
//flex ansi.l
//bison --defines=y.tab.h ansic.y
//gcc -o Acc lex.yy.c ansic.tab.c //se convirtio a C++ al agregar analizador semantico entonces:
//g++ -o Acc lex.yy.c ansic.tab.c 
//Al generar el codigo ensamblador ya solo necesitara un ensamblador para que se pueda generar un archivo.exe
