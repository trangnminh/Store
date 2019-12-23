#include <iostream>
#include <string>
#include <fstream>
#include "Item.h"
#include "Customer.h"
#include "List.h"
#include "public.h"

using namespace std;

/*
 * Most items and customers functions are identical
 * and should use template but
 * then load from file has bug, no known fix
 */

// File I/O functions
bool loadItemsFromFile(const string& itemFileName, List<Item*> *itemList);
void writeItemsToFile(const string& itemFileName, List<Item*> *itemList);
bool loadCustomersFromFile(const string& customerFileName, List<Customer*> *customerList);
void writeCustomersToFile(const string& customerFileName, List<Customer*> *customerList);

// Item list management functions
void printItems(List<Item*> itemList);
void addItem(List<Item*> *itemList);
void editOrDeleteItem(List<Item*> *itemList);
void printOutOfStockItems(List<Item*> itemList);
void searchItems(List<Item*> itemList);
bool isDuplicateNewItem(const string& itemId, List<Item*> *itemList);
bool isDuplicateEditedItem(Item *item, List<Item*> *itemList, int index);

// Customer list management functions
void printCustomers(List<Customer*> customerList);
void addCustomer(List<Customer*> *customerList);
bool isDuplicateNewCustomer(const string& customerId, List<Customer*> *customerList);
bool isDuplicateEditedCustomer(Customer *customer, List<Customer*> *customerList, int index);

// Helper
bool checkArgc(int argc) {
    // Get input files from command line
    if (argc == 3) return true;
    else {
        cout << "Usage: start store.exe customer_file_name.txt item_file_name.txt" << endl;
        return false;
    }
}

/* MAIN */
int main(int argc, char *argv[]) {
    string itemFile;
    string customerFile;

    if (checkArgc(argc)) {
        customerFile = argv[1];
        itemFile = argv[2];
    }
    else return 1;

    // Load all items and customers
    List<Item*> itemList;
    List<Customer*> customerList;
    loadItemsFromFile(itemFile, &itemList);
    loadCustomersFromFile(customerFile, &customerList);

    // Write to file before exit
    writeItemsToFile(itemFile, &itemList);
    writeCustomersToFile(customerFile, &customerList);
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
        fields[i] = s.substr(start, end - start);

        // Copy data to items and append items
        Item *tmp = nullptr;
        if (!isDuplicateNewItem(fields[0], itemList)) {
            if (fields[2] == "Record")
                tmp = new Record(fields[0], fields[1], fields[3],
                                       fields[4], fields[5], fields[6]);
            else if (fields[2] == "DVD")
                tmp = new DVD(fields[0], fields[1], fields[3],
                                    fields[4], fields[5], fields[6]);
            else
                tmp = new Game(fields[0], fields[1], fields[3],
                                     fields[4], fields[5], fields[6]);
        }
        if (tmp) itemList->append(tmp);
    }
    inFile.close();
    return true;
}

// Save items to file
void writeItemsToFile(const string& itemFileName, List<Item*> *itemList) {
    ofstream outFile;
    outFile.open(itemFileName);

    int size = itemList->getSize();
    if (size == 0)
        cout << "List is currently empty" << endl;

    else for (int i = 0; i < size; i++)
        outFile << itemList->get(i)->itemToString() << endl;

    outFile.close();
}

// Loaf customers from file
bool loadCustomersFromFile(const string& customerFileName, List<Customer*> *customerList) {
    ifstream inFile;
    inFile.open(customerFileName);
    if (!inFile) {
        cout << "Error: unable to open file " << customerFileName << endl;
        return false;
    }

    Customer *lastCustomerGot = nullptr;    // Keep track of last read customer

    string s;
    while (getline(inFile, s)) {
        if (s[0] == 'C') {
            string delim = ", ";
            int i = 0;
            string fields[6];

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
            fields[i] = s.substr(start, end - start);

            // Copy data to customers and append customers if not duplicate
            Customer *tmp = nullptr;
            if (!isDuplicateNewCustomer(fields[0], customerList)) {
                if (fields[5] == "Guest") {
                    tmp = new Guest(fields[0], fields[1], fields[2],
                                    fields[3], fields[4]);
                    lastCustomerGot = tmp;
                }
                else if (fields[5] == "Regular") {
                    tmp = new Regular(fields[0], fields[1], fields[2],
                                      fields[3], fields[4]);
                    lastCustomerGot = tmp;
                }
                else {
                    tmp = new VIP(fields[0], fields[1], fields[2],
                                  fields[3], fields[4]);
                    lastCustomerGot = tmp;
                }
            }
            if (tmp) customerList->append(tmp);
        }

        else if (s[0] == 'I') {
            if (lastCustomerGot)
                lastCustomerGot->getListOfRentals()->append(s);
        }
        else continue;
    }
    inFile.close();
    return true;
}

