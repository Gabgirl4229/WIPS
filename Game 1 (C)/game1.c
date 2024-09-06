#include <stdio.h>
#include <time.h>
#include <stdlib.h>


//pages for the entire game
void intro();

void crimeScene();
void forensics();
void loadingScreen();
void invalidScreen();
void gameplayText();
void printBox();
void itemScreen();
void printItems();
void printAnalysis(int arr[]);
void investigate();
void examineEvidence();
void analysis(int analysisItem);
int preparePrintItems(int item);

void page1();
void page2();

void caseSetup();
int objectSelect();
int hostageSelect();
int murderSelect();

void itemList();
int collectEvidence();

//(FOR TESTING ONLY)
void killCode();


//global variables
char name[10];
int caseID[3];
int printItem[8] = {100, 100, 100, 100, 100, 100, 100, 100};

//selected items (customized for each case)
int gameItems[8];
int discoveredItems[8] = {100, 100, 100, 100, 100, 100, 100, 100};
static char foundItemsString[8][25];

static int itemValue[8] = {0};
static int itemQualities[12] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

static int selectedSize;
static int pageNumber;


int totalItems[][12] = {{0, 1, 2, 3, 4, 5}, {6, 7, 8}, {9, 10, 11, 12, 13, 14, 15, 16}, {17, 18}, {19, 20, 21}, {90, 91, 92, 93}};

//master list of items (but in string form)
char totalItemsString[28][25] = {
//Item Clues (theft)
{"Receipt for a Ring Frame"}, {"Jewelry-Polishing Set"}, {"Roll of Cash"}, {"Empty Money Bag"}, {"Tiger Fuzz"}, {"Whisker"}, 
//Weapon Clues (murder)
{"Gun"}, {"Knife"}, {"Rope"}, 
//Person Clues
{"Half-Empty Cup"}, {"Gloves"}, {"Rose"}, {"Book"}, {"Used Hairbrush"}, {"Cigarette Butts"}, {"Shoe Tracks"}, {"Contact Lens"}, 
//Item Clues (murder)
{"Suicide Note"}, {"Smudged Message"}, 
//Location Clues (kidnapping)
{"Party Invite"}, {"Concert Flyer"}, {"Charred Golden Coin"},
//Tutorial Clues
{"Torn Fabric"}, {"Hair Follicle"}, {"Fingerprint"}, {"Coffee Stain"}, 
};


//pre-generated tutorial items
int tutorialItems[4] = {90, 91, 92, 93};




//does nothing lol
int main() {
    srand(time(0));
    intro();
}

//starts the game
void intro() {
char ch;
    printf("Welcome to the game!\n\n> Press A to begin\n> Press B to quit\n");
    scanf(" %c", &ch);

    switch (ch) {
        case 'A':
        case 'a':
            system("clear");
            page1();
            break;
        case 'B':
        case 'b':
            break;
        default:
            invalidScreen();
            intro();
            break;
    }

}

//gets name and initiates/skips tutorial
void page1() {
char ch;

    printf("\n\nWhat is your name, Detective?\n");
    scanf(" %[^\n]9s", name);
    puts("");
    
    puts("Would you like to play the tutorial?");
    printf("> Y\n");
    printf("> N\n");
    scanf(" %c", &ch);

    if (ch == 'Y' || ch == 'y') {
        system("clear");
        page2();
    } else if (ch == 'N' || ch == 'n') {
        system("clear");
        caseSetup();
    } else {
        invalidScreen();
        page1();
    }
}

//tutorial intro
void page2() {
char ch;

    //creates a completely different case ID for the tutorial
    caseID[0] = 9;
    caseID[1] = 9;
    caseID[2] = 1;
    
    
    printf("\n\n");
    for (int n = 1; n <= 82; n++) {
        printf("=");
    }
    printf(" \n\n");
    
    printf("Hello Detective %s! Welcome to your first case.\n", name);
    printf("A thief has been accused of stealing my favorite scarf.\n");
    printf("I need you to find out who did it, for a hefty sum of course.\n\n");
    printf("Let's head to the crime scene!\n");

    puts("(Press A to continue)");
    scanf(" %c", &ch);
    
    if (ch == 'A' || ch == 'a') {
        system("clear");
        itemList();
    } else {
        invalidScreen();
        page2();
    }
}




