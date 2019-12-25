#include <iostream>
#include <string>
#include "Item.h"
#include "public.h"

using namespace std;

int getFunction(functionType type) {
    const string listFunctions = "1 2 3 4 5 6 7 8 9 10 11 12 13";
    const string itemTypeFunctions = "1 2 3";
    const string itemFieldFunctions = "1 2 3 4 5 6 7";
    const string customerFieldFunctions = "1 2 3 4 5";
    const string editOrDeleteFunctions = "1 2 3";
    const string itemOrCustomerFunctions = "1 2";
    const string customerLevelFunctions = "1 2 3";

    string function;
    getline(cin, function);

    if (type == listMgtFuncs && function == "Exit") return EXIT;

    // Validate user input
    while (true) {
        // Check if input has space
        size_t foundSpace = function.find_first_of(' ');
        size_t foundFunction = 0;

        switch (type) {
            case listMgtFuncs: {  // Manage list
                foundFunction = listFunctions.find(function);
                break;
            }
            case itemTypes: { // Choose movie, dvd or game
                foundFunction = itemTypeFunctions.find(function);
                break;
            }
            case itemFields: {    // Modify a field
                foundFunction = itemFieldFunctions.find(function);
                break;
            }
            case customerFields: {
                foundFunction = customerFieldFunctions.find(function);
                break;
            }
            case editOrDelete: {    // Delete or update an item
                foundFunction = editOrDeleteFunctions.find(function);
                break;
            }
            case itemOrCustomer: {
                foundFunction = itemOrCustomerFunctions.find(function);
                break;
            }
            case customerLevels: {
                foundFunction = customerLevelFunctions.find(function);
                break;
            }
            default:;
        }

        // Validate input
        if (function.empty() || foundSpace != string::npos || foundFunction == string::npos) {
            cout << "Error: function not found. Enter again: ";
            getline(cin, function);
        } else break;
    }
    return stoi(function);
}

// Helpers
int getEditOrDeleteFunction() {
    cout << "Enter an option:" << endl
         << "1. Edit this target" << endl
         << "2. Delete this target" << endl
         << "3. Cancel" << endl;

    int function = getFunction(editOrDelete);
    return function;
}

string toLowerCase(string s) {
    for (char &c : s) {
        if ('A' <= c && c <= 'Z')
            c = tolower(c);
    }
    return s;
}

string getNonEmptyInput() {
    while (true) {
        string s;
        getline(cin, s);
        if (!s.empty())
            return s;
        else
            cout << "Empty input. Enter again: ";
    }
}

