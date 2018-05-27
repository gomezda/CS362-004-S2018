#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

void initCheck(struct gameState* g, int* k)
{
   int i;
   int j;
   int c; // coppers in deck
   int e; // estate in deck
   bool found;
   
   printf("Testing the gamestate initialization...\n");
   assert(g->numPlayers >= 2 && g->numPlayers <= 4);
   if(g->numPlayers == 2)
   {
      assert(g->supplyCount[0] == 10);
      assert(g->supplyCount[1] == 8);
      assert(g->supplyCount[2] == 8);
      assert(g->supplyCount[3] == 8);
      assert(g->supplyCount[4] == 46);
      assert(g->supplyCount[5] == 40);
      assert(g->supplyCount[6] == 30);
      // check kingdom card supply smounts
      for(i = 7; i < 27; i++) // loop through all kingdom cards
      {
         found = false; // initialize to false for every kingdom card
         for(j = 0; j < 10; j++) // loop through all kingdom cards chosen
         {
            // printf("k[%i]: %i\n", j, k[j]);
            if(i == k[j]) // if the kingdom card is part of the chosen kingdom cards
            {
               if(i == 10 || i == 16) // if the kingdom card was chosen and is a victory card
               {
                  assert(g->supplyCount[i] == 8);
                  found = true;
               }
               else // else the kingdom card was chosen but not a victory card
               {
                  assert(g->supplyCount[i] == 10);
                  found = true;
               }
            }
         }
         if(found == false)
         {
            assert(g->supplyCount[i] == -1);
         }
      }
   }
   if(g->numPlayers == 3)
   {
      assert(g->supplyCount[0] == 20); // 3 players have 20 curse cards
      assert(g->supplyCount[1] == 12);
      assert(g->supplyCount[2] == 12);
      assert(g->supplyCount[3] == 12);
      assert(g->supplyCount[4] == 39); // caclulated by 60 - (7 * numPlayers)
      assert(g->supplyCount[5] == 40);
      assert(g->supplyCount[6] == 30);
      // check kingdom card supply smounts
      for(i = 7; i < 27; i++) // loop through all kingdom cards
      {
         found = false; // initialize to false for every kingdom card
         for(j = 0; j < 10; j++) // loop through all kingdom cards chosen
         {
            // printf("k[%i]: %i\n", j, k[j]);
            if(i == k[j]) // if the kingdom card is part of the chosen kingdom cards
            {
               if(i == 10 || i == 16) // if the kingdom card was chosen and is a victory card
               {
                  assert(g->supplyCount[i] == 12);
                  found = true;
               }
               else // else the kingdom card was chosen but not a victory card
               {
                  assert(g->supplyCount[i] == 10);
                  found = true;
               }
            }
         }
         if(found == false)
         {
            assert(g->supplyCount[i] == -1);
         }
      }
   }
   if(g->numPlayers == 4)
   {
      assert(g->supplyCount[0] == 30); // 4 players should have 30 curse cards
      assert(g->supplyCount[1] == 12);
      assert(g->supplyCount[2] == 12);
      assert(g->supplyCount[3] == 12);
      assert(g->supplyCount[4] == 32); // calculated by 60 - (7 * numPlayers)
      assert(g->supplyCount[5] == 40);
      assert(g->supplyCount[6] == 30);
      // check kingdom card supply smounts
      for(i = 7; i < 27; i++) // loop through all kingdom cards
      {
         found = false; // initialize to false for every kingdom card
         for(j = 0; j < 10; j++) // loop through all kingdom cards chosen
         {
            // printf("k[%i]: %i\n", j, k[j]);
            if(i == k[j]) // if the kingdom card is part of the chosen kingdom cards
            {
               if(i == 10 || i == 16) // if the kingdom card was chosen and is a victory card
               {
                  assert(g->supplyCount[i] == 12);
                  found = true;
               }
               else // else the kingdom card was chosen but not a victory card
               {
                  assert(g->supplyCount[i] == 10);
                  found = true;
               }
            }
         }
         if(found == false)
         {
            assert(g->supplyCount[i] == -1);
         }
      }
   }
   printf("supplyCounts initialized\n");
   for(i = 0; i < 27; i++)
   {
      assert(g->embargoTokens[i] == 0);
   }
   printf("embargoTokens initialized\n");
   assert(g->outpostPlayed == 0);
   printf("outpostPlayed initialized\n");
   assert(g->outpostTurn == 0);
   printf("outpostTurn initialized\n"); 
   assert(g->whoseTurn == 0);
   printf("whoseTurn initialized\n");
   assert(g->phase == 0);
   printf("phase initialized\n");
   assert(g->numActions == 1);
   printf("numActions initialized\n");
   assert(g->numBuys == 1);
   printf("numBuys initialized\n");
   // check initializatin for player 0, the numbers will differ from other players that haven't drawn yet
   assert(g->deckCount[0] == 5); // 5 deckCount since init function draws 5 cards (at bottom of code) for player 0 only
   printf("player 0 deckCount initialized\n");
   assert(g->handCount[0] == 5);
   printf("player 0 handCount initialized\n");
   assert(g->discardCount[0] == 0);
   printf("player 0 discardCount initialized\n");
   // check initilization for other players
   for(i = 1; i < g->numPlayers; i++) // loop through players that are not player 0
   {
      e = 0;
      c = 0;
      assert(g->deckCount[i] == 10); // check for 11 deck cards (3 estate, 7 copper)
      printf("player %i deckCount initialized\n", i); 
      for(j = 0; j < 11; j++) // loop through all cards in the deck
      {
         if(g->deck[i][j] == 1)
            e++; // increment estate counter if it's in the deck
         if(g->deck[i][j] == 4)
            c++; // increment copper counter if it's in the deck
      }
      assert(e == 3);
      printf("player %i deck initialized with estates\n", i);
      assert(c == 7);
      printf("player %i deck initialized with coppers\n", i);
      assert(g->handCount[i] == 0);
      printf("player %i handCount initialized\n", i);
      assert(g->discardCount[i] == 0);
      printf("player %i discardCount initialized\n", i);
   }
   assert(g->playedCardCount == 0);
   printf("playedCardCount initialized\n");
   printf("PASSED gameState initialization\n"); 
}


