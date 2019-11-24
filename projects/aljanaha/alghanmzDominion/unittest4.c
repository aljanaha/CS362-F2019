#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "unittest_helpers.h"
#include "dominion_helpers.h"
#include <string.h>

void revealsSameCard()
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
    int hand[5] = {tribute, copper, copper, copper, estate};
    setPlayerHand(currentPlayer, 5, hand, &G);
    int nextPlayer = nextTurn(&G);

    G.deck[nextPlayer][G.deckCount[nextPlayer] - 1] = tribute;
    G.deck[nextPlayer][G.deckCount[nextPlayer] - 2] = tribute;
    int actionsBefore = G.numActions;
    int treasureBefore = G.coins;
    int handCountBefore = G.handCount[currentPlayer];
    int tributeRevealedCards[2] = {-1, -1};
    doTribute(&G, currentPlayer, nextPlayer, tributeRevealedCards);
    int actionsAfter = G.numActions;
    int treasureAfter = G.coins;
    int handCountAfter = G.handCount[currentPlayer];
    assert(actionsBefore + 2, actionsAfter, "Incorrect number of actions");
    assert(treasureBefore, treasureAfter, "Incorrect number of treasure");
    assert(handCountBefore - 1, handCountAfter, "Incorrect number of cards in hand");
}

void lastPlayerPlays()
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
    int hand[5] = {tribute, copper, copper, copper, estate};
    setPlayerHand(currentPlayer, 5, hand, &G);
    int nextPlayer = nextTurn(&G);
    G.whoseTurn = nextPlayer;
    G.deck[currentPlayer][G.deckCount[currentPlayer] - 1] = village;
    G.deck[currentPlayer][G.deckCount[currentPlayer] - 1] = smithy;
    setPlayerHand(nextPlayer, 5, hand, &G);
    int actionsBefore = G.numActions;
    int tributeRevealedCards[2] = {-1, -1};
    doTribute(&G, currentPlayer, nextPlayer, tributeRevealedCards);
    int actionsAfter = G.numActions;
    assert(actionsBefore + 4, actionsAfter, "Incorrect number of actions");
}

void revealsDifferentCards()
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
    int hand[5] = {tribute, copper, copper, copper, estate};
    setPlayerHand(currentPlayer, 5, hand, &G);
    int nextPlayer = nextTurn(&G);

    G.deck[nextPlayer][G.deckCount[nextPlayer] - 1] = tribute;
    G.deck[nextPlayer][G.deckCount[nextPlayer] - 2] = copper;
    int actionsBefore = G.numActions;
    int treasureBefore = G.coins;
    int tributeRevealedCards[2] = {-1, -1};
    doTribute(&G, currentPlayer, nextPlayer, tributeRevealedCards);
    int handCountBefore = G.handCount[currentPlayer];
    int actionsAfter = G.numActions;
    int treasureAfter = G.coins;
    int handCountAfter = G.handCount[currentPlayer];
    assert(actionsBefore + 2, actionsAfter, "Incorrect number of actions");
    assert(treasureBefore + 2, treasureAfter, "Incorrect number of treasure");
    assert(handCountBefore - 1, handCountAfter, "Incorrect number of cards in hand");
}

void effectVictory()
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
    int hand[5] = {tribute, copper, copper, copper, estate};
    setPlayerHand(currentPlayer, 5, hand, &G);
    int nextPlayer = nextTurn(&G);

    G.deck[nextPlayer][G.deckCount[nextPlayer] - 1] = duchy;
    G.deck[nextPlayer][G.deckCount[nextPlayer] - 2] = estate;
    int actionsBefore = G.numActions;
    int treasureBefore = G.coins;
    int handCountBefore = G.handCount[currentPlayer];
    int tributeRevealedCards[2] = {-1, -1};
    doTribute(&G, currentPlayer, nextPlayer, tributeRevealedCards);
    int actionsAfter = G.numActions;
    int treasureAfter = G.coins;
    int handCountAfter = G.handCount[currentPlayer];
    assert(actionsBefore, actionsAfter, "Incorrect number of actions");
    assert(treasureBefore, treasureAfter, "Incorrect number of treasure");
    assert(handCountBefore + 3, handCountAfter, "Incorrect number of cards in hand");
}

void nextPlayerNotEnoughCards()
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
    int hand[5] = {tribute, copper, copper, copper, estate};
    setPlayerHand(currentPlayer, 5, hand, &G);
    int nextPlayer = nextTurn(&G);

    G.deck[nextPlayer][G.deckCount[nextPlayer] - 1] = copper;
    G.deckCount[nextPlayer] = 1;
    int actionsBefore = G.numActions;
    int treasureBefore = G.coins;
    int handCountBefore = G.handCount[currentPlayer];
    int tributeRevealedCards[2] = {-1, -1};
    doTribute(&G, currentPlayer, nextPlayer, tributeRevealedCards);
    int actionsAfter = G.numActions;
    int treasureAfter = G.coins;
    int handCountAfter = G.handCount[currentPlayer];
    assert(actionsBefore, actionsAfter, "Incorrect number of actions");
    assert(treasureBefore + 2, treasureAfter, "Incorrect number of treasure");
    assert(handCountBefore - 1, handCountAfter, "Incorrect number of cards in hand");
}

int main()
{
    printf(" Test tributeEffect \n");
    lastPlayerPlays();
    revealsDifferentCards();
    revealsSameCard();
    effectVictory();
    nextPlayerNotEnoughCards();
    return 0;
}