//randomizes one of 9 cases and determines reward
void caseSetup() {
char ch;
//money values
int rewardArr[10] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};
        
    printf("\n\n ");
    for (int n = 1; n <= 80; n++) {
        printf("_");
    }
    printf(" \n\n");
    
    printf(" Detective %s, we need your help!\n", name);

    //generates casetype and reward
    int caseType = rand()%3;
    int reward = rewardArr[rand()%10];
    int objective;

    //generates details of each case type
    switch (caseType) {
        case 0:
            printf(" Someone has stolen ");
            objective = objectSelect();
            printf(" Find out who took it, and you'll receive $%d.\n", reward);
            break;
        case 1:
            printf(" Someone has kidnapped ");
            objective = hostageSelect();
            printf(" Get the hostage back safely, and you'll receive $%d.\n", reward);
            break;
        case 2: 
            printf(" Someone has died unexpectedly from ");
            objective = murderSelect();
            printf(" Figure out who the murderer is, and you'll receive $%d.\n", reward);
            break;
    }
    
    printf("\n ");
    for (int n = 1; n <= 80; n++) {
        printf("_");
    }
    printf(" \n\n");

    //if user accepts the case, the game will start
    //if not, it will re-generate
    printf(" Will you accept the case?\n");
    printf(" > Y\n");
    printf(" > N\n");
    scanf(" %c", &ch);

    //generates case ID
    if (ch == 'Y' || ch == 'y') {
        caseID[0] = caseType;
        caseID[1] = objective;
        caseID[2] = reward;

        system("clear");
        itemList();
    } else if (ch == 'N' || ch == 'n') {
        system("clear");
        caseSetup();
    } else {
        invalidScreen();
        caseSetup();
    }
}

//generates object stolen (for theft)
int objectSelect() {
    int object = rand()%3;

    switch (object) {
        case 0:
            printf("a rare diamond.\n");
            break;
        case 1:
            printf("money from the bank.\n");
            break;
        case 2: 
            printf("a tiger from the zoo.\n");
            break;
    }

    return object;
}

//generates hostage(for kidnapping)
int hostageSelect() {

    int hostage = rand()%3;

    switch (hostage) {
        case 0:
            printf("movie star Chris Something-or-other.\n");
            break;
        case 1:
            printf("pop sensation Wendy Willow.\n");
            break;
        case 2: 
            printf("Princess Regina of North Shore.\n");
            break;
    }

    return hostage;
}

//generates method (for murder)
int murderSelect() {

    int murder = rand()%3;

    switch (murder) {
        case 0:
            printf("a gunshot wound.\n");
            break;
        case 1:
            printf("repeated stabbing.\n");
            break;
        case 2: 
            printf("asphyxiation.\n");
            break;
    }

    return murder;
}




/* Game mechanics (for later):

- Types of forensics
    Fingerprint (cup)
        Shape of Whorl - 3
    Hair Follicle (brush)
        Hair Color - 5
        Hair Length - 4
    Blood (rose, tiger fuzz)
        Blood Type - 8
    Shoe Track (shoe track)
        Foot Size - 14 (sizes 2.5 to 9.5)
    Eye Color (colored contact)
        Eye color - 5
    Vision Impairments (prescription contact)
        Ocular prescription - 3
    Predominant Hand (cup)
        Predominant hand - 3
    Gender (gloves)
        Gender - 2
    Height (book)
        Height - 3


    (theft cases only)
    Last Name (receipt)
        Last Name - 30 (maybe less, if some people have a common last name)
    Profession (Roll of cash)
        Previous Occupation - 1 (for now, will add more)


    (murder cases only)
    Letters in Name (smudged message)
        Letters - 3

    

        

- Types of comparisons
    Tall vs short (books)
    Lefty vs Righty (cup)
    Smoker/non-smoker (cigarette)
    Coffee/Tea/Alcohol (cup)

    (murder cases only)
    Cursive vs print (fake suicide note)
*/ 


