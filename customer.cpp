//
// Created by Trần Mạch Sở Hân on 12/21/19.
//

#include "customer.h"

inline void customer::setCustomer() {
    setId();
    setName();
    setAddress();
    setPhone();
}
inline void customer::setId(const string &id) {
    this -> id = id;
}

inline void customer::setName(const string &name) {
    this -> name = name;
}

inline void customer::setAddress(const string &address) {
    this -> address = address;
}

inline void customer::setPhone(const string &phone) {
    this -> phone = phone;
}


inline void customer::setId() {
    cout << "Enter customer's ID: ";
    while (true) {
        string s;
        getline(cin, s);
        // Validate id input
        bool valid = true;
        for (int i = 1; i < s.length(); i++) {
            if (!isdigit(s[i])) {
                valid = false;
                break;
            }
        }
        if (valid && s.length() == 4 && s[0] == 'C') {
            this -> id = s;
            break;
        }
        else {
            cout << "Error: invalid ID. Valid ID: Cxxx (x: digit)" << endl;
            cout << "Enter again: ";
        }
    }
}

inline void customer::setName() {
    cout << "Enter name: ";
    while (true) {
        string s;
        getline(cin, s);
        if (!s.empty()) {
            this->name = s;
            break;
        }
        else
            cout << "Error: invalid name. Enter again: ";
    }
}

inline void customer::setAddress() {
    cout << "Enter address: ";
    while(true){
        string s;
        getline(cin,s);
        if (!s.empty()){
            this -> address = s;
            break;
        } else
            cout << "Error: invalid name. Enter again: ";
    }
}

inline void customer::setPhone() {
    cout << "Enter phone";
    while (true){
        string s;
        getline(cin, s);
        bool valid = true;
        for (char i : s) {
            if (!isdigit(i)){
                cout << "Number must be a digit" <<endl;
                valid = false;
                break;
            }
        }
        if (s.length() == 11 && valid){
            this -> phone = s;
            break;
        }
        else {
            cout << "Should be 11 number"<< endl;
            cout << "enter again" << endl;
        }
    }
}

inline void customer::setAll(const string &id, const string &name, const string &address, const string &phone) {
    this -> id = id;
    this -> name = name;
    this -> address = address;
    this -> phone = phone;
}

inline void customer::setTotalRentals(int totalRentals) {
    customer::totalRentals = totalRentals;
}


inline int customer::getTotalRentals() const {
    return totalRentals;
}

inline const string &customer::getId() const {
    return id;
}

inline const string &customer::getName() const {
    return name;
}

inline const string &customer::getAddress() const {
    return address;
}

inline const string &customer::getPhone() const {
    return phone;
}

inline int customer::getNumberOfRentals() const {
    return numberOfRentals;
}

inline const string &customer::getType() const {
    return type;
}

inline void customer::setType(const string &type) {
    customer::type = type;
}

inline void customer::upgrade(customer guest) {
    setId(guest.getId());
    setName(guest.getName());
    setAddress(guest.getAddress());
    setPhone(guest.getPhone());
    setTotalRentals(guest.getTotalRentals());
}

//Rent books
inline bool customer::rentItems(int numOfBorrow) {
    numberOfRentals++;
    totalRentals++;
    return true;
}

inline bool customer::turnItems() {
    numberOfRentals--;
    return true;
}

//Print customer
inline void customer::printCustomer() {
    cout.precision(2);
    cout << this -> id << " ," << this -> name << " ," << this -> address << "," <<
    this -> phone << "," << this -> numberOfRentals << "," << this -> type <<endl;
}

inline LinkedList<string> *customer::getItemList() const {
    return itemList;
}


inline bool Guest::rentItems(int numOfBorrow) {
    if ((numberOfRentals+numOfBorrow) > 2){
        return false;
    }
    numberOfRentals++;
    totalRentals++;
    return true;
}

