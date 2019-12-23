#ifndef UNTITLED_ITEM_H
#define UNTITLED_ITEM_H

#include <iostream>
#include <string>
#include "List.h"
#include "public.h"

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

    string getTitle() {
        return this->title;
    }

    int getNumOfCopies() {
        return this->numOfCopies;
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

    virtual void getEditFieldMenu();
    virtual void editItem(int field);
    virtual void display();
};

class Movie : public Item {
public:
    Movie() : Item() {
        this->rentalType = "Movie";
        setGenre();
    }

    void getEditFieldMenu() override;
    void editItem(int field) override;
    void display() override;
};

class DVD : public Item {
public:
    DVD() : Item() {
        this->rentalType = "DVD";
        setGenre();
    }

    void getEditFieldMenu() override;
    void editItem(int field) override;
    void display() override;
};

class Game : public Item {
public:
    Game() : Item() {
        this->rentalType = "Game";
    }
};

#endif //UNTITLED_ITEM_H
