//Contiene las funciones para el manejo e implementacio de tablas de simbolos usando su cabecera con declaraciones necesarias typedefs.h
//Contiene codigo en C++ con estructuras de datos necesarias

#include "typedefs.h"

typedef std::list<symrec*> symboltable;

symboltable *sym_table = NULL;

int currscope = 0; /* Nivel del ámbito inicial (global) */
int data_offset = 0; /* offset inicial en bloque de datos */
unsigned char datablock[64*1024]; /* Bloque de datos de 64 KB */

int data_location(int sz) /* Reserva espacio para dato */
{
	data_offset += sz;
	return data_offset-sz;
}

/* Tabla de variables locales (para bloque entre {})  */
symboltable *localsyms;
/* Tabla de variables locales de funcion siendo analizada */
symrec *curr_func = NULL;

/* Implementar stack de ambitos de variables como lista (tiene metodos push y pop) */
std::list<std::list<symrec *> *> scopes;

/* 0 ambito de variables globales
   1 indica ambito de variables locales de funcion
   2 indica ambito de variables locales de bloque 
   3 indica ambito de variables locales de bloque anidado
   ...
   ** ambito nivel 0 **
   int f;
   float g;
   ...
   int main()
   { ** ambito nivel 1 **
     int a, b;
	 ...
     { ** ambito nivel 2 **
	   int x;
	   char c;
	   ...
	   { ** ambito nivel 3 **
	      int z;
		  int x;
		  ...
	   }
       ...
	 }
     ...
     { ** ambito nivel 2 **
	   float s;
	   int x;
       ...
       { ** ambito nivel 3 **
	      int r;
		  int u;
		  ...
	   }
       ...
     }
     ...
   }
*/

//Constantes para tipos, especificadores de tipo
enum TYPE_SPECIFIERS 
{
	VOID_SPEC	  = 0x0000001,
	CHAR_SPEC	  = 0x0000002,
	SHORT_SPEC	  = 0x0000004,
	INT_SPEC	  = 0x0000008,
	LONG_SPEC	  = 0x0000010,
	FLOAT_SPEC	  = 0x0000020,
	DOUBLE_SPEC	  = 0x0000040,
	STRING_SPEC	  = 0x0000080,
	STRUCT_SPEC	  = 0x0000100,
	UNION_SPEC	  = 0x0000200,
	ENUM_SPEC	  = 0x0000400,
	TYPENAME_SPEC = 0x0000800,
	VAR_SPEC	  = 0x0001000,
	ARRAY_SPEC	  = 0x0002000,
	FUNC_SPEC	  = 0x0004000,
	SIGNED_SPEC	  = 0x0008000,
	UNSIGNED_SPEC = 0x0010000,
	CONST_SPEC	  = 0x0020000,
	VOLATILE_SPEC = 0x0040000,
	STATIC_SPEC	  = 0x0080000,
	TYPEDEF_SPEC  = 0x0100000,
	EXTERN_SPEC	  = 0x0200000,
	AUTO_SPEC	  = 0x0400000,
	REGISTER_SPEC = 0x0800000,
	POINTER_SPEC  = 0x1000000,
	ARG_SPEC	  = 0x2000000,
	ARGELLIP_SPEC = 0x4000000,
};

int ntemp = 0; /* Cuenta el número de variables temporales creadas */

/* Crea el nombre de una nueva variable temporal */
std::string *newtemp(void)
{
	std::string *name = new std::string("@" + std::to_string(ntemp++));
	return name;
}

