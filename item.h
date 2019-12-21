//
// Created by Trần Mạch Sở Hân on 12/20/19.
//

#ifndef TRANG_ITEM_H
#define TRANG_ITEM_H
#include <iostream>
#include <string>

using namespace std;

class item {
protected:
    string id;
    string title;
    string rentalType;
    string loanType;
    int numOfCopies;
    double rentalFee;
    bool available;
public:
    // Constructor
    item() {
        this->numOfCopies = 0;
        this->rentalFee = 0;
        this->available = true;
    }
    // Setter methods
    void setItem();

    void setAll(const string &id, const string &title, const string &rentalType, const string &loanType, int numOfCopies,
         double rentalFee);

    void setId();
    void setTitle();
    void setLoanType();
    void setNumOfCopies();
    void setRentalFee();

    // Helper
    void printItem();
};

// Item with genre
class itemWithGenre : public item {
protected:
    string genre;
public:
    void setGenre();
    void printItemWithGenre();
};

// Movie
class movie : public itemWithGenre {
public:
    movie() {
        this->rentalType = "movie";
    }
};

// DVD
class dvd : public itemWithGenre {
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

#endif //TRANG_ITEM_H
