/* -------------------------------------- 
ANSI C Compiler v.01
By Andres Torres Ceja UDA Compiladores
16/04/2024
-----------------------------------------
*/

/* Seccion de Definiciones 
   Gramatica ya especificada en el manual oficial de ANSI C
*/

%{
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


%}

%union { // Directiva union que contiene la union de los atributos requeridos por los Tokens

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
	
}

/* Definicion de Tokens */
/* Los tokens superiores tienen mas precedencia que los inferiores */

%token <name> IDENTIFIER CONSTANT <sval> STRING_LITERAL SIZEOF // Tokens que llevan atributo yylval
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%nonassoc NOELSE // Para solucionar la ambiguedad del IF-ELSE 
%nonassoc ELSE

%type <typesp> type_specifier
%type <splist> declaration_specifiers
%type <scsp> storage_class_specifier
%type <typeq> type_qualifier
%type <id_data> direct_declarator
%type <id_data> declarator
%type <id_data> init_declarator
%type <idlist> init_declarator_list
%type <sym> primary_expression
%type <sym> postfix_expression
%type <sym> argument_expression_list
%type <sym> unary_expression
%type <sym> cast_expression
%type <sym> multiplicative_expression
%type <sym> additive_expression
%type <sym> shift_expression
%type <sym> relational_expression
%type <sym> equality_expression
%type <sym> and_expression
%type <sym> exclusive_or_expression
%type <sym> inclusive_or_expression
%type <sym> logical_and_expression
%type <sym> logical_or_expression
%type <sym> conditional_expression
%type <sym> assignment_expression
%type <sym> expression
%type <sym> constant_expression
%type <sym> initializer
%type <asop> assignment_operator
%type <pstruct> pointer
%type <idlist> parameter_list
%type <idlist> parameter_type_list
%type <sym> parameter_declaration
%type <splist> type_qualifier_list
%type <symlist> identifier_list
%type <typ> type_name
%type <sqlist> specifier_qualifier_list
%type <instr> N
%type <lists> M
%type <op> unary_operator
%type <sym> logic_expression
%type <lists> selection_statement
%type <lists> statement
%type <lists> labeled_statement
%type <lists> statement_list
%type <lists> compound_statement
%type <lists> iteration_statement
%type <lists> jump_statement
%type <sym> expression_statement
%type <sym> logic_expression_statement


%start translation_unit

%{
 	//extern int yylex(YYSTYPE * yylval_param, YYLTYPE * yylloc_param);	
%}

//%define api.pure
//%locations

%%

/* Seccion de Reglas 
   Gramatica CFG
*/

primary_expression
	: IDENTIFIER			{	printf("primary_expression: IDENTIFIER\n");
								std::string *name = new std::string($1);
								symrec *s = getsym(name);
								if(s == nullptr){
									printf("Variable %s ", $1);
									yyerror("not declared");
								}
								//std::cout << "<" << *name << ">" << std::endl;
								$$.name = name;
								$$.var = s;
								$$.typ = s->typ;
								$$.dimlist = s->dimlist;
								$$.plevel = 0;
							}

	| CONSTANT				{	printf("primary_expression: CONSTANT\n"); // Lleva atributo sym porque ira en la tabla de simbolos
								int typ = $<valtype>1; // sintaxis para leer esa variable de la union, leer el tipo de la variable
								std::string *name;
								symrec* s;
								switch (typ){ // Para las constantes se usa un @ y un numero para diferenciar las constantes de las variables declaradas

									case DOUBLEVAL:
										name = newtemp(); // Crear nueva variable temporal // Le da un nombre temporal por defecto
										s = putsym(name, DOUBLEVAL | CONST_SPEC); // Se pone la constante en la tabla de simbolos y se agrega atributo CONST por constante y/o el tipo, en este caso DOUBLEVAL y name para indicar su nombre
										setval(s, $<dval>1);// Para obtener el atributo 
										$$.val.doubleval = $<dval>1; // val esta en la esctructura VAR_DATA , es el valor inicial, que es a su vez estructura VALUE
										$$.name = name;
										$$.var = s; // Puntero hacia la variable
										$$.typ = s->typ; // Para guardar el tipo
										break;
									case INTVAL:
										name = newtemp();
										s = putsym(name, INTVAL | CONST_SPEC);
										setval(s, $<ival>1);
										$$.val.intval = $<ival>1;
										$$.name = name;
										$$.var = s;
										$$.typ = s->typ;
										break;
									case CHARVAL:
										name = newtemp();
										s = putsym(name, CHARVAL | CONST_SPEC);
										setval(s, $<cval>1);
										$$.val.charval = $<cval>1;
										$$.name = name;
										$$.var = s;
										$$.typ = s->typ;
										break;
								}
							}

	| STRING_LITERAL		{	printf("primary_expression: STRING_LITERAL\n"); // Literales cadena
								std::string *name; //Para nombre de una variable temporal
								symrec* s; //Para variable o constante en la tabla de simbolos
								name = newtemp(); // Crear variable temporal
								s = putsym(name, STRVAL | CONST_SPEC); //Declarar constante cadena en tabla de simbolos
								s->size = strlen($<sval>1) + 1; // Poner atributo size de la cadena, calcular longitud, +1 para caracter nulo
								setval(s, $<sval>1); // Copiar cadena en bloque de datos, copiar byte por byte usando la funcion
								data_location(s->size); // Ajustar posicion libre en bloque dde datos, ajusta el bloque de datos para que tome en cuanta el tamaño de la variable
								$$.var = s; // Asignar en atributos var la constante cadena de la tabla de simbolos
								$$.typ = s->typ; // Asignar en atributo typ el tipo de la constante cadena
								$$.name = new string(s->name); // Asignar en atributo name el nombre de la constante cadena
							}

	| '(' expression ')'	{	printf("primary_expression: '(' expression ')'\n");
								$$ = $2;
							}

	;

postfix_expression
	: primary_expression									{	printf("postfix_expression: primary_expression\n");
																$$ = $1; // Heredar el attributo de la var de la izquierda $ $ a la var de la derecha $ 1
															}

	| postfix_expression '[' expression ']'					{	printf("postfix_expression: postfix_expression '[' expression ']'\n");
																if($1.var == NULL){
																	yyerror("Error: Array name must be specified");
																}
																if(!isintegral($3.typ)){
																	yyerror("Array subscript must be integral typ\n");
																}
																// plevel es el numero de subindices del arreglo se inicializan a cero en regla de primary_expression
																//cout << "\tplevel = " << $ 1.plevel << endl;
																if($1.plevel > 0){
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
																	setval(s0, getsizeof($1.typ));
																	name = newtemp(); //s1 = N
																	symrec *s1 = putsym(name, INTVAL | CONST_SPEC);
																	setval(s1, getrdim($1.dimlist, $1.plevel - 1));
																	name = newtemp(); //s2 = j*sizeof(type)
																	symrec *s2 = putsym(name, INTVAL | VAR_SPEC);
																	gencode(MULT_IR, $3.var, s0, s2);
																	name = newtemp(); //s3 = i*N
																	symrec *s3 = putsym(name, INTVAL | VAR_SPEC);
																	gencode(MULT_IR, $1.var2, s1, s3);
																	name = newtemp(); //s4 = i*N + j*sizeof(type)
																	symrec *s4 = putsym(name, INTVAL | VAR_SPEC);
																	gencode(ADD_IR, s3, s2, s4);
																	$1.var2 = s4; //nuevo i = i*N + j*sizeof(type)															
																} 
																else {
																	/* Para el caso a[i]
																	postfix_expression = a
																	expression = i
																	i se multiplica por sizeof(type)
																	nuevo i = i*sizeof(type) */
																	std::string *name = newtemp(); // s1 = sizeof(type)
																	symrec *s1 = putsym(name, INTVAL | CONST_SPEC);
																	setval(s1, getsizeof($1.typ));
																	name = newtemp(); //s2 = i*sizeof(type)
																	symrec *s2 = putsym(name, INTVAL | VAR_SPEC);
																	gencode(MULT_IR, $3.var, s1, s2);
																	$1.var2 = s2; //nuevo i = i*sizeof(type)
																}
																// PENDIENTE A MODIFICAR
																$$ = $1;
																$$.typ |= ARRAY_SPEC; // agregar atributo spec por si no lo tiene
																$$.plevel++; // Incrementar numero de subinidices;
															}

	| postfix_expression '(' ')'							{	printf("postfix_expression: postfix_expression '(' ')'\n");
																std::string *name = newtemp();
																symrec *s = putsym(name, $1.typ & 0x1f);
																gencode(CALL_IR, $1.var, NULL, s);
																$$.var = s;
																$$.typ = s->typ;
																$$.name = name;
															}

	| postfix_expression '(' argument_expression_list ')'	{	printf("postfix_expression: postfix_expression '(' argument_expression_list ')'\n");
																std::list<VAR_DATA*>::reverse_iterator it;
																for(it = $3.arglist->rbegin(); it != $3.arglist->rend(); it++){
																	gencode(PARAM_IR, (*it)->var, nullptr, nullptr);
																}
																std::string *name = newtemp();
																symrec *s = putsym(name, $1.typ & 0x1f);
																symrec *s3 = new symrec();
																s3->name = "";
																s3->offset = $3.arglist->size();
																gencode(CALL_IR, $1.var, s3, s);
																$$.var = s;
																$$.typ = s->typ;
																$$.name = name;
															}

	| postfix_expression '.' IDENTIFIER						{	printf("postfix_expression: postfix_expression '.' IDENTIFIER\n");
																;
															}

	| postfix_expression PTR_OP IDENTIFIER					{	printf("postfix_expression: postfix_expression PTR_OP IDENTIFIER\n");
																;
															}

	| postfix_expression INC_OP								{	printf("postfix_expression: postfix_expression INC_OP\n");
																if(!isvar($1.typ)){
																	yyerror("Error: Increment operator requires a variable");
																}
																std::string *name = newtemp();
																symrec *s = putsym(name, $1.typ & 0x1f);
																gencode(STORE_IR, $1.var, NULL, s);
																gencode(INC_IR, $1.var, NULL, $1.var);
																$$.var = s;
																$$.typ = s->typ;
																$$.name = name;
															}

	| postfix_expression DEC_OP								{	printf("postfix_expression: postfix_expression DEC_OP\n");
																if(!isvar($1.typ)){
																	yyerror("Error: Decrement operator requires a variable");
																}
																std::string *name = newtemp();
																symrec *s = putsym(name, $1.typ & 0x1f);
																gencode(STORE_IR, $1.var, NULL, s);
																// PENDIENTE A MODIFICAR
																gencode(DEC_IR, $1.var, NULL, $1.var);
																$$.var = s;
																$$.typ = s->typ;
																$$.name = name;
															}

	;

