#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../include/card.h"

void test_mapNumberToSuit()
{
    assert(mapNumberToSuit(0) == 'H');
    assert(mapNumberToSuit(1) == 'D');
    assert(mapNumberToSuit(2) == 'C');
    assert(mapNumberToSuit(3) == 'S');
    assert(mapNumberToSuit(4) == 'H'); // Invalid input, should default to 'H'
}

void test_mapSuitToNumber()
{
    assert(mapSuitToNumber('H') == 0);
    assert(mapSuitToNumber('D') == 1);
    assert(mapSuitToNumber('C') == 2);
    assert(mapSuitToNumber('S') == 3);
    assert(mapSuitToNumber('X') == 0); // Invalid input, should default to 0
}

void test_parseCardInput()
{
    Card card;
    char input1[] = "H4";
    parseCardInput(input1, 1, &card);
    assert(getCardValue(card) == 4);
    assert(getCardSuit(card) == 0);

    char input2[] = "2 13";
    parseCardInput(input2, 2, &card);
    assert(getCardValue(card) == 13);
    assert(getCardSuit(card) == 1);

    char input3[] = "S1";
    parseCardInput(input3, 1, &card);
    assert(getCardValue(card) == 1);
    assert(getCardSuit(card) == 3);

    char input4[] = "3 7";
    parseCardInput(input4, 2, &card);
    assert(getCardValue(card) == 7);
    assert(getCardSuit(card) == 2);
}

void test_getCardValue()
{
    Card card = (1 << VALUE_BITS) | 4;
    assert(getCardValue(card) == 4);
}

void test_getCardSuit()
{
    Card card = (1 << VALUE_BITS) | 4;
    assert(getCardSuit(card) == 1);
}

void test_printCard()
{
    Card card = (1 << VALUE_BITS) | 4;
    printf("Expected: Four of Diamonds\n");
    printf("Actual: ");
    printCard(card);
}

int main()
{
    test_mapNumberToSuit();
    test_mapSuitToNumber();
    test_parseCardInput();
    test_getCardValue();
    test_getCardSuit();
    test_printCard();

    printf("All tests passed!\n");
    return 0;
}