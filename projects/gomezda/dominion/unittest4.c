/* ---------------------------------------------------------------------
 * Test suite for dominion.c-base whoseTurn() function
 * Include the following lines in your makefile:
 *
 * unittest1: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4.c -g unittest4.c dominion.o rngs.o $(CFLAGS)
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
   // hardcode value for G whoseturn
   struct gameState G;
   G.whoseTurn = 1; // player 2 turn

   // test running message
   printf("________________________________________\n\n");
   printf("Running UNITTEST4 WHOSETURN()...\n");

   // check if whoseTurn returns correct value
   if(whoseTurn(&G) == 1)
      printf("PASSED: expected whoseTurn is 1 and true value is %i\n", whoseTurn(&G));
   else
   {
      printf("FAILED: expected whoseTurn is 1 and true value is %i\n", whoseTurn(&G));
      pass = false;
   }

   // overall result
   if(pass == true)
      printf("UNITTEST4 WHOSETURN() SUCCESSFULLY COMPLETED\n");
   else
      printf("UNITTEST4 WHOSETURN() FAILED\n");

   printf("________________________________________\n\n");

   return 0;
}