argument_expression_list
	: assignment_expression									{	printf("argument_expression_list: assignment_expression\n");
																std::list<VAR_DATA*> *newlist = new std::list<VAR_DATA*>();
																VAR_DATA *newstruct = new VAR_DATA();
																*newstruct = $1;
																newlist->push_back(newstruct);
																$$.name = new std::string();
																$$.typ = 0;
																$$.arglist = newlist;
															}

	| argument_expression_list ',' assignment_expression	{	printf("argument_expression_list: argument_expression_list ',' assignment_expression\n");
																VAR_DATA *newstruct = new VAR_DATA();
																*newstruct = $3;
																$$ = $1;
																$$.arglist->push_back(newstruct);
															}

	;

unary_expression
	: postfix_expression				{	printf("unary_expression: postfix_expression\n");
											$$ = $1;
										}

	| INC_OP unary_expression			{	printf("unary_expression: INC_OP unary_expression\n");
											if(!isvar($2.typ)){
												yyerror("Error: Increment operator requires a variable");
											}
											gencode(INC_IR, $2.var, NULL, $2.var);
											$$ = $2;
										}

	| DEC_OP unary_expression			{	printf("unary_expression: DEC_OP unary_expression\n");
											if(!isvar($2.typ)){
												yyerror("Error: Decrement operator requires a variable");
											}
											gencode(DEC_IR, $2.var, NULL, $2.var);
											$$ = $2;
										}

	| unary_operator cast_expression	{	printf("unary_expression: unary_operator cast_expression\n");
											std::string *name;
											symrec *s;
											name = newtemp();
											// Para cada operador unario
											switch($1){
												case PLUS_OP:
													name = $2.name;
													s = $2.var;
													$$.typ = $2.typ;
													break;
												case ADDR_OP:
													name = newtemp();
													s = putsym(name, INTVAL);
													gencode(ADDRESS_IR, $2.var, nullptr, s);
													$$.typ = INTVAL;
													break;
												case DEREF_OP:
													name = newtemp();
													if(!ispointer($2.typ)){
														yyerror("Error: OPERAND MUST BE A POINTER\n");
													}
													s = putsym(name, $2.typ & ~POINTER_SPEC);
													gencode(DEREF_IR, $2.var, nullptr, s);
													$$.typ = $2.typ;
													break;
												case MINUS_OP:
													name = newtemp();
													s = putsym(name, $2.typ);
													gencode(MINUS_IR, $2.var, nullptr, s);
													$$.typ = $2.typ;
													break;
												case ONESCOMP_OP:
													name = newtemp();
													s = putsym(name, INTVAL);
													gencode(ONECOMP_IR, $2.var, nullptr, s);
													$$.typ = INTVAL;
													break;
												case NOT_OP:
													name = newtemp();
													//s = putsym(name, INTVAL);
													gencode(NOT_IR, $2.var, nullptr, s);
													tological(&($2));
													$$.truelist = $2.falselist;
													$$.falselist = $2.falselist;
													$$.typ = INTVAL;
													break;
											}
												$$.name = name;
												$$.var = s;											
										}

	| SIZEOF unary_expression			{	printf("unary_expression: SIZEOF unary_expression\n");
											std::string *name = newtemp();
											symrec *s = putsym(name, INTVAL | CONST_SPEC);
											int sz = getsizeof($2.typ);
											setval(s, sz);
											$$.var = s;
											$$.typ = s->typ;
											$$.name = name;
										}

	| SIZEOF '(' type_name ')'			{	printf("unary_expression: SIZEOF '(' type_name ')'\n");
											std::string *name = newtemp();
											symrec *s = putsym(name, INTVAL | CONST_SPEC);
											int sz = getsizeof($3);
											setval(s, sz);
											$$.var = s;
											$$.typ = s->typ;
											$$.name = name;
										}

	;

unary_operator
	: '&'	{	printf("unary_operator: '&'\n");
				$$ = ADDR_OP;
			}

	| '*'	{	printf("unary_operator: '*'\n");
				$$ = DEREF_OP;
			}

	| '+'	{	printf("unary_operator: '+'\n");
				$$ = PLUS_OP;
			}

	| '-'	{	printf("unary_operator: '-'\n");
				$$ = MINUS_OP;
			}

	| '~'	{	printf("unary_operator: '~'\n");
				$$ = ONESCOMP_OP;
			}

	| '!'	{	printf("unary_operator: '!'\n");
				$$ = NOT_OP;
			}

	;

cast_expression
	: unary_expression						{	printf("cast_expression: unary_expression\n");
												$$ = $1;
												if(isarray($1.typ)){
													
													string *name = newtemp();
													symrec *s = putsym(name, $1.typ & ~ARRAY_SPEC);
													gencode(LOADA_IR, $1.var, $1.var2, s);
													$$.name = name;
													$$.typ = s->typ;
													$$.var = s;
												}
											}

	| '(' type_name ')' cast_expression		{	printf("cast_expression: '(' type_name ')' cast_expression\n");
												std::string* name = newtemp();
												symrec *s;
												int typ = $2 & 0x1f;
												switch(typ){
													case CHARVAL:
														s = putsym(name, CHARVAL | VAR_SPEC);
														gencode(CHAR_IR, $4.var, NULL, s);
														break;
													case INTVAL:
														s = putsym(name, INTVAL | VAR_SPEC);
														gencode(INT_IR, $4.var, NULL, s);
														break;
													case FVAL:
														s = putsym(name, FVAL | VAR_SPEC);
														gencode(FLOAT_IR, $4.var, NULL, s);
														break;
													case DOUBLEVAL:
														s = putsym(name, FVAL | VAR_SPEC);
														gencode(DOUBLE_IR, $4.var, NULL, s);
														break;
												}
												$$.name = name;
												$$.typ = s->typ;
												$$.var = s;
											}

	;

