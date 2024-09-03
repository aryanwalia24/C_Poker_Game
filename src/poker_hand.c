#include "../include/poker_hand.h"
#include <stdlib.h>
#include <string.h>

PokerHand *hands = NULL;
int numHands = 0;

static int checkFlush(const Card cards[], int numCards);
static int checkStraight(const Card cards[], int numCards);
static void getRankFrequencies(const Card cards[], int numCards, int rankFrequencies[]);
static int compareRanks(const void *a, const void *b);

PokerHand *createPokerHand()
{
    static PokerHand hand;
    hand.rank = HIGH_CARD;
    memset(hand.cards, 0, MAX_CARDS * sizeof(Card));
    return &hand;
}

void evaluatePokerHand(Card playerCards[], const Card communityCards[], PokerHand *optimalHand)
{
    Card combined[7]; // 2 player cards + 5 community cards

    memcpy(combined, playerCards, 2 * sizeof(Card));
    memcpy(combined + 2, communityCards, 5 * sizeof(Card));

    // Sorting cards by rank
    qsort(combined, 7, sizeof(Card), compareRanks);

    int rankFrequencies[13] = {0};
    int flush = checkFlush(combined, 7);
    int straight = checkStraight(combined, 7);
    int fourCount = 0, threeCount = 0, pairCount = 0;

    getRankFrequencies(combined, 7, rankFrequencies);
    for (int i = 0; i < 13; i++)
    {
        if (rankFrequencies[i] == 4)
            fourCount = 1;
        if (rankFrequencies[i] == 3)
            threeCount = 1;
        if (rankFrequencies[i] == 2)
            pairCount++;
    }

    // Determine the best possible hand
    if (straight && flush)
    {
        optimalHand->rank = STRAIGHT_FLUSH;
    }
    else if (fourCount)
    {
        optimalHand->rank = FOUR_OF_A_KIND;
    }
    else if (threeCount && pairCount > 0)
    {
        optimalHand->rank = FULL_HOUSE;
    }
    else if (flush)
    {
        optimalHand->rank = FLUSH;
    }
    else if (straight)
    {
        optimalHand->rank = STRAIGHT;
    }
    else if (threeCount)
    {
        optimalHand->rank = THREE_OF_A_KIND;
    }
    else if (pairCount > 1)
    {
        optimalHand->rank = TWO_PAIR;
    }
    else if (pairCount == 1)
    {
        optimalHand->rank = PAIR;
    }
    else
    {
        optimalHand->rank = HIGH_CARD;
    }

    memcpy(optimalHand->cards, combined, MAX_CARDS * sizeof(Card));
}

int comparePokerHands(const PokerHand *hand1, const PokerHand *hand2)
{
    if (hand1->rank > hand2->rank)
        return 1;
    if (hand1->rank < hand2->rank)
        return -1;

    // Same rank, compare values
    for (int i = 0; i < MAX_CARDS; i++)
    {
        if (getCardValue(hand1->cards[i]) > getCardValue(hand2->cards[i]))
            return 1;
        if (getCardValue(hand1->cards[i]) < getCardValue(hand2->cards[i]))
            return -1;
    }

    return 0; // Equal
}

static int checkFlush(const Card cards[], int numCards)
{
    int suits[4] = {0}; // Hearts, Diamonds, Clubs, Spades
    for (int i = 0; i < numCards; i++)
    {
        suits[getCardSuit(cards[i])]++;
    }
    for (int i = 0; i < 4; i++)
    {
        if (suits[i] >= 5)
        {
            return 1;
        }
    }
    return 0;
}

static int checkStraight(const Card cards[], int numCards)
{
    int seqCount = 1;
    for (int i = 1; i < numCards; i++)
    {
        if (getCardValue(cards[i]) == getCardValue(cards[i - 1]) + 1)
        {
            seqCount++;
            if (seqCount >= 5)
                return 1;
        }
        else if (getCardValue(cards[i]) != getCardValue(cards[i - 1]))
        {
            seqCount = 1;
        }
    }
    return 0;
}

static void getRankFrequencies(const Card cards[], int numCards, int rankFrequencies[])
{
    for (int i = 0; i < numCards; i++)
    {
        rankFrequencies[getCardValue(cards[i]) - 1]++;
    }
}

static int compareRanks(const void *a, const void *b)
{
    return getCardValue(*(Card *)b) - getCardValue(*(Card *)a);
}

const char *pokerHandToString(int rank)
{
    switch (rank)
    {
    case HIGH_CARD:
        return "High Card";
    case PAIR:
        return "Pair";
    case TWO_PAIR:
        return "Two Pair";
    case THREE_OF_A_KIND:
        return "Three of a Kind";
    case STRAIGHT:
        return "Straight";
    case FLUSH:
        return "Flush";
    case FULL_HOUSE:
        return "Full House";
    case FOUR_OF_A_KIND:
        return "Four of a Kind";
    case STRAIGHT_FLUSH:
        return "Straight Flush";
    default:
        return "Unknown Hand";
    }
}
