#include <iostream>
#include <ctime>
#include <vector>
#include <iomanip>

/*
Version Changes:
- window width has changed from 82/80 to 72/70
- most arrays have been replaced with vectors
- total item list no longer includes tutorial items and items have been rearranged
- Kidnapping case has been removed (though it is kept in mind, perhaps for higher-level cases?)
- a Suspect structure has been created for storing each suspect's profile
- function collectEvidence() has been renamed to findItem():
- function examineEvidence() has been renamed to examine();
- New pages and qualities were added

Game Ideas:
- Player level starts at 1 and is increased by 1 for every successful case solved
- every 5 levels, prices are increased by 45
- every 10 levels, a new case type will be unlocked (like kidnapping, which will follow a completely different format than theft and murder)
- Kidnapping ideas are just flowing here! okay, think of a 911-call type thing where you help the victim escape their prison (get inspiration from movies like The Call) AND also maybe a follow-the-suspect in the dark game like in FNAF Sister Location! You could do something like the rocket ship activity in class, but with hints like "close" "far away", "left", "right", etc.
- Change the investigating system so that the player must choose which clues seem "important" and add fake clues (put them in a "duds" vector)

Message to Future Gaby when she returns:
Hey! Hope you're doing good and not procrastinating! 
    Everything should be good to go now! You just have to create the realCulprit object and 5/10/15 suspect objects in prisonList.
    Remember, the real culprit should have a normal label, like Suspect 3. And preferably one that changes every round.
    If you want to do anything extra in between, you're still missing the dialogue for all the non-tutorial cases.
*/

//classes
#include "Suspect.h"

//shortcuts
using namespace std;

//function prototypes
void intro();
void tutorial(string name);
void caseSetup(string name);

void invalidScreen();
void continueGame();
int yesorno(string question);

void crimeScene();
void investigate();
void forensics();
void examine();
void directory();
void identify();

string objectSelect();
string murderSelect();
void itemList();
void findItem(int& count);
void analysis(int& item);
void prisonList(int suspects);

void printBox();
void itemScreen();
void printAnalysis(int item);
void suspectScreen();
void gameplayText();
void killCode();

//global variables
int caseID[3];
int pageNumber;

vector<string> selectedItems;
vector<string> foundItems;
vector<int> analyzedQualities;

int analysisIndex;

Suspect culprit("  Culprit");

//(does not include tutorial items)
vector<string> totalItems = {
//theft
"Receipt for a Ring Frame", "Jewelry-Polishing Set", "Roll of Cash", "Empty Money Bag", "Tiger Fuzz", "Whisker", 
//murder
"Gun", "Knife", "Rope", "Suicide Note", "Smudged Message", 
//suspect
"Half-Empty Cup", "Gloves", "Rose", "Book", "Used Hairbrush", "Cigarette Butts", "Shoe Tracks", "Contact Lens"};

//qualities (for printing in part 2)
vector<string> qualities = {
//no quality
"nothing", 
//title
"Mr.", "Ms.", "Mrs.", 
//profession (not completed yet)
"painting", "wrestling",  
//blood type
"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-", 
//fingerprint shape
"loops", "whorls", "arches", 
//predominant hand
"right hand", "left hand", 
//drink preference (if not alcoholic)
"coffee", "tea", "wine", 
//gender
"male", "female", 
//smoker
"yes", "no", 
//height
"short", "average", "tall", 
//hair length
"short", "medium", "long", 
//hair color
"black", "brown", "red", "blonde", "white", 
//shoe size
"2 and 1/2", "3", "3 and 1/2", "4", "4 and 1/2", "5", "5 and 1/2", "6", "6 and 1/2", "7", "7 and 1/2", "8", "8 and 1/2", "9", "9 and 1/2", 
//lens prescription
"near-sighted", "far-sighted", 
//lens color
"blue", "green", "hazel", "brown", "black", 
//handwriting
"print", "cursive", 
//first names
"Kevin", "Christopher", "Mark", "Joshua", "Eugene", "Nancy", "Laura",  "Melissa",  "Susan",  "Jennifer", 
//middle initials
"A", "M", "R", "L", "J", "N", "F", "S", "K", "E", 
//last names
"Rodriguez", "Perez", "Robinson", "Smith", "Moore", "Anderson", "Lee", "Jackson", "Davis", "Garcia" 
};

//starting the game


//welcome to the game
int main() {
    srand(time(0));
    system("clear");

    string line(72, '=');
    cout << endl << endl << line << endl << endl;
    cout << " Welcome to the game!" << endl;
    continueGame();
    intro();
    return 0;
}

//get name and offer tutorial
void intro() {
    string name;

    //boundary line
    string line(70, '_');
    cout << endl << " " << line << " " << endl << endl;
    
    //gets Detective's name
    cout << " What is your name, Detective?" << endl;
    getline(cin, name, '\n');

    //opens up option for tutorial
    if (yesorno(" Would you like to play the tutorial?") == 1) {
        //tutorial page
        system("clear");
        tutorial(name);
    } else {
        //case setup
        system("clear");
        caseSetup(name);
    }  
}

