/* ------------------------------------------------ */
/* Analizador Lexico "Lexer" */
/* Andres Torres 16/04/2024 */
/* Compiladores */
/* ------------------------------------------------ */

/* Seccion de Definiciones : */

/* Codigo en Lex */
/* Expansiones de patrones/reglas : */

D			[0-9]        
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%{

/*Codigo en C entre:*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <string.h> // Pare la funcion strdup()
#include <stdlib.h>
#include <list>
#include <string>
#include <ctype.h>
#include "typedefs.h"

#include <stdlib.h>
#include "y.tab.h" // Cabecera con la enumeracion de tokens

// enum {
    
//     AUTO = 257,
//     BREAK,
//     CASE,
//     CHAR,
//     CONST,
//     CONTINUE,
//     DEFAULT,
//     DO,
//     DOUBLE,
//     ELSE,
//     ENUM,
//     EXTERN,
//     FLOAT,
//     FOR,
//     GOTO,
//     IF,
//     INT,
//     LONG,
//     REGISTER,
//     RETURN,
//     SHORT,
//     SIGNED,
//     SIZEOF,
//     STATIC,
//     STRUCT,
//     SWITCH,
//     TYPEDEF,
//     UNION,
//     UNSIGNED,
//     VOID,
//     VOLATILE,
//     WHILE,
//     IDENTIFIER,
//     CONSTANT,
//     STRING_LITERAL,
//     ELLIPSIS,
//     RIGHT_ASSIGN,
//     LEFT_ASSIGN,
//     ADD_ASSIGN,
//     SUB_ASSIGN,
//     MUL_ASSIGN,
//     DIV_ASSIGN,
//     MOD_ASSIGN,
//     AND_ASSIGN,
//     XOR_ASSIGN,
//     OR_ASSIGN,
//     RIGHT_OP,
//     LEFT_OP,
//     INC_OP,
//     DEC_OP,
//     PTR_OP,
//     AND_OP,
//     OR_OP,
//     LE_OP,
//     GE_OP,
//     EQ_OP,
//     NE_OP
// };

// union {

//     struct
//     {
//         int ival;
//         double dval;
//         int valtype;
//     };
//     char* name;
//     char* sval;
//     char cval;

// } yylval;



// Prototipos iniciales para evitar "implicit declaration" (scope)
extern FILE* yyin;
void count();
int check_type();
void comment();
int yylex();
//void printstr(char* str);
void print_token(int c);

// enum{ // Enumeracion para las constantes
// 	VOIDVAL = 0,
// 	CHARVAL,
// 	INTVAL,
// 	DOUBLEVAL
// };

char* buffer; // Requerira memoria dinamica
int bufsize;
int column = 0;
int lineno = 0;

%}

/* Para no usar funcion yywrap se usa la directiva: */
/* %option noyywrapp */
/* Nuevos estados exclusivos: */
%x INCHAR 
%x INSTR


/* Seccion de Reglas : */
/* Codigo en Lex */

%%

"/*"			{ comment(); } /* Ignorar comentarios */
^#.*			{ ; } /* Ignorar directivas de preprocesador */
"auto"			{ count(); return(AUTO); } /* Palabras reservadas del lenguaje */
"break"			{ count(); return(BREAK); }
"case"			{ count(); return(CASE); }
"char"			{ count(); return(CHAR); }
"const"			{ count(); return(CONST); }
"continue"		{ count(); return(CONTINUE); }
"default"		{ count(); return(DEFAULT); }
"do"			{ count(); return(DO); }
"double"		{ count(); return(DOUBLE); }
"else"			{ count(); return(ELSE); }
"enum"			{ count(); return(ENUM); }
"extern"		{ count(); return(EXTERN); }
"float"			{ count(); return(FLOAT); }
"for"			{ count(); return(FOR); }
"goto"			{ count(); return(GOTO); }
"if"			{ count(); return(IF); }
"int"			{ count(); return(INT); }
"long"			{ count(); return(LONG); }
"register"		{ count(); return(REGISTER); }
"return"		{ count(); return(RETURN); }
"short"			{ count(); return(SHORT); }
"signed"		{ count(); return(SIGNED); }
"sizeof"		{ count(); return(SIZEOF); }
"static"		{ count(); return(STATIC); }
"struct"		{ count(); return(STRUCT); }
"switch"		{ count(); return(SWITCH); }
"typedef"		{ count(); return(TYPEDEF); }
"union"			{ count(); return(UNION); }
"unsigned"		{ count(); return(UNSIGNED); }
"void"			{ count(); return(VOID); }
"volatile"		{ count(); return(VOLATILE); }
"while"			{ count(); return(WHILE); }

{L}({L}|{D})*		{ 	
						count();  /* Regla para encontrar variables con su tipo alterna con /[a-zA-Z]([a-zA-Z]|[0-9]) */
					
						yylval.name = strdup(yytext); /* yytext contiene la cadena que coincidio con una regla determinada */
						return IDENTIFIER;
					
					} 

0[xX]{H}+{IS}?		{ 	
						count(); /* Constantes Hexadecimales, regex con union de clases */
						
						yylval.ival = strtol(yytext, NULL, 16);
						yylval.valtype = INTVAL;
						return(CONSTANT); 

					}

0{D}+{IS}?			{ 	
						count(); /* Constantes Octales */

						yylval.ival = strtol(yytext, NULL, 8);
						yylval.valtype = INTVAL;
						return(CONSTANT); 
					
					}

{D}+{IS}?			{ 	
						count(); /* Constantes Decimales */

						yylval.ival = strtol(yytext, NULL, 10);
						yylval.valtype = INTVAL;
						return(CONSTANT); 

					}


L?'					{ 	
						count(); /* Inicio constantes char, son todos una misma por ello cambia el estado de la maquina y solo se buscan en estado INCHAR */

						BEGIN INCHAR; /* Macro para cambios de estados en maquina de estados finita */
						buffer = (char*)malloc(1); // 1 byte
						buffer[0] = '\0'; /* Se declara un buffer para guardar los caracteres usando \0 como referencia del final de la cadena */
						bufsize = 0;

					}

