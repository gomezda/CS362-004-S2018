/* ---------------------------------------------------------------------
 * Test suite for dominion.c-base fullDeckCount() function
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3.c -g unittest1.c dominion.o rngs.o $(CFLAGS)
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
   int pass = true;
   int player = 3;
   struct gameState G;

   // hardcode G deck values
   G.deckCount[player] = 10;
   G.deck[player][0] = outpost;
   G.deck[player][1] = smithy;
   G.deck[player][2] = mine;
   G.deck[player][3] = silver;
   G.deck[player][4] = gardens;
   G.deck[player][5] = silver;
   G.deck[player][6] = copper;
   G.deck[player][7] = mine;
   G.deck[player][8] = silver;
   G.deck[player][9] = village;

   // hardcode G hand values
   G.handCount[player] = 5;
   G.hand[player][0] = silver;   
   G.hand[player][1] = curse;   
   G.hand[player][2] = village;   
   G.hand[player][3] = copper;   
   G.hand[player][4] = remodel; 

   // hardcode G discard values
   G.discardCount[player] = 1;
   G.discard[player][0] = sea_hag;

   // test running message
   printf("________________________________________\n\n");
   printf("Running UNITTEST3 FULLDECKCOUNT()...\n");

   // check deckCount of outpost
   if(fullDeckCount(player, outpost, &G) == 1)
      printf("PASSED: for outpost, expected fullDeckCount is 1 and true value is %i\n", fullDeckCount(player, outpost, &G));
   else
   {
      printf("FAILED: for outpost, expected fullDeckCount is 1 and true value is %i\n", fullDeckCount(player, outpost, &G));
      pass = false;
   }

   // check deckCount of silver
   if(fullDeckCount(player, silver, &G) == 4)
      printf("PASSED: for silver, expected fullDeckCount is 4 and true value is %i\n", fullDeckCount(player, silver, &G));
   else
   {
      printf("FAILED: for silver, expected fullDeckCount is 4 and true value is %i\n", fullDeckCount(player, silver, &G));
      pass = false;
   }
   assert(fullDeckCount(player, feast, &G) == 0);

   // testing for a card not in the deck
   if(fullDeckCount(player, feast, &G) == 0)
      printf("PASSED: for feast (a card not in the deck), expected fullDeckCount is 0 and value is %i\n", fullDeckCount(player, feast, &G));
   else
   {
      printf("FAILED: for feast (a card not in the deck), expected fullDeckCount is 0 and value is %i\n", fullDeckCount(player, feast, &G));
      pass = false;
   }

   // overall result
   if(pass == true)
      printf("UNITTEST3 FULLDECKCOUNT() SUCCESSFULLY COMPLETED\n");
   else
      printf("UNITTEST3 FULLDECKCOUNT() FAILED\n");

   printf("________________________________________\n\n");

   return 0;
}