//explanation page
void tutorial(string name) {
    caseID[0] = caseID[1] = 9;
    caseID[2] = 1;

    string line(72, '=');
    cout << endl << endl << line << endl << endl;

    cout << " Hello Detective " << name << "! Welcome to your first case." << endl;
    cout << " A thief has stolen my favorite scarf." << endl;
    cout << " Find out who did it, for a hefty sum of course." << endl;
    cout << " Let's head to the crime scene!" << endl;

    continueGame();

    //TESTING
    system("clear");
    itemList();
}

//generates a random case
void caseSetup(string name) {
    vector<int> rewardArr = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};

    string line(72, '=');
    cout << endl << endl << line << endl << endl;

    cout << " Detective " << name << ", we need your help!" << endl;

    //generates case type and reward price
    int caseType = rand()%2;
    int reward = rewardArr[rand()%10];
    string objective, temp;

    switch (caseType) {
        case 0:
            objective = objectSelect();
            temp = objective.at(0);
            objective.erase(0,1);
            cout << " Someone has stolen " << objective << endl;
            cout << " Find out who took it, and you'll receive $" << reward << "." << endl;
            break;
        case 1:
            objective = murderSelect();
            temp = objective.at(0);
            objective.erase(0,1);
            cout << " Someone has died unexpectedly from " << objective << endl;
            cout << " Figure out who the murderer is, and you'll receive $" << reward << "." << endl;
            break;
    }
    
    //if yes, game starts - if no, generate new case
    if (yesorno(" Will you accept the case?") == 1) {
        //creates case ID
        caseID[0] = caseType;
        caseID[1] = stoi(temp);
        caseID[2] = reward;
        //pre-selects items to discover
        system("clear"); 
        itemList();
    } else {
        system("clear");
        caseSetup(name);
    }
}


//actual gameplay


//when the user makes a mistake
void invalidScreen() {
char ch;

    string line(70, '_');
    cout << endl << " " << line << endl << endl;
    
    cout << " That is not a valid response." << endl;
    
    continueGame();
}

//press enter to continue
void continueGame() {
    cout << endl << " (Press Enter to continue)" << endl;
    
    string ch;
    getline(cin, ch, '\n');
    
    if (ch != "") {
        invalidScreen();
    }
}

//yes or no question
int yesorno(string question) {
    //boundary line
    string line(70, '_');
    cout << endl << " " << line << " " << endl << endl;
    
    //displays question and options
    cout << question << endl;
    cout << " > Y" << endl;
    cout << " > N" << endl;
    
    string ch;
    getline(cin, ch, '\n');

    //yes is 1 and no is 0
    if (ch == "Y" || ch == "y") {
        return 1;
    } else if (ch == "N" || ch == "n") {
        return 0;
    } else {
        //mistake
        invalidScreen();
        //runs again and returns answer
        return yesorno(question);
    }
}

//part 1 (theft/murder): searching for clues
void crimeScene() {
    //TESTING
    cout << "Case ID: " << caseID[0] << "-" << caseID[1] << "-$" << caseID[2] << endl;

    //cout << endl << endl;
    printBox();
    itemScreen();
    investigate();
}

void investigate() {
    static int count;

    //asks user to investigate
    if (yesorno(" Investigate?") == 0) {
        //goes to forensics when done 
        system("clear");
        pageNumber++;
        forensics();
    } else {
        //ends investigation when all slots are filled
        if (count >= foundItems.size())  {
            cout << " There are no more items to find." << endl;
        } else {
            findItem(count);
        
            //reveal results
            cout << endl << " You found: " << foundItems.at(count) << endl;
            count++;
        }
        continueGame();
        system("clear");
        crimeScene();
    }
}

//part 2 (theft/murder): analyzing them for qualities
void forensics() {

    printBox();

    if (pageNumber == 20) {
        pageNumber++;
        continueGame();
        system("clear");
        forensics();
        return;
    } else if (pageNumber < 20 || pageNumber > 95) {
        //top line of analysis
        string line(70, '_');
        cout << endl << " " << line << " " << endl << " Results:" << endl;
        analysis(analysisIndex);
    }
    itemScreen();
    examine();
}

void examine() {
    //variables
    string temp;
    bool valid = false;
    //needs to be static or the checking system breaks
    static vector<int> hasBeenChecked(foundItems.size(), 0);
    
    //top line
    string line(70, '_');
    cout << endl << " " << line << " " << endl << endl;

    //asks user to analyze an item (by entering a number)
    cout << " Enter an item's number to analyze it." << endl;
    cout << " Enter " << foundItems.size() + 1 << " when all analysis is complete." << endl;
    //I have to use getline so continueGame doesn't nyoom through... not sure why but this is how it works
    getline(cin, temp, '\n');

    //in case the user enters anything other than the options
    for (int i = 1; i <= foundItems.size() + 1; i++) {
        if (temp == to_string(i)) {
            valid = true;
        }
    }
    if (valid == false) {
        invalidScreen();
        examine();
        return;
    }
    
    
    analysisIndex = stoi(temp);
    //shifts analysisIndex to the item's correct index
    analysisIndex--;

    //goes to the next section when done
    if (analysisIndex == foundItems.size()) {
        cout << endl << " Investigation complete." << endl;
        continueGame();
        system("clear");
        pageNumber = 22;
        directory();
        return;
    }
    
    //check if item has been analyzed already
    if (hasBeenChecked[analysisIndex] == 1) {
        invalidScreen();
        system("clear");
        forensics();
        return;
    } else {
        //if not, set it as analyzed
        hasBeenChecked[analysisIndex] = 1;
    }

    //special case for tutorial items
    if (caseID[0] == 9) {
        if (foundItems.at(analysisIndex) == "Torn Fabric") {
            pageNumber = 96;
        } else if (foundItems.at(analysisIndex) == "Hair Follicle") {
            pageNumber = 97;
        } else if (foundItems.at(analysisIndex) == "Fingerprint") {
            pageNumber = 98;
        } else if (foundItems.at(analysisIndex) == "Coffee Stain") {
            pageNumber = 99;
        }
    } else {
        //makes pageNumber the item's original value in totalItems
        for (int i = 0; i < totalItems.size(); i++) {
            if (foundItems.at(analysisIndex) == totalItems.at(i)) {
                pageNumber = i;
            }
        }
    }
    
    //do the analysis
    analysisIndex = pageNumber;

    system("clear");
    forensics();
}