/* Determinar tamaño en bytes de un tipo de datos */
int getsizeof(int typ)
{
    if (typ & POINTER_SPEC)
		return sizeof(void *);                    
	typ &= 0x1F;
	switch(typ)
	{
		case SHORTVAL:
			return sizeof(short);
			break;
		case USHORTVAL:
			return sizeof(unsigned short);
			break;
		case INTVAL:
			return sizeof(int);
			break;
		case UINTVAL:
			return sizeof(unsigned int);
			break;
		case LONGVAL:
			return sizeof(long);
			break;
		case ULONGVAL:
			return sizeof(unsigned long);
			break;
		case FVAL:
			return sizeof(float);
			break;
		case DOUBLEVAL:
			return sizeof(double);
			break;
		case LDOUBLEVAL:
			return sizeof(long double);
			break;
		case CHARVAL:
			return sizeof(char);
			break;
		case UCHARVAL:
			return sizeof(unsigned char);
			break;
		case SCHARVAL:
			return sizeof(signed char);
			break;
		case VOIDVAL:
			return 0;
			break;
	}
	return 0;
}

/* Convierte una lista de especificadores/qualificadores de tipo en un valor entero */
int get_type(std::list<int> *sqlist)
{
	int t = 0, s;
	std::list<int>::iterator it;
	for(it = sqlist->begin();it!=sqlist->end();it++)
	{
		if((t & *it) != 0)
			yyerror("Error in type specification!");
		t = t | *it;
	}
	s = t & 0xFFC000; /* Extraer modificadores */
	if((t & VOID_SPEC) != 0)
	{
		return VOIDVAL + s;
	}
	if((t & CHAR_SPEC) != 0)
	{
		if((t & (0x3FFF & ~CHAR_SPEC)) != 0)
			yyerror("Error in char type specification!");
		if((t & SIGNED_SPEC) > 0)
			return SCHARVAL + s;
		if((t & UNSIGNED_SPEC) > 0)
			return UCHARVAL + s;
		return CHARVAL + s;
	}
	if((t & SHORT_SPEC) != 0) 
	{
		if((t & (0x3FFF & ~(SHORT_SPEC | INT_SPEC))) != 0)
			yyerror("Error in short type specification!");
		if((t & UNSIGNED_SPEC) > 0)
			return USHORTVAL + s;
		return SHORTVAL + s;
	}
	if(((t & INT_SPEC) != 0) && ((t & LONG_SPEC) == 0)) 
	{
		if((t & (0x3FFF & ~INT_SPEC)) != 0)
			yyerror("Error in int type specification!");
		if((t & UNSIGNED_SPEC) > 0)
			return UINTVAL + s;
		return INTVAL + s;
	}
	if(((t & LONG_SPEC) != 0) && ((t & DOUBLE_SPEC) == 0)) 
	{
		if((t & (0x3FFF & ~(LONG_SPEC | INT_SPEC))) != 0)
			yyerror("Error in long type specification!");
		if((t & UNSIGNED_SPEC) > 0)
			return ULONGVAL + s;
		return LONGVAL + s;
	}
	if((t & FLOAT_SPEC) != 0) 
	{
		if((t & (0x3FFF & ~FLOAT_SPEC)) != 0)
			yyerror("Error in float type specification!");
		return FVAL + s;
	}
	if((t & DOUBLE_SPEC) != 0) 
	{
		if((t & (0x3FFF & ~(DOUBLE_SPEC | LONG_SPEC))) != 0)
			yyerror("Error in double type specification!");
		if((t & LONG_SPEC) != 0)
			return LDOUBLEVAL + s;
		return DOUBLEVAL + s;
	}
	return INTVAL + s;
}

/* Funciones para determinar tipo de un simbolo */

int isfunction(int typ)
{
	return (typ & FUNC_SPEC) != 0;
}

int isarray(int typ)
{
	return (typ & ARRAY_SPEC) != 0;
}

int isconstant(int typ)
{
	return (typ & CONST_SPEC) != 0;
}

int isvar(int typ)
{
	return (typ & VAR_SPEC) != 0;
}

int isintegral(int typ)
{   typ &= 0x1F;
	return (typ >= CHARVAL && typ <= ULONGVAL);
}

int isinteger(int typ)
{   typ &= 0x1F;
	return (typ == INTVAL || typ == UINTVAL);
}

int islong(int typ)
{   typ &= 0x1F;
	return (typ == LONGVAL || typ == ULONGVAL);
}

