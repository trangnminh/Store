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
    itemList = guest.getItemList();
}

//Rent books
inline bool customer::rentItems() {
    numberOfRentals++;
    return true;
}

inline bool customer::turnItems(string itemReturn) {
    //When there is no item in the borrow list
    if (getItemList()->getSize() == 0)
        return false;

    //Run through loop to find the item in the item list
    for (int i = 0; i < getItemList()->getSize(); ++i) {
        if (itemReturn == getItemList()->get(i)){
            numberOfRentals--;
            totalRentals++;
            return true;
        } else{
            cout << "No book was in the customer borrow" <<endl;
            return false;
        }
    }
}

//Print customer
inline void customer::printCustomer() {
    cout.precision(2);
    cout << this -> id << " ," << this -> name << " ," << this -> address << "," <<
    this -> phone << "," << this -> numberOfRentals << "," << this -> type <<endl;
    if(getItemList()->getSize()!=0){
        for (int i = 0; i < getItemList()->getSize(); ++i) {
            cout << getItemList()->get(i)<<endl;
        }
    }
}

inline List<string> *customer::getItemList() const {
    return itemList;
}

inline bool Guest::rentItems() {
    //Once the number renting is more than 2 then false
    if (getNumberOfRentals() > 1){
        return false;
    }
    numberOfRentals++;
    return true;
}

inline bool VIP::rentItems() {
    //When the vip borrow item , point will be added
    point = point + 10;

    if(point > 100){
        free_item = true;
    }

    //Condition if user can rent an iem for free and not use before
    if (free_item && !use_free_item){
        string s;
        cout << "Customer can rent an item for free. Use ?\n1. Yes\n2.No";
        getline(cin,s);
        if (s == "1"){
            use_free_item = true;
        }
    }
    return true;
}

