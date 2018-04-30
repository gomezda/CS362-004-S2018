/* ---------------------------------------------------------------------
 * Test suite for dominion.c-base council_room card
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4.c -g cardtest4.c dominion.o rngs.o $(CFLAGS)
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

   // initialize council_room function arguments
   int currentPlayer = 0; // current player is player 1
   int handPos = 1; // indexes the location of village card in hand array

   // declare a gameState struct and initialize the struct with arbitrary values
   struct gameState G;
   G.numPlayers = 2;
   G.supplyCount[adventurer] = 10; // 10 smithy cards still available
   G.numActions = 1; // at the start of every turn
   G.outpostPlayed = 0;
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
   G.hand[0][0] = adventurer; 
   G.hand[0][1] = village; 
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
   G.deck[0][4] = council_room; // the test card
   // player 2 deck
   G.deck[1][0] = feast;
   G.deck[1][1] = council_room;
   G.deck[1][2] = minion;
   G.deck[1][3] = copper;
   G.deck[1][4] = copper;

   // call adventurer card function that was refactored in dominion.c file
   rCouncil_room(&G, handPos, currentPlayer);

   // test running message
   printf("________________________________________\n\n");
   printf("Running CARDTEST4 (COUNCIL_ROOM CARD TEST)...\n");

   // check to see if hand contains 8 cards (5 at beginning of turn + 4 draw -1 council_room played) 
   if(G.handCount[0] == 8)
      printf("PASSED: drawn cards added correctly to handCount. Expected handCount of 8 and have %i\n", G.handCount[0]);
   else
   {
      printf("FAILED: drawn cards not added correctly to handCount. Expected handCount of 8 but have %i\n", G.handCount[0]); 
      pass = false;
   }

   // Test to see if the discardCount is 1, from the council_room card that was played 
   if(G.discardCount[0] == 1) 
      printf("PASSED: council_room correctly added to discard pile. Expected discardCount of 1 and have %i\n", G.discardCount[0]);
   else
   {
      printf("FAILED: village incorrectly added to discard pile. Expected discardCount of 1 but have %i\n", G.discardCount[0]);
      pass = false;
   }

   // check the deckCount, which should be 1 (5 in deck at beginning of turn -4 draw from council_room effect)
   if(G.deckCount[0] == 1)
      printf("PASSED: drawn card subtracted from the deck. Expected deckCount of 1 and have %i\n", G.deckCount[0]);
   else
   {
      printf("FAILED: drawn card not subtracted from the deck. Expected deckCount of 1 but have %i\n", G.deckCount[0]); 
      pass = false;
   }

   // check to ensure playedCardCount is 1 (from the council_room that was played)
   if(G.playedCardCount == 1)
      printf("PASSED: council_room card correctly added to playedCardCount. Expected playedCardCount of 1 and have %i\n", G.playedCardCount);
   else
   {
      printf("FAILED: council_room card incorrectly added to playedCardCount. Expected playedCardCount of 1 but have %i\n", G.playedCardCount); 
      pass = false;
   }

   // check number of actions, which should be 0 (1 at start -1 council_room played)
   if(G.numActions == 0)
      printf("PASSED: council_room effect correctly added actions to numActions. Expected numActions of 0 and have %i\n", G.numActions);
   else
   {
      printf("FAILED: council_room effect incorrectly added actions to numActions. Expected numActions of 0 but have %i\n", G.numActions); 
      pass = false;
   }

   // check number of buys, which should be 1 (1 at start +1 council_room effect)
   if(G.numBuys == 2)
      printf("PASSED: council_room effect correctly added buys to numBuys. Expected numBuys of 2 and have %i\n", G.numBuys);
   else
   {
      printf("FAILED: council_room effect incorrectly added buys to numBuys. Expected numBuys of 1 but have %i\n", G.numBuys); 
      pass = false;
   }

   // checking player 2 deck effects from council_room, should have 4 (5 deck -1 draw effect)
   if(G.deckCount[1] == 4)
      printf("PASSED: other players draw from deck correctly. Expected 4 and have %i\n", G.deckCount[1]);
   else
   {
      printf("FAILED: other players draw from deck incorrectly. Expected 4 and have %i\n", G.deckCount[1]);
      pass = false;
   }

   // checking player 2 handCount from council_room effects, should have 6 (5 deck +1 draw effect)
   if(G.handCount[1] == 6)
      printf("PASSED: other players draw to hand correctly. Expected handCount of 6 and have %i\n", G.handCount[1]);
   else
   {
      printf("FAILED: other players draw to hand  incorrectly. Expected handCount of 6 and have %i\n", G.handCount[1]);
      pass = false;
   }

   // overall test result
   if(pass == true)
      printf("CARDTEST4 (COUNCIL_ROOM CARD TEST) SUCCESSFULLY COMPLETED\n");
   else
      printf("CARDTEST4 (COUNCIL_ROOM CARD TEST) FAILED\n");

   printf("________________________________________\n\n");

   return 0;
}