//part 3 (theft/murder): figuring out who the culprit is
void directory() {

    //dialogue
    if (pageNumber == 22) {
        //complete culprit and create other suspects
        prisonList((caseID[0] == 9) ? 5: 10);
        
        printBox();
        pageNumber++;
        continueGame();
        system("clear");
        directory();
        return;
    } else if (pageNumber == 23) {
        printBox();

        //display culprit qualities
        string line(70, '_');
        cout << endl << " " << line << " " << endl << " Culprit Qualities:" << endl;

        for (int i : analyzedQualities) {
            if (i != -1) {
                printAnalysis(i);
            }
        }

/*
NOTE: asking the player to begin is useless if they can refer back to the qualities in identify(). For this reason, I am changing the code to use continueGame() instead.

I am keeping the original sample, however, to save it for when different levels are a thing and difficulty can be selected.

In hard mode, the qualities would not be visible (you'd have to try and memorize them).

        if (yesorno(" Ready to begin?") == 1) {
            pageNumber++;
            system("clear");
            directory();
            return;
        } else {
            system("clear");
            directory();
            return;
        }
*/  
        continueGame();
        pageNumber++;
        system("clear");
        directory();
        return;
    }

    suspectScreen();
    identify();
}

void identify() {
    killCode();
}

//behind-the-scenes stuff


//selects theft subcase
string objectSelect() {
    int object = rand()%3;
    
    switch (object) {
        case 0:
            return to_string(object) + "a rare diamond. ";
            break;
        case 1:
            return to_string(object) + "money from the bank. ";
            break;
        case 2:
            return to_string(object) + "a tiger from the zoo. ";
            break;
        //to stop the "It DoEsN't ReTuRn" warning
        default:
            return "que?";
            break;
    }
}

//selects murder subcase
string murderSelect() {
    int murder = rand()%3;

    switch (murder) {
        case 0:
            return to_string(murder) + "a gunshot wound. ";
            break;
        case 1:
            return to_string(murder) + "repeated stabbing. ";
            break;
        case 2:
            return to_string(murder) + "asphyxiation. ";
            break;
        //to stop the "It DoEsN't ReTuRn" warning
        default:
            return "que?";
            break;
    }
}

//generates items and sets first page number
void itemList() {
    switch (caseID[0]) {
        //tutorial items (4)
        case 9:
            pageNumber = 19;
            selectedItems.push_back("Torn Fabric");
            selectedItems.push_back("Hair Follicle");
            selectedItems.push_back("Fingerprint");
            selectedItems.push_back("Coffee Stain");
            break;
        //theft items (8)
        case 0:
            //TESTING
            pageNumber = 19;
            switch (caseID[1]) {
                //diamond
                case 0:
                    //pageNumber = ?
                    selectedItems.push_back(totalItems[0]);
                    selectedItems.push_back(totalItems[1]);
                    break;
                //bank money
                case 1:
                    //pageNumber = ?
                    selectedItems.push_back(totalItems[2]);
                    selectedItems.push_back(totalItems[3]);
                    break;
                //tiger
                case 2:
                    //pageNumber = ?
                    selectedItems.push_back(totalItems[4]);
                    selectedItems.push_back(totalItems[5]);
                    break;
            }

            //random (and unique) suspect clues
            selectedItems.push_back(totalItems[rand()%8 + 11]);

            //for items 4-8...
            for (int i = 3; i < 8; i++) {
                //generate number
                selectedItems.push_back(totalItems[rand()%8 + 11]);
                //for all numbers from item 3... to i
                for (int j = selectedItems.size() - 2; j >= 2; j--) {
                    //if item i is equal to item j
                    if (selectedItems.at(i) == selectedItems.at(j)) {
                        //remove the last item
                        selectedItems.pop_back();
                        //start again from i
                        i--;
                        //skip the j loop and go straight to i
                        continue;
                    }
                }
            }
            break;
        //murder items (8)
        case 1:
            //TESTING
            pageNumber = 19;
            switch (caseID[1]) {
                //gun
                case 0:
                    //pageNumber = ?
                    selectedItems.push_back(totalItems[6]);
                    break;
                //knife
                case 1:
                    //pageNumber = ?
                    selectedItems.push_back(totalItems[7]);
                    break;
                //rope
                case 2:
                    //pageNumber = ?
                    selectedItems.push_back(totalItems[8]);
                    break;
            }
            //suicide note or smudged letter
            selectedItems.push_back(totalItems[rand()%2 + 9]);

            //random (and unique) suspect clues
            selectedItems.push_back(totalItems[rand()%8 + 11]);

            for (int i = 3; i < 8; i++) {
                selectedItems.push_back(totalItems[rand()%8 + 11]);
                for (int j = selectedItems.size() - 2; j >= 2; j--) {
                    if (selectedItems.at(i) == selectedItems.at(j)) {
                        selectedItems.pop_back();
                        i--;
                        continue;
                    }
                }
            }
            break;     
    }
    //defines foundItems vector
    for (int i = 0; i < selectedItems.size(); i++) {
        foundItems.push_back("100");
    }
    //go to crime scene
    crimeScene();
}

