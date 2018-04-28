#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum NAME
{
   jane = 0,
   henry,
   mike  
};

int main()
{
   int a[3] = {jane, henry, mike};

   printf("a[0] is %i\n", a[0]);
   printf("a[1] is %i\n", a[1]);
   printf("a[2] is %i\n", a[2]);
   printf("Value of jane is %i\n", jane);
   printf("Value of mike is %i\n", mike); 

   return 0;
}
