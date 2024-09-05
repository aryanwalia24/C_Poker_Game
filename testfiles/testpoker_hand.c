#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../include/poker_hand.h"
#include "../include/card.h"

void test_createPokerHand()
{
    PokerHand *hand = createPokerHand();
    assert(hand != NULL);
    assert(hand->rank == HIGH_CARD);
    for (int i = 0; i < MAX_CARDS; i++)
    {
        assert(getCardValue(hand->cards[i]) == 0);
        assert(getCardSuit(hand->cards[i]) == 0);
    }
}

void test_evaluatePokerHand()
{
    Card playerCards[2] = {(mapSuitToNumber('H') << VALUE_BITS) | 2, (mapSuitToNumber('H') << VALUE_BITS) | 3};
    Card communityCards[5] = {
        (mapSuitToNumber('H') << VALUE_BITS) | 4,
        (mapSuitToNumber('H') << VALUE_BITS) | 5,
        (mapSuitToNumber('H') << VALUE_BITS) | 6,
        (mapSuitToNumber('H') << VALUE_BITS) | 7,
        (mapSuitToNumber('H') << VALUE_BITS) | 8};
    PokerHand optimalHand;

    evaluatePokerHand(playerCards, communityCards, &optimalHand);
    assert(optimalHand.rank == STRAIGHT_FLUSH);
}

void test_comparePokerHands()
{
    PokerHand hand1, hand2;

    hand1.rank = FULL_HOUSE;
    hand2.rank = FLUSH;
    assert(comparePokerHands(&hand1, &hand2) > 0);

    hand1.rank = PAIR;
    hand2.rank = PAIR;
    hand1.cards[0] = (mapSuitToNumber('H') << VALUE_BITS) | 10;
    hand2.cards[0] = (mapSuitToNumber('H') << VALUE_BITS) | 9;
    assert(comparePokerHands(&hand1, &hand2) > 0);

    hand1.cards[0] = (mapSuitToNumber('H') << VALUE_BITS) | 9;
    hand2.cards[0] = (mapSuitToNumber('H') << VALUE_BITS) | 9;
    assert(comparePokerHands(&hand1, &hand2) == 0);
}

void test_pokerHandToString()
{
    assert(strcmp(pokerHandToString(HIGH_CARD), "High Card") == 0);
    assert(strcmp(pokerHandToString(PAIR), "Pair") == 0);
    assert(strcmp(pokerHandToString(TWO_PAIR), "Two Pair") == 0);
    assert(strcmp(pokerHandToString(THREE_OF_A_KIND), "Three of a Kind") == 0);
    assert(strcmp(pokerHandToString(STRAIGHT), "Straight") == 0);
    assert(strcmp(pokerHandToString(FLUSH), "Flush") == 0);
    assert(strcmp(pokerHandToString(FULL_HOUSE), "Full House") == 0);
    assert(strcmp(pokerHandToString(FOUR_OF_A_KIND), "Four of a Kind") == 0);
    assert(strcmp(pokerHandToString(STRAIGHT_FLUSH), "Straight Flush") == 0);
    assert(strcmp(pokerHandToString(-1), "Unknown Hand") == 0);
}

int main()
{
    test_createPokerHand();
    test_pokerHandToString();

    printf("All tests passed!\n");
    return 0;
}