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
        return;
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
            int startMoney = getValidIntGame(20, 10000, "Enter initial wallet balance: ");
            createPlayer(i + 1, name, startMoney, &(*players)[i]);

            char choice;
            do
            {
                printf("Generate a PIN for %s? (Y/N): ", (*players)[i].name);
                scanf(" %c", &choice);
                while (getchar() != '\n')
                    ;
                if (choice == 'Y' || choice == 'y')
                {
                    (*players)[i].pin = rand() % 9000 + 1000;
                    printf("Player %d's PIN: %d\n\n", i + 1, (*players)[i].pin);

                    printf("Press Enter to clear the PIN from the console...");
                    while (getchar() != '\n')
                        ;
                    clearConsole();
                }
                else
                {
                    (*players)[i].pin = rand() % 9000 + 1000; // setting random pin
                    printf("\nPIN not generated for %s. Cannot view cards Afterwards\n", (*players)[i].name);
                }
            } while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
        }
        else
        {
            fprintf(stderr, "Error reading player name.\n");
            return;
        }
    }

    initialiseDeck(deck);
    shuffleDeck(deck);
}

static int getValidIntGame(int min, int max, const char *prompt)
{
    int value;
    int result;
    do
    {
        printf("%s", prompt);
        result = scanf("%d", &value);
        while (getchar() != '\n')
            ;

        if (result != 1 || value < min || value > max)
        {
            printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
        }
    } while (result != 1 || value < min || value > max);

    return value;
}

static int getValidBet(int wallet, const char *prompt)
{
    int bet;
    int result;
    do
    {
        printf("%s", prompt);
        result = scanf("%d", &bet);
        while (getchar() != '\n')
            ;

        if (result != 1 || bet < 0 || bet > wallet)
        {
            printf("Invalid input. Please enter a bet between 0 and your wallet balance of $%d.\n", wallet);
        }
    } while (result != 1 || bet < 0 || bet > wallet);

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
    printf("\n-------- Game over. Thanks for playing Poker! ---------\n\n");
    superCleanup(*players, *playerCount); // all players
    free(*players);                       // player array
}

void playRound(Player *players, int numPlayers, Deck *deck)
{
    printf("\n--------------- Starting A New Round -------------\n\n");
    printf("Setting Blinds.... \n\n");

    printf("-------------------- Blinds ----------------------\n\n");
    setBlinds(players, numPlayers);

    printf("\n-------------- Dealing Cards to Players ------------\n\n");
    dealCards(players, numPlayers, deck);

    Card *communityCards = (Card *)calloc(5, sizeof(Card));
    for (int i = 0; i < 3; i++)
    {
        communityCards[i] = (Card)drawCard(deck);
    }
    int pot = INITIAL_POT;
    printf("\n-----  Initial pot amount: $%d -----\n", pot);
    executeBettingRound(players, numPlayers, communityCards, &pot);

    printf("\n------------ Revealing The FLOP --------------\n");
    handleFlop(deck, communityCards);
    executeBettingRound(players, numPlayers, communityCards, &pot);

    printf("\n------------- Revealing The TURN --------------\n");
    handleTurn(deck, communityCards);
    executeBettingRound(players, numPlayers, communityCards, &pot);

    printf("\n------------- Revealing The RIVER --------------\n");
    handleRiver(deck, communityCards);
    executeBettingRound(players, numPlayers, communityCards, &pot);

    determineWinner(players, numPlayers, communityCards, &pot);
}

int displayMenu()
{
    int choice;
    while (1)
    {
        printf("\n----------------- Texas Hold'em Poker -----------------\n\n");
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
        if (players[i].hand == NULL)
        {
            players[i].hand = (Card *)calloc(HAND_SIZE, sizeof(Card));
        }
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
            printCard(player->hand[0]);
            printCard(player->hand[1]);
            printf("\n");
            printf("Press Enter to clear the console...");
            while (getchar() != '\n')
                ;
            clearConsole();
        }
        else
        {
            printf("Invalid PIN. Press Enter to continue .\n");
            while (getchar() != '\n')
                ;
        }
    }
    else
    {
        printf("Player's cards are hidden.\n");
    }
}

