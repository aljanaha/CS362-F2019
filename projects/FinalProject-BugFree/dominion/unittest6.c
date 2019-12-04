#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "unittest_helpers.h"
#include "dominion_helpers.h"

void testPositiveCase(int cardToWin, int treasureToSet)
{
    printf("\ttest feast cost Positive\n");
    printf("\tCard to win %d \n", cardToWin);
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, feast, cutpurse,
                 sea_hag, baron, smithy};
    initializeGame(2, k, 2, &G);
    // Set current player hand
    int currentPlayer = whoseTurn(&G);
    // Set player hand including feast
    int hand[5] = {feast, copper, copper, copper, estate};
    setPlayerHand(currentPlayer, 5, hand, &G);
    G.supplyCount[cardToWin] = 1;
    int cardToGainCountBefore = fullDeckCount(currentPlayer, cardToWin, &G);
    int handPos = 0;
    int bonus = 0;
    // Se the treasure
    G.coins = treasureToSet;
    int r = cardEffect(feast, cardToWin, 0, 0, &G, handPos, &bonus);
    int cardToGainCountAfter = fullDeckCount(currentPlayer, cardToWin, &G);
    int treasureAfter = G.coins;
    assert(0, r, "Should succeed");
    assert(cardToGainCountBefore + 1, cardToGainCountAfter, "Incorrect count in card to gain");
    assert(treasureToSet, treasureAfter, "Treasure should not change");
}

void testNegativeCase(int cardToWin, int treasureToSet)
{
    printf("\ttest feast cost Positive\n");
    printf("\tCard to win %d \n", cardToWin);
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, feast, cutpurse,
                 sea_hag, baron, smithy};
    initializeGame(2, k, 2, &G);
    // Set current player hand
    int currentPlayer = whoseTurn(&G);
    // Set player hand including feast
    int hand[5] = {feast, copper, copper, copper, estate};
    setPlayerHand(currentPlayer, 5, hand, &G);
    int cardToGainCountBefore = fullDeckCount(currentPlayer, cardToWin, &G);
    int handPos = 0;
    int bonus = 0;
    // Se the treasure
    G.coins = treasureToSet;
    int r = cardEffect(feast, cardToWin, 0, 0, &G, handPos, &bonus);
    int cardToGainCountAfter = fullDeckCount(currentPlayer, cardToWin, &G);
    int treasureAfter = G.coins;
    assert(-1, r, "Should not succeed");
    assert(cardToGainCountBefore, cardToGainCountAfter, "Should not change the card to gain");
    assert(treasureToSet, treasureAfter, "Treasure should not change");
}

int main()
{
    printf("\n");
    printf("Testing bug #6\n");
    testPositiveCase(mine, 0);
    testPositiveCase(duchy, 0);
    testNegativeCase(gold, 1);
    testNegativeCase(province, 2);
    printf("\n");
}