int ischar(int typ)
{   typ &= 0x1F;
	return (typ >= CHARVAL && typ <= SCHARVAL);
}

int isfloat(int typ)
{   typ &= 0x1F;
	return (typ >= FVAL && typ <= LDOUBLEVAL);
}

int ispointer(int typ)
{
	return (typ & POINTER_SPEC) != 0;
}


int isstring(int typ)
{   typ &= 0x1F;
	return (typ == STRVAL) != 0;
}

/* Determinar el tipo adecuado para una operación binaria */
int gettype(int typ1, int typ2)
{
    int sz1, sz2;
    sz1 = getsizeof(typ1);
    sz2 = getsizeof(typ2);
    if(sz1>sz2)
        return typ1;
    return typ2;
}

/* Agregar símbolo en ambito local */
symrec *putsym(const std::string *sym_name, int typ)
{
	symrec *ptr;
	ptr = new symrec();
	ptr->name = *sym_name;
	ptr->size = getsizeof(typ);
	ptr->typ = typ;
	ptr->offset = data_location(ptr->size);
	sym_table->push_back(ptr);
	return ptr;
}


/* Agregar arreglo a tabla de símbolos local */
symrec *putarrsym(const std::string *sym_name, int typ, int ndim)
{
	symrec *ptr;
	ptr = new symrec();
	ptr->name = *sym_name;
	ptr->size = getsizeof(typ)*ndim;
	ptr->typ = typ;
	ptr->offset = data_location(ptr->size);
	sym_table->push_back(ptr);
	return ptr;
}

int product(list<int > *ilist) 
{
	unsigned prod = 1;

	for (std::list<int >::iterator it = ilist->begin(); it != ilist->end(); ++it) {
		prod = prod * (*it);
	}
	return prod;
}

int allzero(list<int > *ilist)
{

	for (std::list<int >::iterator it = ilist->begin(); it != ilist->end(); ++it) {
		if ((*it) != 0)
			return 0;
	}
	return 1;
}

symrec *putarrsym(const std::string *sym_name, int typ, list<int > *dimlist)
{
	symrec *ptr;
	ptr = new symrec();
	ptr->name = *sym_name;
	ptr->size = getsizeof(typ)*product(dimlist);
	ptr->typ = typ;
	ptr->dimlist = dimlist;
	ptr->offset = data_location(ptr->size);
	sym_table->push_back(ptr);
	return ptr;
}

/* Buscar variable en tabla de ámbito local 
   Si no es encontrada, buscar en tablas guardadas en el stack */
symrec *getsym (const std::string *sym_name)
{
	std::list<symrec *>::iterator ptr = sym_table->begin();	// Obtener inicio de tabla de simbolos locales
	std::list<symrec *>::iterator endptr = sym_table->end(); // Obtener fin de tabla de simbolos locales
	std::list<std::list<symrec *> *>::iterator it = scopes.begin();
	while(1) {
		while(ptr != endptr){
			if ((*ptr)->name.compare(*sym_name) == 0)
				return *ptr;
			ptr++;
		}
		if(it == scopes.end())
			break;
		ptr = (*it)->begin();
		endptr = (*it)->end();
		it++;
	};
	return NULL;
}


/* Buscar variable en ámbito local */
symrec *getlocalsym (const std::string *sym_name)
{
	std::list<symrec *>::iterator ptr = sym_table->begin();
	std::list<symrec *>::iterator endptr = sym_table->end();
	while(ptr != endptr){
		if ((*ptr)->name.compare(*sym_name) == 0)
			return *ptr;
		ptr++;
	}
	return NULL;
}

/* Agregar simbolo a tabla de símbolos local */
symrec *install(const std::string *sym_name, int typ)
{
	symrec *s;
	s = getlocalsym (sym_name);
	if (s == 0)
		s = putsym (sym_name, typ);
	else { 
			/*printf("%s is already defined\n", sym_name);*/
			yyerror("Symbol already defined!");
	}
	return s;
}

