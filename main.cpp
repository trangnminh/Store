#include <iostream>
#include <string>
#include <fstream>
#include "Item.h"
#include "List.h"
#include "public.h"

using namespace std;

// File I/O functions
bool loadItemsFromFile(const string& itemFileName, List<Item*> *itemList);
void writeItemsToFile(const string& itemFileName, List<Item*> *itemList);

// Item list management functions
void printItems(List<Item*> itemList);
void addItem(List<Item*> *itemList);
void editOrDeleteItem(List<Item*> *itemList);
void printOutOfStockItems(List<Item*> itemList);
void searchItems(List<Item*> itemList);
bool isDuplicateNewItem(Item *item, List<Item*> *itemList);
bool isDuplicateEditedItem(Item *item, List<Item*> *itemList, int index);

/* MAIN */
int main(int argc, char *argv[]) {
    string itemFile;

    // Get input files from command line
    if (argc == 3) {
        itemFile = argv[2];
    }
    else {
        cout << "Usage: start store.exe customer_file_name.txt item_file_name.txt" << endl;
        return 1;
    }

    // Create a list to store all items
    List<Item*> itemList;

    // Load all items
    loadItemsFromFile(itemFile, &itemList);
    printItems(itemList);

    if (itemList.getSize() != 0)
        cout << "Loaded " <<  itemList.getSize() << " entries above" << endl;

    // do your shit

    // Write items to file before exit
    writeItemsToFile(itemFile, &itemList);

    return 0;
}

/* FILE I/O */
// Load items from file
bool loadItemsFromFile(const string& itemFileName, List<Item*> *itemList) {
    ifstream inFile;
    inFile.open(itemFileName);
    if (!inFile) {
        cout << "Error: unable to open file " << itemFileName << endl;
        return false;
    }

    // Get each line in text file and split it
    string s;
    while (getline(inFile, s)) {
        string delim = ", ";

        int i = 0;
        string fields[7];

        auto start = 0U;
        auto end = s.find(delim);

        // Split the line around ", "
        while (end != string::npos) {
            // Add the token to fields array
            fields[i++] = s.substr(start, end - start);
            // Set start and end for next token
            start = end + delim.length();
            end = s.find(delim, start);
        }
        // Get last token
        fields[i++] = s.substr(start, end - start);

        // Copy data to items and append items
        if (fields[2] == "Record") {
            Item *tmp = new Record(fields[0], fields[1], fields[3], fields[4], fields[5], fields[6]);
            if (!isDuplicateNewItem(tmp, itemList))
                itemList->append(tmp);
        }
        else if (fields[2] == "DVD") {
            Item *tmp = new DVD(fields[0], fields[1], fields[3], fields[4], fields[5], fields[6]);
            if (!isDuplicateNewItem(tmp, itemList))
                itemList->append(tmp);
        }
        else {
            Item *tmp = new Game(fields[0], fields[1], fields[3], fields[4], fields[5], fields[6]);
            if (!isDuplicateNewItem(tmp, itemList))
                itemList->append(tmp);
        }
    }
    inFile.close();
    return true;
}

// Save items to file
void writeItemsToFile(const string& itemFileName, List<Item*> *itemList) {
    ofstream outFile;
    outFile.open(itemFileName);

    for (int i = 0; i < itemList->getSize(); i++)
        outFile << itemList->get(i)->itemToString() << endl;

    outFile.close();
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
         << "1. Add a new Record" << endl
         << "2. Add a new DVD" << endl
         << "3. Add a new Game" << endl;

    int function = getFunction(getItemType);

    Item *item = nullptr;

    switch (function) {
        case 1: item = new Record(); break;
        case 2: item = new DVD(); break;
        case 3: item = new Game(); break;
        default:;   // Do nothing
    }

    // If item is not duplicate, append to list
    if (!isDuplicateNewItem(item, itemList)) {
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

                    // If edited item is a duplicate, put back old id
                    if (isDuplicateEditedItem(tmp, itemList, i)) {
                        cout << "New ID is a duplicate, reverting to old ID.." << endl;
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

// Check if a new item is a duplicate
bool isDuplicateNewItem(Item *item, List<Item*> *itemList) {
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

// Check if an item is a duplicate (skip itself)
bool isDuplicateEditedItem(Item *item, List<Item*> *itemList, int index) {
    int listSize = itemList->getSize();
    if (listSize != 0) {
        for (int i = 0; i < listSize; i++) {
            if (i != index) {
                Item *tmp = itemList->get(i);
                // Validate unique xxx in Ixxx-yyyy
                if (item->getId().substr(1, 3) == tmp->getId().substr(1, 3))
                    return true;
            }
        }
        return false;
    }
    return false;
}