multiplicative_expression
	: cast_expression								{	printf("multiplicative_expression: cast_expression\n");
														$$ = $1;
													}

	| multiplicative_expression '*' cast_expression	{	printf("multiplicative_expression: multiplicative_expression '*' cast_expression\n");
														int typ = gettype($1.typ, $3.typ) & 0x1f;
														std::string* name = newtemp();
														symrec *s;
														s = putsym(name, typ | VAR_SPEC);
														if(($1.typ & 0x1f) == ($3.typ & 0x1f)){
															gencode(MULT_IR, $1.var, $3.var, s);
														}
														else{
															symrec* s2;
															if(($1.typ & 0x1f) == typ){
																s2 = genconv(typ, $3.var);
																gencode(MULT_IR, $1.var, s2, s);
															}
															else{
																s2 = genconv(typ, $1.var);
																gencode(MULT_IR, s2, $3.var, s);
															}
														}
														$$.var = s;
														$$.typ = s->typ;
														$$.name = name;
													}

	| multiplicative_expression '/' cast_expression	{	printf("multiplicative_expression: multiplicative_expression '/' cast_expression\n");
														int typ = gettype($1.typ, $3.typ) & 0x1f;
														std::string* name = newtemp();
														symrec *s;
														s = putsym(name, typ | VAR_SPEC);
														if(($1.typ & 0x1f) == ($3.typ & 0x1f)){
															gencode(DIV_IR, $1.var, $3.var, s);
														}
														else{
															symrec* s2;
															if(($1.typ & 0x1f) == typ){
																s2 = genconv(typ, $3.var);
																gencode(DIV_IR, $1.var, s2, s);
															}
															else{
																s2 = genconv(typ, $1.var);
																gencode(DIV_IR, s2, $3.var, s);
															}
														}
														$$.var = s;
														$$.typ = s->typ;
														$$.name = name;
													}

	| multiplicative_expression '%' cast_expression	{	printf("multiplicative_expression: multiplicative_expression 'percent' cast_expression\n");
														int typ = gettype($1.typ, $3.typ) & 0x1f;
														std::string* name = newtemp();
														symrec *s;
														s = putsym(name, typ | VAR_SPEC);
														if(($1.typ & 0x1f) == ($3.typ & 0x1f)){
															gencode(MOD_IR, $1.var, $3.var, s);
														}
														else{
															symrec* s2;
															if(($1.typ & 0x1f) == typ){
																s2 = genconv(typ, $3.var);
																gencode(MOD_IR, $1.var, s2, s);
															}
															else{
																s2 = genconv(typ, $1.var);
																gencode(MOD_IR, s2, $3.var, s);
															}
														}
														$$.var = s;
														$$.typ = s->typ;
														$$.name = name;
													}

	;

additive_expression
	: multiplicative_expression							{	printf("additive_expression: multiplicative_expression\n");
															$$ = $1;
														}

	| additive_expression '+' multiplicative_expression	{	printf("additive_expression: additive_expression '+' multiplicative_expression\n");
															int typ = gettype($1.typ, $3.typ) & 0x1f;
															std::string* name = newtemp();
															symrec *s;
															s = putsym(name, typ | VAR_SPEC);
															if(($1.typ & 0x1f) == ($3.typ & 0x1f)){
																gencode(ADD_IR, $1.var, $3.var, s);
															}
															else{
																symrec* s2;
																if(($1.typ & 0x1f) == typ){
																	s2 = genconv(typ, $3.var);
																	gencode(ADD_IR, $1.var, s2, s);
																}
																else{
																	s2 = genconv(typ, $1.var);
																	gencode(ADD_IR, s2, $3.var, s);
																}
															}
															$$.var = s;
															$$.typ = s->typ;
															$$.name = name;
														}

	| additive_expression '-' multiplicative_expression	{	printf("additive_expression: additive_expression '-' multiplicative_expression\n");
															int typ = gettype($1.typ, $3.typ) & 0x1f;
															std::string* name = newtemp();
															symrec *s;
															s = putsym(name, typ | VAR_SPEC);
															if(($1.typ & 0x1f) == ($3.typ & 0x1f)){
																gencode(SUB_IR, $1.var, $3.var, s);
															}
															else{
																symrec* s2;
																if(($1.typ & 0x1f) == typ){
																	s2 = genconv(typ, $3.var);
																	gencode(SUB_IR, $1.var, s2, s);
																}
																else{
																	s2 = genconv(typ, $1.var);
																	gencode(SUB_IR, s2, $3.var, s);
																}
															}
															$$.var = s;
															$$.typ = s->typ;
															$$.name = name;
														}

	;

shift_expression
	: additive_expression							{	printf("shift_expression: additive_expression\n");
														$$ = $1;
													}

	| shift_expression LEFT_OP additive_expression	{	printf("shift_expression: shift_expression LEFT_OP additive_expression\n");
														int typ = gettype($1.typ, $3.typ) & 0x1f;
														if(!isintegral($1.typ & 0x1f)){
															yyerror("Left hand side of left shift operator must be integer\n");
														}
														if(!isintegral($3.typ & 0x1f)){
															yyerror("Right hand side of left shift operator must be integer\n");
														}
														std::string* name = newtemp();
														symrec *s;
														s = putsym(name, typ | VAR_SPEC);
														if(($1.typ & 0x1f) == ($3.typ & 0x1f)){
															gencode(LSHIFT_IR, $1.var, $3.var, s);
														}
														else{
															symrec* s2;
															if(($1.typ & 0x1f) == typ){
																s2 = genconv(typ, $3.var);
																gencode(LSHIFT_IR, $1.var, s2, s);
															}
															else{
																s2 = genconv(typ, $1.var);
																gencode(LSHIFT_IR, s2, $3.var, s);
															}
														}
														$$.var = s;
														$$.typ = s->typ;
														$$.name = name;
													}

	| shift_expression RIGHT_OP additive_expression	{	printf("shift_expression: shift_expression RIGHT_OP additive_expression\n");
														int typ = gettype($1.typ, $3.typ) & 0x1f;
														if(!isintegral($1.typ & 0x1f)){
															yyerror("Left hand side of right shift operator must be integer\n");
														}
														if(!isintegral($3.typ & 0x1f)){
															yyerror("Right hand side of right shift operator must be integer\n");
														}
														std::string* name = newtemp();
														symrec *s;
														s = putsym(name, typ | VAR_SPEC);
														if(($1.typ & 0x1f) == ($3.typ & 0x1f)){
															gencode(RSHIFT_IR, $1.var, $3.var, s);
														}
														else{
															symrec* s2;
															if(($1.typ & 0x1f) == typ){
																s2 = genconv(typ, $3.var);
																gencode(RSHIFT_IR, $1.var, s2, s);
															}
															else{
																s2 = genconv(typ, $1.var);
																gencode(RSHIFT_IR, s2, $3.var, s);
															}
														}
														$$.var = s;
														$$.typ = s->typ;
														$$.name = name;
													}

	;

relational_expression
	: shift_expression								{	printf("relational_expression: shift_expression\n");
														$$ = $1;
													}

	| relational_expression '<' shift_expression	{	printf("relational_expression: relational_expression '<' shift_expression\n");
														int typ = gettype($1.typ, $3.typ) & 0x1f;
															symrec *s1 = $1.var, *s2 = $3.var;
															if(($1.typ & 0x1f) != ($3.typ & 0x1f)){
																if(($1.typ & 0x1f) == typ){
																	s2 = genconv(typ, $3.var);
																}
																else{ // Conversion del segundo operando
																	s1 = genconv(typ, $1.var);
																}
															}
															$$.truelist = makelist(nextinstr);
															gencode(IF_LT_IR, s1, s2, nullptr);
															$$.falselist = makelist(nextinstr);
															gencode(GOTO_IR);
													}

	| relational_expression '>' shift_expression	{	printf("relational_expression: relational_expression '>' shift_expression\n");
														int typ = gettype($1.typ, $3.typ) & 0x1f;
															symrec *s1 = $1.var, *s2 = $3.var;
															if(($1.typ & 0x1f) != ($3.typ & 0x1f)){
																if(($1.typ & 0x1f) == typ){
																	s2 = genconv(typ, $3.var);
																}
																else{ // Conversion del segundo operando
																	s1 = genconv(typ, $1.var);
																}
															}
															$$.truelist = makelist(nextinstr);
															gencode(IF_GT_IR, s1, s2, nullptr);
															$$.falselist = makelist(nextinstr);
															gencode(GOTO_IR);
													}

	| relational_expression LE_OP shift_expression	{	printf("relational_expression: relational_expression LE_OP shift_expression\n");
														int typ = gettype($1.typ, $3.typ) & 0x1f;
															symrec *s1 = $1.var, *s2 = $3.var;
															if(($1.typ & 0x1f) != ($3.typ & 0x1f)){
																if(($1.typ & 0x1f) == typ){
																	s2 = genconv(typ, $3.var);
																}
																else{ // Conversion del segundo operando
																	s1 = genconv(typ, $1.var);
																}
															}
															$$.truelist = makelist(nextinstr);
															gencode(IF_LE_IR, s1, s2, nullptr);
															$$.falselist = makelist(nextinstr);
															gencode(GOTO_IR);
													}

	| relational_expression GE_OP shift_expression	{	printf("relational_expression: relational_expression GE_OP shift_expression\n");
														int typ = gettype($1.typ, $3.typ) & 0x1f;
															symrec *s1 = $1.var, *s2 = $3.var;
															if(($1.typ & 0x1f) != ($3.typ & 0x1f)){
																if(($1.typ & 0x1f) == typ){
																	s2 = genconv(typ, $3.var);
																}
																else{ // Conversion del segundo operando
																	s1 = genconv(typ, $1.var);
																}
															}
															$$.truelist = makelist(nextinstr);
															gencode(IF_GE_IR, s1, s2, nullptr);
															$$.falselist = makelist(nextinstr);
															gencode(GOTO_IR);
													}

	;