//selects objects available for investigation
void itemList() {

//creates modifiable array for selected items
int selectedItems[selectedSize];

    //tutorial case
    if (caseID[0] == 9) {
        selectedSize = 4;
        pageNumber = 0;
        
        for (int i = 0; i < selectedSize; i++) {
            selectedItems[i] = tutorialItems[i];
        }
        
    } else {
        selectedSize = 8;

        //primary item
        switch (caseID[0]) {
            //theft
            case 0:
            switch (caseID[1]) {
                //diamond
                case 0:
                    //pre-load dialogue for each case (SET UP LATER)
                    //pageNumber = ?;
                    selectedItems[0] = totalItems[0][0];
                    selectedItems[1] = totalItems[0][1];
                    break;
                //money
                case 1:
                    selectedItems[0] = totalItems[0][2];
                    selectedItems[1] = totalItems[0][3];
                    break;
                //tiger
                case 2:
                    selectedItems[0] = totalItems[0][4];
                    selectedItems[1] = totalItems[0][5];
                    break;
            }

            //randomizes person clues without duplicates
            selectedItems[2] = totalItems[2][rand()%8];

            for (int i = 3; i < selectedSize; i++) {
                selectedItems[i] = totalItems[2][rand()%8];
                
                for (int j = i - 1; j >= 2; j--) {
                    if (selectedItems[i] == selectedItems[j]) {
                        i--;
                        continue;
                    }
                }

            }
            break;
            //kidnapping (NOT SET UP YET)
            case 1:
                switch (caseID[1]) {
                    //actor
                    case 0:
                    selectedItems[0] = totalItems[4][0];  
                    break;
                    //singer
                    case 1:
                    selectedItems[0] = totalItems[4][1];
                    break;
                    //princess
                    case 2:
                    selectedItems[0] = totalItems[4][2];
                    break;
                }

            selectedItems[1] = totalItems[2][rand()%8];

            for (int i = 2; i < selectedSize - 3; i++) {
                selectedItems[i] = totalItems[2][rand()%8];
                
                for (int j = i - 1; j >= 2; j--) {
                    if (selectedItems[i] == selectedItems[j]) {
                        i--;
                        continue;
                    }
                }

            }
            break;
            //murder
            case 2: 
            switch (caseID[1]) {
                //gun
                case 0:
                selectedItems[0] = totalItems[1][0];
                break;
                //knife
                case 1:
                selectedItems[0] = totalItems[1][1];
                break;
                //rope
                case 2:
                selectedItems[0] = totalItems[1][2];
                break;
            }

            selectedItems[1] = totalItems[3][rand()%2];
                
            //randomizes person clues without duplicates
            selectedItems[2] = totalItems[2][rand()%8];

            for (int i = 3; i < selectedSize; i++) {
                selectedItems[i] = totalItems[2][rand()%8];
                
                for (int j = i - 1; j >= 2; j--) {
                    if (selectedItems[i] == selectedItems[j]) {
                        i--;
                        continue;
                    }
                }

            }
            break;

            
        }
    }
    
    //send array to gameItems
    for (int i = 0; i < selectedSize; i++) {
        gameItems[i] = selectedItems[i];
    }

    //convert gameItems to string
    for (int i = 0; i < selectedSize; i++) {
        for (int j = 0; j < 25; j++) {
            if (caseID[0] == 9) {
                foundItemsString[i][j] = totalItemsString[i+22][j];
            } else {
                foundItemsString[i][j] = totalItemsString[gameItems[i]][j];
            }
        }
    }


    //start gameplay
    crimeScene();
}


//Behind-the-scenes calculations
int collectEvidence() {
static int callCount = 0;
static int j[] = {0, 0, 0, 0, 0, 0, 0, 0};
int item;


    //ends investigation once all items are found
    if (callCount == selectedSize) {
        return 100;
    }
    
    itemValue[callCount] = rand()%selectedSize;

    if (callCount > 0) {
        for (int x = 0; x < callCount; x++) {
            if (j[x] == itemValue[callCount]) {
                itemValue[callCount] = rand()%selectedSize;
                x = -1;
            }
        }
    }
        

    j[callCount] = itemValue[callCount];
    item = gameItems[itemValue[callCount]]; 
    callCount++;
    return item;

}

//will assign quality types to each item
//NOT DONE YET (RETURN EVERY TIME YOU UPDATE THE ITEM/QUALITY LIST)
void analysis(int analysisItem) {
static int count = 0;

//ANOTHER NOTE: Randomization system will go with the analysisPrinting function

    //runs once every time the function is called
    switch (analysisItem) {
        //Jewelry-Polishing Set, Empty Money Bag, Whisker
        case 1: 
        case 3:
        case 5:
        //will give nothing
        itemQualities[count] = 0;
        break;
        //Receipt for a Ring Frame
        case 0:
        //will give culprit's last name 
        itemQualities[count] = 1;
        break;
        //Roll of Cash
        case 2:
        //will give culprit's profession
        itemQualities[count] = 2;
        break;
        //Tiger Fuzz, Rose
        case 4:
        case 11:
        //will give culprit's blood type
        itemQualities[count] = 3;
        break;
        //Gun, Knife, Rope
        case 6:
        case 7:
        case 8:
        //will give fingerprint
        itemQualities[count] = 4;
        break;
        //Half-Empty Cup
        case 9:
        //will give fingerprint or predominant hand
        itemQualities[count] = rand()%2 + 4;
        //will give alcoholic or drink preference 
        itemQualities[count + 1] = rand()%2 + 6;
        count++;
        break;
        //Gloves
        case 10:
        //will give gender
        itemQualities[count] = 8;
        break;
        //Book
        case 12:
        //will give height
        itemQualities[count] = 9;
        break;
        //Used Hairbrush
        case 13:
        //will give hair length and color
        itemQualities[count] = 10;
        itemQualities[count + 1] = 11;
        count++;
        break;
        //Cigarette Butts
        case 14:
        //will give smoker
        itemQualities[count] = 12;
        break;
        //Shoe Tracks
        case 15:
        //will give foot size
        itemQualities[count] = 13;
        break;
        //Contact Lens
        case 16:
        //will give prescription or false eye color
        itemQualities[count] = rand()%2 + 14;
        break;
        //Suicide Note
        case 17:
        //will give handwriting
        itemQualities[count] = 16;
        break;
        //Smudged Message
        case 18:
        //will give initials
        itemQualities[count] = 17;
        break;
        default:
        break;
            
    }
    count++;

    return;
}