void displayCommunityCards(const Card communityCards[], int numCards)
{
    printf("\nCommunity Cards: \n");
    for (int i = 0; i < numCards; i++)
    {
        printCard(communityCards[i]);
    }
    printf("\n");
}

void executeBettingRound(Player *players, int numPlayers, const Card communityCards[], int *pot)
{
    printf("\n---------------- Betting Round ----------------\n");

    int currentBet = 0; //  highest bet in the round

    for (int i = 0; i < numPlayers; i++)
    {
        printf("\n%s's turn:\n", players[i].name);
        char choice;
        do
        {
            printf("Do you want to see your cards? (Y/N): ");
            scanf(" %c", &choice);
            while (getchar() != '\n')
                ;

            if (choice == 'Y' || choice == 'y')
            {
                displayPlayerCards(&players[i], 1);
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
                    printf("\nPress Enter to clear the console...");
                    while (getchar() != '\n')
                        ;
                    clearConsole();
                }
            }
            else if (choice != 'N' && choice != 'n')
            {
                printf("Invalid choice. Please enter 'Y' or 'N'.\n");
            }
        } while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');

        int bet = getValidBet(players[i].wallet, "Enter bet amount (0 to fold): ");

        if (bet > 0)
        {
            if (bet < currentBet)
            {
                printf("Invalid bet amount. Must be at least the current bet of $%d.\n", currentBet);
                i--;
            }
            else
            {
                if (bet > currentBet)
                {
                    printf("%s raises to $%d.\n", players[i].name, bet);
                    currentBet = bet;
                }
                else
                {
                    printf("%s calls $%d.\n", players[i].name, bet);
                }

                players[i].wallet -= bet;
                *pot += bet;
            }
        }
        else if (bet == 0)
        {
            printf("%s folds.\n", players[i].name);
        }
        else
        {
            printf("Invalid bet amount. Please try again.\n");
            i--;
        }
    }
}

void burnCard(Deck *deck)
{
    printf("\nBurning a card...\n");
    drawCard(deck);
}

void handleFlop(Deck *deck, Card communityCards[])
{
    burnCard(deck);
    printf("\n");
    displayCommunityCards(communityCards, 3);
}

void handleTurn(Deck *deck, Card communityCards[])
{
    burnCard(deck);
    communityCards[3] = (Card)drawCard(deck);
    printf("\nTurn card: ");
    printCard(communityCards[3]);
    displayCommunityCards(communityCards, 4);
}

void handleRiver(Deck *deck, Card communityCards[])
{
    burnCard(deck);
    communityCards[4] = (Card)drawCard(deck);
    printf("\nRiver card: ");
    printCard(communityCards[4]);
    displayCommunityCards(communityCards, 5);
}

void determineWinner(Player *players, int numPlayers, const Card communityCards[], int *pot)
{
    if (numPlayers < 1)
    {
        printf("No players to determine a winner.\n");
        return;
    }

    PokerHand *bestHands = (PokerHand *)calloc(2, sizeof(PokerHand));

    printf("\n\n--------------- Evaluating Hands ---------------\n");
    for (int i = 0; i < numPlayers; i++)
    {
        printf("\nEvaluating hand for player %d\n", i + 1);
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

    printf("\n-- Winner is %s with %s and has won $%d! --\n", players[winnerIndex].name, handType, *pot);

    printf("\n---------------- Game Statistics ---------------\n\n");
    for (int i = 0; i < numPlayers; i++)
    {
        printf("%s's wallet balance: $%d\n", players[i].name, players[i].wallet);
        printf("%s's cards: \n", players[i].name);
        printCard(players[i].hand[0]);
        printCard(players[i].hand[1]);
        printf("\n");
    }
    printf("<------------------ Round Over ----------------->\n");
    free(bestHands);
}

void superCleanup(Player *players, int playerCount)
{
    for (int i = 0; i < playerCount; i++)
    {
        freePlayer(&players[i]);
    }
}