void VillageTest(struct gameState *state, int handPos, int currentPlayer)
{
   int oldNumActions;
   int oldHandCount;
   int oldPlayedCardCount;
   //int i;
   oldNumActions = state->numActions;
   oldHandCount = state->handCount[currentPlayer];
   oldPlayedCardCount = state->playedCardCount;
   printf("Starting village test...\n");
   printf("Before calling rVillage handCount is: %i\n", state->handCount[currentPlayer]);
   rVillage(state, handPos, currentPlayer);
   printf("After calling rVillage handCount is: %i\n", state->handCount[currentPlayer]);
   assert(state->handCount[currentPlayer] == oldHandCount); // the net change of handCount should be 0 since you draw 1 card and discard 1 card
   printf("handCount increased by 0\n");
   assert(state->playedCardCount == oldPlayedCardCount + 1); // played card count should increase by 1 since discard places into played card pile
   printf("playedCardCount increased by 1\n");
   assert(state->playedCards[oldPlayedCardCount] == 14); // the last index of playedCards[] should be the discarded village card, represented by enum 14
   printf("discarded village card placed in playedCards\n");
   assert(state->numActions == oldNumActions); // numActions should still be 1 since you use 1 to play the card and then gain 1 action as a card benefit
   printf("numActions applied correctly\n");
   assert(state->hand[currentPlayer][handPos] != -1); // the village card played should not have a -1 in it's hand array position
   printf("handPos of hand[] is not -1 int value\n");
   assert(state->hand[currentPlayer][handPos] >= 0 && state->hand[currentPlayer][handPos] <= 26); // card in the handPos should be another card 
   printf("handPos of hand[] contains another card instead of being empty\n");
   printf("PASSED village test\n"); 

}

int main()
{
   struct gameState* g; // pointer-to-gameState used to point to a gameState struct
   int* k;  // pointer-to-int used to point to an array of kingdom cards
   int seed = -5;
   int currentPlayer = -5;
   int numPlayers = -5;
   int handPos = -5; // indexes the element of hand[] where village card is located
   int rCounter = 0; // loop counter initialized to 0
   int i;

   // seed the random number generator
   srand(time(NULL));

   while(rCounter < 1)
   {
      // create the gamespace
      g = newGame();
      assert(g != NULL); 

      // create kingdom cards by using kingdomCards function
      k = kingdomCards(7, 8, 9, 10, 11, 12, 13, 14, 15, 16); // kingdom cards includes one adventurer and every card is different
      assert(k != NULL);

      printf("\nStarting random village card test %i\n", rCounter);

      // randomize the number of players in valid range of 2 thru 4
      numPlayers = rand() % (4 + 1 - 2) + 2;
      //printf("gamespace random numPlayers: %i\n", numPlayers);

      // randomize current player in range 0 thru (numPlayers - 1)
      currentPlayer = rand() % ((numPlayers - 1) + 1 - 0) + 0;
      //printf("gamespace random currentPlayer: %i\n", currentPlayer);

      // randomize the seed 
      seed = rand() % (1000 + 1 - 1) + 1; 
      //printf("gamespace random seed: %i\n", seed);

      // initialize the gamespace and assert that it was created
      assert(initializeGame(numPlayers, k, seed, g) != -1);

      // run a gamespace initialization check
      initCheck(g, k);

      // draw 5 cards for currentPlayer
      printf("gamespace random hand selection:\n");
      for(i = 0; i < 5; i++)
      {
         drawCard(currentPlayer, g);
      }      

      // place village card into currentplayer's hand at random position
      handPos = rand() % (4 + 1 - 0) + 0;  // random hand position in range 0 thru 4
      g->hand[currentPlayer][handPos] = 14; // make a village card appear in hand of currentPlayer
      printf("gamespace random handPos: %i\n", handPos);
      printf("gamespace random hand selection with included village card:\n");
      for(i = 0; i < 5; i++)
      {
         printf("hand[%i][%i]: %i\n", currentPlayer, i, g->hand[currentPlayer][i]);
      }      

      // call adventurer test with random handPos and random currentPlayer
      VillageTest(g, handPos, currentPlayer);

      // increment the loop counter
      rCounter++;

      free(g);
      free(k);
   }

   return 0;
}



