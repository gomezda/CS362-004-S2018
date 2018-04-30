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
#include <stdbool.h>

int main()
{
   bool pass = true;
   int i;
   struct gameState G; // create a gameState struct variable
   int totalCards = 27; // total number of different types of cards in the game

   // check condition where non of the supply card stacks are empty. isGameOver should return 0 (game not over)
   for(i=0; i < totalCards; i++) 
   {
      G.supplyCount[i] = 1; // make each card type have a stack of one (not empty)
   }
   // test running message
   printf("________________________________________\n\n");
   printf("Running UNITTEST2 ISGAMEOVER()...\n");

   // check if the game continues if no stacks are empty 
   if(isGameOver(&G) == 0)
      printf("PASSED: isGameOver returns 0 when all supply stacks have at least one card\n");
   else
   {
      printf("FAILED: isGameOver does not retun 0 when all supply stacks have at least one card\n");
      pass = false;
   }

   // check when stack of province cards is empty and the rest of supply piles are not empty
   // From dominion.h, province cards are enum 3. 
   G.supplyCount[3] = 0; // make the province card stack empty, and keep the other card stacks non empty 

   // check if the game is over when province stack is empty 
   if(isGameOver(&G) == 1)
      printf("PASSED: isGameOver returns 1 when province stack is empty, and other stacks are not empty\n");
   else
   {
      printf("FAILED: isGameOver does not retun 1 when province stack is empty, and other stacks are not empty\n");
      pass = false;
   }

   // make province stack non empty, then make 3 supply stacks empty, and isGameOver should retun 1 (game ends
   // because there are 3 empty supply card stacks)
   G.supplyCount[copper] = 0; // empty the copper stack
   G.supplyCount[silver] = 0; // empty the silver stack
   G.supplyCount[gold] = 0; // empty the gold stack
   G.supplyCount[province] = 1; // make the province stack not empty

   // check if the game is over when there are 3 empty supply stacks (province stack is not empty) 
   if(isGameOver(&G) == 1)
      printf("PASSED: isGameOver returns 1 when 3 stacks are empty, but the province stack is not empty\n");
   else
   {
      printf("FAILED: isGameOver does not retun 1 when 3 stacks are empty, but the province stack is not empty\n");
      pass = false;
   }

   // make all stacks empty
   for(i=0; i < totalCards; i++) 
   {
      G.supplyCount[i] = 0; 
   }

   // check if the game is over when all stacks are empty 
   if(isGameOver(&G) == 1)
      printf("PASSED: isGameOver returns 1 when all stacks are empty\n");
   else
   {
      printf("FAILED: isGameOver does not retun 1 when all stacks are empty\n");
      pass = false;
   }

   // overall result
   if(pass == true)
      printf("UNITTEST2 ISGAMEOVER() SUCCESSFULLY COMPLETED\n");
   else
      printf("UNITTEST2 ISGAMEOVER() FAILED\n");

   printf("________________________________________\n\n");

   return 0;
}
