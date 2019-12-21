#ifndef STORE_CUSTOMER_H
#define STORE_CUSTOMER_H

#include <iostream>
#include <string>
#include "item.h"
#include "LinkedList.h"

using namespace std;

class customer {
private:
    string customerId;
    string name;
    string address;
    string phone;
    string level;
    LinkedList<item> listOfRentals;
    int rewardPoints;
public:
    customer() {
        this->level = "Guest";
        this->rewardPoints = 0;
    }

    // Getter methods
    string getCustomerId() {
        return this->customerId;
    }

    // Setter methods
    void setCustomer();

    // Helpers
    void printCustomer();
    static string getNonEmptyInput();
};

void customer::setCustomer() {
    cout << "Enter customer's ID: ";
    while (true) {
        string s;
        getline(cin, s);
        // Validate id input
        if (s.length() == 4 && s[0] == 'C' && isdigit(s[1]) && isdigit(s[2]) && isdigit(s[3])) {
            this->customerId = s;
            break;
        } else {
            cout << "Error: invalid ID. Valid ID: Cxxx (x: digit)" << endl;
            cout << "Enter again: ";
        }
    }

    cout << "Enter customer's name: ";
    this->name = getNonEmptyInput();

    cout << "Enter customer's address: ";
    this->address = getNonEmptyInput();

    cout << "Enter customer's phone number: ";
    while (true) {
        string s;
        getline(cin, s);
        // Validate number input
        if (s.empty() || s.find_first_not_of("0123456789") != string::npos) {
            cout << "Input must be digits. Enter again: ";
            continue;
        } else {
            this->phone = s;
            break;
        }
    }
}

void customer::printCustomer() {
    cout << this->customerId << ", " << this->name << ", " << this->address << ", "
         << this->phone << ", " << this->listOfRentals.size() << ", " << this->level << endl;

    if (this->listOfRentals.size() != 0) {
        for (int i = 0; i < this->listOfRentals.size(); i++) {
            this->listOfRentals.get(i).printItem();
        }
    }
}

string customer::getNonEmptyInput() {
    while (true) {
        string s;
        getline(cin, s);
        if (!s.empty())
            return s;
        else
            cout << "Empty input. Enter again: ";
    }
}

#endif //STORE_CUSTOMER_H
