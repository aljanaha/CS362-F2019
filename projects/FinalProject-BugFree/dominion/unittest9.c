#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "unittest_helpers.h"
#include "dominion_helpers.h"

void revealCards(int card1ToReveal, int card2ToReveal, int increaseHand, int increaseActions, int increaseTreasure)
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
    setPlayerHand(currentPlayer, 5, hand, &G);
    int nextPlayer = nextTurn(&G);

    G.deck[nextPlayer][G.deckCount[nextPlayer] - 1] = card1ToReveal;
    G.deck[nextPlayer][G.deckCount[nextPlayer] - 2] = card2ToReveal;
    int actionsBefore = G.numActions;
    int handCountBefore = G.handCount[currentPlayer];
    int handPos = 0;
    int bonus = 0;
    cardEffect(tribute, 0, 0, 0, &G, handPos, &bonus);
    int actionsAfter = G.numActions;
    int handCountAfter = G.handCount[currentPlayer];

    assert(actionsBefore + increaseActions, actionsAfter, "Incorrect number of actions");
    assert(increaseTreasure, bonus, "Incorrect number of treasure");
    assert(handCountBefore + increaseHand - 1, handCountAfter, "Incorrect number of cards in hand");
}

int main()
{
    printf("\n");
    printf("Testing bug #9\n");
    revealCards(copper, copper, 0, 0, 2);
    revealCards(baron, baron, 0, 2, 0);
    revealCards(duchy, duchy, 2, 0, 0);
    printf("\n");
}