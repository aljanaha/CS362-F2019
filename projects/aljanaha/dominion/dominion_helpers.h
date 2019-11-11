#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state,
                int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3,
               struct gameState *state, int handPos, int *bonus);
int baronEffect(struct gameState *state, int choiceDiscardCard);
int minionEffect(struct gameState *state, int choiceGainCoins, int choiceDiscard, int handPos);
int ambassadorEffect(struct gameState *state, int cardToDiscard, int numberOfCardsToDiscard, int handPos);
int tributeEffect(struct gameState *state, int handPos);
int mineEffect(struct gameState *state, int treasureToTrash, int treasureToGain, int handPos);
int nextTurn(struct gameState *G);

#endif
