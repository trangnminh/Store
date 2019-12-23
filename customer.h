//
// Created by Trần Mạch Sở Hân on 12/21/19.
//

#include <iostream>
#include <string>
#include "List.h"
using namespace std;

class Guest;
class Regular;
class VIP;

class customer {
protected:
    string id;
    string name;
    string address;
    string phone;
    int numberOfRentals;

protected:
    string type ;
    int totalRentals;
    List<string> *itemList;

public:
    List<string> *getItemList() const;

public:

    // Setters with arguments
    void setCustomer();
    void setId(const string &id);
    void setName(const string &name);
    void setAddress(const string &address);
    void setPhone(const string &phone);

    //Set with input
    void setId();
    void setName();
    void setAddress();
    void setPhone();
    void setType(const string &type);
    void setAll(const string &id,const string &name,const string &address,const string &phone);

    //Getters
    const string &getId() const;
    const string &getName() const;
    const string &getAddress() const;
    const string &getPhone() const;
    int getNumberOfRentals() const;
    const string &getType() const;
    int getTotalRentals() const;

//    void upgrade();
    void upgrade(customer guest);

    //rent items
    virtual bool rentItems();

    //return items
    virtual bool turnItems(string item);

    //print Customer
    void printCustomer();

};

class Guest : public customer{
public:

    //Constructor
    Guest() {
        this -> type = "Guest";
        this -> numberOfRentals = 0;
        this -> totalRentals = 0;
        itemList = new List<string>;
    }

    //Rent an item but with restriction
    bool rentItems() override ;
};

class VIP : public customer{
private:
    int point ;
    bool free_item = false;
    bool use_free_item = false;

public:
    VIP(){
        this -> type = "VIP";
        point = 0;
    }
    bool rentItems() override ;
};

class Regular : public customer{
public:
    Regular(){
        this -> type = "Regular";
        this -> totalRentals = 0;
    }
};

