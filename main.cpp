/*
 * TO-DO:
 * - (optional) sort
 * - rebuild UI
 * - set while loop for program
 * - print group info
 */

#include <iostream>
#include <string>
#include <fstream>
#include "Item.h"
#include "Customer.h"
#include "List.h"
#include "public.h"

using namespace std;

// List management functions
void addItem(List<Item*> *itemList);
void printOutOfStockItems(List<Item*> itemList);
void addCustomer(List<Customer*> *customerList);
void printCustomersByLevel(List<Customer*> customerList);

void rentItem(List<Item*> *itemList, List<Customer*> *customerList);
void returnItem(List<Item*> *itemList, List<Customer*> *customerList);

// Template functions
template <typename T>
void printList(List<T*> list);

template <typename T>
void editOrDeleteObject(List<T*> *list);

template <typename T>
void searchList(List<T*> list);

template <typename T>
bool isDuplicateNewObject(T *t, List<T *> *list);

template <typename T>
bool isDuplicateEditedObject(T *t, List<T*> *list, int index);

template <typename T>
T* findObject(List<T*> *list);

// File I/O functions
bool loadItemsFromFile(const string& itemFileName, List<Item*> *itemList);
void writeItemsToFile(const string& itemFileName, List<Item*> *itemList);
bool loadCustomersFromFile(const string& customerFileName, List<Customer*> *customerList);
void writeCustomersToFile(const string& customerFileName, List<Customer*> *customerList);

