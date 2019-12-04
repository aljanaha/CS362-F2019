#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "unittest_helpers.h"
#include "dominion_helpers.h"

void testTribute(int card1ToReveal, int card2ToReveal, int increaseTreasure)
{
    printf("\ttest tribute reveal cards \n");
    printf("\tCard to reveal %d, %d \n", card1ToReveal, card2ToReveal);
    // Game instance
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    initializeGame(2, k, 2, &G);

    // Set current player hand

    int currentPlayer = whoseTurn(&G);
    // Set player hand including estate
    int hand[5] = {tribute, copper, copper, copper, estate};
    G.coins = 3;
    setPlayerHand(currentPlayer, 5, hand, &G);
    int nextPlayer = nextTurn(&G);

    G.deck[nextPlayer][G.deckCount[nextPlayer] - 1] = card1ToReveal;
    G.deck[nextPlayer][G.deckCount[nextPlayer] - 2] = card2ToReveal;
    int treasureBefore = G.coins;
    int handPos = 0;
    playCard(handPos, 0, 0, 0, &G);
    int treasureAfter = G.coins;
    assert(treasureBefore + increaseTreasure, treasureAfter, "Incorrect number of treasure");
}

void tesBaron()
{
    printf("\ttest baron reveal cards \n");
    // Game instance
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    initializeGame(2, k, 2, &G);

    // Set current player hand

    int currentPlayer = whoseTurn(&G);
    // Set player hand including estate
    int hand[5] = {baron, copper, copper, copper, estate};
    G.coins = 3;
    setPlayerHand(currentPlayer, 5, hand, &G);
    int treasureBefore = G.coins;
    int handPos = 0;
    playCard(handPos, 1, 0, 0, &G);
    int treasureAfter = G.coins;
    assert(treasureBefore + 4, treasureAfter, "Incorrect number of treasure");
}

int main()
{
    printf("\n");
    printf("Testing bug #8\n");
    testTribute(copper, silver, 4);
    tesBaron();
    printf("\n");
}