/* ---------------------------------------------------------------------
 * Test suite for dominion.c-base adventurer card
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2.c -g cardtest2.c dominion.o rngs.o $(CFLAGS)
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
   bool pass = true; // pass/failure message control variable

   // initialize adventurer function arguments
   int currentPlayer = 0; // current player is player 1
   //int drawntreasure = 0; // keeps track of drawn treasure, must be initialized to 0
   //int temphand[MAX_HAND]; // holds the non-treasure cards that are drawn. MAX_HAND is defined in dominion.h
   //int z = 0; // used to index the temphand array

   // declare a gameState struct and initialize the struct with arbitrary values
   struct gameState G;
   G.numPlayers = 2;
   G.supplyCount[adventurer] = 10; // 10 smithy cards still available
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
   G.hand[0][0] = adventurer; // the test card
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
   G.deck[0][4] = adventurer;
   // player 2 deck
   G.deck[1][0] = feast;
   G.deck[1][1] = council_room;
   G.deck[1][2] = minion;
   G.deck[1][3] = copper;
   G.deck[1][4] = copper;

   // call adventurer card function that was refactored in dominion.c file
   rAdventurer(&G, currentPlayer);

   // test running message
   printf("________________________________________\n\n");
   printf("Running CARDTEST2 (ADVENTURER CARD TEST)...\n");

   // check to see if hand contains 6 cards (5 at beginning of turn + 2 treasure drawn -1 adventurer played) 
   if(G.handCount[0] == 6)
      printf("PASSED: drawn cards added correctly to handCount. Expected handCount of 6 and have %i\n", G.handCount[0]);
   else
   {
      printf("FAILED: drawn cards not added correctly to handCount. Expected handCount of 6 but have %i\n", G.handCount[0]); 
      pass = false;
   }

   // Test to see if the discardCount is 1, from the adventurer card that was drawn but not a treasure card 
   if(G.discardCount[0] == 2) 
      printf("PASSED: adventurer played and adventurer drawn added to discard pile. Expected discardCount of 2 and have %i\n", G.discardCount[0]);
   else
   {
      printf("FAILED: adventurer played and adventurer drawn not added to discard pile. Expected discardCount of 2 but have %i\n", G.discardCount[0]);
      pass = false;
   }

   // check the deckCount, which should be 4 (5 in deck at beginning of turn -1 adventurer -1 silver -1 copper that were drawn)
   if(G.deckCount[0] == 2)
      printf("PASSED: drawn cards subtracted from the deck. Expected deckCount of 2 and have %i\n", G.deckCount[0]);
   else
   {
      printf("FAILED: drawn cards not subtracted from the deck. Expected deckCount of 2 but have %i\n", G.deckCount[0]); 
      pass = false;
   }

   // check to ensure playedCardCount is 1 (from the adventurer that was played)
   if(G.playedCardCount == 1)
      printf("PASSED: adventurer card correctly added to playedCardCount. Expected playedCardCount of 1 and have %i\n", G.playedCardCount);
   else
   {
      printf("FAILED: adventurer card incorrectly added to playedCardCount. Expected playedCardCount of 1 but have %i\n", G.playedCardCount); 
      pass = false;
   }

   if(pass == true)
      printf("CARDTEST2 (ADVENTURER CARD TEST) SUCCESSFULLY COMPLETED\n");
   else
      printf("CARDTEST2 (ADVENTURER CARD TEST) FAILED\n");

   printf("________________________________________\n\n");

   return 0;
}