//randomly assigns an element from selectedItems to foundItems
void findItem(int& count) {

    //exception for last item found (rng doesn't work with one variable left)
    if (count == foundItems.size() - 1) {
        foundItems.at(count) = selectedItems.at(0);
        return;
    }
    
    //find unique item
    foundItems.at(count) = selectedItems.at(rand()%(selectedItems.size() - 1));
    
    //remove said item from selectedItems (to prevent duplicates)
    for (int i = 0; i < selectedItems.size(); i++) {
        //find the item in selectedItems
        if (foundItems.at(count) == selectedItems.at(i)) {
            ///assign the last element to temp
            string temp = selectedItems.at(selectedItems.size() - 1);
            //replace last element with the found item
            selectedItems.at(selectedItems.size() - 1) = foundItems.at(count);
            //put the last element (temp) in the found item's location
            selectedItems.at(i) = temp;
            //erase the last item
            selectedItems.pop_back();
        }
    }   
}

//generates the item's quality number and assigns it to culprit
void analysis(int& item) {
    int quality1 = -1, quality2 = -1, quality3 = -1;
    
    switch (item) {
        //Jewelry-Polishing Set, Empty Money Bag, Whisker
        case 1:    case 3:    case 5:
            //nothing
            quality1 = 0;
            break;
        //Receipt for a Ring Frame (multiple qualities)
        case 0:
            //title
            quality1 = rand()%3 + 1;
            
            if (culprit.getQuality(0) == "not defined") {
                culprit.setQuality(0, qualities.at(quality1));
            }

            //last name
            quality3 = rand()%10 + 81;
            if (culprit.getQuality(3) == "not defined") {
                culprit.setQuality(3, qualities.at(quality3));
            }
            break;
        //Roll of Cash
        case 2:
            quality1 = 4;
            
            if (culprit.getQuality(4) == "not defined") {
                culprit.setQuality(4, qualities.at(quality1));
            }
            break;
        //Tiger Fuzz, Rose
        case 4:    case 13:
            //blood type
            quality1 = rand()%8+6;
            
            if (culprit.getQuality(5) == "not defined") {
                culprit.setQuality(5, qualities.at(quality1));
            }
            break;
        //Gun, Knife, Rope, (T) Fingerprint
        case 6:    case 7:    case 8:    case 98:
            //fingerprint
            quality1 = rand()%3 + 14;
            
            if (culprit.getQuality(6) == "not defined") {
                culprit.setQuality(6, qualities.at(quality1));
            }
            break;
        //Suicide Note
        case 9:
            //handwriting
            quality1 = rand()%2 + 59;
            
            if (culprit.getQuality(17) == "not defined") {
                culprit.setQuality(17, qualities.at(quality1));
            }
            break;
        //Smudged Message
        case 10:
            //change initials based on gender
            if (culprit.getQuality(9) == "not defined") {
                quality1 = rand()%10 + 61;
            } else if (culprit.getQuality(9) == "male") {
                quality1 = rand()%5 + 61;
            } else if (culprit.getQuality(9) == "female") {
                quality1 = rand()%5 + 66;
            }

            //set initials
            quality2 = rand()%10 + 71;
            quality3 = rand()%10 + 81;

            if (culprit.getQuality(18) == "not defined") {
                string a = "     ";
                a.at(0) = qualities.at(quality1).front();
                a.at(2) = qualities.at(quality2).front();
                a.at(4) = qualities.at(quality3).front();
                culprit.setQuality(18, a);
            }
            
            //change initials based on last name
            if (culprit.getQuality(3) != "not defined") {
                culprit.getQuality(18).at(4) = culprit.getQuality(3).at(0);
            }
            break;
        //Half-Empty Cup (multiple qualities)
        case 11:
            //fingerprint or dominant hand
            quality1 = rand()%5 + 14;
            
            if (quality1 < 17 && culprit.getQuality(6) == "not defined") {
                culprit.setQuality(6, qualities.at(quality1));
            } else if (quality1 < 19 && culprit.getQuality(7) == "not defined") {
                culprit.setQuality(7, qualities.at(quality1));
            }
            //drink preference
            quality2 = rand()%3 + 19;
            
            if (culprit.getQuality(8) == "not defined") {
                culprit.setQuality(8, qualities.at(quality2));
            }
            break;
        //Gloves
        case 12:
            //gender
            quality1 = rand()%2 + 22;
            
            if (culprit.getQuality(9) == "not defined") {
                culprit.setQuality(9, qualities.at(quality1));
            }
            break;
        //Book
        case 14:
            //height
            quality1 = rand()%3 + 26;
            
            if (culprit.getQuality(11) == "not defined") {
                culprit.setQuality(11, qualities.at(quality1));
            }
            break;
        //Used Hairbrush, (T) Hair Follicle (multiple qualities)
        case 15:    case 97:
            //hair length
            quality1 = rand()%3 + 29;
            
            if (culprit.getQuality(12) == "not defined") {
                culprit.setQuality(12, qualities.at(quality1));
            }
            
            //hair color
            quality2 = rand()%5 + 32;
            
            if (culprit.getQuality(13) == "not defined") {
                culprit.setQuality(13, qualities.at(quality2));
            }
            break;
        //Cigarette Butts
        case 16:
            //smoker
            quality1 = 24;
            
            if (culprit.getQuality(10) == "not defined") {
                culprit.setQuality(10, qualities.at(quality1));
            }
            break;
        //Shoe Tracks
        case 17:
            //shoe size
            quality1 = rand()%15 + 37;
            
            if (culprit.getQuality(14) == "not defined") {
                culprit.setQuality(14, qualities.at(quality1));
            }
            break;
        //Contact Lens
        case 18:
            //prescription or color
            quality1 = rand()%7 + 52;
            
            if (quality1 < 54 && culprit.getQuality(15) == "not defined") {
                culprit.setQuality(15, qualities.at(quality1));
            } else if (quality1 < 59 && culprit.getQuality(16) == "not defined") {
                culprit.setQuality(16, qualities.at(quality1));
            }
            break;
        //(T) Torn Fabric
        case 96:
            //profession (wrestler only)
            quality1 = 5;
            
            if (culprit.getQuality(4) == "not defined") {
                culprit.setQuality(4, qualities.at(quality1));
            }
            break;
        //(T) Coffee Stain
        case 99:
            //drink preference (coffee only)
            quality1 = 19;
            
            if (culprit.getQuality(8) == "not defined") {
                culprit.setQuality(8, qualities.at(quality1));
            }
            break;
    }

    //send results to printAnalysis
    if (quality1 == 0) {
        printAnalysis(-1);
    } else {
        //adds to the global vector (to print them all at once in section 3 of the base game)
        analyzedQualities.push_back(item);
        printAnalysis(item);
    }
}

