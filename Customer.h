#ifndef STORE_CUSTOMER_H
#define STORE_CUSTOMER_H

#include <iostream>
#include <string>
#include "Item.h"
#include "List.h"
#include "public.h"

using namespace std;

class Customer {
protected:
    string id;
    string name;
    string address;
    string phone;
    int numOfPastRentals;
    string level;
    List<string> *listOfRentals;    // List of currently rented IDs

    int points; // VIP only
    bool canRentFree = false;

public:
    Customer() {
        setId();
        setName();
        setAddress();
        setPhone();
        numOfPastRentals = 0;
        listOfRentals = new List<string>();
        points = 0;
    }

    // Constructor for loading new
    Customer(string id, string name, string address, string phone, const string& numOfPastRentals, const string& points) {
        this->id = id;
        this->name = name;
        this->address = address;
        this->phone = phone;
        this->numOfPastRentals = stoi(numOfPastRentals);
        this->listOfRentals = new List<string>();

        this->points = stoi(points);
    }

    virtual ~Customer() {
        free(listOfRentals);    // Free rentals memory
    }

    // Getters
    string getId() {
        return this->id;
    }

    // getName(), renamed to match Item (template use)
    string getTitle() {
        return this->name;
    }

    string getAddress() {
        return this->address;
    }

    string getPhone() {
        return this->phone;
    }

    int getNumOfPastRentals() {
        return this->numOfPastRentals;
    }

    List<string>* getListOfRentals() {
        return this->listOfRentals;
    }

    string getLevel() {
        return this->level;
    }

    // Setters
    void setId();
    void setName();
    void setAddress();
    void setPhone();

    void setId(string oldId) {
        this->id = std::move(oldId);
    }

    // Rent and return-related functions
    void promote();
    void rent();
    int getPoints();

    void returnItem() {
        this->numOfPastRentals++;
    }

    // Print
    void display() {
        cout << getObjectString() << endl;

        // Print list of rentals
        for (int i = 0; i < this->getListOfRentals()->getSize(); i++) {
            cout << this->getListOfRentals()->get(i) << endl;
        }
    }

    virtual string getObjectString();

    // Edit customer
    void editCustomer(int field);
    void getEditFieldMenu();
};

class Guest : public Customer {
public:
    Guest() : Customer() {
        level = "Guest";
    }

    // Constructor for loading
    Guest(string id, string name, string address, string phone, const string& numOfPastRentals, const string& points) :
    Customer(id, name, address, phone, numOfPastRentals, points) {
        this->level = "Guest";
        this->points = 0;
    }
};

class Regular : public Customer {
public:
    Regular() : Customer() {
        level = "Regular";
    }

    // For loading
    Regular(string id, string name, string address, string phone, const string& numOfPastRentals, const string& points) :
    Customer(id, name, address, phone, numOfPastRentals, points) {
        this->level = "Regular";
        this->points = 0;
    }
};

class VIP : public Customer {
public:
    VIP() : Customer() {
        level = "VIP";
    }

    // For loading
    VIP(string id, string name, string address, string phone, const string& numOfPastRentals, const string& points) :
    Customer(id, name, address, phone, numOfPastRentals, points) {
        this->level = "VIP";
    }

    string getObjectString() override {
        string ret = id + ", " + name + ", " + address + ", " + phone + ", " + to_string(numOfPastRentals)
                + ", " + level + ", " + to_string(points);
        return ret;
    };
};

#endif //STORE_CUSTOMER_H
