#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "unittest_helpers.h"
#include "dominion_helpers.h"

void testPositiveCase(int cardToTrash, int cardToWin)
{
    printf("\ttest remodel cost Positive\n");
    printf("\tCard to win %d card to trash %d \n", cardToWin, cardToTrash);
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, remodel, cutpurse,
                 sea_hag, baron, smithy};
    initializeGame(2, k, 2, &G);
    // Set current player hand
    int currentPlayer = whoseTurn(&G);
    // Set player hand including remodel
    int hand[5] = {remodel, cardToTrash, copper, copper, estate};
    setPlayerHand(currentPlayer, 5, hand, &G);
    int cardToTrashCountBefore = fullDeckCount(currentPlayer, cardToTrash, &G);
    int cardToGainCountBefore = fullDeckCount(currentPlayer, cardToWin, &G);
    int handPos = 0;
    int bonus = 0;
    int r = cardEffect(remodel, 1, cardToWin, 0, &G, handPos, &bonus);
    int cardToTrashCountAfter = fullDeckCount(currentPlayer, cardToTrash, &G);
    int cardToGainCountAfter = fullDeckCount(currentPlayer, cardToWin, &G);
    assert(0, r, "Should succeed");
    assert(cardToTrashCountBefore, cardToTrashCountAfter + 1, "Incorrect count in card to trash");
    assert(cardToGainCountBefore + 1, cardToGainCountAfter, "Incorrect count in card to gain");
}

void testNegativeCase(int cardToTrash, int cardToWin)
{
    printf("\ttest remodel cost negative\n");
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, remodel, cutpurse,
                 sea_hag, baron, smithy};
    initializeGame(2, k, 2, &G);
    // Set current player hand
    int currentPlayer = whoseTurn(&G);
    // Set player hand including remodel
    int hand[5] = {remodel, cardToTrash, copper, copper, estate};
    setPlayerHand(currentPlayer, 5, hand, &G);
    int cardToTrashCountBefore = fullDeckCount(currentPlayer, cardToTrash, &G);
    int cardToGainCountBefore = fullDeckCount(currentPlayer, cardToWin, &G);
    int handPos = 0;
    int bonus = 0;
    int r = cardEffect(remodel, 1, cardToWin, 0, &G, handPos, &bonus);
    int cardToTrashCountAfter = fullDeckCount(currentPlayer, cardToTrash, &G);
    int cardToGainCountAfter = fullDeckCount(currentPlayer, cardToWin, &G);
    assert(-1, r, "Should not succeed");
    assert(cardToTrashCountBefore, cardToTrashCountAfter, "card to trash should not change");
    assert(cardToGainCountAfter, cardToGainCountBefore, "card to gain should not change");
}

int main()
{
    printf("\n");
    printf("Testing bug #3\n");
    testPositiveCase(feast, council_room);
    testPositiveCase(ambassador, tribute);
    testNegativeCase(curse, gold);
    testNegativeCase(estate, duchy);
    printf("\n");
}