<INCHAR>\\.  		{  	
						count(); /* Caracteres especiales que inicien con \ como los escape sequences */

						if(bufsize > 0){

							printf("ERROR: line %d column %d multibyte char constant!\n", lineno + 1, column ); // Codigo de error si no hay caracter
							exit(2); /* lineno y column contienen la linea y columna donde se encuentra una regex */

						}
							switch(yytext[1]){
								case 'a':
									buffer[0] = '\a';
									break;
								case 'b':
									buffer[0] = '\b';
									break;
								case 'f':
									buffer[0] = '\f';
									break;
								case 'n':
									buffer[0] = '\n';
									break;
								case 't':
									buffer[0] = '\t';
									break;
								case 'r':
									buffer[0] = '\r';
									break;
								case 'v':
									buffer[0] = '\v';
									break;
								default:
									buffer[0] = yytext[1];
									break;
								bufsize++;
								
							}

					}

<INCHAR>(\\0[0-7]+)			{   
								count(); /* Caracteres escritos en octal */

								int val; /* Para guardar el valor de la conversion */
								if(bufsize > 0){

									printf("ERROR: line %d column %d multibyte char constant!\n", lineno + 1, column );
									exit(2);

								}

								val = strtol(yytext + 1, NULL, 8);

								if(val > 255){ /* En ASCII no puede excederse 255 carateres */

									printf("ERROR: line %d column %d multibyte char constant!\n", lineno + 1, column );
									exit(2);

								}

								buffer[0] = val;
								bufsize++;

							}

<INCHAR>(\\x{H}+)			{	
								count(); /* Caracteres escritos en Hexadecimal */

								int val;
								if(bufsize > 0){

									printf("ERROR: line %d column %d multibyte char constant!\n", lineno + 1, column );
									exit(2);

								}

								val = strtol(yytext + 2, NULL, 16);

								if(val > 255){ /* En ASCII no puede excederse 255 carateres */

									printf("ERROR: line %d column %d multibyte char constant!\n", lineno + 1, column );
									exit(2);

								}

								buffer[0] = val;
								bufsize++;

							}


