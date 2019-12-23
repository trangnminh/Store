#include <iostream>
#include "customer.cpp"
#include "List.h"

using namespace std;

static List<customer*> customerList;

/* SUB-FUNCTIONS INITIALIZATION */
void printMenu();
int getFunction(int type);
void callFunction(int choice);

void addUpdateCustomer();
void addCusttomer();
void updateCustomer();

void promoteCustomer();

void rentItem();

void returnItem();

void displayCustomer();
void displayGroupCustomer();

int getIdIndex();

//main
int main() {

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
    const string managerFunctions = "1 2 3 4 5 8 9 11"; // will be added later
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
            promoteCustomer();
            break;
        }
        case 4: {
            rentItem();
            break;
        }
        case 5:{
            returnItem();
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
    //Always add new guest
    customer *guest = new Guest();
    guest->setCustomer();
    customerList.append(guest);
}

void updateCustomer(){
    cout << "Update customer" <<endl;
    int id = getIdIndex();
    if (id == -1)
        return;
    customer *getCustomer = customerList.get(id);
    getCustomer->setCustomer();
}

void promoteCustomer(){
    int id = getIdIndex();
    if (id == -1)
        return;
    customer *getCustomer = customerList.get(id);
    bool qualifi = false;   //To check if the customer was qualied are not

    if (getCustomer->getNumberOfRentals() > 2 && getCustomer->getType() == "Guest") {
        customer *newRegular = new Regular();
        newRegular->upgrade(*getCustomer);  //get information from the guest to the new regular
        customerList.append(newRegular);    //Add new regular to the list
        customerList.deleteNode(id);         //mean while delete the old one
        qualifi = true;
    }

    if (getCustomer->getNumberOfRentals() > 2 && getCustomer->getType() == "Regular"){
        VIP *newVip = new VIP();
        newVip->upgrade(*getCustomer);
        customerList.append(newVip);
        customerList.deleteNode(id);
        qualifi = true;
    }

    if (getCustomer->getType() == "VIP"){   //Notify that customer is already the VIP , don't need to upgrade
        cout << "Customer is already VIP" <<endl;
        qualifi = true;
    }

    if(!qualifi)
        cout << "Customer is not qualified to have promotion"<<endl;
}

void rentItem(){
    //Ask user to enter their id
    int id = getIdIndex();
    if (id == -1)
        return;
    customer *getCustomer = customerList.get(id);
    while (true){
        string s;
        cout << "What book do you want to borrow ? ";
        getline(cin,s);
        if (getCustomer->rentItems()){
            getCustomer->getItemList()->append(s);
            cout << "Rent successfully. Continue? \n1.Yes\n2.No\nPlease choose: " ;
            int function = getFunction(3);
            if (function == 2)
                break;
        }
        else{
            cout << "Number of rent book is 2" <<endl;
            break;
        }
    }
}

void returnItem(){
    int id = getIdIndex();
    if (id == -1)
        return;
    customer *getCustomer = customerList.get(id);
    while (true) {
        string itemReturn;
        cout << "Please enter name of book"<<endl;
        getline(cin, itemReturn);
        //get the validate of item return and item list
        if (getCustomer->turnItems(itemReturn)) {
            cout << "Return successfully. ";
            //if no list , break
            if (getCustomer->getItemList()->getSize() != 0) {
                cout << "\n1. Yes\n2. No \nContinue? ";
                int function = getFunction(3);
                if (function == 2) {
                    break;
                }
            } else
                break;
        } else
            break;
    }
}

void displayCustomer(){
    cout << "Display all customers: "<<endl;
    if(customerList.getSize() != 0){
        for (int i = 0; i < customerList.getSize(); ++i) {
            customerList.get(i)->printCustomer();
        }
    }
}


void displayGroupCustomer(){
    int function ;
    cout << "Enter an option: "<<endl
    << "1. Group of guest" <<endl
    << "2. Group of regular" <<endl
    << "3. Group of VIP" <<endl;

    function = getFunction(2);
    bool get = false;
    if (customerList.getSize()!=0 ){
        switch (function){
            case 1:{
                cout << "Guest list: " <<endl;
                for (int i = 0; i < customerList.getSize(); ++i) {
                    if(customerList.get(i)->getType()=="Guest"){
                        customerList.get(i)->printCustomer();
                        get++;
                    }
                }
                break;
            }
            case 2:{
                cout << "Regular list: " <<endl;
                for (int i = 0; i < customerList.getSize(); ++i) {
                    if(customerList.get(i)->getType()=="Regular"){
                        customerList.get(i)->printCustomer();
                        get++;
                    }
                }
                break;
            }
            case 3:{
                cout << "VIP list: " <<endl;
                for (int i = 0; i < customerList.getSize(); ++i) {
                    if(customerList.get(i)->getType()=="VIP"){
                        customerList.get(i)->printCustomer();
                        get++;
                    }
                }
                break;
            }
            default:
                break;
        }
    } else
        cout << "No customer in the list" <<endl;
}

int getIdIndex(){
    //To return the index of id in the list
    string id;
    cout << "Please enter id (xxx with 3 digits): " ;
    getline(cin,id);
    bool found = false;
    if (customerList.getSize()!=0){
        for (int i = 0; i < customerList.getSize(); ++i) {
            customer *getCustomer = customerList.get(i);
            if (id == getCustomer->getId().substr(1, 3))
                return i;
        }
        if(!found){
            cout << "Id was not found" <<endl;
            return -1;
        }
    } else return -1;
}