equality_expression
	: relational_expression								{	printf("equality_expression: relational_expression\n");
															$$ = $1;
														}

	| equality_expression EQ_OP relational_expression	{	printf("equality_expression: equality_expression EQ_OP relational_expression\n");
															int typ = gettype($1.typ, $3.typ) & 0x1f;
															symrec *s1 = $1.var, *s2 = $3.var;
															if(($1.typ & 0x1f) != ($3.typ & 0x1f)){
																if(($1.typ & 0x1f) == typ){
																	s2 = genconv(typ, $3.var);
																}
																else{ // Conversion del segundo operando
																	s1 = genconv(typ, $1.var);
																}
															}
															$$.truelist = makelist(nextinstr);
															gencode(IF_EQ_IR, s1, s2, nullptr);
															$$.falselist = makelist(nextinstr);
															gencode(GOTO_IR);
														}

	| equality_expression NE_OP relational_expression	{	printf("equality_expression: equality_expression NE_OP relational_expression\n");
															int typ = gettype($1.typ, $3.typ) & 0x1f;
															symrec* s1 = $1.var, *s2 = $3.var;
															if(($1.typ & 0x1f) != ($3.typ & 0x1f)){
																if(($1,typ & 0x1f) == typ){
																	s2 = genconv(typ, $3.var);
																}
																else{
																	s1 = genconv(typ, $1.var);
																}
															}
															$$.truelist = makelist(nextinstr);
															gencode(IF_NE_IR, s1, s2, nullptr);
															$$.falselist = makelist(nextinstr);
															gencode(GOTO_IR);
														}

	;

and_expression
	: equality_expression						{	printf("and_expression: equality_expression\n");
													$$ = $1;
												}

	| and_expression '&' equality_expression	{	printf("and_expression: and_expression '&' equality_expression\n");
													int typ = gettype($1.typ, $3.typ) & 0x1f;
													std::string* name = newtemp();
													symrec *s = putsym(name, typ);
													if(($1.typ & 0x1f) == ($3.typ & 0x1f)){
														gencode(AND_IR, $1.var, $3.var, s);
													}
													else{
														symrec* s2;
														if(($1.typ & 0x1f) == typ){
															s2 = genconv(typ, $3.var);
															gencode(AND_IR, $1.var, s2, s);
														}
														else{
															s2 = genconv(typ, $1.var);
															gencode(AND_IR, s2, $3.var, s);
														}
													}
													$$.var = s;
													$$.typ = s->typ;
													$$.name = name;
												}

	;

exclusive_or_expression
	: and_expression								{	printf("exclusive_or_expression: and_expression\n");
														$$ = $1;
													}

	| exclusive_or_expression '^' and_expression	{	printf("exclusive_or_expression: exclusive_or_expression '^' and_expression\n");
														int typ = gettype($1.typ, $3.typ) & 0x1f;
														std::string* name = newtemp();
														symrec *s = putsym(name, typ);
														if(($1.typ & 0x1f) == ($3.typ & 0x1f)){
															gencode(XOR_IR, $1.var, $3.var, s);
														}
														else{
															symrec* s2;
															if(($1.typ & 0x1f) == typ){
																s2 = genconv(typ, $3.var);
																gencode(XOR_IR, $1.var, s2, s);
															}
															else{
																s2 = genconv(typ, $1.var);
																gencode(XOR_IR, s2, $3.var, s);
															}
														}
														$$.var = s;
														$$.typ = s->typ;
														$$.name = name;
													}

	;

inclusive_or_expression
	: exclusive_or_expression								{	printf("inclusive_or_expression: exclusive_or_expression\n");
																$$ = $1;
															}

	| inclusive_or_expression '|' exclusive_or_expression	{	printf("inclusive_or_expression: inclusive_or_expression '|' exclusive_or_expression\n");
																int typ = gettype($1.typ, $3.typ) & 0x1f;
																std::string* name = newtemp();
																symrec* s = putsym(name, typ);
																if(($1.typ & 0x1f) == ($3.typ & 0x1f)){
																	gencode(OR_IR, $1.var, $3.var, s);
																}
																else{
																	symrec* s2;
																	if(($1.typ & 0x1f) == typ){
																		s2 = genconv(typ, $3.var);
																		gencode(OR_IR, $1.var, s2, s);
																	}
																	else{
																		s2 = genconv(typ, $1.var);
																		gencode(OR_IR, s2, $3.var, s);
																	}
																}
																$$.var = s;
																$$.typ = s->typ;
																$$.name = name;
															}

	;

N 
	:	/* EMPTY */		{	// Esta regla sirve para capturar direccion de siguiente instruccion de IR
							$$ = nextinstr;
						}

	;

logical_and_expression
	: inclusive_or_expression									{	printf("logical_and_expression: inclusive_or_expression\n");
																	$$ = $1;
																}

	| logical_and_expression AND_OP N inclusive_or_expression	{	printf("logical_and_expression: logical_and_expression AND_OP inclusive_or_expression\n");
																	backpatch($1.truelist, $3);
																	$$.truelist = $4.truelist;
																	$$.falselist = $1.falselist;
																	$$.falselist->merge(*($4.falselist));
																	$$.typ = INTVAL; // Un valor logico es entero
																}

	;

logical_or_expression
	: logical_and_expression								{	printf("logical_or_expression: logical_and_expression\n");
																$$ = $1;
															}

	| logical_or_expression OR_OP N logical_and_expression	{	printf("logical_or_expression: logical_or_expression OR_OP logical_and_expression\n");
																backpatch($1.falselist, $3);
																$$.falselist = $4.falselist;
																$$.truelist = $1.truelist;
																$$.truelist->merge(*($4.truelist));
																$$.typ = INTVAL; // Un valor logico es entero
															}

	;

M
	: /* EMPTY */		{	// Agregar direccion de siguiente instruccion de IR en atributo nextlist y generar instruccion de salto pendiente
						$$.nextlist = makelist(nextinstr);
						gencode(GOTO_IR);
					}
	
	;


conditional_expression
	: logical_or_expression													{	printf("conditional_expression: logical_or_expression\n");
																				$$ = $1;
																			}

	| logical_or_expression												{	
																			// Verificar si logical_or_expression es logica si no lo es,
																			//generar codigo para comparar con 0
																			if($1.truelist == nullptr || $1.falselist == nullptr){ 
																				std::string* name = newtemp();
																				symrec* s0;
																				if(isfloat($1.typ)){
																					s0 = putsym(name, FVAL | CONST_SPEC);
																					setval(s0, 0.0f);
																				}
																				else{
																					s0 = putsym(name, INTVAL | CONST_SPEC);
																					setval(s0, 0);
																				}
																				$1.truelist = makelist(nextinstr);
																				gencode(IF_NE_IR, $1.var, s0, nullptr);
																				$1.falselist = makelist(nextinstr);
																				gencode(GOTO_IR);
																			}

																		}

	  '?' N expression ':'												{	
																			std::string* name = newtemp();
																			symrec* s = putsym(name, $5.typ & ~CONST_SPEC | VAR_SPEC);
																			gencode(STORE_IR, $5.var, NULL, s);
																			$5.var = s;
																			$5.typ = s->typ;
																		}

	  M N conditional_expression											{
																			printf("conditional_expression: logical_or_expression '?' expression ':' conditional_expression\n");
																			gencode(STORE_IR, $10.var, NULL, $5.var);
																			$$.var = $5.var;
																			$$.typ = $5.typ;
																			backpatch($1.truelist, $4);
																			backpatch($1.falselist, $9);
																			backpatch($8.nextlist, nextinstr);
																			$$.truelist = nullptr;
																			$$.falselist = nullptr;
																		}

	;

