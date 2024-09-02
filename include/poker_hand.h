#ifndef POKER_HAND_H
#define POKER_HAND_H

#include "card.h"

typedef enum
{
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH
} HandRank;

typedef struct
{
    HandRank rank;
    Card cards[5];
} PokerHand;

// Function Prototypes
void evaluatePokerHand(Card playerCards[], Card communityCards[], PokerHand *bestHand);
int comparePokerHands(const PokerHand *hand1, const PokerHand *hand2);
const char *pokerHandToString(HandRank rank);

#endif // POKER_HAND_H
