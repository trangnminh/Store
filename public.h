// Header file for get-function helpers

#ifndef STORE_PUBLIC_H
#define STORE_PUBLIC_H

#include <iostream>
#include <string>
#include "item.h"
#include "List.h"

using namespace std;

// Enums for different types of functions
enum functionType{manageList, getItemType, editOrDelete, getItemField, getItemFieldWithGenre};

// Return user's desired function
int getFunction(functionType type);

// Let user edit or delete an item
int getEditOrDeleteFunction();

// Convert a string to lowercase
string toLowerCase(string s);

#endif //STORE_PUBLIC_H
