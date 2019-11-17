#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "dominion_helpers.h"
#include "randomtest_helpers.h"
#include <time.h>

// int tributeEffect(struct gameState *state, int handPos);

void testTributeEffect()
{
    // Game instance
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    initializeGame(2, k, 2, &G);
    randomInitGame(&G);

    // Set current player hand
    int currentPlayer = whoseTurn(&G);
    // Set player hand at random
    setPlayerRandomHand(currentPlayer, 5, &G);
    int nextPlayer = nextTurn(&G);
    int numberInHandNextPlayer = randomNumber(0, 10);
    setPlayerRandomHand(nextPlayer, numberInHandNextPlayer, &G);
    // Random tribute position in player hand
    int position = randomNumber(1, 5);
    G.hand[currentPlayer][position] = tribute;

    // Deck must be between 0 and 2 but 10 is enough
    int nextPlayerDeckCount = randomNumber(0, 10);
    // This could be empty or non empty
    int nextPlayerDiscardCount = randomNumber(0, 25);

    // Set deck and discard count
    setPlayerRandomDeck(nextPlayer, nextPlayerDeckCount, &G);
    setPlayerRandomDiscard(nextPlayer, nextPlayerDiscardCount, &G);
    int drawCard1 = 0;
    int drawCard2 = 0;
    if (nextPlayerDeckCount > 0)
    {
        drawCard1 = G.deck[nextPlayer][G.deckCount[nextPlayer] - 1];
    }
    if (nextPlayerDeckCount > 1)
    {
        drawCard2 = G.deck[nextPlayer][G.deckCount[nextPlayer] - 2];
    }

    if (nextPlayerDeckCount == 0 && nextPlayerDiscardCount == 1)
    {
        drawCard1 = G.discard[nextPlayer][0];
    }
    int actionsBefore = G.numActions;
    int treasureBefore = G.coins;
    int handCountBefore = G.handCount[currentPlayer];
    printf("tributeEffect: drawCard1:%d ,drawCard2: %d, nextPlayerDeckCount: %d, nextPlayerDiscardCount: %d \n", drawCard1, drawCard2, nextPlayerDeckCount, nextPlayerDiscardCount);
    tributeEffect(&G, position);
    int actionsAfter = G.numActions;
    int treasureAfter = G.coins;
    int handCountAfter = G.handCount[currentPlayer];

    // Oracle
    int expectedAction = 0;
    int expectedTreasure = 0;
    int expectedCards = 0;
    // Only worth it the next oracles

    int doAssertions = 0;
    if (nextPlayerDeckCount >= 1)
    {
        if (cardIsAction(drawCard1))
        {
            expectedAction += 2;
        }
        if (cardIsTreasure(drawCard1))
        {
            expectedTreasure += 2;
        }
        if (cardIsVictory(drawCard1))
        {
            expectedCards += 2;
        }
        if (nextPlayerDeckCount > 1 && drawCard1 != drawCard2)
        {
            if (cardIsAction(drawCard2))
            {
                expectedAction += 2;
            }
            if (cardIsTreasure(drawCard2))
            {
                expectedTreasure += 2;
            }
            if (cardIsVictory(drawCard2))
            {
                expectedCards += 2;
            }
        }
        doAssertions = 1;
    }
    else if (nextPlayerDiscardCount == 1)
    {
        if (cardIsAction(drawCard1))
        {
            expectedAction += 2;
        }
        if (cardIsTreasure(drawCard1))
        {
            expectedTreasure += 2;
        }
        if (cardIsVictory(drawCard1))
        {
            expectedCards += 2;
        }
        doAssertions = 1;
    }

    if (doAssertions)
    {
        assert(actionsBefore + expectedAction - 1, actionsAfter, "Incorrect number of actions");
        assert(treasureBefore + expectedTreasure, treasureAfter, "Incorrect number of treasure");
        assert(handCountBefore - 1 + expectedCards, handCountAfter, "Incorrect number of cards in hand");
    }
}

int main()
{
    printf("Random test tributeEffect \n");
    srand(time(0));
    for (int i = 0; i < 1000; i++)
    {
        printf("Iteration %d \n", i);
        testTributeEffect();
    }
}
