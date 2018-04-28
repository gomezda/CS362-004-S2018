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

int main()
{
   // hardcode the gameState struct variables; note: supplyCount[] is part of the gameState struct
   // which is different than supplyCount(), the function we are testing
   struct gameState G;
   G.supplyCount[curse] = 2;
   G.supplyCount[estate] = 3;
   G.supplyCount[copper] = 4;
   G.supplyCount[adventurer] = 5;
 
   // call supplyCount() and check if the number of cards in the supply match the hardcoded values
   assert(supplyCount(curse, &G) == 2);
   assert(supplyCount(estate, &G) == 3);
   assert(supplyCount(copper, &G) == 4);
   assert(supplyCount(adventurer, &G) == 5);

   printf("All tests for supplyCount() passed.\n");

   return 0;
}
