#include <iostream>
#include <string>
#include "Item.h"
#include "List.h"
#include "public.h"

using namespace std;

// Item list management functions
void printItems(List<Item*> itemList);
void addItem(List<Item*> *itemList);
void editOrDeleteItem(List<Item*> *itemList);
void printOutOfStockItems(List<Item*> itemList);
void searchItems(List<Item*> itemList);
bool isDuplicateItem(Item *item, List<Item*> *itemList);

/* MAIN */
int main() {
    // Create a list to store all items
    List<Item*> itemList;

    addItem(&itemList);
    addItem(&itemList);
    printItems(itemList);

    editOrDeleteItem(&itemList);
    editOrDeleteItem(&itemList);

    printItems(itemList);

    return 0;
}

/* ITEM LIST FUNCTIONS */
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

        if (item->getNumOfCopies() > 0)
            item->setAvailable();
    } else  {
        // Else, free memory
        cout << "Duplicate ID, item will not be added" << endl;
        delete item;
    }
}

// Update a current item
void editOrDeleteItem(List<Item*> *itemList) {
    string id;
    cout << "Enter the targeted item's ID (xxx): ";
    getline(cin, id);

    int listSize = itemList->getSize();
    bool found = false;

    // If list is not empty, search for item
    if (listSize != 0) {
        for (int i = 0; i < listSize; i++) {
            Item *tmp = itemList->get(i);
            if (id == tmp->getId().substr(1, 3)) {
                found = true;
                string oldId = tmp->getId();

                cout << "Selected item: ";
                tmp->display();

                int function = getEditOrDeleteFunction();

                if (function == 1) {
                    tmp->getEditFieldMenu();
                    // If edited item is a duplicate, or have its ID unchanged, put back old id
                    if (isDuplicateItem(tmp, itemList)) {
                        cout << "ID not modified or is a duplicate, reverting to last unique ID.." << endl;
                        tmp->setId(oldId);
                        cout << "Edited item: ";
                        tmp->display();
                    }
                    break;
                }
                else if (function == 2) {
                    // Delete current node
                    itemList->deleteNode(i);
                    cout << "Item deleted" << endl;
                    break;
                }
            }
        }
        if (!found)
            cout << "ID not found" << endl;
    }
}

// Print out of stock items
void printOutOfStockItems(List<Item*> itemList) {
    cout << "Printing out-of-stock items.." << endl;
    int notStocked = 0;
    if (itemList.getSize() != 0) {
        for (int i = 0; i < itemList.getSize(); i++) {
            Item *tmp = itemList.get(i);
            if (tmp->getNumOfCopies() == 0) {
                tmp->display();
                notStocked++;
            }
        }
    }
    if (notStocked == 0) {
        cout << "All items are stocked" << endl;
    }
}

// Search all items containing a keyword in its ID or title
void searchItems(List<Item*> itemList) {
    cout << "Enter a keyword: ";
    string keyword;
    getline(cin, keyword);

    if (keyword.empty()) {
        cout << "Keyword is empty" << endl;
        return;
    }

    // Start searching for matching title or id
    cout << "Searching matched IDs or titles.." << endl;
    int match = 0;

    // Search is case insensitive
    keyword = toLowerCase(keyword);

    if (itemList.getSize() != 0) {
        for (int i = 0; i < itemList.getSize(); i++) {
            Item *tmp = itemList.get(i);
            if (toLowerCase(tmp->getId()).find(keyword) != string::npos ||
                toLowerCase(tmp->getTitle()).find(keyword) != string::npos) {
                tmp->display();
                match++;
            }
        }
    }
    if (match == 0) {
        cout << "No result" << endl;
    }
}

// Check if an item is a duplicate
bool isDuplicateItem(Item *item, List<Item*> *itemList) {
    int listSize = itemList->getSize();
    if (listSize != 0) {
        for (int i = 0; i < listSize; i++) {
            Item *tmp = itemList->get(i);
            // Validate unique xxx in Ixxx-yyyy
            if (item->getId().substr(1, 3) == tmp->getId().substr(1, 3))
                return true;
        }
        return false;
    }
    return false;
}