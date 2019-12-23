#include <iostream>
#include "customer.cpp"
#include "LinkedList.h"

using namespace std;

<<<<<<< HEAD
static LinkedList<Guest> *guestList;
static LinkedList<Regular> *regularList;
static LinkedList<VIP> *VIPList;

/* SUB-FUNCTIONS INITIALIZATION */
void printMenu();
int getFunction(int type);
void callFunction(int choice);

void addUpdateCustomer();
void addCusttomer();
void updateCustomer();

void promoteCustomer(customer he );

void rentBook();
void checkRentBook(customer *customer);

void displayCustomer();
void displayGroupCustomer();

bool isGuestListEmpty();
bool isRegularListEmpty();
bool isVIPListEmpty();
=======
static LinkedList<customer> *guestList;
static LinkedList<customer> *regularList;
static LinkedList<customer> *vipList;

/* SUB-FUNCTIONS INITIALIZATION */
void promoteCustomer(customer he );
void rentBook(customer he);
void printMenu();
void doFunction(int choice);
>>>>>>> 1d35cbc1a6f5bc6b886d81f6d3c9f540bee2bbd8

//main
int main() {
//    Regular regular1;
<<<<<<< HEAD
    guestList = new LinkedList<Guest>();
    regularList = new LinkedList<Regular>();
    VIPList = new LinkedList<VIP>();

    int function = 0;
    do{
        printMenu();
        function = getFunction(1);
        callFunction(function);
    } while (function != 11);
    return 0;
}

void printMenu() {
    cout <<"------------------------------" << endl
         <<"Welcome to Genie's video store" << endl
         << "Enter an option below" << endl
         << "2. Add new customer or update an existing customer" <<endl
         << "3. Promote an existing customer" << endl
         << "4. Rent an item" << endl
         << "5. Return an item" << endl
         << "8. Display all customers" << endl
         << "9. Display group of customers" << endl
         << "11. Exit" << endl;
}

int getFunction(int type) {
    const string managerFunctions = "1 2 3 4 8 9 11"; // will be added later
    const string itemFunctions = "1 2 3";
    const string editOrDeleteFunctions = "1 2";

    string function;
    getline(cin, function);

    // Validate user input
    while (true) {
        // Check if input has space
        size_t foundSpace = function.find_first_of(' ');
        size_t foundFunction = 0;

        // Check input against valid functions based on type
        if (type == 1)  // Manage list
            foundFunction = managerFunctions.find(function);
        if (type == 2) // Access specific type of item
            foundFunction = itemFunctions.find(function);
        if (type == 3)  // Delete or update an item
            foundFunction = editOrDeleteFunctions.find(function);

        // Validate input
        if (function.empty() || foundSpace != string::npos || foundFunction == string::npos) {
            cout << "Error: function not found. Enter again: ";
            getline(cin, function);
        } else break;
    }
    return stoi(function);
}

void callFunction(int function) {
    switch (function) {
        case 2: {
            addUpdateCustomer();
            break;
        }
        case 3: {
            promoteCustomer(guestList->get(0));
            break;
        }
        case 4: {
            rentBook();
            break;
        }
        case 8:{
            displayCustomer();
            break;
        }
        case 9:{
            displayGroupCustomer();
            break;
        }
        default:{
            cout << "Goodbye" << endl;
            break;
        }
    }
}

void addUpdateCustomer(){
    cout << "Enter an option:" << endl
         << "1. Add new customer" << endl
         << "2. Update new customer" << endl;

    //Add or update
    int function = getFunction(3);
    switch (function){
        case 1:{
            addCusttomer();
            break;
        }
        case 2:{
            updateCustomer();
            break;
        }
    }
}

void addCusttomer(){
    Guest guest;
    guest.setCustomer();
    guestList->append(guest);
}

void updateCustomer(){
    cout << "Enter an option:" << endl
         << "1. Update guest" << endl
         << "2. Update regular" << endl
         << "3. Update VIP" << endl;
    cout << "Enter the target's ID";

    string id;
    getline(cin,id);

    int function = getFunction(2);
    switch(function){
        case 1:{
            if(!isGuestListEmpty()){
                bool found = false;
                for (int i = 0; i < guestList->size(); i++) {
                    Guest guest = guestList->get(i);
                    if (guest.getId() == id) {
                        found = true;
                        cout << "Selected item: ";
                        guest.printCustomer();
                        guest.setCustomer();
                        guestList->set(i, guest);
                    }
                }
                if (!found)
                    cout << "Index not found" << endl;
            }
            break;
        }
        case 2:{
            if(!isRegularListEmpty()){
                bool found = false;
                for (int i = 0; i < guestList->size(); i++) {
                    Regular regular = regularList->get(i);
                    if (regular.getId() == id) {
                        found = true;
                        cout << "Selected item: ";
                        regular.printCustomer();
                        regular.setCustomer();
                        regularList->set(i, regular);
                    }
                }
                if (!found)
                    cout << "Index not found" << endl;
            }
            break;
        }
        case 3:{
            if(!isVIPListEmpty()){
                bool found = false;
                for (int i = 0; i < guestList->size(); i++) {
                    VIP vip = VIPList->get(i);
                    if (vip.getId() == id) {
                        found = true;
                        cout << "Selected item: ";
                        vip.printCustomer();
                        vip.setCustomer();
                        VIPList->set(i, vip);
                    }
                }
                if (!found)
                    cout << "Index not found" << endl;
            }
            break;
        }
    }
}