assignment_expression
	: conditional_expression										{	printf("assignment_expression: conditional_expression\n");
																		$$ = $1;
																	}

	| unary_expression assignment_operator assignment_expression	{	printf("assignment_expression: unary_expression assignment_operator assignment_expression\n");
																		string *name;
																		symrec *s, *s2, *s3;
																		if($3.truelist || $3.falselist){
																			std::string *name = newtemp();
																			symrec *s1, *s0;
																			s0 = putsym(name, INTVAL | CONST_SPEC);
																			*(int*)(datablock + s0->offset) = 0; // Valor logico 0
																			name = newtemp();
																			s1 = putsym(name, INTVAL | CONST_SPEC);
																			*(int*)(datablock + s1->offset) = 1; // Valor logico 1
																			name = newtemp();
																			$3.var = putsym(name, INTVAL | VAR_SPEC);
																			$3.typ = INTVAL | VAR_SPEC;
																			$3.name = name;
																			backpatch($3.truelist, nextinstr);
																			gencode(STORE_IR, s1, nullptr, $3.var);
																			gencode(GOTO_IR, nullptr, nullptr, nextinstr + 2);
																			backpatch($3.falselist, nextinstr);
																			gencode(STORE_IR, s0, nullptr, $3.var);
																		}
																		switch($2){
																			case EQ_ASSIGN_OP:
																				if(!isarray($1.typ)){
																					if(($3.typ & 0x1f) == ($1.typ & 0x1f)){
																						gencode(STORE_IR, $3.var, nullptr, $1.var);
																					}
																					else{
																						s3 = genconv($1.typ, $3.var);
																						gencode(STORE_IR, s3, nullptr, $1.var);
																					}
																				} else {
																					if(($3.typ & 0x1f) == ($1.typ & 0x1f))
																						gencode(STOREA_IR, $3.var, $1.var2, $1.var);
																					else{
																						s3 = genconv($1.typ, $3.var);
																						gencode(STOREA_IR, s3, $1.var2, $1.var);
																					}
																				}
																				break;
																			case MUL_ASSIGN_OP:
																				genassign(MULT_IR, &$1, &$3);
																				break;
																			case DIV_ASSIGN_OP:
																				genassign(DIV_IR, &$1, &$3);
																				break;
																			case MOD_ASSIGN_OP:
																				genassign(MOD_IR, &$1, &$3);
																				break;
																			case ADD_ASSIGN_OP:
																				genassign(ADD_IR, &$1, &$3);
																				break;
																			case SUB_ASSIGN_OP:
																				genassign(SUB_IR, &$1, &$3);
																				break;
																			case LEFT_ASSIGN_OP:
																				genassign(LSHIFT_IR, &$1, &$3);
																				break;
																			case RIGHT_ASSIGN_OP:
																				genassign(RSHIFT_IR, &$1, &$3);
																				break;
																			case AND_ASSIGN_OP:
																				genassign(AND_IR, &$1, &$3);
																				break;
																			case XOR_ASSIGN_OP:
																				genassign(XOR_IR, &$1, &$3);
																				break;
																			case OR_ASSIGN_OP:
																				genassign(OR_IR, &$1, &$3);
																				break;
																		}
																	}

	;

assignment_operator
	: '='			{	printf("assignment_operator: '='\n");
						$$ = EQ_ASSIGN_OP;
					}

	| MUL_ASSIGN	{	printf("assignment_operator: MUL_ASSIGN\n");
						$$ = MUL_ASSIGN_OP;
					}

	| DIV_ASSIGN	{	printf("assignment_operator: DIV_ASSIGN\n");
						$$ = DIV_ASSIGN_OP;
					}

	| MOD_ASSIGN	{	printf("assignment_operator: MOD_ASSIGN\n");
						$$ = MOD_ASSIGN_OP;
					}

	| ADD_ASSIGN	{	printf("assignment_operator: ADD_ASSIGN\n");
						$$ = ADD_ASSIGN_OP;
					}

	| SUB_ASSIGN	{	printf("assignment_operator: SUB_ASSIGN\n");
						$$ = SUB_ASSIGN_OP;
					}

	| LEFT_ASSIGN	{	printf("assignment_operator: LEFT_ASSIGN\n");
						$$ = LEFT_ASSIGN_OP;
					}

	| RIGHT_ASSIGN	{	printf("assignment_operator: RIGHT_ASSIGN\n");
						$$ = RIGHT_ASSIGN_OP;
					}

	| AND_ASSIGN	{	printf("assignment_operator: AND_ASSIGN\n");
						$$ = AND_ASSIGN_OP;
					}

	| XOR_ASSIGN	{	printf("assignment_operator: XOR_ASSIGN\n");
						$$ = XOR_ASSIGN_OP;
					}

	| OR_ASSIGN		{	printf("assignment_operator: OR_ASSIGN\n");
						$$ = OR_ASSIGN_OP;
					}

	;

expression
	: assignment_expression					{	printf("expression: assignment_expression\n");
												$$ = $1;
											}

	| expression ',' assignment_expression	{	printf("expression: expression ',' assignment_expression\n");
												;
											}

	;

constant_expression
	: conditional_expression	{	printf("constant_expression: conditional_expression\n");
									$$ = $1;
								}

	;

declaration
	: declaration_specifiers ';'						{	printf("declaration: declaration_specifiers ';'\n");
															;
														}

	| declaration_specifiers init_declarator_list ';'	{	printf("declaration: declaration_specifiers init_declarator_list ';'\n");
															int typ = get_type($1);
															symrec* s; // Variable que apunta a una estructura symrec
															std::list<VAR_DATA*>::iterator it;
															for(it = $2->begin(); it != $2->end(); it ++){
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

	;

declaration_specifiers
	: storage_class_specifier							{	printf("declaration_specifiers: storage_class_specifier\n");
															std::list<int>* newlist = new std::list<int>; // Lista de enteros
															newlist->push_back($1); // Poner primer atributo del no terminal en la cima de la lista
															$$ = newlist; // Se le asigna a la regla declaration_specifier
														}

	| storage_class_specifier declaration_specifiers	{	printf("declaration_specifiers: storage_class_specifier declaration_specifiers\n");
															$$ = $2;
															$$->push_back($1);
														}

	| type_specifier									{	printf("declaration_specifiers: type_specifier\n");
															std::list<int>* newlist = new std::list<int>; // Lista de enteros
															newlist->push_back($1); // Poner primer atributo del no terminal en la cima de la lista
															$$ = newlist; // Se le asigna a la regla declaration_specifier
														}

	| type_specifier declaration_specifiers				{	printf("declaration_specifiers: type_specifier declaration_specifiers\n");
															$$->push_back($1);
															$$ = $2;
														}

	| type_qualifier									{	printf("declaration_specifiers: type_qualifier\n");
															std::list<int>* newlist = new std::list<int>; // Lista de enteros
															newlist->push_back($1); // Poner primer atributo del no terminal en la cima de la lista
															$$ = newlist; // Se le asigna a la regla declaration_specifier
														}

	| type_qualifier declaration_specifiers				{	printf("declaration_specifiers: type_qualifier declaration_specifiers\n");
															$$->push_back($1);
															$$ = $2;
														}

	;

init_declarator_list
	: init_declarator							{	printf("init_declarator_list: init_declarator\n");
													std::list<VAR_DATA*>* ptr = new std::list<VAR_DATA*>;
													//VAR_DATA *newstruct = $ 1 //$ 1 ya es una estructura VAR_DATA entonces no es necesario
													ptr->push_back($1); 
													$$ = ptr;
												}

	| init_declarator_list ',' init_declarator	{	printf("init_declarator_list: init_declarator_list ',' init_declarator\n");
													$1->push_back($3);
													$$ = $1;
												}

	;

init_declarator
	: declarator					{	printf("init_declarator: declarator\n");
										$$ = $1;
										$$->init = 0; // Variable no inicializada
									}

	| declarator '=' initializer	{	printf("init_declarator: declarator '=' initializer\n");
										$$ = $1;
										$$->init = 1; // Variable inicializada
										$$->var = $3.var;
									}

	;

storage_class_specifier
	: TYPEDEF	{	printf("storage_class_specifier: TYPEDEF\n");
					$$ = TYPEDEF_SPEC;
				}

	| EXTERN	{	printf("storage_class_specifier: EXTERN\n");
					$$ = EXTERN_SPEC;
				}

	| STATIC	{	printf("storage_class_specifier: STATIC\n");
					$$ = STATIC_SPEC;
				}

	| AUTO		{	printf("storage_class_specifier: AUTO\n");
					$$ = AUTO_SPEC;
				}

	| REGISTER	{	printf("storage_class_specifier: REGISTER\n");
					$$ = REGISTER_SPEC;
				}

	;

type_specifier
	: VOID						{	printf("type_specifier: VOID\n");
									$$ = VOID_SPEC;
								}

	| CHAR						{	printf("type_specifier: CHAR\n");
									$$ = CHAR_SPEC;
								}

	| SHORT						{	printf("type_specifier: SHORT\n");
									$$ = SHORT_SPEC;
								}

	| INT						{	printf("type_specifier: INT\n");
									$$ = INT_SPEC;
								}

	| LONG						{	printf("type_specifier: LONG\n");
									$$ = LONG_SPEC;
								}

	| FLOAT						{	printf("type_specifier: FLOAT\n");
									$$ = FLOAT_SPEC;
								}

	| DOUBLE					{	printf("type_specifier: DOUBLE\n");
									$$ = DOUBLE_SPEC;
								}	

	| SIGNED					{	printf("type_specifier: SIGNED\n");
									$$ = SIGNED_SPEC;
								}

	| UNSIGNED					{	printf("type_specifier: UNSIGNED\n");
									$$ = UNSIGNED_SPEC;
								}

	| struct_or_union_specifier	{	printf("type_specifier: struct_or_union_specifier\n");
									;
								}

	| enum_specifier			{	printf("type_specifier: enum_specifier\n");
									;
								}

	| TYPE_NAME					{	printf("type_specifier: TYPE_NAME\n");
									$$ = TYPENAME_SPEC;
								}
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'	{	printf("struct_or_union_specifier: struct_or_union IDENTIFIER '{' struct_declaration_list '}'\n");
																		;
																	}

	| struct_or_union '{' struct_declaration_list '}'				{	printf("struct_or_union_specifier: struct_or_union '{' struct_declaration_list '}'\n");
																		;
																	}

	| struct_or_union IDENTIFIER									{	printf("struct_or_union_specifier: struct_or_union IDENTIFIER\n");
																		;
																	}

	;

struct_or_union
	: STRUCT	{	printf("struct_or_union: STRUCT\n");
					;
				}

	| UNION		{	printf("struct_or_union: UNION\n");
					;
				}

	;

struct_declaration_list
	: struct_declaration							{	printf("struct_declaration_list: struct_declaration\n");
														;
													}

	| struct_declaration_list struct_declaration	{	printf("struct_declaration_list: struct_declaration_list struct_declaration\n");
														;
													}

	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'	{	printf("struct_declaration: specifier_qualifier_list struct_declarator_list ';'\n");
																;
															}

	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list	{	printf("specifier_qualifier_list: type_specifier specifier_qualifier_list\n");
													$2->push_back($1);
													$$ = $2;
												}

	| type_specifier							{	printf("specifier_qualifier_list: type_specifier\n");
													std::list<int>* newlist = new std::list<int>();
													newlist->push_back($1);
													$$ = newlist;
												}

	| type_qualifier specifier_qualifier_list	{	printf("specifier_qualifier_list: type_qualifier specifier_qualifier_list\n");
													$2->push_back($1);
													$$ = $2;
												}

	| type_qualifier							{	printf("specifier_qualifier_list: type_qualifier\n");
													std::list<int>* newlist = new std::list<int>();
													newlist->push_back($1);
													$$ = newlist;
												}

	;

