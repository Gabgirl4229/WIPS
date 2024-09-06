#include <iostream>
#include <iomanip>
#include "Suspect.h"

//get function
string Suspect::getQuality(int attribute) {
    switch(attribute) {
        case 0:
            return title;
            break;
        case 1:
            return firstName;
            break;
        case 2:
            return middleInitial;
            break;
        case 3:
            return lastName;
            break;
        case 4:
            return profession;
            break;
        case 5:
            return bloodType;
            break;
        case 6:
            return fingerprint;
            break;
        case 7:
            return dominantHand;
            break;
        case 8:
            return drinkPreference;
            break;
        case 9:
            return gender;
            break;
        case 10:
            return smoker;
            break;
        case 11:
            return height;
            break;
        case 12:
            return hairLength;
            break;
        case 13:
            return hairColor;
            break;
        case 14:
            return shoeSize;
            break;
        case 15:
            return lensPrescription;
            break;
        case 16:
            return lensColor;
            break;
        case 17:
            return handwriting;
            break;
        case 18:
            return initials;
            break;
        default:
            return label;
            break;
    }
}

//set function
void Suspect::setQuality(int attribute, string quality) {
    switch(attribute) {
        case 0:
            title = quality;
            break;
        case 1:
            firstName = quality;
            break;
        case 2:
            middleInitial = quality;
            break;
        case 3:
            lastName = quality;
            break;
        case 4:
            profession = quality;
            break;
        case 5:
            bloodType = quality;
            break;
        case 6:
            fingerprint = quality;
            break;
        case 7:
            dominantHand = quality;
            break;
        case 8:
            drinkPreference = quality;
            break;
        case 9:
            gender = quality;
            break;
        case 10:
            smoker = quality;
            break;
        case 11:
            height = quality;
            break;
        case 12:
            hairLength = quality;
            break;
        case 13:
            hairColor = quality;
            break;
        case 14:
            shoeSize = quality;
            break;
        case 15:
            lensPrescription = quality;
            break;
        case 16:
            lensColor = quality;
            break;
        case 17:
            handwriting = quality;
            break;
        case 18:
            initials = quality;
            break;
        default:
            label = quality;
            break;
    }
}

//no-argument constructor
Suspect::Suspect() {
    for (int i = 0; i < 20; i++) {
        setQuality(i, "not defined");
    }
}

//user-defined constructor
Suspect::Suspect(string newLabel) {
    label = newLabel;
    for (int i = 0; i < 19; i++) {
        setQuality(i, "not defined");
    }
}

//copy constructor
Suspect::Suspect(Suspect& suspect) {
    label = suspect.label;
    for (int i = 0; i < 19; i++) {
        setQuality(i, suspect.getQuality(i));
    }
}

//in-class methods
void Suspect::printQualities(int& n) {

    //immediate exit for "not defined" qualities
    switch (n) {
    //title, first name, middle initial, last name
    case 3:
        if (title == "not defined" && firstName == "not defined" && initials == "not defined" && middleInitial == "not defined" && initials == "not defined" && lastName == "not defined" && initials == "not defined") {
            return;
        }
        break;
    //profession
    case 4:
        if (profession == "not defined") {
            return;
        }
        break;
    //blood type
    case 5:
        if (bloodType == "not defined") {
            return;
        }
        break;
    //fingerprint
    case 6:
        if (fingerprint == "not defined") {
            return;
        }
        break;
    //dominant hand
    case 7:
        if (dominantHand == "not defined") {
            return;
        }
        break;
    //drink preference
    case 8:
        if (drinkPreference == "not defined") {
            return;
        }
        break;
    //gender
    case 9:
        if (gender == "not defined") {
            return;
        }
        break;
    //smoker
    case 10:
        if (smoker == "not defined") {
            return;
        }
        break;
    //height
    case 11:
        if (height == "not defined") {
            return;
        }
        break;
    //hair length
    case 12:
        if (hairLength == "not defined") {
            return;
        }
        break;
    //hair color
    case 13:
        if (hairColor == "not defined") {
            return;
        }
        break;
    //shoe size
    case 14:
        if (shoeSize == "not defined") {
            return;
        }
        break;
    //lens prescription
    case 15:
        if (lensPrescription == "not defined") {
            return;
        }
        break;
    //lens color
    case 16:
        if (lensColor == "not defined") {
            return;
        }
        break;
    //handwriting
    case 17:
        if (handwriting == "not defined") {
            return;
        }
        break;
    default:
        break;
    }
    
    //first space for every line
    int width = 2;
    cout << setw(width) << "| ";
    
    switch (n) {
    //suspect page title
    case 1:
        cout << setw(20) << label << ":";
        width = 10;
        break;
    //title, first name, middle initial, last name
    case 3:
        width = 0;
        if (title != "not defined") {
            cout << title << " ";
            width += title.length() + 1;
        }
        if (firstName != "not defined") {
            cout << firstName << " ";
            width += firstName.length() + 1;
        } else if (initials != "not defined") {
            cout << initials.at(0) << ". ";
            width += 3;
        }
        if (middleInitial != "not defined") {
            cout << middleInitial << ". ";
            width += middleInitial.length() + 2;
        } else if (initials != "not defined") {
            cout << initials.at(2) << ". ";
            width += 3;
        }
        if (lastName != "not defined") {
            cout << lastName;
            width += lastName.length();
        }  else if (initials != "not defined") {
            cout << initials.at(4) << ". ";
            width += 3;
        }
        width = 31 - width;
        break;
    //profession
    case 4:
        cout << "Profession: " << profession;
        width = 31 - 12 - profession.length();
        break;
    //blood type
    case 5:
        cout << "Blood Type: " << bloodType;
        width = 31 - 12 - bloodType.length();
        break;
    //fingerprint
    case 6:
        cout << "Fingerprint Shape: " << fingerprint;
        width = 31 - 19 - fingerprint.length();
        break;
    //dominant hand
    case 7:
        cout << "Dominant Hand: " << dominantHand;
        width = 31 - 15 - dominantHand.length();
        break;
    //drink preference
    case 8:
        cout << "Drink Preference: " << drinkPreference;
        width = 31 - 18 - drinkPreference.length();
        break;
    //gender
    case 9:
        cout << "Gender: " << gender;
        width = 31 - 8 - gender.length();
        break;
    //smoker
    case 10:
        cout << "Smoker: " << smoker;
        width = 31 - 8 - smoker.length();
        break;
    //height
    case 11:
        cout << "Height: " << height;
        width = 31 - 8 - height.length();
        break;
    //hair length
    case 12:
        cout << "Hair Length: " << hairLength;
        width = 31 - 13 - hairLength.length();
        break;
    //hair color
    case 13:
        cout << "Hair Color: " << hairColor;
        width = 31 - 12 - hairColor.length();
        break;
    //shoe size
    case 14:
        cout << "Shoe Size: " << shoeSize;
        width = 31 - 11 - shoeSize.length();
        break;
    //lens prescription
    case 15:
        cout << "Lens Prescription: " << lensPrescription;
        width = 31 - 19 - lensPrescription.length();
        break;
    //lens color
    case 16:
        cout << "Lens Color: " << lensColor;
        width = 31 - 12 - lensColor.length();
        break;
    //handwriting
    case 17:
        cout << "Handwriting: " << handwriting;
        width = 31 - 13 - handwriting.length();
        break;
    default:
        width = 31;
    }

    //last spaces at the end
    cout << setw(width + 1) << "|";

    //right side
    cout << setw(38) << "|" << endl;
}