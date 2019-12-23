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
    string type ;
    int totalRentals;
    List<string> *itemList;

public:
    List<string> *getItemList() const;

public:

    // Setters
    void setCustomer();
    void setId(const string &id);
    void setName(const string &name);
    void setAddress(const string &address);
    void setPhone(const string &phone);

    void setId();
    void setName();
    void setAddress();
    void setPhone();
    void setTotalRentals(int totalRentals);
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
    virtual bool rentItems(int numOfBorrow);

    //return items
    virtual bool turnItems();

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


    bool rentItems(int numOfBorrow) override ;
};


class VIP : public customer{
private:
    int point ;
public:
    VIP(){
        this -> type = "VIP";
    }
};

class Regular : public customer{
public:
    Regular(){
        this -> type = "Regular";
    }
};

