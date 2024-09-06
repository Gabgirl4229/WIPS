#include <iostream>

using namespace std;

#ifndef SUSPECT_H
#define SUSPECT_H

class Suspect {
private:
    string title;
    string firstName;
    string middleInitial;
    string lastName;
    string profession;
    string bloodType;
    string fingerprint;
    string dominantHand;
    string drinkPreference;
    string gender;
    string smoker;
    string height;
    string hairLength;
    string hairColor;
    string shoeSize;
    string lensPrescription;
    string lensColor;
    string handwriting;
    string initials;

    //for object identification (not part of qualities)
    string label;

public:
    //get function
    string getQuality(int attribute);

    //set function
    void setQuality(int attribute, string quality);

    //no-argument constructor
    Suspect();

    //user-defined constructor
    Suspect(string newLabel);

    //copy constructor
    Suspect(Suspect& suspect);
    
    //in-class methods
    void printQualities(int& n);
};

#endif