struct_declarator_list
	: struct_declarator								{	printf("struct_declarator_list: struct_declarator\n");
														;
													}

	| struct_declarator_list ',' struct_declarator	{	printf("struct_declarator_list: struct_declarator_list ',' struct_declarator\n");
														;
													}

	;

struct_declarator
	: declarator							{	printf("struct_declarator: declarator\n");
												;
											}

	| ':' constant_expression				{	printf("struct_declarator: ':' constant_expression\n");
												;
											}

	| declarator ':' constant_expression	{	printf("struct_declarator: declarator ':' constant_expression\n");
												;
											}

	;

enum_specifier
	: ENUM '{' enumerator_list '}'				{	printf("enum_specifier: ENUM '{' enumerator_list '}'\n");
													;
												}

	| ENUM IDENTIFIER '{' enumerator_list '}'	{	printf("enum_specifier: ENUM IDENTIFIER '{' enumerator_list '}'\n");
													;
												}

	| ENUM IDENTIFIER							{	printf("enum_specifier: ENUM IDENTIFIER\n");
													;
												}

	;

enumerator_list
	: enumerator						{	printf("enumerator_list: enumerator\n");
											;
										}

	| enumerator_list ',' enumerator	{	printf("enumerator_list: enumerator_list ',' enumerator\n");
											;
										}

	;

enumerator
	: IDENTIFIER							{	printf("enumerator: IDENTIFIER\n");
												;
											}

	| IDENTIFIER '=' constant_expression	{	printf("enumerator: IDENTIFIER '=' constant_expression\n");
												;
											}

	;

type_qualifier
	: CONST				{	printf("type_qualifier: CONST\n");
							$$ = CONST_SPEC;
						}

	| VOLATILE			{	printf("type_qualifier: VOLATILE\n");
							$$ = VOLATILE_SPEC;
						}

	;

declarator
	: pointer direct_declarator		{	printf("declarator: pointer direct_declarator\n");
										$$ = $2;
										$$->plevel = $1.level;
										$$->typ |= POINTER_SPEC | $1.typq;
									}

	| direct_declarator				{	printf("declarator: direct_declarator\n");
										$$ = $1;
										if(isarray($$->typ)){
											if(allzero($$->dimlist)){
												$$->typ &= ~ARRAY_SPEC;
											}
											//Arreglos sin dimensiones son punteros
											if(allzero($$->dimlist)){
												$$->typ &= ~ARRAY_SPEC;
												$$->typ |= POINTER_SPEC;
											}
											else{
												if(product($$->dimlist) == 0)
													yyerror("Array dimensions must be specified!");
											}
										}
									}

	;

direct_declarator
	: IDENTIFIER									{	printf("direct_declarator: IDENTIFIER\n");
														VAR_DATA *newsym = new VAR_DATA();
														string* namestr = new string ($1); // El nombre es el atributo id del token IDENTIFIER
														//cout << "name = " << *name << endl; //depuracion
														$$ = newsym;
														$$->name = namestr; //char* = cadena de c, string cadena de C++
														$$->dimlist = nullptr;
														$$->typ = 0;
													}

	| '(' declarator ')'							{	printf("direct_declarator: '(' declarator ')'\n");
														;
													}

	| direct_declarator '[' constant_expression ']'	{	printf("direct_declarator: direct_declarator '[' constant_expression ']'\n"); // Arreglo con dimensiones
														if(!isintegral($3.typ)){
															yyerror("Array dimensions must be integral");
														}
														if(!isconstant($3.typ)){
															yyerror("Array dimensions must be constant");	
														}
														$$ = $1; //Herencia/Propagacion de atributo del primero
														if($$->dimlist == nullptr){
															$$->dimlist = new std::list<int>;
														}
														$$->dimlist->push_back($3.val.intval);
														$$->typ |= ARRAY_SPEC; // Agregar un bit
														
													}

	| direct_declarator '[' ']'						{	printf("direct_declarator: direct_declarator '[' ']'\n"); // Arreglo sin dimensiones, como en la ultima de un arreglo bidimensional
														$$ = $1; //Herencia/Propagacion de atributo del primero
														if($$->dimlist == nullptr){
															$$->dimlist = new std::list<int>;
														}
														$$->dimlist->push_back(0); // Agregar 0 a la lista
														$$->typ |= ARRAY_SPEC; // Agregar un bit
													}
													
	| direct_declarator '(' parameter_type_list ')'	{	printf("direct_declarator: direct_declarator '(' parameter_type_list ')'\n");
														$$ = $1;
														$$->typ |= FUNC_SPEC;
														$$->arglist = $3;
														$$->init = 0;
													}
													
	| direct_declarator '(' identifier_list ')'		{	printf("direct_declarator: direct_declarator '(' identifier_list ')'\n");
														$$ = $1;
														$$->typ |= FUNC_SPEC;
													}

	| direct_declarator '(' ')'						{	printf("direct_declarator: direct_declarator '(' ')'\n");
														$$ = $1;
														$$->typ |= FUNC_SPEC;
														$$->init = 0;
													}

	;

pointer
	: '*'								{	printf("pointer: '*'\n");
											$$.typq = POINTER_SPEC; // Atributo sintetizado
											$$.level = 1;
										}

	| '*' type_qualifier_list			{	printf("pointer: '*' type_qualifier_list\n");
											$$.typq = get_type($2) | POINTER_SPEC;
											$$.level = 1;
										}

	| '*' pointer						{	printf("pointer: '*' pointer\n");
											$$ = $2;
											$$.level++;
										}

	| '*' type_qualifier_list pointer	{	printf("pointer: '*' type_qualifier_list pointer\n");
											$$ = $3;
											$$.typq = get_type($2);
											$$.level++;
										}

	;

type_qualifier_list
	: type_qualifier						{	printf("type_qualifier_list: type_qualifier\n");
												std::list<int>* newlist = new list<int>();
												newlist->push_back($1);
												$$ = newlist;
											}

	| type_qualifier_list type_qualifier	{	printf("type_qualifier_list: type_qualifier_list type_qualifier\n");
												$$ = $1;
												$$->push_back($2);
											}

	;


parameter_type_list
	: parameter_list				{	printf("parameter_type_list: parameter_list\n");
										$$ = $1;
									}

	| parameter_list ',' ELLIPSIS	{	printf("parameter_type_list: parameter_list ',' ELLIPSIS\n");
										$$ = $1;
									}

	;

parameter_list
	: parameter_declaration						{	printf("parameter_list: parameter_declaration\n");
													std::list<VAR_DATA*>* newlist = new std::list<VAR_DATA*>;
													VAR_DATA* newstruct = new VAR_DATA();
													*newstruct = $1;
													newlist->push_back(newstruct);
													$$ = newlist;
												}

	| parameter_list ',' parameter_declaration	{	printf("parameter_list: parameter_list ',' parameter_declaration\n");
													$$ = $1;
													VAR_DATA *newstruct = new VAR_DATA();
													*newstruct = $3;
													$$->push_back(newstruct);
												}

	;

parameter_declaration
	: declaration_specifiers declarator				{	printf("parameter_declaration: declaration_specifiers declarator\n");
														$$.name = $2->name;
														if(!isarray($2->typ)){
															$$.typ = get_type($1);
														}
														else{
															$$.typ = get_type($1) | ARRAY_SPEC;
														}
													}

	| declaration_specifiers abstract_declarator	{	printf("parameter_declaration: declaration_specifiers abstract_declarator\n");
														;
													}
													
	| declaration_specifiers						{	printf("parameter_declaration: declaration_specifiers\n");
														;
													}

	;

