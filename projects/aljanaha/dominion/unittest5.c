#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "unittest_helpers.h"
#include "dominion_helpers.h"
#include <string.h>

void correctEffect(int cardToDiscard, int cardToWin)
{
    // Game instance
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    initializeGame(2, k, 2, &G);

    // Set current player hand

    int currentPlayer = whoseTurn(&G);
    // Set player hand including estate
    int hand[5] = {mine, cardToDiscard, silver, gold, estate};
    setPlayerHand(currentPlayer, 5, hand, &G);

    int totalBeforeDiscard = fullDeckCount(currentPlayer, cardToDiscard, &G);
    int totalBeforeGain = fullDeckCount(currentPlayer, cardToWin, &G);
    int supplyBefore = supplyCount(cardToWin, &G);

    int r = mineEffect(&G, 1, cardToWin, 0);

    int totalAfterDiscard = fullDeckCount(currentPlayer, cardToDiscard, &G);
    int totalAfterGain = fullDeckCount(currentPlayer, cardToWin, &G);
    int supplyAfter = supplyCount(cardToWin, &G);

    assert(0, r, "Should have worked");
    assert(totalBeforeDiscard - 1, totalAfterDiscard, "Card should be trashed");
    assert(totalBeforeGain + 1, totalAfterGain, "Should win the desired treasure");
    assert(supplyBefore - 1, supplyAfter, "Incorrect number of cards in supply");

    int handAfter[3] = {silver, gold, estate};
    assertOne(!compareArrays(handAfter, G.hand[currentPlayer], 3, 3), "Hand is not the one expected");
}

void trashCopper()
{
    correctEffect(copper, silver);
}

void trashSilver()
{
    correctEffect(silver, gold);
}

void incorrectOptions(int cardToDiscard, int cardToWin)
{
    // Game instance
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    initializeGame(2, k, 2, &G);

    // Set current player hand

    int currentPlayer = whoseTurn(&G);
    // Set player hand including estate
    int hand[5] = {mine, cardToDiscard, silver, gold, estate};
    setPlayerHand(currentPlayer, 5, hand, &G);

    int totalBeforeDiscard = fullDeckCount(currentPlayer, cardToDiscard, &G);
    int totalBeforeGain = fullDeckCount(currentPlayer, cardToWin, &G);
    int supplyBefore = supplyCount(cardToWin, &G);

    int r = mineEffect(&G, 1, cardToWin, 0);

    int totalAfterDiscard = fullDeckCount(currentPlayer, cardToDiscard, &G);
    int totalAfterGain = fullDeckCount(currentPlayer, cardToWin, &G);
    int supplyAfter = supplyCount(cardToWin, &G);

    assert(-1, r, "Should have not worked");
    assert(totalBeforeDiscard, totalAfterDiscard, "Card should have not been trashed");
    assert(totalBeforeGain, totalAfterGain, "Should not win the desired treasure");
    assert(supplyBefore, supplyAfter, "Supply unchanged");
}

void incorrectCardsToWin()
{

    incorrectOptions(silver, adventurer);
    incorrectOptions(estate, silver);
}
void incorrectPriceGap()
{
    incorrectOptions(copper, gold);
}

int main()
{
    printf(" Test mineEffect \n");
    trashCopper();
    trashSilver();
    incorrectCardsToWin();
    incorrectPriceGap();

    return 0;
}