//Actual Gameplay
void crimeScene() {
    
    //(FOR TESTING ONLY) prints case ID
    printf("Case ID: (%d, %d, $%d)\n", caseID[0], caseID[1], caseID[2]);
    
    //(FOR TESTING ONLY) prints the selected items list
    for (int i = 0; i < selectedSize; i++) {
        printf("%d ", gameItems[i]);
        printf("%s ", foundItemsString[i]);
    }
    
    printf("\n\n");

    
    //visuals
    printBox();
    itemScreen();

    investigate();
}

void forensics() {
    
    //(FOR TESTING ONLY) prints case ID
    printf("Case ID: (%d, %d, $%d)\n", caseID[0], caseID[1], caseID[2]);
    
    //(FOR TESTING ONLY) prints the selected items list
    for (int i = 0; i < selectedSize; i++) {
        printf("%d ", gameItems[i]);
    }
    printf("\n\n");

    //visuals
    printBox();
    
    if (pageNumber == 1) {
        loadingScreen();
        forensics();
    } else if (pageNumber >= 3) {
        printAnalysis(itemQualities);
    }

    itemScreen();

    examineEvidence();
}

//loading screen intended for changing pages/dialogue without changing the rest of the screen
void loadingScreen() {
char ch;
    
    printf("\n ");
    for (int n = 1; n <= 80; n++) {
        printf("_");
    }
    printf(" \n");
    
    puts(" (Press A to continue)");
        scanf(" %c", &ch);
    
        if (ch == 'A' || ch == 'a') {
            system("clear");
            pageNumber++;
        } else {
            invalidScreen();
        } 
    return;
}

//IF SOMEONE TYPES IN THE WRONG LETTER (NOT FINISHED YET)
void invalidScreen() {
char ch;

    printf("\n ");
    for (int n = 1; n <= 80; n++) {
        printf("_");
    }
    printf(" \n");

    puts(" That is not a valid response.");
    
    puts(" (Press A to continue)");
        scanf(" %c", &ch);
    
        if (ch == 'A' || ch == 'a') {
            system("clear");
        }  else {
            invalidScreen();
        }
    return;
}

void investigate() {
char ch;
static int count = 0;
int itemIndex;

    printf("\n ");
    for (int n = 1; n <= 80; n++) {
        printf("_");
    }
    printf(" \n");
    
    printf(" Investigate?\n");
    printf(" > Y\n > N\n");
    scanf(" %c", &ch);
    
    if (ch == 'N' || ch == 'n') {
        system("clear");
        pageNumber++;
        forensics();
    } else if (ch == 'Y' || ch == 'y') {
        puts("");

        int item = collectEvidence();
        //item = gameItems[itemValue[callCount]];

        if (item == 100) {
            printf("There are no more items to find.\n");
        } else {
            for (int i = 0; i < selectedSize; i++)  {
                if (item == gameItems[itemValue[i]]) {
                    itemIndex = i;
                    break;
                }
            }

            printf("You found: %s\n", foundItemsString[itemValue[itemIndex]]);
            discoveredItems[count] = item;

            //(FOR TESTING ONLY) prints discoveredItems array
            for (int i = 0; i < selectedSize;i++) {
                printf("%d\t", discoveredItems[i]);
            }
            puts("");

            //sends item to printItems for printing
            for (int i = 0; i < selectedSize; i++) {
                if (count == 0) {
                    printItem[i] = item;
                    count++;
                    break;
                } else if (printItem[i] == 100) {

                    printItem[i] = item;
                    count++;
                    break;
                    
                }
            }
        }

        puts("(Press A to continue)");
        scanf(" %c", &ch);
    
        if (ch == 'A' || ch == 'a') {
            system("clear");
            crimeScene();
        } else {
            invalidScreen();
            crimeScene();
            
        }
        
    } else {
        invalidScreen();
        crimeScene();
    } 
}

