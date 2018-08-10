//Libraries
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//Constant Declarations
#define QUIT 'Q'
#define DONE 0
#define PLAY 'P'
#define HOUSE 'H'
#define HALF 'A'
#define EMPTY 'E'
#define TRUE 1
#define FALSE 0
#define ERROR 3
#define SIZE 3
#define APPLE 0
#define ORANGE 1
#define PEAR 2
#define STARTINGCRED 10
//Functions for money handling
int check_credit();
void bet_result(float wager, char result);
int collect_bet(void);
//Functions for menu handling and error checking
void print_menu(void);
void get_option(void);
void process_option(char what_to_do);
//Function to play the game
int play_the_game();
//Convert int to name of fruit for print out
char *name_of_fruit(int Fruit);
//Global variable for total money
float Total;
//Global variable for menu handling
int Option;
//Structure for column
typedef struct
{
    int Fruit;
} Column;
//Structure for Empty Row
typedef struct
{
    Column Column1;
    Column Column2;
    Column Column3;
} Slot;
int main(int argc, char *argv[]) //Allow for command line cheats for testing
{
    //Cheat for extra credits
    if (argv[1] != NULL)
    {
        Total = atoi(argv[1]);
    }
    else
    {
        Total = STARTINGCRED;
    }
    //Keep running the program until quit is selected
    while (Option != QUIT)
    {
        print_menu();
        get_option();
        process_option(Option);
    }
}
int play_the_game()
{
    //Variable for bet
    float fltWager = 0;
    //Variable for random answer
    int intAnswer;
    //Striucture for game result
    Slot Result;

    //Setup the random seed
    srand(time(NULL));

    //Collect the Bet from user
    if ((fltWager = collect_bet()) != 'X')
    {
    }
    else
    {
        return ERROR;
    }

    //Pick a random number from 0-2 and place in the Slot
    intAnswer = rand() % SIZE;
    Result.Column1.Fruit = intAnswer;

    //Pick a random number from 0-2 and place in the Slot
    intAnswer = rand() % SIZE;
    Result.Column2.Fruit = intAnswer;

    //Pick a random number from 0-2 and place in the Slot
    intAnswer = rand() % SIZE;
    Result.Column3.Fruit = intAnswer;

    //Print out the played slot
    printf("[*Slot 1*][*Slot 2*][*Slot 3*]\n");
    printf("[%s][%s][%s]\n", name_of_fruit(Result.Column1.Fruit), name_of_fruit(Result.Column2.Fruit), name_of_fruit(Result.Column3.Fruit));

    //Conditional to determine winnings
    if (Result.Column1.Fruit == Result.Column2.Fruit && Result.Column1.Fruit == Result.Column3.Fruit)
    {
        bet_result(fltWager, HOUSE);
        printf("You have won %.0f\n", fltWager);
    }
    else if (Result.Column1.Fruit == Result.Column2.Fruit || Result.Column1.Fruit == Result.Column3.Fruit || Result.Column2.Fruit == Result.Column3.Fruit)
    {
        bet_result(fltWager, HALF);
        printf("You have won %.0f\n", fltWager / 2);
    }
    else
    {
        bet_result(fltWager, EMPTY);
        printf("I'm sorry you have lost %.0f", fltWager);
    }
}
char *name_of_fruit(int Fruit)
{ //Function returns name of fruit rather than 0/1/2
    switch (Fruit)
    {
    case APPLE:
        return "  Apple ";
    case ORANGE:
        return " Orange ";
    case PEAR:
        return "  Pear  ";
    default:
        process_option(QUIT);
    }
}
int collect_bet()
{ //Collect the bet amount and check that the user is not overbetting
    int wager = 0;

    printf("Please input the amount you wish to bet!\n");
    fflush(stdin);
    if (scanf("%d", &wager) == 1)
    {
    }
    else
    {
        printf("Invalid value try again!\n");
        return 'X';
    }

    if (wager > Total)
    {
        printf("You do not have that much money to bet!\n");
        return 'X';
    }
    else
    {
        return wager;
    }
}
void process_option(char what_to_do)
{ //Menu optons
    //Play the game
    if (what_to_do == PLAY)
    {
        play_the_game();
    }
    //Quit the program and tell the user what their total win/loss was
    else if (what_to_do == QUIT)
    {
        if (Total > STARTINGCRED)
        {
            printf("You have won %.0f credits in total. Goodbye!\n", Total - STARTINGCRED);
        }
        else if (Total < STARTINGCRED)
        {
            printf("You have lost %.0f credits in total. Goodbye!\n", STARTINGCRED - Total);
        }
        else if (Total == STARTINGCRED)
        {
            printf("You didn't win or lose any credits. Goodbye!\n");
        }
        exit(DONE);
    }
    //Error Handling
    else if (what_to_do == 'X')
    {
        printf("There has been an unexpected problem with your bet, Exiting!");
        exit(ERROR);
    }
    //More error handling
    else
    {
        printf("Input not understood, please try again!\n");
    }
}
int check_credit()
{ //Check if user has enough remaining credit for a bet
    if (Total < 2)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
void bet_result(float wager, char result)
{ //Passed in values work out new total
    switch (result)
    {
    case HOUSE:
        Total = Total + wager;
        break;
    case HALF:
        Total = round(Total + (0.5 * wager));
        break;
    case EMPTY:
        Total = Total - wager;
        break;
    }

    //Make sure they have enough credit to continue playing
    if (check_credit() == FALSE)
    {
        printf("I'm sorry you no longer have enough money to gamble with, you'll have to leave!\n");
        process_option(QUIT);
    }
}
void print_menu(void)
{
    //Print out menu
    printf("\nWelcome to my slot machine program\n");

    printf("\n	Your Current Total is %.0f\n", Total);
    printf("	P to play slot machine\n");
    printf("	Q to Quit program\n");
}
void get_option(void)
{ //Collect user choice
    fflush(stdin);
    Option = getchar();
    Option = toupper(Option);
}