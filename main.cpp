//---- Morse Code Converter - Read input file, print and write output to screen and output file ----//
//                                                                                                  //
//      In this program, the user will use a text file that is converted from either English        //
//      to Morse Code, or Morse Code to English. They will also write the number of words that      //
//      they want to be translated, and then write the phrase of text for conversion. Then,         //
//      after the output is created by the program, a new next file is created for printing         //
//      the output separately.                                                                      //
//                                                                                                  //
//              PROGRAMMER ID: Kobe Cofini                                                          //
//              PROGRAM NAME: Morse Code File In Out.cpp                                            //
//              RUN DATE: 5 Dec 2018                                                                //
//                                                                                                  //
//--------------------------------------------------------------------------------------------------//
#include "stdafx.h"

// -------------- Preprocessing Directives -------------- //
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

int main (void) // naming of the main function
{ //begin code

    system("TITLE MORSE CODE FILE IN-OUT CONVERSION"); // program box title

    // coloured text code
    HANDLE h = GetStdHandle (STD_OUTPUT_HANDLE);
    WORD wOldColorAttrs;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    wOldColorAttrs = csbiInfo.wAttributes;

    // -------------- Declare Function Prototypes -------------- //

    void intro (void); // title screen function
    //float TPS (int[9], int); // Throttle Position Sensor Calculations
    void printFile (char[1+1], int[1+1], char[500+1][500+1]); // Pass Calculations to Output File
    void endProgram (void); // End Program

    // -------------- Declare Local Variables -------------- //

    FILE *inputFile, *outputFile; // file pointers
    int count; // 'for' loop variable for every word
    int ltrcount; // 'for' loop variable for every letter of the alphabet
    int numWords[1+1]; // holds number of words inside input file
    int numHold; // temporarily hold number of words for easy utilization of 'for' loops
    // (using single variable instead of an array)
    char convType[500+1]; // holds if translation or decryption

    char wordArray[500+1][500+1]; // array for text input
    char wordHold[500+1]; // temporarily hold string for easy utilization of value during conversion

    //[how many characters in each string][how many strings in array]
    char outputArray[500+1][500+1]; // array for output text ([# of strings][length of each string])
    int invalid = 0; // holds if invalid input

    // Morse lettering for text conversion
    char morseArray[26+1][500+1] = {
            ".-", // Morse A
            "-...", // Morse B
            "-.-.", // Morse C
            "-..", // Morse D
            ".", // Morse E
            "..-.", // Morse F
            "--.", // Morse G
            "....", // Morse H
            "..", // Morse I
            ".---", // Morse J
            "-.-", // Morse K
            ".-..", // Morse L
            "--", // Morse M
            "-.", // Morse N
            "---", // Morse O
            ".--.", // Morse P
            "--.-", // Morse Q
            ".-.", // Morse R
            "...", // Morse S
            "-", // Morse T
            "..-", // Morse U
            "...-", // Morse V
            ".--", // Morse W
            "-..-", // Morse X
            "-.--", // Morse Y
            "--.." // Morse Z
    };

    char letterArray[26+1][1000+1] = {
            "a", // English A
            "b", // English B
            "c", // English C
            "d", // English D
            "e", // English E
            "f", // English F
            "g", // English G
            "h", // English H
            "i", // English I
            "j", // English J
            "k", // English K
            "l", // English L
            "m", // English M
            "n", // English N
            "o", // English O
            "p", // English P
            "q", // English Q
            "r", // English R
            "s", // English S
            "t", // English T
            "u", // English U
            "v", // English V
            "w", // English W
            "x", // English X
            "y", // English Y
            "z" // English Z
    };

    char greekArray[24+1][1000] = {
            "α", // Greek Alpha
            "β", // Greek Beta
            "γ", // Greek Gamma
            "δ", // Greek Delta
            "ε", // Greek Epsilon
            "ζ", // Greek Zeta
            "η", // Greek Eta
            "θ", // Greek Theta
            "ι", // Greek Iota
            "ξ", // Greek Kappa
            "λ", // Greek Lambda
            "μ", // Greek Mu
            "ν", // Greek Nu
            "ξ", // Greek Xi
            "ο", // Greek Omicron
            "π", // Greek Pi
            "ρ", // Greek Rho
            "σ", // Greek Sigma
            "τ", // Greek Tau
            "υ", // Greek Upsilon
            "φ", // Greek Phi
            "χ", // Greek Chi
            "ψ", // Greek Psi
            "ω", // Greek Omega
    };


    // -------------- Display Intro -------------- //

    intro(); // title screen function

    // -------------- File Names and Find File -------------- //

    inputFile = fopen("d:textinput.txt", "r"); // open input file to read
    outputFile = fopen("d:translation.txt", "w"); // open output file to write

    if(inputFile == NULL) // check to see if file will open or can be found
    {
        printf("\nThe input file is not available.");
        printf("\nPress ENTER to exit..."); // once user presses ENTER program dumps
        getch(); // hold screen
        exit(1); // exit function requires <stdlib.h> in preprocessing directives
    } // end if statement

    // -------------- Take User Input -------------- //

    for(count=0; !feof(inputFile); count++) // For loop which exits at the end of the file
    {
        if(count == 0)
            fscanf(inputFile, "%c", &convType[0]); // Gets conversion type from input
        fflush(stdin); // clear keyboard clutter
        if(count == 1)
            fscanf(inputFile, "%d", &numWords[0]); // Gets number of words from input
        fflush(stdin); // clear keyboard clutter
        if(count >= 2)
            fscanf(inputFile, "%s", &wordArray[count - 2]); // Gets words/morse code to convert
        fflush(stdin); // clear keyboard clutter
    }
    fgetc(inputFile); // looks for the ENTER key entered at end of text file
    fclose(inputFile); // close input file

    // -------------- Print Out Initial Input -------------- //

    system("cls"); // clear screen
    printf("Input:");
    strlwr(convType); // change convType to lower case character
    printf("\n\nConversion Type Inputted = %c", convType[0]);

    printf("\nNumber of Words Inputted = %d", numWords[0]);
    numHold = numWords[0]; // transfer value to single variable

    for(count = 0; count < numHold; count++)
    {
        strlwr(wordArray[count]); // change convType to lower case character
        printf("\nWord Number %d = %s", count + 1, wordArray[count]);
    }
    getch(); // hold screen

    // -------------- String Translation -------------- //

    switch(convType[0])
    {
        case 't':
            system("cls"); // clear screen
            printf("Translation Selected (English -> Morse Code)");

            for(count = 0; count < numWords[0]; count++) // all words are converted
            {
                for(ltrcount = 0; ltrcount < 26; ltrcount++)
                {
                    if(strcmp(wordArray[count], letterArray[ltrcount]) == 0) // compare alphabet
                    {
                        strcpy(outputArray[count], morseArray[ltrcount]); // copy translated word to output
                    } // end if statement
                } // end inner 'for' loop
            } // end outer 'for' loop
            getch(); // hold screen

            system("cls"); // clear screen
            printf("Translation: \n\n");
            for(count = 0; count < numWords[0]; count++) // all words are printed out
                printf("%s ", outputArray[count]);
            getch(); // hold screen
            break;
        case 'd':
            system("cls"); // clear screen
            printf("Decryption Selected (Morse Code -> English)");

            for(count = 0; count < numWords[0]; count++) // all words are converted
            {
                for(ltrcount = 0; ltrcount < 26; ltrcount++)
                {
                    if(strcmp(wordArray[count], morseArray[ltrcount]) == 0) // compare alphabet
                    {
                        strcpy(outputArray[count], letterArray[ltrcount]); // copy translated word to output
                    } // end if statement
                } // end inner 'for' loop
            } // end outer 'for' loop
            getch(); // hold screen

            system("cls"); // clear screen
            printf("Decryption: \n\n");
            for(count = 0; count < numWords[0]; count++) // all words are printed out
                printf("%s ", outputArray[count]);
            getch(); // hold screen

            break;
        default:
            system("cls"); // clear screen
            printf("Invalid conversion type! The first character must be either a 't' or a 'd'");
            invalid = 1; // invalid input
    } // end switch statement

    if(invalid == 0) // while valid conversion type
    {
        // should be function calls here

        // -------------- Text File Output -------------- //

        // 'for' loop to print out converted words to file
        fprintf(outputFile, "Translation type: ");
        switch(convType[0])
        {
            case 't':
                fprintf(outputFile, "Translation\n");
                break;
            case 'd':
                fprintf(outputFile, "Decryption\n");
                break;
        } // End switch statement

        fprintf(outputFile, "\nNumber of Words Inputted: %d\n\n", numWords[0]);

        for(count = 0; count < numWords[0]; count++)
            fprintf(outputFile, "%s ", outputArray[count]);

        SetConsoleTextAttribute ( h, FOREGROUND_RED | FOREGROUND_INTENSITY ); // text red
    } // End if statement

    endProgram(); // call end of program text

    getch(); // hold screen
    return 0; // press any key to continue

} // end main

