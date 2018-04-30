/* ---------------------------------------------------------------------
 * Test suite for dominion.c-base smithy card
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1.c -g cardtest1.c dominion.o rngs.o $(CFLAGS)
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
   int i; // loop control variable
   bool pass = true; // pass/failure message control variable

   // Smithy arguments
   int handPos = 0; // indexes location of smithy in the hand array
   int currentPlayer = 0; // current player is player 1

   // declare a gameState struct and initialize the struct with arbitrary values
   struct gameState G;
   G.numPlayers = 2;
   G.supplyCount[smithy] = 10; // 10 smithy cards still available
   G.numActions = 1; // at the start of every turn
   G.outpostPlayed = 0;
   //G.outpostTurn = 0;
   G.whoseTurn = 0; // player 1's turn
   G.phase = 0;
   G.numActions = 1; // at the start of every turn
   G.numBuys = 1;  // at the start of every turn
   G.playedCardCount = 0; // no cards played yet
   G.handCount[0] = 5; // player 1 has 5 cards in hand
   G.handCount[1] = 5; // player 2 has 5 cards in hand
   G.deckCount[0] = 5; // player 1 has 5 cards in the deck
   G.deckCount[1] = 5; // player 2 has 5 cards in the deck
   G.discardCount[0] = 0; // player 1 has no discards
   G.discardCount[1] = 0; // player 2 has no discards
   G.handCount[0] = 5; // player 1 has 5 cards in hand
   G.handCount[1] = 5; // player 2 has 5 cards in hand
   // player 1 hand
   G.hand[0][0] = smithy; // the test card
   G.hand[0][1] = copper;
   G.hand[0][2] = copper;
   G.hand[0][3] = great_hall;
   G.hand[0][4] = copper;
   // player 2 hand
   G.hand[1][0] = copper;
   G.hand[1][1] = great_hall;
   G.hand[1][2] = sea_hag;
   G.hand[1][3] = copper;
   G.hand[1][4] = copper;
   // player 1 deck
   G.deck[0][0] = mine;
   G.deck[0][1] = village;
   G.deck[0][2] = copper;
   G.deck[0][3] = silver;
   G.deck[0][4] = copper;
   // player 2 deck
   G.deck[1][0] = feast;
   G.deck[1][1] = copper;
   G.deck[1][2] = minion;
   G.deck[1][3] = copper;
   G.deck[1][4] = copper;

   // call smithy card function that was refactored in dominion.c file
   rSmithy(&G, handPos, currentPlayer);

   // test running message
   printf("________________________________________\n\n");
   printf("Running CARDTEST1 (SMITHY CARD TEST)...\n");

   // Test to see if handCount is 7 (5 original hand cards + 3 drawn cards -1  smithy played)
   if(G.handCount[0] == 7)
      printf("PASSED: drawn cards added correctly to handCount. Expected handCount of 7 and have %i\n", G.handCount[0]);
   else
   {
      printf("FAILED: drawn cards not added correctly to handCount. Expected handCount of 7 but have %i\n", G.handCount[0]); 
      pass = false;
   }

   // Test to see if the discard count is 1 ( +1 smithy played)
   if(G.discardCount[0] == 1) // if the discardCount of player 1 is not empty
      printf("PASSED: played smithy card correctly added to discardCount. Expected discardCount of 1 and have %i\n", G.discardCount[0]);
   else
   {
      printf("FAILED: played smithy card incorrectly added to discardCount. Expected discardCount of 1 but have %i\n", G.discardCount[0]);
      pass = false;
   }

   // Test to see if the deck count is 2 (5 original deck cards -3 drawn cards) 
   if(G.deckCount[0] == 2)
      printf("PASSED: drawn cards correctly subtracted from the deck. Expected deckCount of 2 and have %i\n", G.deckCount[0]);
   else
   {
      printf("FAILED: drawn cards incorrectly subtracted from the deck. Expected deckCount of 2 but have %i\n", G.deckCount[0]); 
      pass = false;
   }

   // Test to see if the cardsPlayedCount is 1 when Smithy gets played 
   if(G.playedCardCount == 1)
      printf("PASSED: smithy correctly added to playedCardCount. Expected playedCardCount of 1 and have %i\n", G.playedCardCount);
   else
   {
      printf("FAILED: smithy incorrectly added to playedCardCount. Expected playedCardCount of 1 but have %i\n", G.playedCardCount); 
      pass = false;
   }

   // overall result
   if(pass == true)
      printf("CARDTEST1 (SMITHY CARD TEST) SUCCESSFULLY COMPLETED\n");
   else
      printf("CARDTEST1 (SMITHY CARD TEST) FAILED\n");

   printf("________________________________________\n\n");

   return 0;
}
