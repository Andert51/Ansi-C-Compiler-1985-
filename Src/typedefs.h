//COntiene constantes y cabeceras necesarias
#include <iostream>
#include <list>

using namespace std;

//Estructura que representa la tabla de simbolos para variables/simbolos 
struct symrec
{	
    std::string name; /* Nombre de la variable */
    int size; /* Tamaño de símbolo en bytes */ //Direccion de RAM donde se asigno
    int init; /* Si es inicializada */ //Valor de inicializacion, si se inicializo
    int typ; /* Tipo de datos del símbolo */ //Tipo de la variable
    int offset; /* offset dentro del bloque de datos */ //Offset dentro del bloque de datos, de RAM, bloque donde las apalicaciones almacenan sus variables, tambien puede conocerse como un stack
    struct { //Estructura de tabla de simbolos de variables locales de una funcion
        int func_type; //tipo de la funcion
        std::list<struct symrec *> *sym_table; //variables de la funcion  
    } func_desc; /* Para información sobre la función */
    std::list<int > *dimlist; /* Almacenar las dimensiones de un arreglo */ //Si es un arreglo
};

typedef struct symrec symrec;

//Constantes para los tipos, con sus valores
enum VARTYPES
	{
		VOIDVAL = 1,
		CHARVAL,
		UCHARVAL,
		SCHARVAL,
		SHORTVAL,
		USHORTVAL,
		INTVAL,
		UINTVAL,
		LONGVAL,
		ULONGVAL,
		FVAL,
		DOUBLEVAL,
		LDOUBLEVAL,
		STRVAL,
		STRUCVAL,
		UNIONVAL,
		ENUMVAL,
		TYPENM
	};

//para almacenar un solo valor de constantes porque es una union
typedef union VALUE {
		char charval;
		int intval;
		float floatval;
		double doubleval;
	} VALUE;

//guardar informacion de algunas variables que no estan en la tabla de simbolos, para al completarse se puedan ir a la tabla de simbolos principal
typedef struct VAR_DATA {
	std::string *name;
	VALUE val;
	int init;
	int typ;
	symrec *var; // para indicar variable (temporal o de programa, función, constante) de tabla de símbolos
	symrec *var2; // para indicar subíndice de arreglo
	int plevel; // para indicar el nivel del puntero
	std::list<int> *truelist;
	std::list<int> *falselist;
	std::list<VAR_DATA *> *arglist;
	std::list<int > *dimlist;
} VAR_DATA;

//guardar infromacion de los case de un switch
typedef struct CASE_DATA {
	VALUE val;
	int typ;
	int addr;
} CASE_DATA;

//para indicar los saltos en el programa
typedef struct GOTO_DATA {
	std::string *name; //etiqueta
	int addr; //direccion del codigo
} GOTO_DATA;
