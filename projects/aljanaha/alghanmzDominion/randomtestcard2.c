#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "dominion_helpers.h"
#include "randomtest_helpers.h"
#include <time.h>
#include <string.h>

void testMinionEffect()
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
    int playerHandSize = randomNumber(1, 10);
    setPlayerRandomHand(currentPlayer, playerHandSize, &G);
    int nextPlayer = nextTurn(&G);
    int numberInHandNextPlayer = randomNumber(0, 10);
    setPlayerRandomHand(nextPlayer, numberInHandNextPlayer, &G);
    // Random minion position in player hand
    int position = randomNumber(1, playerHandSize);
    // Random choice to discard
    int choiceGainCoins = randomNumber(0, 1);
    int choiceDiscard = randomNumber(0, 1);

    G.hand[currentPlayer][position] = minion;
    int treasureBefore = G.coins;
    struct gameState gBefore;
    memcpy(&gBefore, &G, sizeof(struct gameState));
    printf("minionEffect: choiceGainCoins:%d ,choiceDiscard: %d, position: %d \n", choiceGainCoins, choiceDiscard, position);
    doMinion(choiceGainCoins, choiceDiscard, &G, position, currentPlayer);
    int treasureAfter = G.coins;

    // Oracles
    if (choiceGainCoins)
    {
        assert(treasureBefore + 2, treasureAfter, "Incorrect treasure");
    }
    else
    {
        assert(G.handCount[currentPlayer], 4, "Should have exactly 4 cards in hand");
        assert(gBefore.discardCount[currentPlayer] + gBefore.handCount[currentPlayer], G.discardCount[currentPlayer], "Discard pile incorrect size");
        if (numberInHandNextPlayer >= 5)
        {
            assert(G.handCount[nextPlayer], 4, "Should have exactly 4 cards in hand");
            assert(gBefore.discardCount[nextPlayer] + gBefore.handCount[nextPlayer], G.discardCount[nextPlayer], "Discard pile incorrect size");
        }
    }
}

int main()
{
    printf("Random test minionEffect \n");
    srand(time(0));
    for (int i = 0; i < 1000; i++)
    {
        printf("Iteration %d \n", i);
        testMinionEffect();
    }
}