symrec *installarg(std::list<VAR_DATA *> *arglist)
{
	symrec *s;
	std::list<VAR_DATA *>::iterator it;
	if(arglist == NULL)
		return NULL;
	for(it = arglist->begin(); it != arglist->end(); it++)
	{	
		s = getlocalsym ((*it)->name);
		if(s == NULL) {
			if(!isarray((*it)->typ))
				s = putsym((*it)->name, (*it)->typ);
			else
				s = putarrsym((*it)->name, (*it)->typ | ARRAY_SPEC, (*it)->val.intval);
		}
		else { 
				yyerror("Argument symbol already defined");
		}
	}
	return NULL;
}

// Poner modificador ARG_SPEC a cada variable de tabla de símbolos
// Pudo haberse hecho en función installarg
void setargs() 
{
	std::list<symrec *>::iterator it = sym_table->begin();
	while(it != sym_table->end())
	{
		(*it)->typ |= ARG_SPEC;
		it++;
	}
}

void installarray(const std::string *sym_name, int typ, int ndim)
{
	symrec *s;
	s = getsym (sym_name);
	if (s == 0)
		s = putarrsym(sym_name, typ | ARRAY_SPEC, ndim);
	else { 
			/*printf("%s is already defined\n", sym_name);*/
			yyerror("Symbol already defined!");
	}
}

void installarray(const std::string *sym_name, int typ, list<int > *dimlist)
{
	symrec *s;
	s = getsym(sym_name);
	if (s == 0)
		s = putarrsym(sym_name, typ | ARRAY_SPEC, dimlist);
	else {
		/*printf("%s is already defined\n", sym_name);*/
		yyerror("Symbol already defined!");
	}
}

void initvar(symrec *s, symrec *c) 
{
	if (s && c) {
		s->init = 1;
		if (isfloat(s->typ)) {
			if (isfloat(c->typ))
				*(float *)(datablock + s->offset) = *(float *)(datablock + c->offset);
			else
				if (isinteger(c->typ))
					*(float *)(datablock + s->offset) = *(int *)(datablock + c->offset);
				else
					if (ischar(c->typ))
						*(float *)(datablock + s->offset) = *(char *)(datablock + c->offset);
		}
		else
			if (isinteger(s->typ)) {
				if (isfloat(c->typ))
					*(int *)(datablock + s->offset) = *(float *)(datablock + c->offset);
				else
					if (isinteger(c->typ))
						*(int *)(datablock + s->offset) = *(int *)(datablock + c->offset);
					else
						if (ischar(c->typ))
							*(int *)(datablock + s->offset) = *(char *)(datablock + c->offset);
			}
			else
				if (ischar(s->typ))
					*(char *)(datablock + s->offset) = *(char *)(datablock + c->offset);
	}
}

/* Retornar j-ésima dimensión */
int getdim(list<int > *dimlist, int j)
{
	list<int >::iterator it = std::next(dimlist->begin(), j);
	return *it;
}

/* Retornar j-ésima dimensión empezando desde el final */
int getrdim(list<int > *dimlist, int j)
{
	list<int >::iterator it = std::prev(dimlist->end(), j + 1);
	return *it;
}

void enter_scope()
{
	scopes.push_front(sym_table);   // Guardar tabla de símbolos activa
	sym_table = new symboltable();	// Crear nueva tabla
	currscope++;					// Incrementar el nivel de ámbito
}

void exit_scope()
{
	sym_table->splice(sym_table->end(), *localsyms); // Agregar simbolos locales a tabla de función
	localsyms = sym_table;
	sym_table = scopes.front();					    // Restaurar tabla de simbolos anterior
	scopes.pop_front();							    // Remover tabla del stack
	currscope--;									// Decrementar nivel de scope
}

