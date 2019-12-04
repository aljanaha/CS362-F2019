#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "unittest_helpers.h"
#include "dominion_helpers.h"

void testAmbassador(int *cardsToDiscard, int numberCardsDiscard)
{
    printf("\ttest ambassador \n");

    // Game instance
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, ambassador, smithy};

    initializeGame(2, k, 2, &G);

    // Set current player hand

    int currentPlayer = whoseTurn(&G);
    // Set player hand including ambassador
    int hand[5] = {ambassador, copper, copper, copper, copper};
    for (int i = 0; i < numberCardsDiscard; i++)
    {
        hand[5 - i - 1] = cardsToDiscard[i];
    }
    setPlayerHand(currentPlayer, 5, hand, &G);
    int handPos = 0;
    int bonus = 0;
    int supplyCountBefore = G.supplyCount[cardsToDiscard[0]];
    int copiesBefore = fullDeckCount(currentPlayer, cardsToDiscard[0], &G);
    cardEffect(ambassador, 5, numberCardsDiscard, 0, &G, handPos, &bonus);
    int supplyCountAfter = G.supplyCount[cardsToDiscard[0]];
    int copiesAfter = fullDeckCount(currentPlayer, cardsToDiscard[0], &G);
    assert(supplyCountBefore + numberCardsDiscard - G.numPlayers, supplyCountAfter, "Incorrect number of cards in supply");
    assert(copiesBefore, copiesAfter + numberCardsDiscard, "Incorrect number of cards in player cards");
}

int main()
{
    printf("\n");
    printf("Testing bug #10\n");
    int cards1[2] = {copper, copper};
    int cardsSize1 = 2;
    testAmbassador(cards1, cardsSize1);

    int cards2[2] = {silver, silver};
    int cardsSize2 = 1;
    testAmbassador(cards2, cardsSize2);
    printf("\n");
}