void examineEvidence() {
int choice;
int analysisItem;
int index;
char ch;

static int hasBeenChecked[8] = {0};

    printf("\n ");
    for (int n = 1; n <= 80; n++) {
        printf("_");
    }
    printf(" \n");


    if (selectedSize == 4) {
        for (int i = selectedSize; i < 8; i++) {
            discoveredItems[i] = 0;
        }
    }
    
    //(FOR TESTING ONLY)
    for (int i = 0; i < 8; i++) {
        printf(" %d ", discoveredItems[i]);
    }
    printf(" \n");

    printf(" Which item would you like to analyze?\n");

    for (int i = 0; i < selectedSize; i++) {
        printf(" > %d - Item %d\n", i + 1, i + 1);
    }
    printf(" > %d - End Examination\n", selectedSize + 1);
    
    scanf("%d", &choice);

    if (discoveredItems[choice - 1] == 100) {
        printf("Invalid input.\n");
        
        puts("(Press A to continue)");
        scanf(" %c", &ch);
    
        if (ch == 'A' || ch == 'a') {
            system("clear");
            forensics();
        } 
    }

    switch (choice) {
        case 1: 
            analysisItem = discoveredItems[0];
            if (hasBeenChecked[0] == 1) {
                invalidScreen();
                forensics();
            } else {
                hasBeenChecked[0] = 1;
            }
            break;
        case 2: 
            analysisItem = discoveredItems[1];
            if (hasBeenChecked[1] == 1) {
                invalidScreen();
                forensics();
            } else {
                hasBeenChecked[1] = 1;
            }
            break;
        case 3: 
            analysisItem = discoveredItems[2];
            if (hasBeenChecked[2] == 1) {
                invalidScreen();
                forensics();
            } else {
                hasBeenChecked[2] = 1;
            }
            break;
        case 4: 
            analysisItem = discoveredItems[3];
            if (hasBeenChecked[3] == 1) {
                invalidScreen();
                forensics();
            } else {
                hasBeenChecked[3] = 1;
            }
            break;
        case 5: 
            if (choice - 1 == selectedSize) {
                printf("\nInvestigation complete.\n");

                puts("(Press A to continue)");
                scanf(" %c", &ch);
    
                if (ch == 'A' || ch == 'a') {
                    system("clear");
                    //(FOR TESTING ONLY)
                    killCode();
                } 
            } else {   
                if (hasBeenChecked[4] == 1) {
                    invalidScreen();
                    forensics();
                } else {
                    analysisItem = discoveredItems[4];
                    hasBeenChecked[4] = 1;
                }
            }
            break;
        case 6: 
            analysisItem = discoveredItems[5];
            if (hasBeenChecked[5] == 1) {
                invalidScreen();
                forensics();
            } else {
                hasBeenChecked[5] = 1;
            }
            break;
        case 7: 
            analysisItem = discoveredItems[6];
            if (hasBeenChecked[6] == 1) {
                invalidScreen();
                forensics();
            } else {
                hasBeenChecked[6] = 1;
            }
            break;
        case 8:
            analysisItem = discoveredItems[7];
            if (hasBeenChecked[7] == 1) {
                invalidScreen();
                forensics();
            } else {
                hasBeenChecked[7] = 1;
            }
            break;
        case 9:
            printf("\nInvestigation complete.\n");

            puts("(Press A to continue)");
                scanf(" %c", &ch);
    
                if (ch == 'A' || ch == 'a') {
                    system("clear");
                    //(FOR TESTING ONLY)
                    killCode();
                } 
            break;
        default: 
            invalidScreen();
            break;
    }

    pageNumber = analysisItem + 3;


    //assigns qualities to the item in question
    analysis(analysisItem);

    //returns to main page
    system("clear");
    forensics();
    
}

//will later be renamed "endOfGame" - ends the game early
void killCode() {
char ch;
    
    system("clear");
    printf("Code has been killed.\n");
    scanf(" %c", &ch);
}


//just for visuals/simplicity (no input required)
void printBox() {
    
    for (int n = 1; n <= 82; n++) {
        printf("=");
    }
    
    printf("\n\n ");
    for (int n = 1; n <= 80; n++) {
        printf("_");
    }
    printf(" \n");

    for (int n = 1; n <= 2; n++) {
        printf("|%81s\n", "|");
    }

    //these 4 rows are for gameplay text
    gameplayText();
    
    for (int n = 1; n <= 2; n++) {
        printf("|%81s\n", "|");
    }
    
    printf("|");
    for (int n = 1; n <= 80; n++) {
        printf("_");
    }
    printf("|\n");
}

void itemScreen() {
static int itemOrder = 0;

    printf("\n ");
    for (int n = 1; n <= 80; n++) {
        printf("_");
    }
    printf(" \n");

    //calculates and displays items collected
    printf(" Items: \n");
    printItems();
    
}

