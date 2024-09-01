#include "../include/game.h"
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>

static int getValidInt(int min, int max, const char *prompt);
static int getValidBet(int wallet, const char *prompt);

void initializeGame(Player players[], int *numPlayers, Deck *deck)
{
    int playerCount = getValidInt(2, MAX_PLAYERS, "Enter the number of players (2-%d): ");
    *numPlayers = playerCount;

    char name[MAX_NAME_LENGTH];
    for (int i = 0; i < playerCount; i++)
    {
        printf("Enter name for player %d: ", i + 1);
        scanf("%s", name);
        if (createPlayer(i, name, START_MONEY, &players[i]) != 0)
        {
            printf("Error creating player. Try again.\n");
            i--;
        }
    }

    initializeDeck(deck);
    shuffleDeck(deck);
}

void startGame(Player players[], int numPlayers, Deck *deck)
{
    int continueGame = 1;
    while (continueGame)
    {
        continueGame = displayMenu();
        if (continueGame)
        {
            playRound(players, numPlayers, deck);
        }
    }
    printf("Game over. Thanks for playing!\n");
}

void playRound(Player players[], int numPlayers, Deck *deck)
{
    printf("\nStarting a new round...\n");
    shuffleDeck(deck);

    printf("Setting blinds...\n");
    setBlinds(players, numPlayers);

    printf("Dealing cards to players...\n");
    dealCards(players, numPlayers, deck);

    executeBettingRound(players, numPlayers);

    // Modes
    handleFlop(deck);
    executeBettingRound(players, numPlayers);

    handleTurn(deck);
    executeBettingRound(players, numPlayers);

    handleRiver(deck);
    executeBettingRound(players, numPlayers);

    determineWinner(players, numPlayers);
    printf("Round complete.\n");
}

int displayMenu()
{
    int choice;
    while (1)
    {
        printf("\n--- Texas Hold'em Poker ---\n");
        printf("1. Start a new round\n");
        printf("2. Exit game\n");
        printf("Choose an option: ");

        choice = getValidInt(1, 2, "");

        if (choice == 1)
            return 1; // Continue game
        else if (choice == 2)
            return 0; // Exit game
        else
            printf("Invalid choice. Please try again.\n");
    }
}

void setBlinds(Player players[], int numPlayers)
{
    if (numPlayers < 2)
    {
        printf("Not enough players to set blinds.\n");
        return;
    }

    //  first player is the small blind, and the next is the big blind
    int smallBlindIdx = 0;
    int bigBlindIdx = 1;

    updateWallet(&players[smallBlindIdx], -SMALL_BLIND);
    updateWallet(&players[bigBlindIdx], -BIG_BLIND);

    printf("%s pays the small blind of $%d\n", players[smallBlindIdx].name, SMALL_BLIND);
    printf("%s pays the big blind of $%d\n", players[bigBlindIdx].name, BIG_BLIND);
}

void dealCards(Player players[], int numPlayers, Deck *deck)
{
    for (int i = 0; i < numPlayers; i++)
    {
        printf("%s receives two cards.\n", players[i].name);
        drawCard(deck); // first card
        drawCard(deck); // second card
    }
}

void executeBettingRound(Player players[], int numPlayers)
{
    printf("Executing betting round...\n");
    for (int i = 0; i < numPlayers; i++)
    {
        if (players[i].wallet > 0)
        {
            int bet = getValidBet(players[i].wallet, "Enter bet amount (or 0 to check/fold): ");
            if (bet > 0)
            {
                updateWallet(&players[i], -bet);
                printf("%s bets $%d.\n", players[i].name, bet);
            }
        }
    }
}

// flop (reveal 3 community cards)
void handleFlop(Deck *deck)
{
    printf("Revealing the flop...\n");
    drawCard(deck); // Card 1
    drawCard(deck); // Card 2
    drawCard(deck); // Card 3
}

// turn (reveal 1 community card)
void handleTurn(Deck *deck)
{
    printf("Revealing the turn...\n");
    drawCard(deck);
}

// river (reveal 1 community card)
void handleRiver(Deck *deck)
{
    printf("Revealing the river...\n");
    drawCard(deck);
}

void determineWinner(Player players[], int numPlayers)
{
    if (numPlayers < 1)
    {
        printf("No players to determine a winner.\n");
        return;
    }

    Card communityCards[5];
    PokerHand bestHands[MAX_PLAYERS];

    for (int i = 0; i < numPlayers; i++)
    {
        evaluatePokerHand(players[i].hand, communityCards, &bestHands[i]);
    }

    int winnerIndex = 0;
    for (int i = 1; i < numPlayers; i++)
    {
        if (comparePokerHands(&bestHands[i], &bestHands[winnerIndex]) > 0)
        {
            winnerIndex = i;
        }
    }

    printf("The winner is %s with a %d!\n", players[winnerIndex].name, bestHands[winnerIndex].rank);
}

static int getValidInt(int min, int max, const char *prompt)
{
    char buffer[256];
    int value;

    while (1)
    {
        printf(prompt, max);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            char *ptr = buffer;
            int isValid = 1;
            while (*ptr != '\0' && *ptr != '\n')
            {
                if (!isdigit((unsigned char)*ptr))
                {
                    isValid = 0;
                    break;
                }
                ptr++;
            }

            if (isValid)
            {
                value = strtol(buffer, NULL, 10);
                if (value >= min && value <= max)
                {
                    return value;
                }
            }
            printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
        }
        else
        {
            printf("Error reading input. Please try again.\n");
        }
    }
}

static int getValidBet(int wallet, const char *prompt)
{
    char buffer[256];
    int bet;

    while (1)
    {
        printf(prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            char *ptr = buffer;
            int isValid = 1;
            while (*ptr != '\0' && *ptr != '\n')
            {
                if (!isdigit((unsigned char)*ptr))
                {
                    isValid = 0;
                    break;
                }
                ptr++;
            }

            if (isValid)
            {
                bet = strtol(buffer, NULL, 10);
                if (bet >= 0 && bet <= wallet)
                {
                    return bet;
                }
            }
            printf("Invalid bet. You must bet between 0 and %d.\n", wallet);
        }
        else
        {
            printf("Error reading input. Please try again.\n");
        }
    }
}
