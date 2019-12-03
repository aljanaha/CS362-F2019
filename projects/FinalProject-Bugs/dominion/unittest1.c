#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "unittest_helpers.h"
#include "dominion_helpers.h"

void testMineTrashing()
{
    printf("\ttestMineTrashing\n");
    struct gameState G;
    // Cards to play
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, baron, smithy};

    initializeGame(2, k, 2, &G);

    // Set current player hand

    int currentPlayer = whoseTurn(&G);
    // Set player hand including treasure
    int cardToTrash = copper;
    int hand[5] = {mine, cardToTrash, copper, copper, estate};
    setPlayerHand(currentPlayer, 5, hand, &G);
    int cardToTrashCountBefore = fullDeckCount(currentPlayer, estate, &G);
    int handPos = 0;
    int bonus = 0;
    cardEffect(mine, 1, silver, 0, &G, handPos, &bonus);
    int cardToTrashCountAfter = fullDeckCount(currentPlayer, estate, &G);
    assert(cardToTrashCountBefore, cardToTrashCountAfter + 1, "Incorrect decrease in card to trash");
}

void testTributeTrashing()
{
    printf("\ttestTributeTrashing\n");
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
    int card1ToReveal = tribute;
    int card2ToReveal = copper;
    G.deck[nextPlayer][G.deckCount[nextPlayer] - 1] = card1ToReveal;
    G.deck[nextPlayer][G.deckCount[nextPlayer] - 2] = card2ToReveal;

    int card1ToRevealCountBefore = fullDeckCount(nextPlayer, card1ToReveal, &G);
    int card2ToRevealCountBefore = fullDeckCount(nextPlayer, card2ToReveal, &G);
    int handPos = 0;
    int bonus = 0;
    int r = cardEffect(tribute, 0, 0, 0, &G, handPos, &bonus);

    int card1ToRevealCountAfter = fullDeckCount(nextPlayer, card1ToReveal, &G);
    int card2ToRevealCountAfter = fullDeckCount(nextPlayer, card2ToReveal, &G);

    assert(0, r, "Tribute effect should have worked");
    assert(card1ToRevealCountAfter + 1, card1ToRevealCountBefore, "Card 1 should have been trashed");
    assert(card2ToRevealCountAfter + 1, card2ToRevealCountBefore, "Card 2 should have been trashed");
}

int main()
{
    printf("\n");
    printf("Testing bug #1\n");
    testMineTrashing();
    testTributeTrashing();
    printf("\n");
}