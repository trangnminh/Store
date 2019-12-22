#include <iostream>
#include "customer.cpp"
#include "LinkedList.h"

using namespace std;

static LinkedList<customer> *guestList;
static LinkedList<customer> *regularList;
static LinkedList<customer> *vipList;

/* SUB-FUNCTIONS INITIALIZATION */
void promoteCustomer(customer he );
void rentBook(customer he);
void printMenu();
void doFunction(int choice);

//main
int main() {
//    Regular regular1;
    string choice;
    do{
        printMenu();
        getline(cin,choice);
        doFunction(stoi(choice));
    }while (choice != "11");
    return 0;
}

void doFunction(int choice){
    switch(choice){
        case 3:{
            promoteCustomer(guestList->get(0));
            break;
        }
        case 4:{
            rentBook(guestList->get(0));
            break;
        }
        case 5:{

        }
        default:
            break;
    }
}
void printMenu() {
    cout <<"------------------------------" << endl
         <<"Welcome to Genie's video store" << endl
         << "Enter an option below" << endl
         << "3. Promote an existing customer" << endl
         << "4. Rent an item" << endl
         << "5. Return an item" << endl
         << "11. Exit" << endl;
}

void promoteCustomer(customer he ){
    if (he.getTotalRentals() > 2 && he.getType() == "Guest"){
        customer *regular = new Regular();
        regular->upgrade(he);
    }
    if (he.getTotalRentals() > 3 && he.getType() == "Regular"){
        customer *vip = new VIP();
        vip -> upgrade(he);
    }
}

void rentBook(customer he){
    int borrowBooks = 0;
    while (true){
        string s;
        cout << "What book do you want to borrow ? ";
        getline(cin,s);
        if (he.rentBook(borrowBooks)){
            cout << "Rent successfully. Continue? \n1.Yes\n2.No\nPlease choose: " ;
            borrowBooks++;
            getline(cin,s);
            if (s=="2")
                break;
        }
        else{
            cout << "Number of rent book is 2";
            break;
        }
    }
}