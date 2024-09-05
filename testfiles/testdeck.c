#include <assert.h>
#include <stdio.h>
#include "../include/deck.h"

void test_initialiseDeck()
{
    Deck deck;
    initialiseDeck(&deck);

    assert(deck.cards != NULL);
    assert(deck.inplay != NULL);
    assert(deck.top == 0);

    for (int i = 0; i < NUM_CARDS; i++)
    {
        assert(deck.inplay[i] == 0);
    }
    cleanupDeck(&deck);
}

void test_shuffleDeck()
{
    Deck deck;
    initialiseDeck(&deck);

    Card originalDeck[NUM_CARDS];
    for (int i = 0; i < NUM_CARDS; i++)
    {
        originalDeck[i] = deck.cards[i];
    }

    shuffleDeck(&deck);
    int isShuffled = 0;
    for (int i = 0; i < NUM_CARDS; i++)
    {
        if (deck.cards[i] != originalDeck[i])
        {
            isShuffled = 1;
            break;
        }
    }
    assert(isShuffled);
    cleanupDeck(&deck);
}

void test_drawCard()
{
    Deck deck;
    initialiseDeck(&deck);

    Card firstCard = deck.cards[0];
    Card drawnCard = drawCard(&deck);

    assert(drawnCard == firstCard);
    assert(deck.top == 1);
    assert(deck.inplay[0] == 1);

    cleanupDeck(&deck);
}

int main()
{
    test_initialiseDeck();
    test_shuffleDeck();
    test_drawCard();

    printf("All tests passed!\n");
    return 0;
}