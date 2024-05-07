/* C Program to print a sentence. */
#include <stdio.h>

int r, k;
int h[2];
int printf();
int* ptr;
float myfunc(int a, int b)
{
   return a * b;
}
int main(int argc, char *argv[])
{
   double x = 0.1;
   float y = 1.5/3;
   int z = 3+2u;
   char c = '\x0d2', cc = '\0342';
   int i;
   z = sizeof(int);
   r = x-3*4/2;
   y *= 2.5e5;
   if(r>3)
      printf(L"C Programming // %d\n", 5); /* printf() prints the content inside quotation */
   else
      r = z;
      r += 0x0aa;
   z = 5 - (int)3.1;
   for(i = 0;i < 5;i++) 
   {
      printf("%d\n", i);
   }
/*
   z = y > 1e9 ? 1 : 0;
   
   Si la condición y > 1e9 es verdadera, entonces z se establecerá en 1.
   Si la condición y > 1e9 es falsa, entonces z se establecerá en 0.
   Equivalente : */
   
   if (y > 1e9)
   {
   z = 1;
   }
   else
   {
   z = 0;
   } 

   for (i = 0; i < 5; i++)
   {
      printf("%d\n", i);
   }
   z = myfunc(h[1], 5);
   z = myfunc(3.1, 2.4);
   z = y > 1e9 ? 1 : 0;
   z--;
   return z;
}