void printItems() {
static int count = 0;

    //prints a blank list of items the first time
    if (count == 0) {
        for (int i = 0; i < selectedSize; i++) {
            printf("%s\n", " ");
        }
        count = 1;
    } else {
        for (int i = 0; i < selectedSize; i++) {
            //prints blank if the slot is not filled yet
            if (printItem[i] == 100) {
                printf("%s\n", " ");
            } else {
                //prints the string that matches the item's tag
                printf(" %s\n", foundItemsString[itemValue[i]]);
            }
        }
    }

}

//NOT DONE YET (RETURN EVERY TIME YOU UPDATE THE ITEM/QUALITY LIST)
void printAnalysis(int arr[]) {
static int count = 0;
static int countCase[60] = {0};
char qualities[][40] = {{"lastname"}, {"profession"}, {"A+"}, {"A-"}, {"B+"}, {"B-"}, {"AB+"}, {"AB-"}, {"O+"}, {"O-"}, {"loops"}, {"whorls"}, {"arches"}, {"right hand"}, {"left hand"}, {"coffee"}, {"tea"}, {"male"}, {"female"}, {"tall"}, {"short"}, {"average"}, {"short"}, {"medium"}, {"long"}, {"black"}, {"brown"}, {"red"}, {"blonde"}, {"white"}, {"2 and 1/2"}, {"3"}, {"3 and 1/2"}, {"4"}, {"4 and 1/2"}, {"5"}, {"5 and 1/2"}, {"6"}, {"6 and 1/2"}, {"7"}, {"7 and 1/2"}, {"8"}, {"8 and 1/2"}, {"9"}, {"9 and 1/2"}, {"near-sighted"}, {"far-sighted"}, {"blue"}, {"green"}, {"hazel"}, {"brown"}, {"black"}, {"print"}, {"cursive"}, {"initials A B C"}};
    
    //prints results of analysis
    printf("\n ");
    for (int n = 1; n <= 80; n++) {
        printf("_");
    }
    
    printf(" \n");
    
    //FOR TESTING ONLY - prints itemQualities[]
    for (int i = 0; i < 12; i++) {
        printf(" %d", itemQualities[i]);
    }
    puts("");

    //prints one line of dialogue based on the quality type
    switch (arr[count]) {
        case 0: 
        if (countCase[arr[count]] == 1) {
            puts("This is something we already know.");
        }
        puts(" Nothing was found.");
        break;
        case 1:
        printf(" The culprit's last name is ");
        printf("%s.\n", qualities[0]);
        break;
        case 2:
        printf(" The culprit previously worked as %s.\n", qualities[1]);
        break;
        case 3:
        printf(" The culprit's blood type is %s.\n", qualities[rand()%8 + 2]);
        break;
        //special case (multiple qualities)
        //revise this system (murder item breaks it as soon as case 4 is activated)
        case 4:
        case 5:
            if (arr[count] == 4) {
                printf(" The culprit's fingerprint contains %s.\n", qualities[rand()%3 + 10]);
            } else if (arr[count] == 5) {
                printf(" The culprit mainly uses their %s.\n", qualities[rand()%2 + 13]);
            }

            if (arr[count + 1] == 6) {
                puts(" The culprit likes to drink alcohol.");
            } else if (arr[count + 1] == 7) {
                printf(" The culprit likes to drink %s.\n", qualities[rand()%2 + 15]);
            } else {
                break;
            }

        count++;
        break;
        case 8:
        printf(" The culprit is %s.\n", qualities[rand()%2 + 17]);
        break;
        case 9:
        printf(" The culprit's height is %s.\n", qualities[rand()%3 + 19]);
        break;
        //special case (multiple qualities)
        case 10:
        printf(" The culprit's hair length is %s.\n", qualities[rand()%3 + 22]);
        printf(" The culprit has %s hair.\n", qualities[rand()%5 + 25]);
        count++;
        break;
        case 12:
        puts(" The culprit likes to smoke cigarettes.");
        break;
        case 13:
        printf(" The culprit's foot size is %s.\n", qualities[rand()%15 + 28]);
        break;
        case 14:
        printf(" The culprit is %s.\n", qualities[rand()%2 + 44]);
        break;
        case 15:
        printf(" The culprit's eyes are not naturally %s.\n", qualities[rand()%5 + 46]);
        break;
        case 16:
        printf(" The culprit hand-writes in %s.\n", qualities[rand()%2 + 51]);
        break;
        case 17:
        printf("The culprit's initials are: %s.\n", qualities[53]);
        break;
        
        
    }
    count++;
}


