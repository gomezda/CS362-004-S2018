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
   struct gameState *G;
   struct gameState *C;
   int currentPlayer;
   int *drawnTreasure;
   int numPlayers;
   int result;
   int seed;
   int k[10];
   int tempHand[500];
   int i;
   int *z;
   bool adventurerExists;
   bool pass; 

   // initialize
   adventurerExists = false;
   drawnTreasure = 0;

   // seed the random number generator
   srand(time(NULL));


   // randomize kingdom cards from set of valid cards and ensure smithy card get selected
   while(adventurerExists == false)
   {
      for(i=0; i < 10; i++)
      {
         //k[i] = rand() % (26 + 1 - 7) + 7; // random number in range 7 thru 26
         k[i] = i + 7; // random number in range 7 thru 26
         if(k[i] == adventurer && adventurerExists == false) // if one of the cards is a smithy then set control variable to exit while loop
            adventurerExists = true;
      }
   } 
   
   printf("Contents of k array:\n");
   for(i = 0; i < 10; i++)
   {
      printf("k[%i]: %i\n", i, k[i]);
   }

   // randomize the number of players in valid range of 2 thru 4
   numPlayers = rand() % (4 + 1 - 2) + 2; 
   printf("numPlayers: %i\n", numPlayers);

   // randomize current player in range 1 thru numPlayers - 1
   currentPlayer = rand() % ((numPlayers - 1) + 1 - 1) + 1;

   // randomize the seed 
   seed = rand() % (1000 + 1 - 1) + 1; 
   printf("seed: %i\n", seed);

   // declare a gameState struct, allocate memory, and then initialize it 
   G = newGame();
   result = initializeGame(numPlayers, k, seed, G);
   if(result < 0)
   {
      printf("FAIL: could not initialize. Exit 1.\n");
      exit (1);
   }
   C = malloc(sizeof(struct gameState)); // allocate memory for a new gameState and make C point to it
   memcpy(C, G, sizeof(struct gameState)); // copy G to C 

   printf("Before adventurer card is called, G->hand[currentPlayer]: %i\n", *(G->hand[currentPlayer]));
   printf("Before adventurer card is called, C->hand[currentPlayer]: %i\n", *(C->hand[currentPlayer]));


   // call adventurer card function, then make a copy of the gameState G to gamestate C 
   rAdventurer(G, drawnTreasure, drawnTreasure, z, tempHand, currentPlayer);

   printf("After adventurer card is called, G->hand[currentPlayer]: %i\n", *(G->hand[currentPlayer]));
   printf("After adventurer card is called, C->hand[currentPlayer]: %i\n", *(C->hand[currentPlayer]));

   // test running message
   printf("________________________________________\n\n");
   printf("Running random ADVENTURER card test...\n");

   // check to see if hand contains 6 cards (5 at beginning of turn + 2 treasure drawn -1 adventurer played) 
   if(G->handCount[currentPlayer] == (C->handCount[currentPlayer] + drawnTreasure - 1))
      printf("PASSED: drawn cards added correctly to handCount. Expected handCount of %i and have %i\n", (C->handCount[currentPlayer] + drawnTreasure - 1), G->handCount[currentPlayer]);
   else
   {
      printf("FAILED: drawn cards not added correctly to handCount.\n" ); 
      pass = false;
   }


   /*
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
*/
   return 0;
}
