#include <iostream>
#include <string>
#include "Item.h"
#include "List.h"

using namespace std;

// Enums for different types of functions
enum functionType{manageList, getItemType, editOrDelete};

// Global functions
void printItems(List<Item*> itemList);
void addItem(List<Item*> *itemList);
void editOrDeleteItem(List<Item*> *itemList);

// Helpers
int getFunction(functionType type);
bool isDuplicateItem(Item *item, List<Item*> *itemList);
bool isEditItem();

/* MAIN */
int main() {
    // Create a list to store all items
    List<Item*> itemList;

    addItem(&itemList);
    addItem(&itemList);
    addItem(&itemList);
    addItem(&itemList);
    addItem(&itemList);

    cout << "After add: " << endl;
    printItems(itemList);
    cout << itemList.getSize() << endl;

    cout << "Delete 2 items" << endl;
    editOrDeleteItem(&itemList);
    editOrDeleteItem(&itemList);

    cout << "After delete" << endl;
    printItems(itemList);
    cout << itemList.getSize() << endl;

    cout << "Delete head: " << endl;
    itemList.deleteHead();

    cout << "Delete tail: " << endl;
    itemList.deleteTail();

    cout << "After delete 2" << endl;
    printItems(itemList);
    cout << itemList.getSize() << endl;

    cout << "Edit last: " << endl;
    editOrDeleteItem(&itemList);

    cout << "After edit: " << endl;
    printItems(itemList);
    cout << itemList.getSize() << endl;

    cout << "Edit again: " << endl;
    editOrDeleteItem(&itemList);

    cout << "After edit 2: " << endl;
    printItems(itemList);
    cout << itemList.getSize() << endl;

    cout << "Delete last: " << endl;
    editOrDeleteItem(&itemList);

    cout << "Final:" << endl;
    printItems(itemList);
    cout << itemList.getSize() << endl;

    return 0;
}

// Print list of items
void printItems(List<Item*> itemList) {
    if (itemList.getSize() != 0) {
        for (int i = 0; i < itemList.getSize(); i++) {
            itemList.get(i)->display();
        }
    }
}

// Add a new item to list
void addItem(List<Item*> *itemList) {
    cout << "Enter an option:" << endl
         << "1. Add a new Movie" << endl
         << "2. Add a new DVD" << endl
         << "3. Add a new Game" << endl;

    int function = getFunction(getItemType);

    Item *item = nullptr;

    switch (function) {
        case 1: item = new Movie(); break;
        case 2: item = new DVD(); break;
        case 3: item = new Game(); break;
        default:;   // Do nothing
    }

    // If item is not duplicate, append to list
    if (!isDuplicateItem(item, itemList)) {
        itemList->append(item);
        cout << "Added: ";
        item->display();
    } else  {
        // Else, free memory
        cout << "Duplicate ID, item will not be added" << endl;
        delete item;
    }
}

// Update a current item
void editOrDeleteItem(List<Item*> *itemList) {
    string id;
    cout << "Enter the targeted item's ID: ";
    getline(cin, id);

    int listSize = itemList->getSize();
    bool found = false;

    // If list is not empty, search for item
    if (listSize != 0) {
        for (int i = 0; i < listSize; i++) {
            Item *tmp = itemList->get(i);
            if (id == tmp->getId()) {
                found = true;
                string oldId = tmp->getId();

                cout << "Selected item: ";
                tmp->display();

                if (isEditItem()) {
                    tmp->setItem();
                    // If edited item is a duplicate, put back old id
                    if (isDuplicateItem(tmp, itemList)) {
                        cout << "Duplicate ID, reverting to old ID.." << endl;
                        tmp->setId(oldId);
                    }
                    cout << "Edited item: ";
                    tmp->display();
                    break;
                }
                else {
                    // Delete current node
                    itemList->deleteNode(i);
                    cout << "Item deleted" << endl;
                    break;
                }
            }
        }
        if (!found)
            cout << "Index not found" << endl;
    }
}

// Return user's desired function
int getFunction(functionType type) {
    const string listFunctions = "1 2 3";
    const string itemTypeFunctions = "1 2 3";
    const string editOrDeleteFunctions = "1 2";

    string function;
    getline(cin, function);

    // Validate user input
    while (true) {
        // Check if input has space
        size_t foundSpace = function.find_first_of(' ');
        size_t foundFunction = 0;

        if (type == manageList)  // Manage list
            foundFunction = listFunctions.find(function);

        if (type == getItemType) // Fetch a movie, dvd or game
            foundFunction = itemTypeFunctions.find(function);

        if (type == editOrDelete)  // Delete or update an item
            foundFunction = editOrDeleteFunctions.find(function);

        // Validate input
        if (function.empty() || foundSpace != string::npos || foundFunction == string::npos) {
            cout << "Error: function not found. Enter again: ";
            getline(cin, function);
        } else break;
    }
    return stoi(function);
}

// Check if an item is a duplicate
bool isDuplicateItem(Item *item, List<Item*> *itemList) {
    int listSize = itemList->getSize();
    if (listSize != 0) {
        for (int i = 0; i < listSize; i++) {
            Item *tmp = itemList->get(i);
            if (item->getId() == tmp->getId())
                return true;
        }
        return false;
    }
    return false;
}

// Let user edit or delete an item
bool isEditItem() {
    cout << "Enter an option:" << endl
         << "1. Edit this item" << endl
         << "2. Delete this item" << endl;

    int function = getFunction(editOrDelete);
    return function == 1;
}
