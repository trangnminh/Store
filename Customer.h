#ifndef STORE_CUSTOMER_H
#define STORE_CUSTOMER_H

#include <iostream>
#include <string>
#include <utility>
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

    // Getters
    string getId() {
        return this->id;
    }

    List<string>* getListOfRentals() {
        return this->listOfRentals;
    }

    // Setters
    void setId();
    void setName();
    void setAddress();
    void setPhone();

    // Print
    void display();
    virtual string customerToString() {
        string ret = id + ", " + name + ", " + address + ", " + phone + ", " + to_string(numOfRentals);
        return ret;
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

    string customerToString() override {
        string ret = Customer::customerToString() + ", Guest";
        return ret;
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

    string customerToString() override {
        string ret = Customer::customerToString() + ", Regular";
        return ret;
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

    string customerToString() override {
        string ret = Customer::customerToString() + ", VIP";
        return ret;
    }
};


#endif //STORE_CUSTOMER_H
