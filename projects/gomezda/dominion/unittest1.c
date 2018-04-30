/* ---------------------------------------------------------------------
 * Test suite for dominion.c-base supplyCount() function
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1.c -g unittest1.c dominion.o rngs.o $(CFLAGS)
 * -------------------------------------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

int main()
{
   bool pass = true;
   // hardcode the gameState struct variables; note: supplyCount[] is part of the gameState struct
   // which is different than supplyCount(), the function we are testing
   struct gameState G;
   G.supplyCount[curse] = 2;
   G.supplyCount[estate] = 3;
   G.supplyCount[copper] = 4;
   G.supplyCount[adventurer] = 5;
   
   // test running message
   printf("________________________________________\n\n");
   printf("Running UNITTEST1 SUPPLYCOUNT()...\n");

   // call supplyCount() and check if the number of cards in the supply match the hardcoded values
   if(supplyCount(curse, &G) == 2)
      printf("PASSED: correct curse supplyCount. Expected supplyCount of 2 and have %i\n", supplyCount(curse, &G));
   else
   {
      printf("FAILED: incorrect curse supplyCount. Expected supplyCount of 2 and have %i\n", supplyCount(curse, &G));
      pass = false;
   }

   // call supplyCount90 and check if copper supplyCount() matches hardcoded value
   if(supplyCount(copper, &G) == 4)
      printf("PASSED: correct copper supplyCount. Expected supplyCount of 4 and have %i\n", supplyCount(copper, &G));
   else
   {
      printf("FAILED: incorrect copper supplyCount. Expected supplyCount of 4 and have %i\n", supplyCount(copper, &G));
      pass = false;
   }

   // overall result
   if(pass == true)
      printf("UNITTEST1 SUPPLYCOUNT() SUCCESSFULLY COMPLETED\n");
   else
      printf("UNITTEST1 SUPPLYCOUNT() FAILED\n");

   printf("________________________________________\n\n");

   return 0;
}
