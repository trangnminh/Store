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

void Customer::editCustomer(int field) {
    switch (field) {
        case 1: {
            setId();
            break;
        }
        case 2: {
            setName();
            break;
        }
        case 3: {
            setAddress();
            break;
        }
        case 4: {
            setPhone();
            break;
        }
        default:;
    }
    cout << "Edited customer: " << customerToString() << endl;
}

// Get editor menu
void Customer::getEditFieldMenu() {
    while (true) {
        cout << "Enter an option:" << endl
             << "1. Edit ID" << endl
             << "2. Edit name" << endl
             << "3. Edit address" << endl
             << "4. Edit phone" << endl
             << "5. Quit editing" << endl;

        int field = getFunction(customerFields);
        if (field == 5) break;
        editCustomer(field);
    }
}