void prisonList(int suspects) {
    //number of suspects/additions and threshold of "sameness" allowed when creating
    int susNum, extraQual, sameness;

    //gamemode (to be used later)
    string mode;

    //create empty vector of suspects 
    vector<Suspect> suspectList;
    
    //create the realCulprit object and complete the qualities
    Suspect realCulprit(culprit);
    suspectList.push_back(realCulprit);


    //tutorial: 5 qualities, no mandatory additions
    if (caseID[0] == 9) {
        susNum = 5;
        extraQual = 2;
        mode = "super easy";
    } else { //theft or murder: ? qualities, ? possible mandatory additions
        susNum = 15;
        extraQual = 4;
        mode = "easy";
    }

    //complete realCulprit with mandatory additions
    for (int n = 0; n < 19; n++) {
        realCulprit.printQualities(n);
    }

    //create list of suspects
    for (int i = 0; i < susNum - 1; i++) {
        Suspect suspect;
        suspectList.push_back(suspect);
    }

    //determine difficulty
    if (mode == "super easy") {
        sameness = 0;
    } else if (mode == "easy") {
        sameness = 3;
    }
    
    //complete suspects
    for (int i = 0; i < extraQual; i++) { //for each extra quality...
        for (int i = 1; i < susNum; i++) { //for each suspect
            for (int n = 0; n < 18; i++) { //for each defined quality...
                if (realCulprit.getQuality(n) != "not defined") {
                    //first copy sameness qualities from culprit
                    
                }
            }
        }
    }

    //add randomized name labels
    int arr[susNum];
    for (int i = 0; i < susNum; i++) { //for all suspects (including realCulprit)
        arr[i] = i + 1;
    }
    for (int i = 0; i < susNum; i++) { //for all suspects (including realCulprit)
        suspectList[i].setQuality(19, "Suspect ");
        //remember to add the randomized numbers!
    }

    //do extra additions
    for (int i = 0; i < extraQual; i++) { //for each extra quality...
        for (int i = 1; i < susNum; i++) { //for each suspect...
            //AAAAAAAAAAAAAA
        }
    }

    

    continueGame();
    system("clear");

    //for any qualities that are directly correlated
}

//visuals only


void printBox() {
    //top line
    string line1(72, '=');
    cout << endl << endl << line1;

    //top border of box
    string line2(70, '_');
    cout << endl << endl << " " << line2 << " " << endl;
    //sides of box
    for (int n = 1; n <= 2; n++) {
        cout << "|" << setw(71) << "|" << endl;
    }
    //4 rows of gameplay text
    gameplayText();
    //sides of box
    for (int n = 1; n <= 2; n++) {
        cout << "|" << setw(71) << "|" << endl;
    }
    //bottom border of box
    string line3(70, '_');
    cout << "|" << line3 << "|" << endl;
}

