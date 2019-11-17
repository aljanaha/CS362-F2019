#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "dominion_helpers.h"
#include "randomtest_helpers.h"
#include <time.h>

void testBaronEffect()
{
        // Game instance
        struct gameState G;
        // Cards to play
        int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                     sea_hag, baron, smithy};

        initializeGame(2, k, 2, &G);
        randomInitGame(&G);
        // Set current player hand
        int currentPlayer = whoseTurn(&G);
        // Set player hand at random
        setPlayerRandomHand(currentPlayer, 5, &G);
        // Random baron position in player hand
        int position = randomNumber(1, 5);
        // Random choice to discard
        int choiceDiscardCard = randomNumber(0, 1);

        G.hand[currentPlayer][position] = baron;

        int estatesBefore = fullDeckCount(currentPlayer, estate, &G);
        int treasureBefore = G.coins;
        int estatesInHandBefore = fullHandCount(currentPlayer, estate, &G);
        printf("baronEffect: choiceDiscardCard: %d \n", choiceDiscardCard);
        baronEffect(&G, choiceDiscardCard);
        int treasureAfter = G.coins;
        int estatesAfter = fullDeckCount(currentPlayer, estate, &G);
        // Oracle
        if (choiceDiscardCard)
        {
                // Choose to discard
                if (estatesInHandBefore > 0)
                {
                        assert(treasureBefore + 4, treasureAfter, "Incorrect treasure");
                }
                else
                {
                        assert(estatesBefore + 1, estatesAfter, "Should have won an estate");
                }
        }
        else
        {
                assert(estatesBefore + 1, estatesAfter, "Should have won an estate");
        }
}

int main()
{
        printf("Random test baronEffect \n");
        srand(time(0));
        for (int i = 0; i < 10000; i++)
        {
                printf("Iteration %d \n", i);
                testBaronEffect();
        }
}