<INCHAR>[^\\']+		{   
						count(); /* Caracteres normales, que no empiecen con / ni con ' como cadenas de caracteres */

						if(bufsize > 0){

							printf("ERROR: line %d column %d multibyte char constant!\n", lineno + 1, column );
							exit(2);

						}
						
						buffer[0] = yytext[0];
						bufsize++;

					}

<INCHAR>'			{   
						count(); /* Finalizacion de constantes char */

						BEGIN INITIAL;
						yylval.cval = buffer[0];
						yylval.valtype = CHARVAL;
						free(buffer);
						return(CONSTANT); 

					}

{D}+{E}{FS}?		{ 	
						count(); /* Constantes float, con exponente e */

						yylval.dval = atof(yytext); /* Convertir a double */
						yylval.valtype = DOUBLEVAL;
						return(CONSTANT); 
						
					}

{D}*"."{D}+({E})?{FS}?	{ 	
							count(); /* Consantes float */
							
							yylval.dval = atof(yytext); // Convertir a double
							yylval.valtype = DOUBLEVAL;
							return(CONSTANT); 

						}

{D}+"."{D}*({E})?{FS}?	{ 	
							count(); /* Constantes float */

							yylval.dval = atof(yytext); /* Convertir a double */
							yylval.valtype = DOUBLEVAL;
							return(CONSTANT); 

						}

L?\"		{ 	
				count(); /* Inicio de cadenas */

				BEGIN INSTR;
				buffer = (char*)malloc(1); // 1 byte
				buffer[0] = '\0'; // Se declara un buffer para guardar la cadena y sus caracteres usando \0 como referencia del final de la cadena
				bufsize = 0;
						
			}

<INSTR>[^\\"]		{   
						count(); /* Caracteres normales, que no empiecen con / ni con ' como cadenas de caracteres */
						
						buffer = (char*)realloc(buffer, bufsize + 2);
						buffer[bufsize] = yytext[0];
						bufsize++;

					}


<INSTR>(\\0[0-7]+)			{   
								count(); /* Caracteres escritos en octal */

								buffer = (char*)realloc(buffer, bufsize + 2);
								int val; /* Para guardar el valor de la conversion */
							
								val = strtol(yytext + 1, NULL, 8);

								if(val > 255){ /* En ASCII no puede excederse 255 carateres */

									printf("ERROR: line %d column %d multibyte char constant!\n", lineno + 1, column );
									exit(2);

								}

								buffer[bufsize] = val;
								bufsize++;

							}

<INSTR>(\\x{H}+)			{	
								count(); /* Caracteres escritos en Hexadecimal */

								buffer = (char*)realloc(buffer, bufsize + 2);
								int val;

								val = strtol(yytext + 2, NULL, 16);

								if(val > 255){ /* En ASCII no puede excederse 255 carateres */

									printf("ERROR: line %d column %d multibyte char constant!\n", lineno + 1, column );
									exit(2);

								}

								buffer[bufsize] = val;
								bufsize++;

							}

<INSTR>\\.  		{  		
							count(); /* Caracteres especiales que inicien con \ como los escape codes */

							buffer = (char*)realloc(buffer, bufsize + 2); /* Reasignacion de memoria dinamica */
							switch(yytext[1]){

								case 'a':
									buffer[bufsize] = '\a';
									break;
								case 'b':
									buffer[bufsize] = '\b';
									break;
								case 'f':
									buffer[bufsize] = '\f';
									break;
								case 'n':
									buffer[bufsize] = '\n';
									break;
								case 't':
									buffer[bufsize] = '\t';
									break;
								case 'r':
									buffer[bufsize] = '\r';
									break;
								case 'v':
									buffer[bufsize] = '\v';
									break;
								default:
									buffer[bufsize] = yytext[1];
									break;
								bufsize++;
								
							}

					}

<INSTR>\"			{ 	
						count();

						BEGIN INITIAL;
						yylval.sval = strdup(buffer);
						free(buffer);
						return(STRING_LITERAL);

					}