void itemScreen() {
    static int count = 0;
    
    //top line and Items title
    string line(70, '_');
    cout << endl << " " << line << " " << endl << " Items:" << endl;

    //prints a blank list of items the first time
    if (count == 0) {
        for (int i = 0; i < foundItems.size(); i++) {
            cout << endl;
        }
        count = 1;
    } else {
        for (int i = 0; i < foundItems.size(); i++) {
            //prints a blank if not filled yet
            if (foundItems.at(i) == "100") {
                cout << endl;
            } else {
                //prints found items
                cout << " " << i + 1 << " - "<< foundItems.at(i) << endl;
            }
        }
    }
}

void printAnalysis(int item) {
    //prints dialogue for each quality type
    switch (item) {
        //all dud/repeat items
        case -1:
            cout << " No new information was found." << endl;
            break;
        //Receipt for a Ring Frame (multiple qualities)
        case 0:
            //NOT COMPLETED YET
            //title
            cout << " The receipt is addressed to a " << culprit.getQuality(0) << " " << culprit.getQuality(3) << "." << endl;
            break;
        //Roll of Cash, (T) Torn Fabric
        case 2:    case 96:
            //NOT COMPLETED YET
            //profession (artist only and wrestler only)
            cout << " The culprit works in " << culprit.getQuality(4) << "." << endl;
            break;
        //Tiger Fuzz, Rose
        case 4:    case 13:
            //blood type
            cout << " The culprit's blood type is " << culprit.getQuality(5) << "." << endl;
            break;
        //Gun, Knife, Rope, (T) Fingerprint
        case 6:    case 7:    case 8:    case 98:
            //fingerprint
            cout << " The culprit's fingerprint is in the shape of " << culprit.getQuality(6) << "." << endl;
            break;
        //Suicide Note
        case 9:
            //handwriting
            cout << " The culprit's handwriting is in " << culprit.getQuality(17) << "." << endl;
            break;
        //Smudged Message
        case 10:
            //initials
            cout << " The initials written are " << culprit.getQuality(18).at(0) << ", " << culprit.getQuality(18).at(2) << ", and " << culprit.getQuality(18).at(4) << "." << endl;
            break;
        //Half-Empty Cup (multiple qualities)
        case 11:
            //fingerprint or dominant hand
            if (culprit.getQuality(6) != "not defined") {
                cout << " The culprit's fingerprint is in the shape of " << culprit.getQuality(6) << "." << endl;
            } else if (culprit.getQuality(7) != "not defined") {
                cout << " The culprit primarily uses their " << culprit.getQuality(7) << " hand." << endl;
            }
            //drink preference
            cout << " The culprit likes to drink " << culprit.getQuality(8) << "." << endl;
            break;
        //Gloves
        case 12:
            //gender
            cout << " The culprit is " << culprit.getQuality(9) << "." << endl;
            break;
        //Book
        case 14:
            //height
            cout << " Someone with " << culprit.getQuality(11) << " height selected this book." << endl;
            break;
        //Used Hairbrush, (T) Hair Follicle (multiple qualities)
        case 15:    case 97:
            //hair length
            cout << " The hair on this brush is from a " << culprit.getQuality(12) << "-length hairstyle." << endl;
            
            //hair color
            cout << " The culprit has " << culprit.getQuality(13) << " hair." << endl;
            break;
        //Cigarette Butts
        case 16:
            cout << " The culprit smokes cigarettes." << endl;
            break;
        //Shoe Tracks
        case 17:
            //shoe size
            cout << " The culprit's shoe size is " << culprit.getQuality(14) << "." << endl;
            break;
        //Contact Lens
        case 18:
            //prescription or color            
            if (culprit.getQuality(15) != "not defined") {
                cout << " The culprit is " << culprit.getQuality(15) << "." << endl;
            } else if (culprit.getQuality(16) != "not defined") {
                cout << " The culprit's eyes are not naturally " << culprit.getQuality(16) << "." << endl;
            break;
        //(T) Coffee Stain - coffee only
        case 99:
            //drink preference
            cout << " The culprit likes to drink " << culprit.getQuality(8) << "." << endl;
            break;
        }
    }
}

void suspectScreen() {
    //top line
    string line1(72, '=');
    cout << endl << endl << line1;

    //top border of box
    string line2(70, '_');
    cout << endl << endl << " " << line2 << " " << endl;

    //sides and interior of box
    for (int n = 0; n <= 18; n++) {
        culprit.printQualities(n);
    }

    //bottom border of box
    string line3(32, '_');
    string line4(37, '_');
    cout << "|" << line3 << "|" << line4 << "|" << endl; 
}

