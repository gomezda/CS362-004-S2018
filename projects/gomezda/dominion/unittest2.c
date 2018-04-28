/* ---------------------------------------------------------------------
 * Test suite for dominion.c-base isGameOver() function
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2.c -g unittest2.c dominion.o rngs.o $(CFLAGS)
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
   int i;
   struct gameState G; // create a gameState struct variable
   int totalCards = 27; // total number of different types of cards in the game

   // check condition where non of the supply card stacks are empty. isGameOver should return 0 (game not over)
   for(i=0; i < totalCards; i++) // loop through all the cards
   {
      G.supplyCount[i] = 1; // make each card type have a stack of one (not empty)
   }
   assert(isGameOver(&G) == 0); // if isGameOver returns a nonzero then send an error message to stderr

   // check when stack of province cards is empty and the rest of supply piles are not empty
   // From dominion.h, province cards are enum 3. 
   G.supplyCount[3] = 0; // make the province card stack empty, and keep the other card stacks non empty 
   assert(isGameOver(&G) == 1); // isGameOver should retun 1 if the province card stack is empty 

   // make province stack non empty, then make 3 supply stacks empty, and isGameOver should retun 1 (game ends
   // because there are 3 empty supply card stacks)
   G.supplyCount[copper] = 0; // empty the copper stack
   G.supplyCount[silver] = 0; // empty the silver stack
   G.supplyCount[gold] = 0; // empty the gold stack
   G.supplyCount[province] = 1; // make the province stack not empty
   assert(isGameOver(&G) == 1); // Game should be over with 3 empty supply stacks and isGameOver should return 1

   // make all stacks empty, and the game should be over 
   for(i=0; i < totalCards; i++) // loop through all the cards
   {
      G.supplyCount[i] = 0; // make each card type have a stack of one (not empty)
   }
   assert(isGameOver(&G) == 1); // game should be over with every stack set to empty

   printf("All tests for isGameOver() passed.\n");

   return 0;
}
