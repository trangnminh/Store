#include <iostream>
#include <string>
#include "public.h"
#include "Customer.h"

using namespace std;

void Customer::setId() {
    cout << "Enter customer's ID: ";
    while (true) {
        string s;
        getline(cin, s);
        // Validate id input
        if (s.length() == 4 && s[0] == 'C' && isdigit(s[1]) && isdigit(s[2]) && isdigit(s[3])) {
            this->id = s;
            break;
        } else {
            cout << "Error: invalid ID. Valid ID: Cxxx (x: digit)" << endl;
            cout << "Enter again: ";
        }
    }
}

void Customer::setName() {
    cout << "Enter customer's name: ";
    this->name = getNonEmptyInput();
}

void Customer::setAddress() {
    cout << "Enter customer's address: ";
    this->address = getNonEmptyInput();
}

void Customer::setPhone() {
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

void Customer::display() {
    // Print customer info
    cout << id << ", " << name << ", " << address << ", " << phone << ", "
    << listOfRentals->getSize() << ", " << level << endl;

    // Print list of rented IDs
    for (int i = 0; i < listOfRentals->getSize(); i++)
        cout << listOfRentals->get(i) << endl;
}