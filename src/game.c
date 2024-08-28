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
    // FUntions to add later 


    printf("\nStarting a new round...\n");
    shuffleDeck(deck);

    printf("Setting blinds...\n");
    // setBlinds(players, numPlayers);

    printf("Dealing cards to players...\n");
    // dealCards(players, numPlayers, deck);

    // executeBettingRound(players, numPlayers);

    // Modes
    // handleFlop(deck);
    // executeBettingRound(players, numPlayers);

    // handleTurn(deck);
    // executeBettingRound(players, numPlayers);

    // handleRiver(deck);
    // executeBettingRound(players, numPlayers);

    // determineWinner(players, numPlayers);
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


// INput Validators (handle failure conditions for input stream)
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
