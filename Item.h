#ifndef UNTITLED_ITEM_H
#define UNTITLED_ITEM_H

#include <iostream>
#include <string>
#include "List.h"
#include "public.h"

using namespace std;

// Item parent class
class Item {
protected:
    string id;
    string title;
    string rentalType;
    string loanType;
    int numOfCopies = 0;
    double rentalFee = 0;
    string genre;
    bool available = false;

public:
    // Constructors
    Item() {
        setId();
        setTitle();
        setLoanType();
        setNumOfCopies();
        setRentalFee();
    }

    Item(string id, string title, string loanType, string numOfCopies, string rentalFee, string genre) {
        this->id = id;
        this->title = title;
        this->loanType = loanType;
        this->numOfCopies = stoi(numOfCopies);
        this->available = this->numOfCopies > 0;
        this->rentalFee = stod(rentalFee);
    }

    // Getters
    string getId() {
        return this->id;
    }

    string getTitle() {
        return this->title;
    }

    int getNumOfCopies() {
        return this->numOfCopies;
    }

    // Return item string for File I/O
    virtual string itemToString() {
        string s = to_string(this->rentalFee);
        size_t found = s.find(".");
        // Workaround for setprecision(2) due to lack of <iomanip>
        s = s.substr(0, found + 3);

        string ret = this->id + ", " + this->title + ", " + this->rentalType + ", " + this->loanType + ", " +
                     to_string(this->numOfCopies) + ", " + s;
        return ret;
    }

    // Setters
    void setId();
    void setTitle();
    void setLoanType();
    void setNumOfCopies();
    void setRentalFee();
    void setGenre();

    void setId(string s) {
        this->id = std::move(s);
    }

    void setAvailable() {
        this->available = true;
    }

    // Edit item
    void getEditFieldMenu();
    void editItem(int field);

    // Print
    void display();
};

// Record
class Record : public Item {
public:
    Record() : Item() {
        this->rentalType = "Record";
        setGenre();
    }

    Record(string id, string title, string loanType, string numOfCopies, string rentalFee, string genre) :
    Item(id, title, loanType, numOfCopies, rentalFee, genre) {
        this->rentalType = "Record";
        this->genre = genre;
    }

    string itemToString() override {
        string ret = Item::itemToString() + ", " + this->genre;
        return ret;
    }
};

// DVD
class DVD : public Item {
public:
    DVD() : Item() {
        this->rentalType = "DVD";
        setGenre();
    }

    DVD(string id, string title, string loanType, string numOfCopies, string rentalFee, string genre) :
    Item(id, title, loanType, numOfCopies, rentalFee, genre) {
        this->rentalType = "DVD";
        this->genre = genre;
    }

    string itemToString() override {
        string ret = Item::itemToString() + ", " + this->genre;
        return ret;
    }
};

// Game
class Game : public Item {
public:
    Game() : Item() {
        this->rentalType = "Game";
    }

    Game(string id, string title, string loanType, string numOfCopies, string rentalFee) :
    Item(id, title, loanType, numOfCopies, rentalFee, genre) {
        this->rentalType = "Game";
    }
};

#endif //UNTITLED_ITEM_H
