//-------------------- Bank Machine - Withdraw, deposit, and view balance ------------------//
//																							//
// In this program, the user will use an ATM in order to access their funds. They will		//
// have the choice to either withdraw their money that is in their account, deposit and		//
// add more money to their balance, or simply view their balance separately.				//
//																							//
//				PROGRAM ID: Bank Machine.cpp												//
//				PROGRAMMER NAME: Kobe Cofini												//
//				RUN DATE: Thursday September 13 2018										//
//																							//
//------------------------------------------------------------------------------------------//

#include "stdafx.h"
// libraries to store program information
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int main (void) // naming of the main function
{ // begin main function

    system("TITLE Bank Machine"); // naming of program box

    // DECLARE VARIABLES -------------------------------------------------------
    float deposit = 0, withdraw = 0, chq = 500, sav = 5000, amount = 0, total = 0; // holds account values
    int choice; // holds if user wants deposit or withdraw
    char choice2; // holds if user wants chequing or savings
    int pin = 0; // holds user password
    int correct = 0; // holds if password is right
    int attempts; // holds # of pin attempts
    int error = 0; // hold if withdraw error occurred
    int error2 = 0; // hold if invalid input
    char exit[50] = "Please press enter to exit the program";

    // TAKE USER INPUT -------------------------------------------------------
    for( attempts = 0; attempts < 3; attempts++ ) // User enters password
    {
        system("cls"); // clear screen
        printf("\t\tOFFICIAL BANK OF CANADA\n\n");
        printf("\n\nPlease enter your four digit PIN and press ENTER (Attempt %d): ", attempts + 1);
        scanf("%d", &pin); // holds pin entered by user
        fflush(stdin); // clear keyboard clutter

        switch(pin)
        {
            case 1234: // correct pin
                correct = 1;
                attempts = 3; // pass through 'for' loop
                break;

            default: // incorrect pin
                system("cls");
                printf("Incorrect PIN!");

                switch(attempts)
                {
                    case 0:
                        printf("\nYou have 2 attempts left");
                        break;

                    case 1:
                        printf("\nYou have 1 attempt left");
                        break;

                    case 2:
                        printf("\nYou have no attempts left, and are locked out for the time being.");
                        break;
                } // end nested switch statement

                getch(); // hold screen
                break;
        } // end switch statement
    } // end 'for' loop

    switch(correct) // enter account if correct pin
    {
        case 1:
            do
            {
                system("cls"); // clear screen
                error2 = 0; // reset error2
                printf("Please enter 1 to deposit, 2 to withdraw,");
                printf("\n3 to view balance, or 4 to exit.");
                scanf("%d", &choice); // holds menu choice

                switch(choice)
                {
                    case 1: // deposit
                        printf("\n\nPlease press c to enter your chequing, or s to enter your savings");
                        scanf("%c", &choice2); // holds menu choice

                        system("cls"); // clear screen
                        switch(choice2)
                        {
                            case 'c':
                                printf("CHEQUING: $%.2f", chq);
                                break;
                            case 's':
                                printf("\nSAVINGS: $%.2f", sav);
                                break;
                        } // end nested switch statement

                        printf("\nHow much do you want to deposit? $");
                        scanf("%f", &deposit);
                        break;

                    case 2: // withdraw
                        printf("\n\nPlease press 1 to enter your chequing, or 2 to enter your savings");
                        scanf("%d", &choice2); // holds menu choice

                        do
                        {
                            system("cls"); // clear screen
                            switch(choice2)
                            {
                                case 'c': // chequing
                                    printf("CHEQUING: $%.2f", chq);
                                    break;
                                case 's': // savings
                                    printf("\nSAVINGS: $%.2f", sav);
                                    break;
                            } // end nested switch statement

                            printf("\nHow much do you want to withdraw? $");
                            scanf("%f", &withdraw);

                            switch(choice2)
                            {
                                case 'c': // chequing
                                    if(withdraw > chq)
                                    {
                                        error = 1;
                                        system("cls"); // clear screen
                                        printf("Error: withdraw amount is more than balance. Please try again.");
                                    }
                                    else
                                        error = 0; // no withdraw error
                                    break;
                                case 's': // savings
                                    if(withdraw > sav)
                                    {
                                        error = 1;
                                        system("cls"); // clear screen
                                        printf("Error: withdraw amount is more than balance. Please try again.");
                                    }
                                    else
                                        error = 0; // no withdraw error
                                    break;
                            } // end nested switch statement

                        }while(error = 1);
                        break;

                    case 3:
                        printf("Your chequing balance is $%.2f", chq);
                        printf("\nYour savings balance is $%.2f", sav);
                        getch(); // hold screen
                        break;

                    case 4:
                        system("cls"); // clear screen
                        printf("You have exited your account. Please come back again!");
                        printf("\n%s", exit);
                        getch(); // hold screen
                        break;

                    default:
                        error2 = 1;
                        system("cls"); // clear screen
                        printf("Invalid input!");
                        getch();
                        break;

                } // end nested switch statement
            }while(error2 == 1);
            break;


        default:
            printf("\n%s", exit);
            break;

    } // end switch statement

    // CALCULATIONS -------------------------------------------------------
    switch(correct)
    {
        case 1: // check again to make sure pin was correct
            switch(choice)
            {
                case 1: // deposit
                    switch(choice2)
                    {
                        case 'c': // chequing
                            chq += deposit; // add deposit to chequing
                            break;

                        case 's': // savings
                            sav += deposit; // add deposit to savings
                            break;
                    }
                    break;

                case 2: // withdraw
                    switch(choice2)
                    {
                        case 'c': // chequing
                            chq -= withdraw; // subtract withdraw from chequing
                            break;

                        case 's': // savings
                            sav -= withdraw; // subtract withdraw from savings
                            break;
                    } // end nested switch statement
                    break;
            } // end nested switch statement
            break;

        default:
            printf("\n");
            break;
    } // end switch statement

    // PRINT OUTPUT -------------------------------------------------------
    switch(correct)
    {
        case 1: // check again to make sure pin was correct
            switch(choice2)
            {
                case 'c': // chequing
                    printf("\n\nThe amount in your chequing account is now $%f", chq);
                    getch(); // hold screen
                    break;

                case 's': // savings
                    printf("\n\nThe amount in your savings account is now $%f", sav);
                    getch(); // hold screen
                    break;
            }

            system("cls"); // clear screen
            printf("%s", exit);

            break;

        default:
            // do nothing
            break;
    } // end switch statement

    getch(); // hold screen
    return 0; // key press to exit

} // end main function