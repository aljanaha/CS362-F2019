#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "unittest_helpers.h"
#include "dominion_helpers.h"

void testScore(int deckSize, int *deck, int handSize, int *hand, int discardSize, int *discard, int expectedScore)
{
    printf("\ttest score \n");
    printf("\ttest for %d score \n", expectedScore);
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, feast, cutpurse,
                 sea_hag, baron, smithy};
    initializeGame(2, k, 2, &G);
    // Set current player hand
    int currentPlayer = whoseTurn(&G);
    // Set player hand including feast

    setPlayerHand(currentPlayer, handSize, hand, &G);
    setPlayerDiscard(currentPlayer, discardSize, discard, &G);
    setPlayerDeck(currentPlayer, deckSize, deck, &G);
    int computedScore = scoreFor(currentPlayer, &G);
    assert(expectedScore, computedScore, "Incorrect expected score");
}

int main()
{
    printf("\n");
    printf("Testing bug #5\n");
    int deck1Size = 0;
    int deck1[0] = {};
    int hand1Size = 0;
    int hand1[0] = {};
    int discard1Size = 0;
    int discard1[0] = {};
    int expectedScore1 = 0;
    testScore(deck1Size, deck1, hand1Size, hand1, discard1Size, discard1, expectedScore1);

    int deck2Size = 5;
    int deck2[5] = {estate, duchy, province, curse, great_hall};
    int hand2Size = 0;
    int hand2[0] = {};
    int discard2Size = 0;
    int discard2[0] = {};
    int expectedScore2 = 10;
    testScore(deck2Size, deck2, hand2Size, hand2, discard2Size, discard2, expectedScore2);

    int deck3Size = 0;
    int deck3[0] = {};
    int hand3Size = 5;
    int hand3[5] = {estate, duchy, province, curse, great_hall};
    int discard3Size = 0;
    int discard3[0] = {};
    int expectedScore3 = 10;
    testScore(deck3Size, deck3, hand3Size, hand3, discard3Size, discard3, expectedScore3);

    int deck4Size = 0;
    int deck4[0] = {};
    int hand4Size = 0;
    int hand4[0] = {};
    int discard4Size = 5;
    int discard4[5] = {estate, duchy, province, curse, great_hall};
    int expectedScore4 = 10;
    testScore(deck4Size, deck4, hand4Size, hand4, discard4Size, discard4, expectedScore4);

    int deck5Size = 5;
    int deck5[5] = {estate, duchy, province, curse, great_hall};
    int hand5Size = 5;
    int hand5[5] = {estate, duchy, province, curse, great_hall};
    int discard5Size = 0;
    int discard5[0] = {};
    int expectedScore5 = 20;
    testScore(deck5Size, deck5, hand5Size, hand5, discard5Size, discard5, expectedScore5);
    printf("\n");
}