"..."			{ count(); return(ELLIPSIS); } /* Operadores */
">>="			{ count(); return(RIGHT_ASSIGN); }
"<<="			{ count(); return(LEFT_ASSIGN); }
"+="			{ count(); return(ADD_ASSIGN); }
"-="			{ count(); return(SUB_ASSIGN); }
"*="			{ count(); return(MUL_ASSIGN); }
"/="			{ count(); return(DIV_ASSIGN); }
"%="			{ count(); return(MOD_ASSIGN); }
"&="			{ count(); return(AND_ASSIGN); }
"^="			{ count(); return(XOR_ASSIGN); }
"|="			{ count(); return(OR_ASSIGN); }
">>"			{ count(); return(RIGHT_OP); }
"<<"			{ count(); return(LEFT_OP); }
"++"			{ count(); return(INC_OP); }
"--"			{ count(); return(DEC_OP); }
"->"			{ count(); return(PTR_OP); }
"&&"			{ count(); return(AND_OP); }
"||"			{ count(); return(OR_OP); }
"<="			{ count(); return(LE_OP); }
">="			{ count(); return(GE_OP); }
"=="			{ count(); return(EQ_OP); }
"!="			{ count(); return(NE_OP); }
";"			{ count(); return(';'); }
("{"|"<%")		{ count(); return('{'); }
("}"|"%>")		{ count(); return('}'); }
","			{ count(); return(','); }
":"			{ count(); return(':'); }
"="			{ count(); return('='); }
"("			{ count(); return('('); }
")"			{ count(); return(')'); }
("["|"<:")		{ count(); return('['); }
("]"|":>")		{ count(); return(']'); }
"."			{ count(); return('.'); }
"&"			{ count(); return('&'); }
"!"			{ count(); return('!'); }
"~"			{ count(); return('~'); }
"-"			{ count(); return('-'); }
"+"			{ count(); return('+'); }
"*"			{ count(); return('*'); }
"/"			{ count(); return('/'); }
"%"			{ count(); return('%'); }
"<"			{ count(); return('<'); }
">"			{ count(); return('>'); }
"^"			{ count(); return('^'); }
"|"			{ count(); return('|'); }
"?"			{ count(); return('?'); }

[ \t\v\n\f]		{ count(); }

.			{ ; } /* Regla default para ignorar caracteres no especificados */

%%

// Seccion de Codigo usuario en C 

int yywrap() { // Funcion para indicar si faltan archivos por procesar

	return(1); // Siempre retorna 1 para cuando se compila un solo archivo, permitir retorno 0 para mas archivos
}


void comment() {
	char c, c1;

loop:
	while ((c = yyinput()) != '*' && c != 0) 
		;

	if ((c1 = yyinput()) != '/' && c != 0) // En c es input() en c++ es yyinput()
	{
		unput(c1);
		goto loop;
	}

	if (c != 0)
		;
}

void count() {

	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n'){

			column = 0;
			lineno++;

		}
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;

}


const char* tokens[] = {	// Este arreglo debe ser identico a la enumeracion de y.tab.h // C++ es mas estricto con la seguridad en los punteros string por eso se agrega const
	"AUTO",
	"BREAK",
	"CASE",
	"CHAR",
	"CONST",
	"CONTINUE",
	"DEFAULT",
	"DO",
	"DOUBLE",
	"ELSE",
	"ENUM",
	"EXTERN",
	"FLOAT",
	"FOR",
	"GOTO",
	"IF",
	"INT",
	"LONG",
	"REGISTER",
	"RETURN",
	"SHORT",
	"SIGNED",
	"SIZEOF",
	"STATIC",
	"STRUCT",
	"SWITCH",
	"TYPEDEF",
	"UNION",
	"UNSIGNED",
	"VOID",
	"VOLATILE",
	"WHILE",
    "IDENTIFIER",
	"CONSTANT",
	"STRING_LITERAL",
	"ELLIPSIS",
	"RIGHT_ASSIGN",
	"LEFT_ASSIGN",
	"ADD_ASSIGN",
	"SUB_ASSIGN",
	"MUL_ASSIGN",
	"DIV_ASSIGN",
	"MOD_ASSIGN",
	"AND_ASSIGN",
	"XOR_ASSIGN",
	"OR_ASSIGN",
	"RIGHT_OP",
	"LEFT_OP",
	"INC_OP",
	"DEC_OP",
	"PTR_OP",
	"AND_OP",
	"OR_OP",
	"LE_OP",
	"GE_OP",
	"EQ_OP",
	"NE_OP"
};

