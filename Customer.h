#ifndef STORE_CUSTOMER_H
#define STORE_CUSTOMER_H

#include <iostream>
#include <string>
#include "List.h"
#include "public.h"

using namespace std;

class Customer {
protected:
    string id;
    string name;
    string address;
    string phone;
    int numOfRentals;
    string level;
    List<string> *listOfRentals;    // List of rented IDs
public:
    Customer() {
        setId();
        setName();
        setAddress();
        setPhone();

        numOfRentals = 0;
        listOfRentals = new List<string>();
    }

    Customer(string id, string name, string address, string phone, const string& numOfRentals) {
        this->id = std::move(id);
        this->name = std::move(name);
        this->address = std::move(address);
        this->phone = std::move(phone);
        this->numOfRentals = stoi(numOfRentals);
        listOfRentals = new List<string>();
    }

    virtual ~Customer() {
        free(listOfRentals);    // Free rentals memory
    }

    // Getters
    string getId() {
        return this->id;
    }

    List<string>* getListOfRentals() {
        return this->listOfRentals;
    }

    string getTitle() {
        return this->name;
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

    // Print
    void display() {
        cout << customerToString() << endl;
    }

    string customerToString() {
        string ret = id + ", " + name + ", " + address + ", " + phone + ", " + to_string(numOfRentals) + ", " + level;
        return ret;
    }

    void editCustomer(int field);

    // Get editor menu
    void getEditFieldMenu() {
        while (true) {
            cout << "Enter an option:" << endl
                 << "1. Edit ID" << endl
                 << "2. Edit name" << endl
                 << "3. Edit address" << endl
                 << "4. Edit phone" << endl
                 << "5. Quit editing" << endl;

            int field = getFunction(itemFields);
            if (field == 5) break;
            editCustomer(field);
        }
    }
};

class Guest : public Customer {
public:
    Guest() : Customer() {
        level = "Guest";
    }

    // Constructor with predefined fields
    Guest(string id, string name, string address, string phone, const string& numOfRentals) :
    Customer(std::move(id), std::move(name), std::move(address), std::move(phone), numOfRentals) {
        this->level = "Guest";
    }
};

class Regular : public Customer {
public:
    Regular() : Customer() {
        level = "Regular";
    }

    // Constructor with predefined fields
    Regular(string id, string name, string address, string phone, const string& numOfRentals) :
    Customer(std::move(id), std::move(name), std::move(address), std::move(phone), numOfRentals) {
        this->level = "Regular";
    }
};

class VIP : public Customer {
private:
    int points;
public:
    VIP() : Customer() {
        points = 0;
        level = "VIP";
    }

    // Constructor with predefined fields
    VIP(string id, string name, string address, string phone, const string& numOfRentals) :
    Customer(std::move(id), std::move(name), std::move(address), std::move(phone), numOfRentals) {
        this->level = "VIP";
        this->points = 0;
    }
};

#endif //STORE_CUSTOMER_H
