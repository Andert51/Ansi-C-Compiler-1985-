
#include <stdio.h>

int printf();

int main()
{
    /* Esto es un comentario en C */ 
    char myString[] = "Hello"; /* Con un char mystring[5] ocurre un problema de segmentacion por arreglo declarado conmenos memoria de la usada*/
    printf("%s World in ANSI C Compiler\n", myString);
    return 0;
    
}
