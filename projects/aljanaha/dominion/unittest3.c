#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "unittest_helpers.h"
#include "dominion_helpers.h"
#include <string.h>

void discardAmbassador()
{
    // Game instance
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, baron, smithy};

    initializeGame(2, k, 2, &G);
    int cardToDiscard = copper;

    // Set current player hand

    int currentPlayer = whoseTurn(&G);
    // Set player hand including estate
    int hand[5] = {ambassador, cardToDiscard, cardToDiscard, cardToDiscard, estate};
    setPlayerHand(currentPlayer, 5, hand, &G);

    int nextPlayer = nextTurn(&G);
    struct gameState gBefore;
    memcpy(&gBefore, &G, sizeof(struct gameState));
    int r = ambassadorEffect(&G, 0, 2, 0);

    assert(-1, r, "Ambassador should not have worked");
    assertOne(!unchangedPlayer(currentPlayer, &G, &gBefore), "player should not change");
    assertOne(!unchangedPlayer(nextPlayer, &G, &gBefore), "Next player should not change");
}

void incorrectDiscardCardscount()
{
    // Game instance
    struct gameState G;
    struct gameState gBefore;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, baron, smithy};

    initializeGame(2, k, 2, &G);
    int cardToDiscard = copper;

    // Set current player hand

    int currentPlayer = whoseTurn(&G);
    // Set player hand including estate
    int hand[5] = {ambassador, cardToDiscard, cardToDiscard, cardToDiscard, estate};
    setPlayerHand(currentPlayer, 5, hand, &G);

    int nextPlayer = nextTurn(&G);

    memcpy(&gBefore, &G, sizeof(struct gameState));
    int r = ambassadorEffect(&G, 1, -1, 0);

    assert(-1, r, "Ambassador should not have worked");
    assertOne(!unchangedPlayer(currentPlayer, &G, &gBefore), "player should not change");
    assertOne(!unchangedPlayer(nextPlayer, &G, &gBefore), "Next player should not change");

    memcpy(&gBefore, &G, sizeof(struct gameState));
    r = ambassadorEffect(&G, 1, 3, 0);
    assert(-1, r, "Ambassador should not have worked");
    assertOne(!unchangedPlayer(currentPlayer, &G, &gBefore), "player should not change");
    assertOne(!unchangedPlayer(nextPlayer, &G, &gBefore), "Next player should not change");

    int handNew[5] = {ambassador, cardToDiscard, silver, silver, estate};
    setPlayerHand(currentPlayer, 5, handNew, &G);
    memcpy(&gBefore, &G, sizeof(struct gameState));
    r = ambassadorEffect(&G, 1, 2, 0);
    assert(-1, r, "Ambassador should not have worked");
    assertOne(!unchangedPlayer(currentPlayer, &G, &gBefore), "player should not change");
    assertOne(!unchangedPlayer(nextPlayer, &G, &gBefore), "Next player should not change");
}

void testAmbassadorEffect()
{

    // Game instance
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, baron, smithy};

    initializeGame(2, k, 2, &G);
    int cardToDiscard = copper;

    // Set current player hand

    int currentPlayer = whoseTurn(&G);
    // Set player hand including estate
    int hand[5] = {ambassador, cardToDiscard, cardToDiscard, cardToDiscard, estate};
    setPlayerHand(currentPlayer, 5, hand, &G);

    int nextPlayer = nextTurn(&G);

    // Supply count before
    int supplyBefore = supplyCount(cardToDiscard, &G);
    // Next player
    int coppersPlayerTwoBefore = fullDeckCount(nextPlayer, cardToDiscard, &G);
    int r = ambassadorEffect(&G, 1, 2, 0);
    int expectedHand[3] = {cardToDiscard, estate};
    int supplyAfter = supplyCount(cardToDiscard, &G);
    int coppersPlayerAfter = fullDeckCount(nextPlayer, cardToDiscard, &G);
    assert(0, r, "Ambassador effect should have worked");
    assertOne(!compareArrays(expectedHand, G.hand[currentPlayer], 2, 2), "Hand is not the one expected");
    assert(supplyBefore + 2, supplyAfter+1, "Incorrect supply card count");
    assert(coppersPlayerTwoBefore + 1, coppersPlayerAfter, "Second player should have won 1 cards");
}

int main()
{
    printf(" Test ambassadorEffect \n");
    testAmbassadorEffect();
    discardAmbassador();
    incorrectDiscardCardscount();
    return 0;
}