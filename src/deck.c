#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/deck.h"

#define VALUE_BITS 4
#define VALUE_MASK 0xF
#define SUIT_BITS 2
#define SUIT_MASK 0x30

void initialiseDeck(Deck *deck)
{
    // initialising array of size 52 (cards) , calloc for setting intial bits to 0
    deck->cards = (Card *)calloc(NUM_CARDS, sizeof(Card));
    deck->inplay = (int *)calloc(NUM_CARDS, sizeof(int));
    if (deck->cards == NULL || deck->inplay == NULL)
    {
        fprintf(stderr, "Memory allocation failed for deck. Trying again...\n");
        if (deck->cards != NULL)
        {
            free(deck->cards);
        }
        if (deck->inplay != NULL)
        {
            free(deck->inplay);
        }
        return;
    }

    // Setting card values & suits in deck (Values 0-12 => 1-13 ,Suit 0-3 => 1-4)
    int idx = 0;
    for (unsigned int suit = 0; suit < 4; suit++)
    {
        for (unsigned int val = 1; val <= 13; val++)
        {
            deck->cards[idx] = ((suit << VALUE_BITS) & SUIT_MASK) | (val & VALUE_MASK);
            deck->inplay[idx] = 0;
            idx++;
        }
    }
    deck->top = 0;
}

// fisher-yates algorithm
void shuffleDeck(Deck *deck)
{
    srand((unsigned int)time(NULL));

    for (int i = NUM_CARDS - 1; i >= 1; i--)
    {
        int j = rand() % (i + 1); // Random index range [0, i]
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

Card drawCard(Deck *deck)
{
    if (deck->cards == NULL)
    {
        printf("Deck is not initialized. Please initialize the deck first.\n");
        return 0;
    }
    if (deck->top >= NUM_CARDS)
    {
        printf("All cards have been drawn.\n");
        return 0;
    }

    // drawing random card from the deck top ( shuffled index 0)
    Card currCard = deck->cards[deck->top];
    deck->inplay[deck->top] = 1;
    deck->top++;

    return currCard;
}

/* Memory Cleanup */
void cleanupDeck(Deck *deck)
{
    if (deck->cards != NULL)
    {
        free(deck->cards);
    }
    if (deck->inplay != NULL)
    {
        free(deck->inplay);
    }
}