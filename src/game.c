#include "../include/game.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

static int getValidIntGame(int min, int max, const char *prompt);
static int getValidBet(int wallet, const char *prompt);

void initializeGame(Player **players, int *playerCount, Deck *deck)
{
    srand(time(NULL));
    *playerCount = 2;
    *players = (Player *)malloc(*playerCount * sizeof(Player));
    if (*players == NULL)
    {
        fprintf(stderr, "Memory allocation failed for players.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *playerCount; i++)
    {
        printf("Enter name for player %d: ", i + 1);
        char name[MAX_NAME_LENGTH];
        if (fgets(name, MAX_NAME_LENGTH, stdin) != NULL)
        {
            size_t len = strlen(name);
            if (len > 0 && name[len - 1] == '\n')
            {
                name[len - 1] = '\0';
            }
            int startMoney = getValidIntGame(0, 10000, "Enter initial wallet balance: ");
            createPlayer(i + 1, name, startMoney, &(*players)[i]);

            char choice;
            printf("Do you want to generate a PIN for %s? (Y/N): ", (*players)[i].name);
            scanf(" %c", &choice);
            while (getchar() != '\n')
                ;
            if (choice == 'Y' || choice == 'y')
            {
                (*players)[i].pin = rand() % 9000 + 1000;
                printf("Player %d's PIN: %d\n", i + 1, (*players)[i].pin);

                printf("Press Enter to clear the PIN from the console...");
                while (getchar() != '\n')
                    ;
                clearConsole();
            }
        }
        else
        {
            fprintf(stderr, "Error reading player name.\n");
            exit(EXIT_FAILURE);
        }
    }

    initialiseDeck(deck);
    shuffleDeck(deck);
}

static int getValidIntGame(int min, int max, const char *prompt)
{
    int value;
    do
    {
        printf("%s", prompt);
        scanf("%d", &value);
        while (getchar() != '\n')
            ;
    } while (value < min || value > max);
    return value;
}

static int getValidBet(int wallet, const char *prompt)
{
    int bet;
    do
    {
        printf("%s", prompt);
        scanf("%d", &bet);
        while (getchar() != '\n')
            ;
        if (bet > wallet)
        {
            printf("Insufficient balance. You have $%d. Enter a smaller bet.\n", wallet);
        }
    } while (bet < 0 || bet > wallet);
    return bet;
}

void startGame(Player **players, int *playerCount, Deck *deck)
{
    int continueGame = 1;

    while (continueGame)
    {
        continueGame = displayMenu();
        if (continueGame)
        {
            initializeGame(players, playerCount, deck);
            playRound(*players, *playerCount, deck);
        }
    }
    printf("\n---------- Game over. Thanks for playing Poker! ----------\n");
    superCleanup(*players, *playerCount);
    free(*players);
}

void playRound(Player *players, int numPlayers, Deck *deck)
{
    printf("\n--------------- Starting A New Round -------------\n");
    printf("Setting Blinds \n\n");

    printf("---------------------- Blinds ------------------------\n");
    setBlinds(players, numPlayers);

    printf("\n-------------- Dealing Cards to Players ------------\n");
    dealCards(players, numPlayers, deck);

    Card communityCards[5] = {0};
    int pot = INITIAL_POT;
    printf("\nInitial pot amount: $%d\n", pot);

    for (int i = 0; i < numPlayers; i++)
    {
        printf("\n%s's turn:\n", players[i].name);
        char choice;
        printf("Do you want to see your cards? (Y/N): ");
        scanf(" %c", &choice);
        while (getchar() != '\n')
            ;
        if (choice == 'Y' || choice == 'y')
        {
            displayPlayerCards(&players[i], 1);
            printf("Press Enter to clear the console...");
            while (getchar() != '\n')
                ;
            clearConsole();
        }
        int bet = getValidBet(players[i].wallet, "Enter bet amount (or 0 to check/fold): ");
        if (bet > 0)
        {
            players[i].wallet -= bet;
            pot += bet;
            printf("%s bets $%d.\n", players[i].name, bet);
        }
        else
        {
            printf("%s checks/folds.\n", players[i].name);
        }
    }

    executeBettingRound(players, numPlayers, communityCards, &pot);

    printf("\n-------------- Revealing The FLOP -------------------\n");
    handleFlop(deck, communityCards);
    executeBettingRound(players, numPlayers, communityCards, &pot);

    printf("\n-------------- Revealing The TURN -------------------\n");
    handleTurn(deck, communityCards);
    executeBettingRound(players, numPlayers, communityCards, &pot);

    printf("\n-------------- Revealing The RIVER -------------------\n");
    handleRiver(deck, communityCards);
    executeBettingRound(players, numPlayers, communityCards, &pot);

    determineWinner(players, numPlayers, communityCards, &pot);
}

int displayMenu()
{
    int choice;
    while (1)
    {
        printf("\n------------------ Texas Hold'em Poker -------------\n\n");
        printf("1. Start a new round\n");
        printf("2. Exit game\n\n");
        printf("Choose an option: ");

        choice = getValidIntGame(1, 2, "");

        if (choice == 1)
        {
            return 1; // Start a new round
        }
        else if (choice == 2)
        {
            return 0; // Exit game
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }
    }
}

void setBlinds(Player *players, int numPlayers)
{
    if (numPlayers < 2)
    {
        printf("Not enough players to set blinds.\n");
        return;
    }
    printf("%s pays Small Blind: $%d\n", players[0].name, SMALL_BLIND);
    printf("%s pays Big Blind: $%d\n", players[1].name, BIG_BLIND);

    players[0].wallet -= SMALL_BLIND;
    players[1].wallet -= BIG_BLIND;
}

void dealCards(Player *players, int numPlayers, Deck *deck)
{
    if (numPlayers < 1)
    {
        printf("No players to deal cards to.\n");
        return;
    }

    printf("Dealing cards...\n");
    for (int i = 0; i < numPlayers; i++)
    {
        players[i].hand[0] = drawCard(deck);
        players[i].hand[1] = drawCard(deck);
    }
}

void displayPlayerCards(const Player *player, int display)
{
    if (display)
    {
        int enteredPin;
        printf("Enter PIN to display %s's cards: ", player->name);
        scanf("%d", &enteredPin);
        while (getchar() != '\n')
            ;
        if (enteredPin == player->pin)
        {
            printf("Your cards are:\n");
            printf("1. ");
            printCard(player->hand[0]);
            printf("2. ");
            printCard(player->hand[1]);
            printf("\n");
            printf("Press Enter to clear the console...");
            while (getchar() != '\n')
                ;
            clearConsole();
        }
        else
        {
            printf("Incorrect PIN. Cannot display cards.\n");
        }
    }
    else
    {
        printf("Player's cards are hidden.\n");
    }
}

void displayCommunityCards(const Card communityCards[], int numCards)
{
    printf("Community Cards: ");
    for (int i = 0; i < numCards; i++)
    {
        printCard(communityCards[i]);
        if (i < numCards - 1)
        {
            printf(", ");
        }
    }
    printf("\n");
}

void executeBettingRound(Player *players, int numPlayers, const Card communityCards[], int *pot)
{
    printf("\n------------ Betting Round ------------\n");
    for (int i = 0; i < numPlayers; i++)
    {
        printf("\n%s's turn:\n", players[i].name);
        char choice;
        printf("Do you want to see your cards? (Y/N): ");
        scanf(" %c", &choice);
        while (getchar() != '\n')
            ;

        if (choice == 'Y' || choice == 'y')
        {
            displayPlayerCards(&players[i], 1);
            printf("Press Enter to clear the console...");
            while (getchar() != '\n')
                ;
            clearConsole();

            printf("Do you want to see the community cards? (Y/N): ");
            scanf(" %c", &choice);
            while (getchar() != '\n')
                ;

            if (choice == 'Y' || choice == 'y')
            {
                displayCommunityCards(communityCards, 5);
                printf("Press Enter to clear the console...");
                while (getchar() != '\n')
                    ;
                clearConsole();
            }
        }

        int bet = getValidBet(players[i].wallet, "Enter bet amount (or 0 to check/fold): ");
        if (bet > 0)
        {
            players[i].wallet -= bet;
            *pot += bet;
            printf("%s bets $%d.\n", players[i].name, bet);
        }
        else
        {
            printf("%s checks/folds.\n", players[i].name);
        }
    }
}

void handleFlop(Deck *deck, Card communityCards[])
{
    printf("\nRevealing the flop...\n");
    for (int i = 0; i < 3; i++)
    {
        communityCards[i] = drawCard(deck);
    }
    displayCommunityCards(communityCards, 3);
}

void handleTurn(Deck *deck, Card communityCards[])
{
    printf("\nRevealing the turn...\n");
    communityCards[3] = drawCard(deck);
    displayCommunityCards(&communityCards[3], 1);
}

void handleRiver(Deck *deck, Card communityCards[])
{
    printf("\nRevealing the river...\n");
    communityCards[4] = drawCard(deck);
    displayCommunityCards(&communityCards[4], 1);
}

void determineWinner(Player *players, int numPlayers, const Card communityCards[], int *pot)
{
    if (numPlayers < 1)
    {
        printf("No players to determine a winner.\n");
        return;
    }

    PokerHand bestHands[MAX_PLAYERS];

    for (int i = 0; i < numPlayers; i++)
    {
        printf("Evaluating hand for player %d\n", i + 1);
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

    const char *handType = pokerHandToString(bestHands[winnerIndex].rank);
    players[winnerIndex].wallet += *pot;

    printf("\n------ The Winner is %s with %s and has won $%d! ------\n", players[winnerIndex].name, handType, *pot);

    printf("\n-------------- Game Statistics -------------\n");
    for (int i = 0; i < numPlayers; i++)
    {
        printf("%s's wallet balance: $%d\n", players[i].name, players[i].wallet);
        printf("%s's cards: \n", players[i].name);
        printCard(players[i].hand[0]);
        printCard(players[i].hand[1]);
        printf("\n");
    }
    printf("\nRound complete.\n");
}

void superCleanup(Player *players, int playerCount)
{
    for (int i = 0; i < playerCount; i++)
    {
        freePlayer(&players[i]);
    }
}