//dialogue system - NOT DONE YET
//NOT DONE YET (RETURN EVERY TIME YOU UPDATE THE ITEM/QUALITY LIST)
void gameplayText (int caseID_A, int caseID_B) {

    //will use caseID to figure out which page to start from

    //change this later so that all the item pages start at 0
    
    //switch system: each "page" in the story will be defined here
    switch (pageNumber) {
        case 0:
            printf("|%30s%s%-30s|\n", "", "Welcome to my house.", "");
            printf("|%11s%s%-11s|\n", "", "I would have cleaned it up before but, you know, evidence.", "");
            printf("|%13s%s%-13s|\n", "", "The thief ransacked my place, and everything's a mess!", "");
            printf("|%12s%s%-12s|\n", "", "On the bright side, we can search for clues left behind.", "");
            break;
        case 1:
            printf("|%30s%s%-30s|\n", "", "We've found so much!", "");
            printf("|%28s%s%-28s|\n", "", "I think we're done here.", "");
            printf("|%12s%s%-12s|\n", "", "I wish I could stay and clean, but we've got work to do.", "");
            printf("|%8s%s%-8s|\n", "", "Let's go to the forensics lab and examine the evidence we found.", "");
            break;
        case 2: 
            printf("|%18s%s%-18s|\n", "", "Here we are! Can you smell the formaldehyde?", "");
            printf("|%16s%s%-16s|\n", "", "The forensics lab scans for all sorts of things.", "");
            printf("|%15s%s%-15s|\n", "", "Blood type, fingerprints, graphology, you name it!", "");
            printf("|%27s%s%-27s|\n", "", "Select an item to scan it.", "");
            break;
        //do case 3: to case 21:1
        case 3:
            printf("|%33s%s%-33s|\n", "", "Analysis Item:", "");
            printf("|%28s%s%-28s|\n", "", "Receipt for a Ring Frame", "");
            printf("|%26s%s%-26s|\n", "", "The receipt is addressed to someone...", "");
            //come back to this later, when you have a naming system
            printf("|%27s%s%-27s|\n", "", "Mr./Ms./Mrs. CULPRIT NAME.", "");
            break;
        case 4:
            printf("|%33s%s%-33s|\n", "", "Analysis Item:", "");
            printf("|%29s%s%-29s|\n", "", "Jewelry-Polishing Set ", "");
            printf("|%14s%s%-14s|\n", "", "The culprit must have cleaned the diamond with this.", "");
            printf("|%12s%s%-12s|\n", "", "Unfortunately, it seems the polishing set was wiped too.", "");
            break;
        case 5:
            printf("|%33s%s%-33s|\n", "", "Analysis Item:", "");
            printf("|%34s%s%-34s|\n", "", "Roll of Cash", "");
            printf("|%12s%s%-12s|\n", "", "Woah, this is a lot of- wait a minute, it's counterfeit!", "");
            printf("|%19s%s%-19s|\n", "", "Whoever pulled this off must be an artist.", "");
            break;
        case 6:
            printf("|%33s%s%-33s|\n", "", "Analysis Item:", "");
            printf("|%32s%s%-32s|\n", "", "Empty Money Bag ", "");
            printf("|%19s%s%-19s|\n", "", "Looks like there's no need for it anymore.", "");
            printf("|%20s%s%-20s|\n", "", "There's no data either - that's too bad.", "");
            break;
        case 7:
            printf("|%33s%s%-33s|\n", "", "Analysis Item:", "");
            printf("|%35s%s%-35s|\n", "", "Tiger fuzz", "");
            printf("|%18s%s%-18s|\n", "", "There's a bit of blood on this ball of fuzz.", "");
            printf("|%21s%s%-21s|\n", "", "Seems like that tiger is quite fierce.", "");
            break;
        case 8:
            printf("|%33s%s%-33s|\n", "", "Analysis Item:", "");
            printf("|%36s%s%-36s|\n", "", "Whisker ", "");
            printf("|%16s%s%-16s|\n", "", "A single whisker, much too long for a house cat.", "");
            printf("|%25s%s%-25s|\n", "", "The tiger was definitely here.", "");
            break;
        case 9:
            printf("|%33s%s%-33s|\n", "", "Analysis Item:", "");
            printf("|%38s%s%-38s|\n", "", "Gun ", "");
            printf("|%23s%s%-23s|\n", "", "The murder weapon was left behind!", "");
            printf("|%17s%s%17s|\n", "", "The gun has a fingerprint on it. Unbelievable!", "");
            break;
        case 10:
            printf("|%33s%s%-33s|\n", "", "Analysis Item:", "");
            printf("|%37s%s%-37s|\n", "", "Knife ", "");
            printf("|%23s%s%-23s|\n", "", "The murder weapon was left behind!", "");
            printf("|%20s%s%-20s|\n", "", "Huh? The knife's got fingerprints on it.", "");
            break;
        case 11:
            printf("|%33s%s%-33s|\n", "", "Analysis Item:", "");
            printf("|%38s%s%-38s|\n", "", "Rope", "");
            printf("|%23s%s%-23s|\n", "", "The murder weapon was left behind!", "");
            printf("|%19s%s%-19s|\n", "", "The culprit left fingerprints on the rope.", "");
            break;
        case 12:
            printf("|%33s%s%-33s|\n", "", "Analysis Item:", "");
            printf("|%33s%s%-33s|\n", "", "Half-Empty Cup", "");
            printf("|%15s%s%-15s|\n", "", "Looks like the culprit was thirsty after all that.", "");
            printf("|%21s%s%-21s|\n", "", "The cup can give us extra information.", "");
            break;
        case 13:
            printf("|%33s%s%-33s|\n", "", "Analysis Item:", "");
            printf("|%37s%s%-37s|\n", "", "Gloves", "");
            printf("|%24s%s%-24s|\n", "", "A set of gloves was left behind.", "");
            printf("|%16s%s%-16s|\n", "", "They clearly came from a gendered clothing shop.", "");
            break;

        case 14:
            printf("|%33s%s%-33s|\n", "", "Analysis Item:", "");
            printf("|%38s%s%-38s|\n", "", "Rose", "");
            printf("|%12s%s%-12s|\n", "", "A rose was taken from this bouquet and dropped suddenly.", "");
            printf("|%12s%s%-12s|\n", "", "It pricked the culprit and now has a bit of blood on it.", "");
            break;
        case 15:
            printf("|%33s%s%-33s|\n", "", "Analysis Item:", "");
            printf("|%38s%s%-38s|\n", "", "Book", "");
            printf("|%18s%s%-18s|\n", "", "It was taken from that bookshelf over there.", "");
            printf("|%11s%s%-11s|\n", "", "The shelf it was taken from tells us the culprit's height.", "");
            break;
        case 16:
            printf("|%33s%s%-33s|\n", "", "Analysis Item:", "");
            printf("|%33s%s%-33s|\n", "", "Used Hairbrush", "");
            printf("|%7s%s%-7s|\n", "", "What kind of careless person takes the time to brush their hair...", "");
            printf("|%31s%s%-31s|\n", "", "At a crime scene?!", "");
            break;
        case 17:
            printf("|%33s%s%-33s|\n", "", "Analysis Item:", "");
            printf("|%32s%s%-32s|\n", "", "Cigarette Butts ", "");
            printf("|%12s%s%-12s|\n", "", "There are cigarette butts tossed on the floor. How rude.", "");
            printf("|%25s%s%-25s|\n", "", "The culprit is a heavy smoker.", "");
            break;
        case 18:
            printf("|%33s%s%-33s|\n", "", "Analysis Item:", "");
            printf("|%34s%s%-34s|\n", "", "Shoe Tracks ", "");
            printf("|%18s%s%-18s|\n", "", "These sneaker prints are common around here,", "");
            printf("|%19s%s%-19s|\n", "", "The shoe size, however, will prove useful.", "");
            break;
        case 19:
            printf("|%33s%s%-33s|\n", "", "Analysis Item:", "");
            printf("|%34s%s%-34s|\n", "", "Contact Lens", "");
            printf("|%19s%s%-19s|\n", "", "This must have been uncomfortable to wear.", "");
            printf("|%13s%s%-13s|\n", "", "It's got a unique prescription and color...or does it?", "");
            break;
        case 20:
            printf("|%33s%s%-33s|\n", "", "Analysis Item:", "");
            printf("|%34s%s%-34s|\n", "", "Suicide Note", "");
            printf("|%6s%s%-6s|\n", "", "Looking at the victim's handwriting, this note is clearly a forgery.", "");
            printf("|%5s%s%-5s|\n", "", "Even without the analysis, it's impossible to commit suicide this way.", "");
            break;
        case 21:
            printf("|%33s%s%-33s|\n", "", "Analysis Item:", "");
            printf("|%32s%s%-32s|\n", "", "Smudged Message ", "");
            printf("|%15s%s%-15s|\n", "", "The victim must have known who their attacker was.", "");
            printf("|%14s%s%-14s|\n", "", "They wrote the culprit's name, but it's all smudged.", "");
            break;
        


/*   
//Location Clues (kidnapping)
{"Party Invite"}, {"Concert Flyer"}, {"Charred Golden Coin"}
*/
    }
    
    /*
    //prototype for a single page; just replace s with whatever you want
    printf("|%40s%s%-40s|\n", "", "s", "");
    printf("|%40s%s%-40s|\n", "", "s", "");
    printf("|%40s%s%-40s|\n", "", "s", "");
    printf("|%40s%s%-40s|\n", "", "s", "");

    Idea: The actor/singer/royal's room is ransacked!
    Looks like he/she put up a fight.
    */
    
}