identifier_list
	: IDENTIFIER						{	printf("identifier_list: IDENTIFIER\n");
											std::list<VAR_DATA*>* newlist = new std::list<VAR_DATA*>();
											VAR_DATA* newsym = new VAR_DATA();
											newsym->name = new std::string($1);
											newsym->dimlist = NULL;
											newsym->typ = 0;
											newlist->push_back(newsym);
											$$ = newlist;
										}

	| identifier_list ',' IDENTIFIER	{	printf("identifier_list: identifier_list ',' IDENTIFIER\n");
											VAR_DATA* newsym = new VAR_DATA();
											newsym->name = new std::string($3);
											newsym->dimlist = NULL;
											newsym->typ = 0;
											$$ = $1;
											$$->push_back(newsym);
										}

	;

type_name
	: specifier_qualifier_list						{	printf("type_name: specifier_qualifier_list\n");
														$$ = get_type($1);
													}

	| specifier_qualifier_list abstract_declarator	{	printf("type_name: specifier_qualifier_list abstract_declarator\n");
														$$ = get_type($1);
													}

	;

abstract_declarator
	: pointer								{	printf("abstract_declarator: pointer\n");
												;
											}

	| direct_abstract_declarator			{	printf("abstract_declarator: direct_abstract_declarator\n");
												;
											}

	| pointer direct_abstract_declarator	{	printf("abstract_declarator: pointer direct_abstract_declarator\n");
												;
											}

	;

direct_abstract_declarator
	: '(' abstract_declarator ')'								{	printf("direct_abstract_declarator: '(' abstract_declarator ')'\n");
																	;
																}

	| '[' ']'													{	printf("direct_abstract_declarator: '[' ']'\n");
																	;
																}

	| '[' constant_expression ']'								{	printf("direct_abstract_declarator: '[' constant_expression ']'\n");
																	;
																}

	| direct_abstract_declarator '[' ']'						{	printf("direct_abstract_declarator: direct_abstract_declarator '[' ']'\n");
																	;
																}

	| direct_abstract_declarator '[' constant_expression ']'	{	printf("direct_abstract_declarator: direct_abstract_declarator '[' constant_expression ']'\n");
																	;
																}

	| '(' ')'													{	printf("direct_abstract_declarator: '(' ')'\n");
																	;
																}

	| '(' parameter_type_list ')'								{	printf("direct_abstract_declarator: '(' parameter_type_list ')'\n");
																	;
																}

	| direct_abstract_declarator '(' ')'						{	printf("direct_abstract_declarator: direct_abstract_declarator '(' ')'\n");
																	;
																}

	| direct_abstract_declarator '(' parameter_type_list ')'	{	printf("direct_abstract_declarator: direct_abstract_declarator '(' parameter_type_list ')'\n");
																	;
																}

	;

initializer
	: assignment_expression			{	printf("initializer: assignment_expression\n");
										$$ = $1;
									}

	| '{' initializer_list '}'		{	printf("initializer: '{' initializer_list '}'\n");
										;
									}

	| '{' initializer_list ',' '}'	{	printf("initializer: '{' initializer_list ',' '}'\n");
										;
									}

	;

initializer_list
	: initializer						{	printf("initializer_list: initializer\n");
											;
										}

	| initializer_list ',' initializer	{	printf("initializer_list: initializer_list ',' initializer\n");
											;
										}

	;

P	: /* */		{

				}
	
	;

statement
	: labeled_statement		{	printf("statement: labeled_statement\n");
								$$ = $1;
								$$.nextlist = NULL;
							}

	| P						{
								enter_scope();
							}

	 compound_statement		{	printf("statement: compound_statement\n");
	 							printlocalvars();
								exit_scope();
								$$ = $3;	
							}

	| expression_statement	{	printf("statement: expression_statement\n");
								$$.nextlist = merge($1.truelist, $1.falselist);
								$$.breaklist = NULL;
								$$.continuelist = NULL;
								$$.gotolist = NULL;
								$$.caselist = NULL;
							}

	| selection_statement	{	printf("statement: selection_statement\n");
								$$ = $1;
								$$.caselist = NULL;
							}

	| iteration_statement	{	printf("statement: iteration_statement\n");
								$$ = $1;
								$$.caselist = NULL;
							}

	| jump_statement		{	printf("statement: jump_statement\n");
								$$ = $1;
								$$.caselist = NULL;
							}

	;

labeled_statement
	: IDENTIFIER ':' N statement					{	printf("labeled_statement: IDENTIFIER ':' statement\n");
														putlab(new string($1), $3);
														$$.nextlist = NULL;
														$$.breaklist = NULL;
														$$.continuelist = NULL;
														$$.gotolist = NULL;
														$$.caselist = NULL;
												}

	| CASE constant_expression ':' N statement	{	printf("labeled_statement: CASE constant_expression ':' statement\n");
													$$.breaklist = $5.breaklist;
													$$.continuelist = $5.continuelist;
													$$.gotolist = $5.gotolist;
													if(!isconstant($2.typ)){
														yyerror("Error: CASE expression must be constant\n");
													}
													if(!isintegral($2.typ)){
														yyerror("Error: CASE expression must be integral constant\n");
													}
													$$.caselist = makecaselist($2.val, $2.typ, $4);
												}

	| DEFAULT ':' N statement					{	printf("labeled_statement: DEFAULT ':' statement\n");
													$$.breaklist = $4.breaklist;
													$$.continuelist = $4.continuelist;
													$$.gotolist = $4.gotolist;
													$$.caselist = makecaselist($3);
												}

	;

compound_statement
	: '{' '}'									{	printf("compound_statement: '{' '}'\n");
													$$.breaklist = NULL;
													$$.continuelist = NULL;
													$$.gotolist = NULL;
													$$.nextlist = NULL;
												}

	| '{' statement_list '}'					{	printf("compound_statement: '{' statement_list '}'\n");
													$$ = $2;
												}

	| '{' declaration_list '}'					{	printf("compound_statement: '{' declaration_list '}'\n");
													$$.breaklist = NULL;
													$$.continuelist = NULL;
													$$.gotolist = NULL;
													$$.nextlist = NULL;
												}

	| '{' declaration_list statement_list '}'	{	printf("compound_statement: '{' declaration_list statement_list '}'\n");
													$$ = $3;
												}

	;

declaration_list
	: declaration					{	printf("declaration_list: declaration\n");
										;
									}
									
	| declaration_list declaration	{	printf("declaration_list: declaration_list declaration\n");
										;
									}

	;

statement_list
	: statement						{	printf("statement_list: statement\n");
										$$ = $1;
									}

	| statement_list 
	  N statement					{	printf("statement_list: statement_list statement\n");
	  									backpatch($1.nextlist, $2);
										$$ = $1;
										$$.nextlist = $3.nextlist;
										$$.breaklist = merge($1.breaklist, $3.breaklist);
										$$.continuelist = merge($1.continuelist, $3.continuelist);
										$$.gotolist = merge($1.gotolist, $3.gotolist);
										$$.caselist = merge($1.caselist, $3.caselist);
									}

	;

expression_statement
	: ';'				{	printf("expression_statement: ';'\n");
							$$.truelist = nullptr;
							$$.falselist = nullptr;
						}

	| expression ';'	{	printf("expression_statement: expression ';'\n");
							$$ = $1;
						}

	;

logic_expression 
	: expression				{
									tological(&($1));
									$$ = $1;
								}

	;

selection_statement
	: IF '(' logic_expression ')'  N 
	  statement %prec NOELSE									{	printf("selection_statement: IF '(' expression ')' statement NOELSE\n");
																	backpatch($3.truelist, $5);
																	$$.nextlist = merge($3.falselist, $6.nextlist);
																	$$.breaklist = $6.breaklist;
																	$$.continuelist = $6.continuelist;
																	$$.gotolist = $6.gotolist;
																}

	| IF '(' logic_expression ')' N
	 statement ELSE M N statement								{	printf("selection_statement: IF '(' expression ')' statement ELSE statement\n");
																	backpatch($3.truelist, $5);
																	backpatch($3.falselist, $9);
																	$$.nextlist = merge($6.nextlist, $8.nextlist, $10.nextlist);
																	$$.breaklist = merge($6.breaklist, $10.breaklist);
																	$$.continuelist = merge($6.continuelist, $10.continuelist);
																	$$.gotolist = merge($6.gotolist, $10.gotolist);
																}

	| SWITCH '(' expression ')' 
	  M statement												{	printf("selection_statement: SWITCH '(' expression ')' statement\n");
																	if(!isintegral($3.typ)){
																		yyerror("Error: switch expression must be integreal\n");
																	}
																	$6.breaklist = merge($6.breaklist, makelist(nextinstr));
																	gencode(GOTO_IR);
																	backpatch($5.nextlist, nextinstr);
																	std::list<CASE_DATA*>::iterator it;
																	if($6.caselist != NULL){
																		for(it = $6.caselist->begin(); it != $6.caselist->end(); it++){
																			int addr = (*it)->addr;
																			int typ = (*it)->typ;
																			if(typ == VOIDVAL){
																				gencode(GOTO_IR, addr);
																			}
																			else { 
																				std::string *name = newtemp();
																				symrec *s = putsym(name, INTVAL | CONST_SPEC);
																				symrec *s1 = $3.var;
																				*(int*)((char*)datablock + s1->offset) = (*it)->val.intval;
																				if(isconstant($3.typ)){
																					name = newtemp();
																					s1 = putsym(name, INTVAL | CONST_SPEC);
																					*(int*)((char*)datablock + s->offset) = $3.val.intval;
																				}
																				gencode(IF_EQ_IR, s1, s, addr);
																			}
																		}
																	}
																	backpatch($6.breaklist, nextinstr);
																	$$.breaklist = NULL;
																	$$.continuelist = $6.continuelist;
																	$$.gotolist = $6.gotolist;
																	$$.nextlist = NULL;
															}

	;

