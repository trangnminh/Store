#ifndef STORE_ITEM_H
#define STORE_ITEM_H

#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

// Item
class item {
protected:
    string id;
    string title;
    string rentalType;
    string loanType;
    int numOfCopies;
    double rentalFee;
    bool available;
    string genre;

public:
    // Constructor
    item() {
        this->numOfCopies = 0;
        this->rentalFee = 0;
        this->genre = "N/A";
        this->available = true;
    }
    // Setter methods
    void setItem();
    void setId();
    void setTitle();
    void setLoanType();
    void setNumOfCopies();
    void setRentalFee();
    void setGenre();

    // Helper
    void printItem();
};

// Movie
class movie : public item {
public:
    movie() {
        this->rentalType = "movie";
    }
};

// DVD
class dvd : public item {
public:
    dvd() {
        this->rentalType = "dvd";
    }
};

// Game
class game : public item {
public:
    game() {
        this->rentalType = "game";
    }
};


#endif //STORE_ITEM_H
