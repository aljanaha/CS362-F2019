#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "unittest_helpers.h"
#include "dominion_helpers.h"

void testGainEstate()
{
    // Game instance
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, baron, smithy};

    initializeGame(2, k, 2, &G);

    // Set current player hand

    int currentPlayer = whoseTurn(&G);
    // Set player hand including treasure
    int hand[5] = {baron, copper, copper, copper, estate};
    setPlayerHand(currentPlayer, 5, hand, &G);

    int estatesBefore = fullDeckCount(currentPlayer, estate, &G);
    baronEffect(&G, 0);
    int estatesAfter = fullDeckCount(currentPlayer, estate, &G);
    assert(estatesBefore + 1, estatesAfter, "Incorrect increase in treasure");
}

void testBaronDiscardingNotHaving()
{
    // Game instance
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, baron, smithy};

    initializeGame(2, k, 2, &G);

    // Set current player hand

    int currentPlayer = whoseTurn(&G);
    // Set player hand not including treasure
    int hand[5] = {baron, copper, copper, copper, copper};
    setPlayerHand(currentPlayer, 5, hand, &G);
    // THe bug is commented as it makes the program run forever. But if not commented it gets stuck
    int estatesBefore = fullDeckCount(currentPlayer, estate, &G);
    int treasureBefore = G.coins;
    int r = baronEffect(&G, 1);
    int treasureAfter = G.coins;
    int estatesAfter = fullDeckCount(currentPlayer, estate, &G);
    assert(0, r, "Baron should not work");
    assert(estatesBefore+1, estatesAfter, "Should not change estates");
    assert(treasureBefore, treasureAfter, "Should not increase treasure");
}

void testBaronDiscardingHaving()
{
    // Game instance
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, baron, smithy};

    initializeGame(2, k, 2, &G);

    // Set current player hand

    int currentPlayer = whoseTurn(&G);
    // Set player hand including estate
    int hand[5] = {baron, copper, copper, copper, estate};
    setPlayerHand(currentPlayer, 5, hand, &G);

    int treasureBefore = G.coins;
    int discardedBefore = G.discardCount[currentPlayer];
    baronEffect(&G, 1);
    int treasureAfter = G.coins;
    int discardedAfter = G.discardCount[currentPlayer];
    assert(treasureBefore + 4, treasureAfter, "Incorrect increase in treasure");
    assert(discardedBefore + 2, discardedAfter, "Incorrect count in the discarded pile");
}

int main()
{
    printf(" Test baronEffect \n");
    // testBaronDiscardingNotHaving();
    // testBaronDiscardingHaving();
    testGainEstate();
    return 0;
}