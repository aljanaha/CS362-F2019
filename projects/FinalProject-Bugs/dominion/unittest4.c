#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "unittest_helpers.h"
#include "dominion_helpers.h"

void testGameOverCardsPositive(int *cards, int cardsSize)
{
    printf("\ttest game over  positive\n");
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, remodel, cutpurse,
                 sea_hag, baron, smithy};
    int i = 0;

    initializeGame(2, k, 2, &G);
    // Set the supply count for the cards

    int gameOverBefore = isGameOver(&G);
    for (i = 0; i < cardsSize; i++)
    {
        setSupplyCount(&G, cards[i], 0);
    }
    int gameOverAfter = isGameOver(&G);
    assert(0, gameOverBefore, "Game should not be over at the begining");
    assert(1, gameOverAfter, "Game should be over");
}

void testGameOverCardsNegative(int *cards, int cardsSize)
{
    printf("\ttest  game over  negative\n");
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, remodel, cutpurse,
                 sea_hag, baron, smithy};
    int i = 0;

    initializeGame(2, k, 2, &G);
    // Set the supply count for the cards

    int gameOverBefore = isGameOver(&G);
    for (i = 0; i < cardsSize; i++)
    {
        setSupplyCount(&G, cards[i], 0);
    }
    int gameOverAfter = isGameOver(&G);
    assert(0, gameOverBefore, "Game should not be over at the begining");
    assert(0, gameOverAfter, "Game should not be over");
}

int main()
{
    printf("\n");
    printf("Testing bug #4\n");
    int positive1[3] = {salvager, sea_hag, treasure_map};
    testGameOverCardsPositive(positive1, 3);
    int positive2[3] = {curse, estate, duchy};
    testGameOverCardsPositive(positive2, 3);
    int negative1[2] = {salvager, sea_hag};
    testGameOverCardsNegative(negative1, 2);
    int negative2[1] = {curse};
    testGameOverCardsNegative(negative2, 1);
    printf("\n");
}