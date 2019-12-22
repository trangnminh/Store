#ifndef UNTITLED_ITEM_H
#define UNTITLED_ITEM_H

#include <iostream>
#include <string>
#include <utility>
#include "List.h"

using namespace std;

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
    // Constructor
    Item() {
        setId();
        setTitle();
        setLoanType();
        setNumOfCopies();
        setRentalFee();
    }

    // Getters
    string getId() {
        return this->id;
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

    // General editor
    virtual void setItem() {
        setId();
        setTitle();
        setLoanType();
        setNumOfCopies();
        setRentalFee();
    }

    // Print Item's info
    virtual void display() {
        cout.precision(2);
        cout << this->id << ", " << this->title << ", " << this->rentalType << ", "
             << this->loanType << ", " << this->numOfCopies << ", "
             << fixed << this->rentalFee << endl;
    }
};

class Movie : public Item {
public:
    Movie() : Item() {
        this->rentalType = "Movie";
        setGenre();
    }

    void display() override {
        cout.precision(2);
        cout << this->id << ", " << this->title << ", " << this->rentalType << ", "
             << this->loanType << ", " << this->numOfCopies << ", "
             << fixed << this->rentalFee << ", " << this->genre << endl;
    }

    void setItem() override {
        setId();
        setTitle();
        setLoanType();
        setNumOfCopies();
        setRentalFee();
        setGenre();
    }
};

class DVD : public Item {
public:
    DVD() : Item() {
        this->rentalType = "DVD";
        setGenre();
    }

    void display() override {
        cout.precision(2);
        cout << this->id << ", " << this->title << ", " << this->rentalType << ", "
             << this->loanType << ", " << this->numOfCopies << ", "
             << fixed << this->rentalFee << ", " << this->genre << endl;
    }

    void setItem() override {
        setId();
        setTitle();
        setLoanType();
        setNumOfCopies();
        setRentalFee();
        setGenre();
    }
};

class Game : public Item {
public:
    Game() : Item() {
        this->rentalType = "Game";
    }
};

#endif //UNTITLED_ITEM_H
