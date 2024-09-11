#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Array for quandal inputs/outputs; can handle a quandle that goes up to 10
int input[35] = {0};
int output[1225] = {0};
int setNum = 0;

int menu();
int createSet();
void setupSet(int amount);
void displaySet(int amount);
void clearSet();
void checkQuandle();
bool axiomOne();
bool axiomTwo();
bool axiomThree();

int main() {
    int option = menu();

    if (option == 1) {
        //determine set size
        puts("Let's create a set!");
        setNum = createSet();

        //populate the set
        if (setNum < 0) {
            setNum = (-1 * setNum);
        } else {
            setupSet(setNum);
        }
        
    } else if (option == 2) {
        //display the set as a table
        puts("Displaying your set now...");
        displaySet(setNum);
    } else if (option == 3) {
        //checks all 3 axioms
        puts("Checking if your set is a quandle...");
        checkQuandle();
    } else if (option == 4) {
        //reset all values to zero
        puts("The set has been made empty.");
        clearSet();
    } else if (option == 5) {
        //exit the infinite loop
        puts("Exiting now.");
        return 0;
    }
    
    main();

    return 0;
}

int menu() {

    //user input
    int choice;

    //Asks user to make a selection
    puts("");
    puts("Main Menu");
    puts("1 - Create a set");
    puts("2 - Display set information");
    puts("3 - Check quandle status");
    puts("4 - Clear current set");
    puts("5 - Exit program");
    printf("Input: ");
    scanf("%d", &choice);

    puts("");

    switch (choice) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            system("cls");
            return choice;
        default:
            puts("Oops! That's not a valid option.");
            return 0;
    }
}

int createSet() {

    //double checks to confirm a table does not exist
    if (setNum > 0) {
        puts("Oops! You must reset your set to create another one.");
        return -1 * setNum;
    }

    //user input
    int num; 

    //Asks user to define table size
    puts("");
    puts("How many numbers are in your set? (Choose up to 35).");
    printf("Input: ");
    scanf("%d", &num);

    if ((num <= 0) || (num > 35)) {
        puts("Oops! That's not a valid option.");
        return createSet();
    } else {
        return num;
    }

}

void setupSet(int amount) {
    //user input
    int entry;

    //defines input numbers
    for (int i = 1; i <= amount; i++) {
        input[i - 1] = i;
    }

    puts("Thank you!");

    //defines output numbers
    for (int i = 1; i <= amount; i++) {
        for (int j = 1; j <= amount; j++) {
            printf("Type in the result of (%d * %d).\n", i, j);
            printf("Input: ");
            scanf("%d", &entry);
            output[((i - 1) * amount) + (j - 1)] = entry;
        }
    }

    return;
}

void displaySet(int amount) {
    //double checks to confirm a table has been made
    if (amount <= 0) {
        puts("Oops! You haven't made a set yet.");
        return;
    }

    puts("");
    printf("      |"); //blank corner

    for (int i = 0; i < amount; i++) {
        printf("%4d  |", input[i]); //header row
    }

    puts("");
    for (int i = 0; i <= amount; i++) {
            printf("-------"); // divider line for row
        }
    puts("");
    
    for (int i = 0; i < amount; i++) {
        printf("%4d  |", input[i]); //header column
        for (int j = 0; j < amount; j++) {
            printf("%4d  |", output[(i * amount) + j]);
        }

        puts("");
        for (int j = 0; j <= amount; j++) {
            printf("-------"); //divider lines for rows
        }
        puts("");
    }
    
    return;
}

void clearSet() {
    //reset amount of numbers in set
    setNum = 0;

    //reset input array
    for (int i = 0; i < 10; i++) {
        input[i] = 0;
    }

    //reset output array
    for (int i = 0; i < 100; i++) {
        input[i] = 0;
    }

    return;
}

void checkQuandle() {

    //double checks to confirm a table has been made
    if (setNum <= 0) {
        puts("Oops! You haven't made a set yet.");
        return;
    }

    //failure cases
    if (axiomOne() == false) {
        puts("The set fails to meet Axiom One.");
        puts("Therefore it is not a Quandle.");
        puts("");
        return;
    }

    if (axiomTwo() == false) {
        puts("The set fails to meet Axiom Two.");
        puts("Therefore it is not a Quandle.");
        puts("");
        return;
    }

    if (axiomThree() == false) {
        puts("The set fails to meet Axiom Three.");
        puts("Therefore it is not a Quandle.");
        puts("");
        return;
    }

    //success case
    puts("The set meets all three axioms.");
    puts("Therefore it is a Quandle.");
    puts("");
    return;
}

bool axiomOne() {
    for (int i = 0; i < setNum; i++) {
        if (input[i] != output[(i * setNum) + i]) {
            return false;
        }
    }
    return true;
}

bool axiomTwo() {
    for (int h = 0; h < setNum; h++) {
        for (int i = 0; i < setNum; i++) {
            for (int j = i + 1; j < setNum; j++) {
                if (output[(i * setNum) + h] == output[(j * setNum) + h])  {
                    return false;
                }
            }
        }
    }
    return true;
}

bool axiomThree() {
    int a, b, c;
    int v, w, x, y, z;


    for (int i = 0; i < setNum; i++) {
        for (int j = 0; j < setNum; j++) {
            for (int k = 0; k < setNum; k++) {
                //variables a, b, and c in the set
                a = input[i];
                b = input[j];
                c = input[k];

                v = output[(i * setNum) + j]; //v = (a * b)
                w = output[((v- 1) * setNum) + k]; //w = (a * b) * c
                x = output[(i * setNum) + k]; //x = (a * c)
                y = output[(j * setNum) + k]; //y = (b * c)
                z = output[((x - 1) * setNum) + (y - 1)]; //z = (x * y) = (a * c) * (b * c)

                if (w != z)
                    return false;

            }

        }
    }


    return true;
}
