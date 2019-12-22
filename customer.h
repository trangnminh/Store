//
// Created by Trần Mạch Sở Hân on 12/21/19.
//

#include <iostream>
#include <string>

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
public:


public:


public:
    //Constructors
    customer(){
        this->numberOfRentals =0;
    }
    // Setters
    void setId(const string &id);
    void setName(const string &name);
    void setAddress(const string &address);
    void setPhone(const string &phone);
    void setId();
    void setName();
    void setAddress();
    void setPhone();
    void setType(const string &type);
    void setAll(const string &id,const string &name,const string &address,const string &phone);
    void setTotalRentals(int totalRentals);

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

    //rentBook items
    virtual bool rentBook(int numOfBorrow);

    virtual bool turnBook();
};

class Guest : public customer{
public:

    //Constructor
    Guest() : customer(){
        setId();
        setName();
        setPhone();
        setAddress();
        this -> type = "Guest";
    }

    bool rentBook(int numOfBorrow) override ;
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