void gameplayText() {
    switch (pageNumber) {
        //items
        case 0:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(23) << "" << "Receipt for a Ring Frame" << setw(23) << "" << "|" << endl;
            cout << "|" << setw(16) << "" << "The receipt is addressed to someone..." << setw(16) << "" << "|" << endl;
            cout << "|" << setw(17) << "" << "Now we know the culprit's last name." << setw(17) << "" << "|" << endl;
            break;
        case 1:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(24) << "" << "Jewelry-Polishing Set " << setw(24) << "" << "|" << endl;
            cout << "|" << setw(14) << "" << "The culprit cleaned the diamond with this." << setw(14) << "" << "|" << endl;
            cout << "|" << setw(15) << "" << "Aw man! The polishing set was wiped too." << setw(15) << "" << "|" << endl;
            break;
        case 2:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(29) << "" << "Roll of Cash" << setw(29) << "" << "|" << endl;
            cout << "|" << setw(13) << "" << "So much  left behind - but it's counterfeit!" << setw(13) << "" << "|" << endl;
            cout << "|" << setw(14) << "" << "Whoever pulled this off must be an artist." << setw(14) << "" << "|" << endl;
            break;
        case 3:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(27) << "" << "Empty Money Bag " << setw(27) << "" << "|" << endl;
            cout << "|" << setw(16) << "" << "Looks like there's no need for it now." << setw(16) << "" << "|" << endl;
            cout << "|" << setw(15) << "" << "There's no data either - that's too bad." << setw(15) << "" << "|" << endl;
            break;
        case 4:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(30) << "" << "Tiger Fuzz" << setw(30) << "" << "|" << endl;
            cout << "|" << setw(18) << "" << "There's blood on this wad of fuzz." << setw(18) << "" << "|" << endl;
            cout << "|" << setw(16) << "" << "Seems like that tiger is quite fierce." << setw(16) << "" << "|" << endl;
            break;
        case 5:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(31) << "" << "Whisker " << setw(31) << "" << "|" << endl;
            cout << "|" << setw(14) << "" << "It's much too long to be from a house cat." << setw(14) << "" << "|" << endl;
            cout << "|" << setw(20) << "" << "The tiger was definitely here." << setw(20) << "" << "|" << endl;
            break;
        case 6:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(33) << "" << "Gun " << setw(33) << "" << "|" << endl;
            cout << "|" << setw(18) << "" << "The murder weapon was left behind!" << setw(18) << "" << "|" << endl;
            cout << "|" << setw(19) << "" << "It has a fingerprint on it, too." << setw(19) << "" << "|" << endl;
            break;
        case 7:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(32) << "" << "Knife " << setw(32) << "" << "|" << endl;
            cout << "|" << setw(18) << "" << "The murder weapon was left behind!" << setw(18) << "" << "|" << endl;
            cout << "|" << setw(15) << "" << "Huh? The knife's got fingerprints on it." << setw(15) << "" << "|" << endl;
            break;
        case 8:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(33) << "" << "Rope" << setw(33) << "" << "|" << endl;
            cout << "|" << setw(18) << "" << "The murder weapon was left behind!" << setw(18) << "" << "|" << endl;
            cout << "|" << setw(14) << "" << "The culprit left fingerprints on the rope." << setw(14) << "" << "|" << endl;
            break;
        case 9:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(29) << "" << "Suicide Note" << setw(29) << "" << "|" << endl;
            cout << "|" << setw(16) << "" << "It's obvious this note is a forgery..." << setw(16) << "" << "|" << endl;
            cout << "|" << setw(13) << "" << "It is impossible to commit suicide this way." << setw(13) << "" << "|" << endl;
            break;
        case 10:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(27) << "" << "Smudged Message " << setw(27) << "" << "|" << endl;
            cout << "|" << setw(14) << "" << "The victim must have known their attacker." << setw(14) << "" << "|" << endl;
            cout << "|" << setw(15) << "" << "A name was jotted down in messy writing." << setw(15) << "" << "|" << endl;
            break;
        case 11:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(28) << "" << "Half-Empty Cup" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(19) << "" << "I guess the culprit was thirsty." << setw(19) << "" << "|" << endl;
            cout << "|" << setw(16) << "" << "The cup can give us extra information." << setw(16) << "" << "|" << endl;
            break;
        case 12:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(32) << "" << "Gloves" << setw(32) << "" << "|" << endl;
            cout << "|" << setw(19) << "" << "A set of gloves was left behind." << setw(19) << "" << "|" << endl;
            cout << "|" << setw(11) << "" << "They clearly came from a gendered clothing shop." << setw(11) << "" << "|" << endl;
            break;
        case 13:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(33) << "" << "Rose" << setw(33) << "" << "|" << endl;
            cout << "|" << setw(18) << "" << "A rose was taken from its bouquet." << setw(18) << "" << "|" << endl;
            cout << "|" << setw(15) << "" << "It pricked someone, who then bled on it." << setw(15) << "" << "|" << endl;
            break;
        case 14:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(33) << "" << "Book" << setw(33) << "" << "|" << endl;
            cout << "|" << setw(13) << "" << "It was taken from that bookshelf over there." << setw(13) << "" << "|" << endl;
            cout << "|" << setw(12) << "" << "You can tell exactly which shelf it came from." << setw(12) << "" << "|" << endl;
            break;
        case 15:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(28) << "" << "Used Hairbrush" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(15) << "" << "What kind of idiot brushes their hair..." << setw(15) << "" << "|" << endl;
            cout << "|" << setw(26) << "" << "At a crime scene?!" << setw(26) << "" << "|" << endl;
            break;
        case 16:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(27) << "" << "Cigarette Butts " << setw(27) << "" << "|" << endl;
            cout << "|" << setw(18) << "" << "Cigarette butts are on the ground." << setw(18) << "" << "|" << endl;
            cout << "|" << setw(20) << "" << "The culprit is a heavy smoker." << setw(20) << "" << "|" << endl;
            break;
        case 17:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(29) << "" << "Shoe Tracks " << setw(29) << "" << "|" << endl;
            cout << "|" << setw(13) << "" << "These sneaker prints are common around here." << setw(13) << "" << "|" << endl;
            cout << "|" << setw(14) << "" << "The shoe size, however, will prove useful." << setw(14) << "" << "|" << endl;
            break;
        case 18:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(29) << "" << "Contact Lens" << setw(29) << "" << "|" << endl;
            cout << "|" << setw(14) << "" << "This must have been uncomfortable to wear." << setw(14) << "" << "|" << endl;
            cout << "|" << setw(14) << "" << "They must have some prescription or color." << setw(14) << "" << "|" << endl;
            break;
        //tutorial
        case 19:
            cout << "|" << setw(25) << "" << "Welcome to my house!" << setw(25) << "" << "|" << endl;
            cout << "|" << setw(12) << "" << "I would have cleaned it, but we need evidence." << setw(12) << "" << "|" << endl;
            cout << "|" << setw(14) << "" << "Everything's a mess, thanks to that thief!" << setw(14) << "" << "|" << endl;
            cout << "|" << setw(19) << "" << "Let's just wrap this up quickly." << setw(19) << "" << "|" << endl;
            break;
        case 20:
            cout << "|" << setw(25) << "" << "We've found so much!" << setw(25) << "" << "|" << endl;
            cout << "|" << setw(23) << "" << "I think we're done here." << setw(23) << "" << "|" << endl;
            cout << "|" << setw(19) << "" << "Let's head to the forensics lab!" << setw(19) << "" << "|" << endl;
            cout << "|" << setw(14) << "" << "There we'll examine the evidence we found." << setw(14) << "" << "|" << endl;
            break;
        case 21:
            cout << "|" << setw(13) << "" << "Here we are! Can you smell the formaldehyde?" << setw(13) << "" << "|" << endl;
            cout << "|" << setw(13) << "" << "The forensics lab scans a variety of things." << setw(13) << "" << "|" << endl;
            cout << "|" << setw(14) << "" << "Blood, fingerprints, graphology, anything!" << setw(14) << "" << "|" << endl;
            cout << "|" << setw(22) << "" << "Select an item to scan it." << setw(22) << "" << "|" << endl;
            break;
        case 22:
            cout << "|" << setw(15) << "" << "You were so efficient with the analysis!" << setw(15) << "" << "|" << endl;
            cout << "|" << setw(11) << "" << "At this rate, we'll find the culprit in no time." << setw(11) << "" << "|" << endl;
            cout << "|" << setw(15) << "" << "Now it's time to visit the local prison." << setw(15) << "" << "|" << endl;
            cout << "|" << setw(14) << "" << "We have a list of suspects waiting for us." << setw(14) << "" << "|" << endl;
            break;
        case 23:
            cout << "|" << setw(16) << "" << "Almost everybody here is on probation." << setw(16) << "" << "|" << endl;
            cout << "|" << setw(14) << "" << "They're here for repeat misdemeanors, too." << setw(14) << "" << "|" << endl;
            cout << "|" << setw(14) << "" << "Let's review the information on our thief." << setw(14) << "" << "|" << endl;
            cout << "|" << setw(12) << "" << "I bet this is specific enough for prosecution." << setw(12) << "" << "|" << endl;
            break;
        //other case dialogue (TBD)
        //tutorial items
        case 96:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(29) << "" << "Torn Fabric " << setw(29) << "" << "|" << endl;
            cout << "|" << setw(12) << "" << "That scarf was imported just for its strength!" << setw(12) << "" << "|" << endl;
            cout << "|" << setw(12) << "" << "It would be easier to rip a phone book in two." << setw(12) << "" << "|" << endl;
            break;
        case 97:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(28) << "" << "Hair Follicle " << setw(28) << "" << "|" << endl;
            cout << "|" << setw(18) << "" << "This single hair contains so much!" << setw(18) << "" << "|" << endl;
            cout << "|" << setw(15) << "" << "With it comes accurate length and color." << setw(15) << "" << "|" << endl;
            break;
        case 98:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(29) << "" << "Fingerprint " << setw(29) << "" << "|" << endl;
            cout << "|" << setw(15) << "" << "There's a muddy fingerprint on my table." << setw(15) << "" << "|" << endl;
            cout << "|" << setw(19) << "" << "The shape of it is clear as day." << setw(19) << "" << "|" << endl;
            break;
        case 99:
            cout << "|" << setw(28) << "" << "Analysis Item:" << setw(28) << "" << "|" << endl;
            cout << "|" << setw(29) << "" << "Coffee Stain" << setw(29) << "" << "|" << endl;
            cout << "|" << setw(15) << "" << "Oh, come on! Coffee stains on the table?" << setw(15) << "" << "|" << endl;
            cout << "|" << setw(16) << "" << "This butthead is such a coffee addict." << setw(16) << "" << "|" << endl;
            break;
        //sample
        //cout << "|" << setw() << "" << "" << setw() << "" << "|" << endl;
    }
}

//last page of the game (currently for testing only)
void killCode() {
    //system("clear");
    cout << "Code has been killed." << endl;
}