void promoteCustomer(customer he ){
    string id;
    cout << "Please enter id: ";
    getline(cin,id);
    bool found = false;
    if(guestList->size() != 0){
        for (int i = 0; i < guestList->size(); i++) {
            Guest guest = guestList->get(i);
            if (guest.getId() == id) {
                found = true;
                if (he.getTotalRentals() > 2 ){
                    Regular newRegular;
                    newRegular.upgrade(guest);  //get information from the guest to the new regular
                                                //Append the new regular to the regular list
                                                //delete the guest in guest list
                }
            }
        }
    }
    if (!found && guestList->size() != 0){
        for (int i = 0; i < regularList->size(); i++) {
            Regular regular = regularList->get(i);
            if (regular.getId() == id) {
                found = true;
                if (he.getTotalRentals() > 2 ){
                    VIP newVip;
                    newVip.upgrade(regular);    //get information from the regular to the new vip
                                                //Append the new vip to the vip list
                                                //delete the regular in regular list
                }
            }
        }
    }
    if (!found && guestList->size() != 0){
        for (int i = 0; i < VIPList->size(); i++) {
            VIP vip = VIPList->get(i);
            if (vip.getId() == id) {
                found = true;
                cout << "Customer is already VIP" <<endl;
            }
        }
    }
    if (!found)
        cout << "Id not found" << endl;
}

void rentBook(){
    string id;
    cout << "Enter customer's id: ";
    getline(cin,id);
    bool found = false;
    if(guestList->size() != 0){
        for (int i = 0; i < guestList->size(); i++) {
            Guest guest = guestList->get(i);
            if (guest.getId() == id) {
                found = true;
                checkRentBook(&guest);
            }
        }
    }
    if (!found && guestList->size() != 0){
        for (int i = 0; i < regularList->size(); i++) {
            Regular regular = regularList->get(i);
            if (regular.getId() == id) {
                found = true;
                checkRentBook(&regular);
            }
        }
    }
    if (!found && guestList->size() != 0){
        for (int i = 0; i < VIPList->size(); i++) {
            VIP vip = VIPList->get(i);
            if (vip.getId() == id) {
                found = true;
                checkRentBook(&vip);
            }
        }
    }
    if (!found)
        cout << "Id not found" << endl;
}

void checkRentBook(customer *customer){
=======
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
>>>>>>> 1d35cbc1a6f5bc6b886d81f6d3c9f540bee2bbd8
    int borrowBooks = 0;
    while (true){
        string s;
        cout << "What book do you want to borrow ? ";
        getline(cin,s);
<<<<<<< HEAD
        if (customer->rentItems(borrowBooks)){
            customer->getItemList()->append(s);
            cout << "Rent successfully. Continue? \n1.Yes\n2.No\nPlease choose: " ;
            borrowBooks++;
            int function = getFunction(3);
            if (function == 2)
=======
        if (he.rentBook(borrowBooks)){
            cout << "Rent successfully. Continue? \n1.Yes\n2.No\nPlease choose: " ;
            borrowBooks++;
            getline(cin,s);
            if (s=="2")
>>>>>>> 1d35cbc1a6f5bc6b886d81f6d3c9f540bee2bbd8
                break;
        }
        else{
            cout << "Number of rent book is 2";
            break;
        }
    }
<<<<<<< HEAD
}

void displayCustomer(){
    if(guestList->size() != 0){
        for (int i = 0; i < guestList->size(); i++)
            guestList->get(i).printCustomer();
    }
    if(regularList->size() != 0){
        for (int i = 0; i < regularList->size(); i++)
            regularList->get(i).printCustomer();
    }
    if (VIPList->size() != 0){
        for (int i = 0; i < VIPList->size(); i++)
            VIPList->get(i).printCustomer();
    }
}


void displayGroupCustomer(){
    int function ;
    cout << "Enter an option: "<<endl
    << "1. Group of guest" <<endl
    << "2. Group of regular" <<endl
    << "3. Group of VIP" <<endl;

    function = getFunction(2);
    switch (function){
        case 1:{
            if(!isGuestListEmpty()){
                for (int i = 0; i < guestList->size(); i++)
                    guestList->get(i).printCustomer();
            }
            break;
        }
        case 2:{
            if(!isRegularListEmpty()){
                for (int i = 0; i < regularList->size(); i++)
                    regularList->get(i).printCustomer();
            }
            break;
        }
        case 3:{
            if (!isVIPListEmpty()){
                for (int i = 0; i < VIPList->size(); i++)
                    VIPList->get(i).printCustomer();
            }
        }
        default:
            break;
    }
}

bool isGuestListEmpty() {
    if (guestList->size() == 0) {
        cout << "Guest list is empty" << endl;
        return true;
    }
    return false;
}

bool isRegularListEmpty(){
    if (regularList->size() == 0) {
        cout << "Regular list is empty" << endl;
        return true;
    }
    return false;
}

bool isVIPListEmpty(){
    if (VIPList->size() == 0) {
        cout << "VIP list is empty" << endl;
        return true;
    }
    return false;
=======
>>>>>>> 1d35cbc1a6f5bc6b886d81f6d3c9f540bee2bbd8
}