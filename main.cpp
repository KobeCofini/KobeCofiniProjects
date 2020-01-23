// This program is to be used in conjunction with the Morse Code Translator program.
// It it necessary to input the words with a space in between each letter,
// which can be very cumbersome to do manually for a user's input.txt file.
// This supplementary function solves the problem.
#include <iostream>
//#include <conio.h>

int main();

int main() {

    FILE *inputFile, *outputFile; // file pointers;

    inputFile = fopen("d:makespaces.txt", "r"); // open input file to read
    outputFile = fopen("d:spacing.txt", "w"); // open output file to write

    if(inputFile == NULL) // check to see if file will open or can be found
    {
        printf("\nThe input file is not available.");
        printf("\nPress ENTER to exit..."); // once user presses ENTER program dumps
        getch(); // hold screen
        exit(1); // exit function requires <stdlib.h> in preprocessing directives
    } // end if statement

    int countChars;

    char wordArray[1000] = "I like to eat cheese"; // holds text inputted

    for(countChars = 0; !feof(inputFile); countChars++) // For loop which exits at the end of the file
    {
        if(isspace(wordArray[countChars])) {
            wordArray[countChars] = ' ';
        }
        else {
            fscanf(inputFile, "%c", &wordArray[countChars]); // Gets language for output (Morse Only)
        }
    }

    int counter;
    char textSpacing[1000]; // holds text with spaces between characters

    for(counter = 0; counter < countChars; counter++) {
        if(counter % 2 == 0) // if count is even (every other slot)
            textSpacing[counter] = wordArray[counter / 2];
        else
            textSpacing[counter] = ' ';
    }

    printf(textSpacing);

    return 0;
}

