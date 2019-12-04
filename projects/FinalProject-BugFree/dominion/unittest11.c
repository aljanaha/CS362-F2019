#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "unittest_helpers.h"
#include "dominion_helpers.h"
#include <string.h>

void testMinion(int choice1, int choice2)
{
    printf("\ttest minion \n");
    printf("\tchoice 1 %d, choice2 %d \n", choice1, choice2);
    // Game instance
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    initializeGame(2, k, 2, &G);

    // Set current player hand

    int currentPlayer = whoseTurn(&G);
    // Set player hand including minion
    int hand[5] = {minion, copper, copper, copper, copper};
    int handPos = 0;
    int bonus = 0;
    setPlayerHand(currentPlayer, 5, hand, &G);
    struct gameState gBefore;
    memcpy(&gBefore, &G, sizeof(struct gameState));
    int treasureBefore = G.coins;
    int handCountBefore = G.handCount[currentPlayer];
    int discardCountBefore = G.discardCount[currentPlayer];
    int deckCountBefore = G.deckCount[currentPlayer];
    int r = cardEffect(minion, choice1, choice2, 0, &G, handPos, &bonus);
    int treasureAfter = G.coins;
    int handCountAfter = G.handCount[currentPlayer];
    int discardCountAfter = G.discardCount[currentPlayer];
    int deckCountAfter = G.deckCount[currentPlayer];
    if (choice1 && choice2)
    {
        assert(-1, r, "Should not work");
        assertOne(unchangedPlayer(currentPlayer, &G, &gBefore), "player should not change");
    }
    else if (choice1)
    {
        assert(treasureBefore + 2, treasureAfter, "Treasure is incorrect");
        assert(handCountBefore - 1, handCountAfter, "Treasure is incorrect");
        assert(deckCountBefore, deckCountAfter, "Incorrect deck count");
    }
    else if (choice2)
    {
        assert(treasureBefore, treasureAfter, "Treasure is incorrect");
        assert(4, handCountAfter, "Incorrect hand count");
        assert(discardCountBefore + handCountBefore, discardCountAfter, "Incorrect discard count");
        assert(deckCountBefore - 4, deckCountAfter, "Incorrect deck count");
    }
}

int main()
{
    printf("\n");
    printf("Testing bug #11\n");
    testMinion(1, 1);
    testMinion(0, 1);
    testMinion(1, 0);
    printf("\n");
}