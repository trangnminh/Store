#ifndef STORE_CUSTOMER_H
#define STORE_CUSTOMER_H

#include <iostream>
#include <string>
#include "item.h"
#include "LinkedList.h"

using namespace std;

class customer {
protected:
    string customerId;
    string name;
    string address;
    string phone;
    string level;
    LinkedList<movie> rentedMovies;
    LinkedList<dvd> rentedDVDs;
    LinkedList<game> rentedGames;
public:
    customer() {
        this->level = "Guest";
    };
    ~customer();
};

class guest : public customer {

};

class regular : public customer {
    regular() {
        this->level = "Regular";
    }
};

class vip : public customer {
private:
    int rewardPoints;
public:
    vip() {
        this->level = "VIP";
        this->rewardPoints = 0;
    }
};

#endif //STORE_CUSTOMER_H