logic_expression_statement 
	: expression_statement									{
																$$ = $1;
																// Verificar si una expresion es comparacion u operacion logica
																if($1.truelist == nullptr || $1.falselist == nullptr){
																	std::string *name = newtemp();
																	symrec *s0;
																	s0 = putsym(name, INTVAL | CONST_SPEC);
																	*(int*)(datablock + s0->offset) = 0;
																	$$.truelist = makelist(nextinstr);
																	gencode(IF_NE_IR, $1.var, s0, nullptr);
																	$$.falselist = makelist(nextinstr);
																	gencode(GOTO_IR);
																}
															}

	;

iteration_statement
	: WHILE N '(' logic_expression ')' N statement									{	printf("iteration_statement: WHILE '(' expression ')' statement\n");
																						backpatch($7.nextlist, $2);
																						backpatch($7.continuelist , $2);
																						backpatch($4.truelist, $6);
																						$$.nextlist = $4.falselist;
																						gencode(GOTO_IR, $2);
																						backpatch($7.breaklist, nextinstr);
																						$$.breaklist = NULL;
																						$$.continuelist = NULL;
																						$$.gotolist = $7.gotolist;
																						
																					}

	| DO N statement WHILE N '(' 
	  logic_expression ')' ';'														{	printf("iteration_statement: DO statement WHILE '(' expression ')' ';'\n");
																						backpatch($7.truelist, $2);
																						backpatch($3.nextlist, $5);
																						backpatch($3.continuelist, $5);
																						backpatch($3.breaklist, nextinstr);
																						$$.breaklist = NULL;
																						$$.continuelist = NULL;
																						$$.nextlist = $7.falselist;
																						$$.gotolist = $3.gotolist;
																					}

	| FOR '(' expression_statement N 
	  logic_expression_statement N  ')' statement									{	printf("iteration_statement: FOR '(' expression_statement expression_statement ')' statement\n");
																						backpatch($5.truelist, $6);
																						backpatch($8.nextlist, $4);
																						backpatch($8.continuelist, $4);
																						$$.nextlist = $5.falselist;
																						gencode(GOTO_IR, $4);
																						backpatch($8.breaklist, nextinstr);
																						$$.breaklist = NULL;
																						$$.continuelist = NULL;
																						$$.gotolist = $8.gotolist;
																					}

	| FOR '(' expression_statement N
	  expression_statement N expression 
	  ')' M N statement																{	printf("iteration_statement: FOR '(' expression_statement expression_statement expression ')' statement\n");
																						backpatch($5.truelist, $10);
																						backpatch($11.nextlist, $6);
																						backpatch($11.continuelist, $6);
																						backpatch($9.nextlist, $4);
																						$$.nextlist = $5.falselist;
																						gencode(GOTO_IR, $6);
																						backpatch($11.breaklist, nextinstr);
																						$$.breaklist = NULL;
																						$$.continuelist = NULL;
																						$$.gotolist = $11.gotolist;
																					}

	;

jump_statement
	: GOTO IDENTIFIER ';'		{	printf("jump_statement: GOTO IDENTIFIER ';'\n");
									$$.continuelist = NULL;
									$$.breaklist = NULL;
									$$.nextlist = NULL;
									$$.caselist = NULL;
									$$.gotolist = makelist(new string($2), nextinstr);
									gencode(GOTO_IR);
								}

	| CONTINUE ';'				{	printf("jump_statement: CONTINUE ';'\n");
									$$.breaklist = NULL;
									$$.nextlist = NULL;
									$$.caselist = NULL;
									$$.gotolist = NULL;
									$$.continuelist = makelist(nextinstr);
									gencode(GOTO_IR);
								}

	| BREAK ';'					{	printf("jump_statement: BREAK ';'\n");
									$$.nextlist = NULL;
									$$.continuelist = NULL;
									$$.caselist = NULL;
									$$.gotolist = NULL;
									$$.breaklist = makelist(nextinstr);
									gencode(GOTO_IR);
								}

	| RETURN ';'				{	printf("jump_statement: RETURN ';'\n");
									$$.breaklist = NULL;
									$$.nextlist = NULL;
									$$.continuelist = NULL;
									$$.caselist = NULL;
									$$.gotolist = NULL;
									gencode(RET_IR);
								}

	| RETURN expression ';'		{	printf("jump_statement: RETURN expression ';'\n");
									// Verificar si hay saltos truelist/falselist en expresion
									// si los hay, es porque contiene operaciones logicas
									// entonces calcular su valor logico 0 o 1
									if($2.truelist || $2.falselist){
											std::string *name = newtemp();
											symrec *s1, *s0;
											s0 = putsym(name, INTVAL | CONST_SPEC);
											setval(s0, 0);
											name = newtemp();
											s1 = putsym(name, INTVAL | CONST_SPEC);
											setval(s1, 1);
											name = newtemp();
											$2.var = putsym(name, INTVAL | VAR_SPEC);
											$2.typ = INTVAL | VAR_SPEC;
											$2.name = name;
											backpatch($2.truelist, nextinstr);
											gencode(STORE_IR, s1, nullptr, $2.var);
											gencode(GOTO_IR, nullptr, nullptr, nextinstr + 2);
											backpatch($2.falselist, nextinstr);
											gencode(STORE_IR, s0, nullptr, $2.var);
									}

									$$.breaklist = NULL;
									$$.nextlist = NULL;
									$$.continuelist = NULL;
									$$.caselist = NULL;
									$$.gotolist = NULL;
									gencode(RET_IR, $2.var, nullptr, nullptr);
									
								}
	;

translation_unit
	: external_declaration						{	printf("translation_unit: external_declaration\n");
													;
												}

	| translation_unit external_declaration		{	printf("translation_unit: translation_unit external_declaration\n");
													;
												}
	;

external_declaration
	: function_definition	{	printf("external_declaration: function_definition\n");
								;
							}
							
	| declaration			{	printf("external_declaration: declaration\n");
								;
							}

	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement		{	printf("function_definition: declaration_specifiers declarator declaration_list compound_statement\n");
	
																				}

	| declaration_specifiers declarator 										{
																					int typ = get_type($1) | $2->typ; // Agregar bits extras para por ejemplo punteros
																					curr_func = getlocalsym($2->name);
																					if(curr_func == nullptr){
																						curr_func = putsym($2->name, typ | FUNC_SPEC);
																					}	
																					gencode(PROC_IR, curr_func);
																					localsyms = new symboltable();
																					enter_scope();
																					installarg($2->arglist);
																					lab_table.clear(); // Limpiar tabla de etiquetas
																					setargs();
																				}

	  compound_statement														{	printf("function_definition: declaration_specifiers declarator compound_statement\n");
																					printlocalvars();
																					exit_scope();
																					curr_func->func_desc.sym_table = localsyms;
																					gencode(ENDPROC_IR, curr_func);
																				}

	| declarator declaration_list compound_statement							{	printf("function_definition: declarator declaration_list compound_statement\n");
																					;
																				}

	| declarator 																{	// Acciones de mitad de regla
																					int typ = INTVAL | $1->typ; // Agregar bits extras para por ejemplo punteros
																					curr_func = getlocalsym($1->name);
																					if(curr_func == nullptr){
																						curr_func = putsym($1->name, typ | FUNC_SPEC);
																					}		
																					gencode(PROC_IR, curr_func);																			
																					localsyms = new symboltable();
																					enter_scope(); // Iniciar un nuevo ambito local de variables
																					installarg($1->arglist);
																					lab_table.clear(); // Limpiar tabla de etiquetas
																					setargs(); // Agregar atributo ARG_SPEC a variables

																				}	 
		
	  compound_statement														{	printf("function_definition: declarator compound_statement\n");
																					printlocalvars();
																					exit_scope();
																					curr_func->func_desc.sym_table = localsyms;
																					gencode(ENDPROC_IR, curr_func);
																				}

	;

%%

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