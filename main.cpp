#include <iostream>
#include <string>

#include "item.h"
#include "LinkedList.h"
#include "customer.h"

using namespace std;

// Global lists
static LinkedList<item> *itemList;
static LinkedList<customer> *customerList;

/* SUB-FUNCTIONS INITIALIZATION */
void printMenu();
int getFunction(int type);
void callFunction(int function);

void printListOfItems();
void addItem();
void updateOrDeleteItem();
void addCustomer();

bool isItemListEmpty();
bool isCustomerListEmpty();
bool isDuplicateItem(item item);
bool isDuplicateCustomer(customer customer);
bool isEditItem();

int main() {
    // Create new lists
    itemList = new LinkedList<item>();
    customerList = new LinkedList<customer>();

    int function = 0;
    do {
        printMenu();
        function = getFunction(1);
        callFunction(function);
    } while (function != 11);

    return 0;
}

// Print function menu
void printMenu() {
    cout <<"------------------------------" << endl
         <<"Welcome to Genie's video store" << endl
         << "Enter an option below" << endl
         << "1. Print list of items" << endl
         << "2. Add a new item" << endl
         << "3. Update/delete a current item" << endl
         << "4. Add a new customer" << endl

         << "11. Exit" << endl;
}

// Return user's desired function
int getFunction(int type) {
    const string managerFunctions = "1 2 3 4 11"; // will be added later
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
        if (type == 2)  // Delete or update an item
            foundFunction = editOrDeleteFunctions.find(function);

        // Validate input
        if (function.empty() || foundSpace != string::npos || foundFunction == string::npos) {
            cout << "Error: function not found. Enter again: ";
            getline(cin, function);
        } else break;
    }
    return stoi(function);
}

// Call user's desired function
void callFunction(int function) {
    switch (function) {
        case 1:
            printListOfItems();
            break;
        case 2:
            addItem();
            break;
        case 3:
            updateOrDeleteItem();
            break;
        case 4:
            addCustomer();
            break;
        default:
            cout << "Goodbye" << endl;
    }
}

// Print list of items
void printListOfItems() {
    if (!isItemListEmpty()) {
        for (int i = 0; i < itemList->size(); i++) {
            itemList->get(i).printItem();
        }
    }
}

// Add new item
void addItem() {
    item item;
    item.setItem();
    if (!isDuplicateItem(item)) {
        itemList->append(item);
        cout << "Added item: ";
        item.printItem();
    }   // Else, do nothing
}

// Update/delete a current item
void updateOrDeleteItem() {
    string id;
    cout << "Enter the targeted item's ID: ";
    getline(cin, id);

    if (!isItemListEmpty()) {
        bool found = false;
        for (int i = 0; i < itemList->size(); i++) {
            item item = itemList->get(i);
            if (item.getId() == id) {
                found = true;
                cout << "Selected item: ";
                item.printItem();
                if (isEditItem()) {
                    item.setItem();
                    if (!isDuplicateItem(item)) {
                        itemList->set(i, item);
                        cout << "Edited item: ";
                        item.printItem();
                    }
                    else break; // If duplicate, keep item the same
                } else  // User chose to delete
                    itemList->remove(i);
            }
        }
        if (!found)
            cout << "Index not found" << endl;
    }
}

// Add a new customer
void addCustomer() {
    customer customer;
    customer.setCustomer();
    if (!isDuplicateCustomer(customer)) {
        customerList->append(customer);
        cout << "Added customer: ";
        customer.printCustomer();
    }   // Else, do nothing
}

// Helper
bool isItemListEmpty() {
    if (itemList->size() == 0) {
        cout << "Item list is empty" << endl;
        return true;
    }
    return false;
}

bool isCustomerListEmpty() {
    if (customerList->size() == 0) {
        cout << "Customer list is empty" << endl;
        return true;
    }
    return false;
}

bool isDuplicateItem(item item) {
    for (int i = 0; i < itemList->size(); i++) {
        if (item.getId() == itemList->get(i).getId()) {
            cout << "This item is already in the list and will not be added or deleted" << endl;
            return true;
        }
    }
    return false;
}

bool isDuplicateCustomer(customer customer) {
    for (int i = 0; i < customerList->size(); i++) {
        if (customer.getCustomerId() == customerList->get(i).getCustomerId()) {
            cout << "This customer is already in the list and will not be added or deleted" << endl;
            return true;
        }
        return false;
    }
}

bool isEditItem() {
    cout << "Enter an option:" << endl
         << "1. Update this item" << endl
         << "2. Delete this item" << endl;

    int function = getFunction(2);
    return function == 1;
}




//         << "2. Add new customer of update an existing customer" << endl
//         << "3. Promote an existing customer" << endl
//         << "4. Rent an item" << endl
//         << "5. Return an item" << endl
//         << "6. Display all items" << endl
//         << "7. Display out-of-stock items" << endl
//         << "8. Display all customers" << endl
//         << "9. Display group of customers" << endl
//         << "10. Search items or customers" << endl