// Save customers to file
void writeCustomersToFile(const string& customerFileName, List<Customer*> *customerList) {
    ofstream outFile;
    outFile.open(customerFileName);

    int size = customerList->getSize();
    if (size == 0)
        cout << "List is currently empty" << endl;

    else for (int i = 0; i < size; i++) {
        Customer *tmp = customerList->get(i);
        // Print customer info
        outFile << tmp->customerToString() << endl;
        // Print list of rentals
        if (tmp->getListOfRentals()->getSize() != 0) {
            for (int j = 0; j < tmp->getListOfRentals()->getSize(); ++j) {
                outFile << tmp->getListOfRentals()->get(j) << endl;
            }
        }
    }
    outFile.close();
}

/* ITEM LIST FUNCTIONS */
// Print list of items
void printItems(List<Item*> itemList) {
    if (itemList.getSize() != 0) {
        for (int i = 0; i < itemList.getSize(); i++) {
            itemList.get(i)->display();
        }
    } else
        cout << "List is currently empty" << endl;
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
    if (!isDuplicateNewItem(item->getId(), itemList)) {
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
    } else
        cout << "List is currently empty" << endl;
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
    } else {
        cout << "List is currently empty" << endl;
        return;
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
    else {
        cout << "List is currently empty" << endl;
        return;
    }
    if (match == 0) {
        cout << "No result" << endl;
    }
}

/* CUSTOMER LIST FUNCTIONS */
void printCustomers(List<Customer*> customerList) {
    if (customerList.getSize() != 0) {
        for (int i = 0; i < customerList.getSize(); i++) {
            customerList.get(i)->display();
        }
    } else
        cout << "List is currently empty" << endl;
}

void addCustomer(List<Customer*> *customerList) {
    Customer *customer = new Guest();

    if (!isDuplicateNewCustomer(customer->getId(), customerList)) {
        customerList->append(customer);
        cout << "Added: ";
        customer->display();
    } else  {
        // Else, free memory
        cout << "Duplicate ID, customer will not be added" << endl;
        delete customer;
    }
}

/* DUPLICATE CHECKS */
bool isDuplicateNewItem(const string& itemId, List<Item*> *itemList) {
    int listSize = itemList->getSize();
    if (listSize != 0) {
        for (int i = 0; i < listSize; i++) {
            Item *tmp = itemList->get(i);
            // Validate unique xxx in Ixxx-yyyy
            if (itemId.substr(1, 3) == tmp->getId().substr(1, 3))
                return true;
        }
        return false;
    }
    return false;
}

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

bool isDuplicateNewCustomer(const string& customerId, List<Customer*> *customerList) {
    int listSize = customerList->getSize();
    if (listSize != 0) {
        for (int i = 0; i < listSize; i++) {
            Customer *tmp = customerList->get(i);
            // Validate unique xxx in Cxxx
            if (customerId.substr(1, 3) == tmp->getId().substr(1, 3))
                return true;
        }
        return false;
    }
    return false;
}

bool isDuplicateEditedCustomer(Customer *customer, List<Customer*> *customerList, int index) {
    int listSize = customerList->getSize();
    if (listSize != 0) {
        for (int i = 0; i < listSize; i++) {
            if (i != index) {
                Customer *tmp = customerList->get(i);
                // Validate unique xxx in Ixxx-yyyy
                if (tmp->getId().substr(1, 3) == tmp->getId().substr(1, 3))
                    return true;
            }
        }
        return false;
    }
    return false;
}