void printchr(char c)
{

	switch(c)
	{
		case '\a':
			printf("\\a");
			break;
		case '\b':
			printf("\\b");
			break;
		case '\f':
			printf("\\f");
			break;
		case '\n':
			printf("\\n");
			break;
		case '\r':
			printf("\\r");
			break;
		case '\t':
			printf("\\t");
			break;
		case '\v':
			printf("\\v");
			break;
		default:
			if(isprint(c))
				printf("%c",c);
			else
				printf("\\x%02x", (unsigned char)c);
			break;
	}
}

void printstr(char *str)
{
	char c;
	while((c = *str++)!= '\0')
	{
		printchr(c);
	}
}

void printlocalvars()
{
	std::list<symrec *>::iterator ptr = sym_table->begin();	// Obtener inicio de tabla de simbolos locales
	std::list<symrec *>::iterator endptr = sym_table->end(); // Obtener fin de tabla de simbolos locales
	if(ptr==endptr)
		return;
	cout << "Local Variable Table scope: " << currscope << endl;
	cout << "Name" << endl;
	while(ptr != endptr)
	{
		cout << (*ptr)->name;
		if(isfunction((*ptr)->typ))
			cout << " FUNC" << endl;
		else
			if(isconstant((*ptr)->typ)) 
			{
				cout << " CONST ";
				switch((*ptr)->typ & 0x1F)
				{
					case SHORTVAL:
						cout << "short " << *(short *)(datablock+(*ptr)->offset);
						break;
					case USHORTVAL:
						cout << "unsigned short " << *(unsigned short *)(datablock+(*ptr)->offset);
						break;
					case INTVAL:
						cout << "int " << *(int *)(datablock+(*ptr)->offset);
						break;
					case UINTVAL:
						cout << "unsigned int " << *(unsigned int *)(datablock+(*ptr)->offset);
						break;
					case LONGVAL:
						cout << "long " << *(long *)(datablock+(*ptr)->offset);
						break;
					case ULONGVAL:
						cout << "unsigned long " << *(unsigned long *)(datablock+(*ptr)->offset);
						break;
					case FVAL:
						cout << "float " << *(float *)(datablock+(*ptr)->offset);
						break;
					case DOUBLEVAL:
						cout << "double " << *(double *)(datablock+(*ptr)->offset);
						break;
					case LDOUBLEVAL:
						cout << "long double " << *(long double *)(datablock+(*ptr)->offset);
						break;
					case CHARVAL:
						cout << "char 0x" << setw(2) << hex << (int)*(unsigned char *)(datablock+(*ptr)->offset);
						break;
					case UCHARVAL:
						cout << "unsigned char 0x" << setw(2) << hex << (int)*(unsigned char *)(datablock+(*ptr)->offset);
						break;
					case SCHARVAL:
						cout << "signed char 0x" << setw(2) << hex << (int)*(unsigned char *)(datablock+(*ptr)->offset);
						break;
					case VOIDVAL:
						cout << "void ";
						break;
					case STRVAL:
						cout << "string " << '"' ;
						printstr((char *)(datablock+(*ptr)->offset));
						cout << '"' ;
						break;
				}
				cout << dec << endl;
			}
			else {
				cout << " VAR";
				if(isarray((*ptr)->typ))
					cout << " ARRAY";
				if((*ptr)->typ & ARG_SPEC)
					cout << " ARG";
				switch((*ptr)->typ & 0x1F)
				{
					case SHORTVAL:
						cout << " short";
						break;
					case USHORTVAL:
						cout << " unsigned short";
						break;
					case INTVAL:
						cout << " int";
						break;
					case UINTVAL:
						cout << " unsigned int";
						break;
					case LONGVAL:
						cout << " long";
						break;
					case ULONGVAL:
						cout << " unsigned long";
						break;
					case FVAL:
						cout << " float";
						break;
					case DOUBLEVAL:
						cout << " double";
						break;
					case LDOUBLEVAL:
						cout << " long double";
						break;
					case CHARVAL:
						cout << " char";
						break;
					case UCHARVAL:
						cout << " unsigned char";
						break;
					case SCHARVAL:
						cout << " signed char";
						break;
					case VOIDVAL:
						cout << " void";
						break;
				}
				cout << endl;
			}
		ptr++;
	}
}

