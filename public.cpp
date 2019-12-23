#include <iostream>
#include <string>
#include "customer.cpp"
#include "public.h"

using namespace std;

int getFunction(functionType type) {
    const string listFunctions = "1 2 3";
    const string itemTypeFunctions = "1 2 3";
    const string editOrDeleteFunctions = "1 2 3";
    const string itemFieldFunctions = "1 2 3 4 5 6";
    const string itemFieldWithGenreFunctions = "1 2 3 4 5 6 7";

    string function;
    getline(cin, function);

    // Validate user input
    while (true) {
        // Check if input has space
        size_t foundSpace = function.find_first_of(' ');
        size_t foundFunction = 0;

        switch (type) {
            case manageList: {  // Manage list
                foundFunction = listFunctions.find(function);
                break;
            }
            case getItemType: { // Choose movie, dvd or game
                foundFunction = itemTypeFunctions.find(function);
                break;
            }
            case editOrDelete: {    // Delete or update an item
                foundFunction = editOrDeleteFunctions.find(function);
                break;
            }
            case getItemField: {    // Modify a field
                foundFunction = itemFieldFunctions.find(function);
                break;
            }
            case getItemFieldWithGenre: {
                foundFunction = itemFieldWithGenreFunctions.find(function);
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

int getEditOrDeleteFunction() {
    cout << "Enter an option:" << endl
         << "1. Edit this item" << endl
         << "2. Delete this item" << endl
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