// void printstr(char* str){

// 	for(int i = 0; i < strlen(str); i++){

// 		if(isprint(str[i]))
// 			printf("%c", str[i]);
// 		else
// 			printf("\\%o", str[i]);

// 	}

// }

void print_token(int c) {
    if (c < 256)
        printf("[%c]", c);
    else {
        switch (c) {
            case CONSTANT:
                switch (yylval.valtype) {
                    case INTVAL:
                        printf("[%s, %d]", tokens[c - AUTO], yylval.ival);
                        break;
                    case DOUBLEVAL:
                        printf("[%s, %g]", tokens[c - AUTO], yylval.dval);
                        break;
                    case CHARVAL:
                        if (isprint(yylval.cval))
                            printf("[%s, '%c']", tokens[c - AUTO], yylval.cval);
                        else
                            printf("[%s, '\\x%02x']", tokens[c - AUTO], (unsigned char)yylval.cval);
                        break;
                }
                break;
            case IDENTIFIER:
                printf("[%s, \"%s\"]", tokens[c - AUTO], yylval.name);
                break;
            case STRING_LITERAL: //switch mejorado para mostrar codigos de escape
                printf("[%s, \"", tokens[c - AUTO]);
                for (int i = 0; yylval.sval[i] != '\0'; i++) {
                    switch (yylval.sval[i]) {
                        case '\n':
                            printf("\\n");
                            break;
                        case '\t':
                            printf("\\t");
                            break;
                        case '\r':
                            printf("\\r");
                            break;
                        case '\f':
                            printf("\\f");
                            break;
                        case '\b':
                            printf("\\b");
                            break;
                        case '\"':
                            printf("\\\"");
                            break;
                        case '\\':
                            printf("\\\\");
                            break;
                        default:
                            if (isprint(yylval.sval[i]))
                                printf("%c", yylval.sval[i]);
                            else
                                printf("\\%03o", (unsigned char)yylval.sval[i]);
                            break;
                    }
                }
                printf("\"]");
                break;
            default:
                printf("[%s]", tokens[c - AUTO]);
                break;
        }
    }
}

// Funcion Main ya no necesaria para el Lexer

/* int main(int argc, char* argv[]) {

    printf("Lexic Analyzer LEXER ANSI C v.01 by Andres Torres\n");
    int c;
    if (argc < 2) { // Es decir que espera al menos dos prompts [0] y [1], si es menor a eso sale
        printf("Usage: %s \"file\"\n", argv[0]);
		printf("Lexic Analyzer requires two arguments. Procces exit with failure (1)\n" );
        exit(1);
    } else {
		
        yyin = fopen(argv[1], "rt"); // El archivo a abrir en lectura de texto rt esta en argv[1]
        if (yyin == NULL) {
            printf("Error: Couldn't open file %s\n", argv[1]);
            exit(1);
        }

        char resp;
        printf("Display Preference: V/H: ");
        resp = getchar();
        getchar(); // Consumir el carácter de nueva línea en el búfer

        if (resp == 'V' || resp == 'v') {
            printf("Vertical Display:\n");
            while ((c = yylex()) != 0) { // yylex es el analizador y devuelve el token encontrado en forma numerica
                printf("\n");
                print_token(c); // Imprimir el token encontrado por yylex hasta que devuelva 0 y sea fin de analisis lexico
            }
        } else if (resp == 'H' || resp == 'h') {
            printf("Horizontal Display:\n");
            while ((c = yylex()) != 0) {
                print_token(c);
            }
            printf("\n");
        } else {
            printf("Invalid preference. Please enter 'H' or 'V'.\n");
        }

		printf("\n\n");
		printf("All tokens analized. Procces exits with succes (0)\n");
        fclose(yyin);
    }

    return 0;
} */