// Helper
bool checkArgc(int argc) {
    // Get input files from command line
    if (argc == 3) return true;
    else {
        cout << "Usage: start store.exe customer_file_name.txt item_file_name.txt" << endl
        << "* NOTE: display format is as follows:" << endl
        << "* Item: Ixxx-yyyy, title, rentalType, loanType, numOfCopies, rentalFee, genre (if non-Game)" << endl
        << "* Customer: Cxxx, name, address, phone, numOfRentals, level" << endl
        << "* (list of rented IDs)" << endl;
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

    // do stuff
    //rentItem(&itemList, &customerList);
    //rentItem(&itemList, &customerList);

    // Write to file before exit
    writeItemsToFile(itemFile, &itemList);
    writeCustomersToFile(customerFile, &customerList);
    return 0;
}

/* LIST FUNCTIONS */
void addItem(List<Item*> *itemList) {
    cout << "Enter an option:" << endl
         << "1. Add a new Record" << endl
         << "2. Add a new DVD" << endl
         << "3. Add a new Game" << endl;

    int function = getFunction(itemTypes);

    Item *item = nullptr;

    switch (function) {
        case 1: item = new Record(); break;
        case 2: item = new DVD(); break;
        case 3: item = new Game(); break;
        default:;   // Do nothing
    }

    // If item is not duplicate, append to list
    if (!isDuplicateNewObject<Item>(item, itemList)) {
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

void printOutOfStockItems(List<Item*> itemList) {
    cout << "Printing out-of-stock items.." << endl;
    int notStocked = 0;
    if (itemList.getSize() > 0) {
        for (int i = 0; i < itemList.getSize(); i++) {
            Item *tmp = itemList.get(i);
            if (tmp->getNumOfCopies() == 0) {
                tmp->display();
                notStocked++;
            }
        }
    } else {
        cout << "Item list is empty" << endl;
        return;
    }
    if (notStocked == 0) {
        cout << "All items are stocked" << endl;
    }
}

void addCustomer(List<Customer*> *customerList) {
    Customer *customer = new Guest();
    if (!isDuplicateNewObject<Customer>(customer, customerList)) {
        customerList->append(customer);
        cout << "Added: ";
        customer->display();
    } else  {
        // Else, free memory
        cout << "Duplicate ID, customer will not be added" << endl;
        delete customer;
    }
}

void printCustomersByLevel(List<Customer*> customerList) {
    cout << "Enter an option:" << endl
         << "1. Print all Guests" << endl
         << "2. Print all Regulars" << endl
         << "2. Print all VIPs" << endl;

    int function = getFunction(customerLevels);

    int listSize = customerList.getSize();
    if (listSize > 0) {
        switch (function) {
            case 1: {
                for (int i = 0; i < customerList.getSize(); i++) {
                    Customer *tmp = customerList.get(i);
                    if (tmp->getLevel() == "Guest")
                        cout << tmp->getCustomerToString() << endl;
                }
                break;
            }
            case 2: {
                for (int i = 0; i < customerList.getSize(); i++) {
                    Customer *tmp = customerList.get(i);
                    if (tmp->getLevel() == "Regular")
                        cout << tmp->getCustomerToString() << endl;
                }
                break;
            }
            case 3: {
                for (int i = 0; i < customerList.getSize(); i++) {
                    Customer *tmp = customerList.get(i);
                    if (tmp->getLevel() == "VIP")
                        cout << tmp->getCustomerToString() << endl;
                }
                break;
            }
            default:;
        }
    }
    else {
        cout << "Customer list is empty" << endl;
    }
}

void rentItem(List<Item*> *itemList, List<Customer*> *customerList) {
    cout << "Enter an item ID (xxx) to rent: ";
    auto *item = findObject<Item>(itemList);

    if (item != nullptr)
        cout << "Item to rent: " << item->getItemToString() << endl;
    else return;

    cout << "Enter a customer ID (xxx): ";
    auto *customer = findObject<Customer>(customerList);

    if (customer != nullptr) {
        cout << "Customer: " << customer->getCustomerToString() << endl;
    }
    else return;

    // Both item and customer found, rent with constraints
    if (!item->getAvailable()) {
        cout << "Item is out of stock" << endl;
        return;
    }

    // Check if item is already rented
    int listSize = customer->getListOfRentals()->getSize();
    if (listSize > 0) {
        for (int i = 0; i < listSize; i++) {
            if (item->getId() == customer->getListOfRentals()->get(i)) {
                cout << "Item is already in customer's rental list" << endl;
                return;
            }
        }
    }

    // Check if ineligible customer
    if (customer->getLevel() == "Guest") {
        if (customer->getListOfRentals()->getSize() >= 2 || item->getLoanType() == "2-day") {
            cout << "Failed: this Guest is renting a maximum of 2 items, or is trying to rent a 2-day item" << endl;
            return;
        }
    }
    // Item and customer both eligible
    customer->getListOfRentals()->append(item->getId());

    if (customer->getLevel() != "VIP" || customer->getPoints() < 100) {
        cout.precision(2);
        cout << "Cost ($): " << item->getRentalFee() << endl;
    }

    customer->rent();
    item->getRented();
    cout << "Item rented successfully" << endl;
}

void returnItem(List<Item*> *itemList, List<Customer*> *customerList) {
    cout << "Enter an item ID (xxx) to return: ";
    auto *item = findObject<Item>(itemList);

    if (item != nullptr)
        cout << "Item to return: " << item->getItemToString() << endl;
    else return;

    cout << "Enter a customer ID (xxx): ";
    auto *customer = findObject<Customer>(customerList);

    if (customer != nullptr) {
        cout << "Customer: " << customer->getCustomerToString() << endl;
    }
    else return;

    // Find item in customer's list of rentals
    bool found = false;

    int listSize = customer->getListOfRentals()->getSize();
    if (listSize != 0) {
        for (int i = 0; i < listSize; i++) {
            if (item->getId() == customer->getListOfRentals()->get(i)) {
                found = true;
                // Delete item off rental list
                customer->getListOfRentals()->deleteNode(i);
                // Item logistics
                item->getReturned();
                customer->returnItem();
                cout << "Item returned successfully" << endl;

                // Promote customer is applicable
                if (customer->getNumOfPastRentals() >= 3) {
                    customer->promote();
                }
            }
        }
        if (!found)
            cout << "Item is not in customer's list of rentals" << endl;
    }
    else {
        cout << "Customer's list of rentals is empty" << endl;
    }
}

/* TEMPLATES */
template <typename T>
void printList(List<T*> list) {
    if (list.getSize() > 0) {
        for (int i = 0; i < list.getSize(); i++) {
            list.get(i)->display();
        }
    } else
        cout << "List is empty" << endl;
}

template <typename T>
void editOrDeleteObject(List<T*> *list) {
    string id;
    cout << "Enter the targeted ID (xxx): ";
    getline(cin, id);

    int listSize = list->getSize();
    bool found = false;

    // If list is not empty, search for item
    if (listSize > 0) {
        for (int i = 0; i < listSize; i++) {
            T *tmp = list->get(i);
            if (id == tmp->getId().substr(1, 3)) {
                found = true;
                string oldId = tmp->getId();

                cout << "Selected: ";
                tmp->display();

                int function = getEditOrDeleteFunction();

                if (function == 1) {
                    tmp->getEditFieldMenu();

                    // If edited item is a duplicate, put back old id
                    if (isDuplicateEditedObject(tmp, list, i)) {
                        cout << "New ID is a duplicate, reverting to old ID.." << endl;
                        tmp->setId(oldId);
                        cout << "Edited: ";
                        tmp->display();
                    }
                    break;
                }
                else if (function == 2) {
                    // Delete current node
                    list->deleteNode(i);
                    cout << "Target deleted" << endl;
                    break;
                }
            }
        }
        if (!found)
            cout << "ID not found" << endl;
    } else
        cout << "List is empty" << endl;
}

// Search all items containing a keyword in its ID or title
template <typename T>
void searchList(List<T*> list) {
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

    if (list.getSize() > 0) {
        for (int i = 0; i < list.getSize(); i++) {
            T *tmp = list.get(i);
            if (toLowerCase(tmp->getId()).find(keyword) != string::npos ||
                toLowerCase(tmp->getTitle()).find(keyword) != string::npos) {
                tmp->display();
                match++;
            }
        }
    }
    else {
        cout << "Targeted list is empty" << endl;
        return;
    }
    if (match == 0) {
        cout << "No result" << endl;
    }
}

// Check if a new object is a duplicate
template <typename T>
bool isDuplicateNewObject(T *t, List<T *> *list) {
    int listSize = list->getSize();
    if (listSize > 0) {
        for (int i = 0; i < listSize; i++) {
            T *tmp = list->get(i);
            // Validate unique xxx
            if (t->getId().substr(1, 3) == tmp->getId().substr(1, 3))
                return true;
        }
        return false;
    }
    return false;
}

// Check if an edited object is a duplicate (skip itself)
template <typename T>
bool isDuplicateEditedObject(T *t, List<T*> *list, int index) {
    int listSize = list->getSize();
    if (listSize > 0) {
        for (int i = 0; i < listSize; i++) {
            if (i != index) {
                T *tmp = list->get(i);
                // Validate unique xxx
                if (t->getId().substr(1, 3) == tmp->getId().substr(1, 3))
                    return true;
            }
        }
        return false;
    }
    return false;
}

// Find a specific item or customer
template <typename T>
T* findObject(List<T*> *list) {
    string id;
    getline(cin, id);

    if (id.empty()) {
        cout << "Input is empty" << endl;
        return nullptr;
    }

    int listSize = list->getSize();
    T* tmp = nullptr;

    if (listSize > 0) {
        for (int i = 0; i < listSize; i++) {
            tmp = list->get(i);
            if (id == tmp->getId().substr(1, 3))
                return tmp;
        }
    } else {
        cout << "Targeted list is empty" << endl;
    }
    if (tmp == nullptr)
        cout << "ID not found in database" << endl;

    return nullptr;
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

        if (fields[2] == "Record")
            tmp = new Record(fields[0], fields[1], fields[3],
                             fields[4], fields[5], fields[6]);
        else if (fields[2] == "DVD")
            tmp = new DVD(fields[0], fields[1], fields[3],
                          fields[4], fields[5], fields[6]);
        else
            tmp = new Game(fields[0], fields[1], fields[3],
                           fields[4], fields[5]);

        if (!isDuplicateNewObject(tmp, itemList))
            itemList->append(tmp);
        else
            delete tmp;
    }
    inFile.close();
    return true;
}

// Save items to file
void writeItemsToFile(const string& itemFileName, List<Item*> *itemList) {
    ofstream outFile;
    outFile.open(itemFileName);

    int size = itemList->getSize();
    if (size <= 0)
        cout << "Item list is empty" << endl;

    else for (int i = 0; i < size; i++)
            outFile << itemList->get(i)->getItemToString() << endl;

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

            // Copy data to customers and append customers if not duplicate
            Customer *tmp = nullptr;

            if (fields[5] == "Guest") {
                tmp = new Guest(fields[0], fields[1], fields[2],
                                fields[3], fields[4], "0");
                lastCustomerGot = tmp;
            }

            else if (fields[5] == "Regular") {
                tmp = new Regular(fields[0], fields[1], fields[2],
                                  fields[3], fields[4], "0");
                lastCustomerGot = tmp;
            }
            else {
                tmp = new VIP(fields[0], fields[1], fields[2],
                              fields[3], fields[4], fields[6]);
                lastCustomerGot = tmp;
            }
            if (!isDuplicateNewObject<Customer>(tmp, customerList)) {
                customerList->append(tmp);
            }
            else {
                delete tmp;
                lastCustomerGot = nullptr;
            }
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
    if (size <= 0)
        cout << "Customer list is empty" << endl;

    else for (int i = 0; i < size; i++) {
            Customer *tmp = customerList->get(i);
            // Print customer info
            outFile << tmp->getCustomerToString() << endl;
            // Print list of rentals
            for (int j = 0; j < tmp->getListOfRentals()->getSize(); j++) {
                outFile << tmp->getListOfRentals()->get(j) << endl;
            }
        }
    outFile.close();
}