#include "dominion.h"
#include <stdio.h>
#include <string.h>
#include "rngs.h"
#include <stdlib.h>
#include "unittest_helpers.h"
#include "dominion_helpers.h"

void testGainTreasure()
{
    // Game instance
    struct gameState G;
    // Cards to play, includes minion
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, baron, smithy};

    initializeGame(2, k, 2, &G);

    // Set current player hand

    int currentPlayer = whoseTurn(&G);
    // Set player hand including minion
    int hand[5] = {minion, copper, copper, copper, estate};
    setPlayerHand(currentPlayer, 5, hand, &G);
    // Set next player hand
    int nextPlayer = nextTurn(&G);
    int handNext[5] = {copper, copper, copper, copper, copper};
    setPlayerHand(nextPlayer, 5, handNext, &G);

    int treasureBefore = G.coins;
    doMinion(1, 0, &G, 0, currentPlayer);
    int treasureAfter = G.coins;
    // The increased treasure should be 2
    assert(treasureBefore + 2, treasureAfter, "Incorrect increase in treasure");
}

void testDiscardHand()
{
    // Game instance
    struct gameState G;
    // Cards to play, includes minion
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, baron, smithy};

    initializeGame(2, k, 2, &G);

    // Set current player hand

    int currentPlayer = whoseTurn(&G);
    // Set player hand including minion
    int hand[5] = {minion, copper, copper, copper, estate};
    setPlayerHand(currentPlayer, 5, hand, &G);
    // Set next player hand
    int nextPlayer = nextTurn(&G);
    int handNext[5] = {copper, copper, copper, copper, copper};
    setPlayerHand(nextPlayer, 5, handNext, &G);

    struct gameState gBefore;
    memcpy(&gBefore, &G, sizeof(struct gameState));
    doMinion(0, 1, &G, 0, currentPlayer);
    // All cards in hands before minion should be in the discard pile of each player
    assert(gBefore.discardCount[currentPlayer] + gBefore.handCount[currentPlayer], G.discardCount[currentPlayer], "Discard pile incorrect for current player");
    assert(gBefore.discardCount[nextPlayer] + gBefore.handCount[nextPlayer], G.discardCount[nextPlayer], "Discard pile for next player is incorrect");
    // Both player should have only 4 cards in hand
    assert(4, G.handCount[currentPlayer], "Incorrect hand count for current player");
    assert(4, G.handCount[nextPlayer], "Incorrect hand count for next player");
}

void testDiscardHandOnlyPlayer()
{
    // Game instance
    struct gameState G;
    // Cards to play, includes minion
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, baron, smithy};

    initializeGame(2, k, 2, &G);

    // Set current player hand

    int currentPlayer = whoseTurn(&G);
    // Set player hand including minion
    int hand[3] = {minion, copper, copper};
    setPlayerHand(currentPlayer, 3, hand, &G);
    // Set next player hand
    int nextPlayer = nextTurn(&G);
    int handNext[4] = {copper, copper, copper, copper};
    setPlayerHand(nextPlayer, 3, handNext, &G);

    struct gameState gBefore;
    memcpy(&gBefore, &G, sizeof(struct gameState));
    doMinion(0, 1, &G, 0, currentPlayer);
    // The discard pile should have all the cards from the hand
    assert(gBefore.discardCount[currentPlayer] + gBefore.handCount[currentPlayer], G.discardCount[currentPlayer], "Discard pile incorrect for current player");
    // Player should have 4 cards in its hand
    assert(4, G.handCount[currentPlayer], "Incorrect hand count for current player");
    // The next player should be unaffected
    assertOne(!unchangedPlayer(nextPlayer, &G, &gBefore), "Next player should not change");
}

int main()
{
    printf(" Test doMinion \n");
    testGainTreasure();
    testDiscardHand();
    testDiscardHandOnlyPlayer();
    return 0;
}