// --------------------- Calculation Functions with Screen Output --------------------- //**********

void intro (void) // title screen function
{
    system("cls"); // clear screen

    // print out "MORSE CODE CONVERTER"
    system("COLOR 0B"); // text colour light blue kl
    printf("\n                                ___          _      ");
    //system("COLOR 0E"); // text colour yellow
    printf("\n  /\\/\\   ___  _ __ ___  ___    / __\\___   __| | ___ ");
    //system("COLOR 0B"); // text colour light blue
    printf("\n /    \\ / _ \\| '__/ __|/ _ \\  / /  / _ \\ / _` |/ _ \\");
    //system("COLOR 0E"); // text colour yellow
    printf("\n/ /\\/\\ \\ (_) | |  \\__ \\  __/ / /__| (_) | (_| |  __/");
    //system("COLOR 0B"); // text colour light blue
    printf("\n\\/    \\/\\___/|_|  |___/\\___| \\____/\\___/ \\__,_|\\___|");
    printf("\n                                                    ");
    //system("COLOR 0E"); // text colour yellow
    printf("\n   ___                          _                   ");
    //system("COLOR 0B"); // text colour light blue
    printf("\n  / __\\___  _ ____   _____ _ __| |_ ___ _ __        ");
    //system("COLOR 0E"); // text colour yellow
    printf("\n / /  / _ \\| '_ \\ \\ / / _ \\ '__| __/ _ \\ '__|       ");
    //system("COLOR 0B"); // text colour light blue
    printf("\n/ /__| (_) | | | \\ V /  __/ |  | ||  __/ |          ");
    //system("COLOR 0E"); // text colour yellow
    printf("\n\\____/\\___/|_| |_|\\_/ \\___|_|   \\__\\___|_|          ");
    printf("\n");
    getch(); // hold screen

    system("cls"); // clear screen
    printf("\nInstructions: A text file with the name of textinput.txt will be used as input.");
    printf("\nThe format inside the text file will be [command] [number of words] [text],");
    printf("\nseparated by spaces.");
    getch(); // hold screen
    printf("\n\nThe 'command' portion will one of two letters: \nA 't' for translation\nor\nA 'd' for decryption");
    getch(); // hold screen
    printf("\n\nThe 'number of words' portion is a single integer (e.g. '5', not 'five')");
    getch(); // hold screen
    printf("\n\nThe 'text' portion is a string of words separated by spaces between each letter");
    printf("\n(e.g aaron -> text file input is 'a a r o n', output is .- .- .-. --- -.)");
    getch(); // hold screen
    printf("\n\nOr, if you want decryption, you will format it regularly like this:");
    printf("\n.- .- .-. --- -. -> aaron");
    getch(); // hold screen

    return; // return to main
} // end intro

void endProgram (void)
{
    system("cls"); // clear screen
    printf("This is the end of the program.\n");
    printf("Press ENTER to exit.\n");
    getch(); // hold screen
}