void printvars()
{
	std::list<symrec *>::iterator ptr = sym_table->begin();	// Obtener inicio de tabla de simbolos locales
	std::list<symrec *>::iterator endptr = sym_table->end(); // Obtener fin de tabla de simbolos locales
	std::list<std::list<symrec *> *>::iterator it = scopes.begin();
	if(currscope==0)
	{
		cout << "\n";
		cout << "Global Variable Table: " << endl;
	}
	else
	{
		cout << "\n";
		cout << "Local Variable Table Scope:  " << currscope << endl;
	}
	cout << "Name" << endl;
	while(1) {
		while(ptr != endptr){
			cout << (*ptr)->name;
			if(isfunction((*ptr)->typ))
				cout << " FUNC" << endl;
			else
				if(isconstant((*ptr)->typ))
				{
					cout << " CONST ";
					switch((*ptr)->typ & 0x1F)
					{
						case SHORTVAL:
							cout << "short " << *(short *)(datablock+(*ptr)->offset);
							break;
						case USHORTVAL:
							cout << "unsigned short " << *(unsigned short *)(datablock+(*ptr)->offset);
							break;
						case INTVAL:
							cout << "int " << *(int *)(datablock+(*ptr)->offset);
							break;
						case UINTVAL:
							cout << "unsigned int " << *(unsigned int *)(datablock+(*ptr)->offset);
							break;
						case LONGVAL:
							cout << "long " << *(long *)(datablock+(*ptr)->offset);
							break;
						case ULONGVAL:
							cout << "unsigned long " << *(unsigned long *)(datablock+(*ptr)->offset);
							break;
						case FVAL:
							cout << "float " << *(float *)(datablock+(*ptr)->offset);
							break;
						case DOUBLEVAL:
							cout << "double " << *(double *)(datablock+(*ptr)->offset);
							break;
						case LDOUBLEVAL:
							cout << "long double " << *(long double *)(datablock+(*ptr)->offset);
							break;
						case CHARVAL:
							cout << "char 0x" << setw(2) << hex << (int)*(unsigned char *)(datablock+(*ptr)->offset);
							break;
						case UCHARVAL:
							cout << "unsigned char 0x" << setw(2) << hex << (int)*(unsigned char *)(datablock+(*ptr)->offset);
							break;
						case SCHARVAL:
							cout << "signed char 0x" << setw(2) << hex << (int)*(unsigned char *)(datablock+(*ptr)->offset);
							break;
						case VOIDVAL:
							cout << "void ";
							break;
						case STRVAL:
							cout << "string " << '"' ;
							printstr((char *)(datablock+(*ptr)->offset));
							cout << '"' ;
							break;
					}
					cout << dec << endl;
				}
				else {
					cout << " VAR";
					if(isarray((*ptr)->typ))
						cout << " ARRAY";
					if((*ptr)->typ & ARG_SPEC)
						cout << " ARG";
					switch((*ptr)->typ & 0x1F)
					{
						case SHORTVAL:
							cout << " short";
							break;
						case USHORTVAL:
							cout << " unsigned short";
							break;
						case INTVAL:
							cout << " int";
							break;
						case UINTVAL:
							cout << " unsigned int";
							break;
						case LONGVAL:
							cout << " long";
							break;
						case ULONGVAL:
							cout << " unsigned long";
							break;
						case FVAL:
							cout << " float";
							break;
						case DOUBLEVAL:
							cout << " double";
							break;
						case LDOUBLEVAL:
							cout << " long double";
							break;
						case CHARVAL:
							cout << " char";
							break;
						case UCHARVAL:
							cout << " unsigned char";
							break;
						case SCHARVAL:
							cout << " signed char";
							break;
						case VOIDVAL:
							cout << " void";
							break;
					}
					cout << endl;
				}
			ptr++;
		}
		if(it == scopes.end())
			break;
		ptr = (*it)->begin();
		endptr = (*it)->end();
		it++;
	};
}
