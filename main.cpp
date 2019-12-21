#include <iostream>
#include <string>

#include "item.h"

using namespace std;

/* SUB-FUNCTIONS INITIALIZATION */
void printMenu();
int getFunction(int type);
void callFunction(int function);

void printListOfItems();
void addItem();

// Global list (bad practice, may review later)
auto *movieList = new LinkedList<movie>();
auto *dvdList = new LinkedList<dvd>();
auto *gameList = new LinkedList<game>();

int main() {
    int function = 0;
    do {
        printMenu();
        function = getFunction(1);
        cout << "You selected " << function << endl;
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

         << "11. Exit" << endl;
}

// Return user's desired function
int getFunction(int type) {
    const string managerFunctions = "1 2 11"; // will be added later
    const string addItemFunctions = "1 2 3";
    const string printListOfItemsFunction = "1 2 3";

    string function;
    getline(cin, function);

    // Validate user input
    while (true) {
        // Check if input has space
        size_t foundSpace = function.find_first_of(' ');
        size_t foundFunction = 0;

        // Check input against valid functions based on type
        if (type == 1)  // Manager
            foundFunction = managerFunctions.find(function);
        if (type == 2) // Print list
            foundFunction = printListOfItemsFunction.find(function);
        if (type == 3)  // Add items
            foundFunction = addItemFunctions.find(function);

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
        default:
            cout << "Goodbye" << endl;
    }
}

// Print list of items by type
void printListOfItems() {
    cout << "Enter an option:" << endl
         << "1. Print list of movies" << endl
         << "2. Print list of DVDs" << endl
         << "3. Print list of games" << endl;

    int function = getFunction(2);

    switch (function) {
        case 1: {
            if (movieList->size() == 0) {
                cout << "Movie list is empty" << endl;
                break;
            }
            else for (int i = 0; i < movieList->size(); i++) {
                movieList->get(i).printItem();
            }
            break;
        }
        case 2: {
            if (dvdList->size() == 0) {
                cout << "DVD list is empty" << endl;
                break;
            }
            else for (int i = 0; i < dvdList->size(); i++) {
                    dvdList->get(i).printItem();
                }
            break;
        }
        case 3: {
            if (gameList->size() == 0) {
                cout << "Game list is empty" << endl;
                break;
            } else
                for (int i = 0; i < movieList->size(); i++) {
                    gameList->get(i).printItem();
                }
            break;
        }
        default:;
    }
}

// Add new item
void addItem() {
    cout << "Enter an option:" << endl
         << "1. Add new movie record" << endl
         << "2. Add new DVD" << endl
         << "3. Add new game" << endl;

    int function = getFunction(3);

    switch (function) {
        case 1: {
            movie movie;
            movie.setItem();
            movie.setGenre();
            movieList->append(movie);
            break;
        }
        case 2: {
            dvd dvd;
            dvd.setItem();
            dvd.setGenre();
            dvdList->append(dvd);
            break;
        }
        case 3: {
            game game;
            game.setItem();
            gameList->append(game);
            break;
        }
        default:; // do nothing
    }
}

//         << "2. Update or delete an existing item" << endl
//         << "2. Add new customer of update an existing customer" << endl
//         << "3. Promote an existing customer" << endl
//         << "4. Rent an item" << endl
//         << "5. Return an item" << endl
//         << "6. Display all items" << endl
//         << "7. Display out-of-stock items" << endl
//         << "8. Display all customers" << endl
//         << "9. Display group of customers" << endl
//         << "10. Search items or customers" << endl

//    movie movie1;
//    auto *movieList = new LinkedList<movie>();
//
//    movie1.setItem();
//    movie1.setGenre();
//
//    movieList->append(movie1);
//    movie gotMovie = movieList->get(0);
//    gotMovie.printItemWithGenre();
//
//    auto *gameList = new LinkedList<game>();
//    game game1;
//    game1.setItem();
//
//    gameList->append(game1);
//    game gotGame = gameList->get(0);
//    gotGame.printItem();
//
//    game game2;
//    game2.setItem();
//
//    gameList->append(game2);
//    game gotGame2 = gameList->get(1);
//    gotGame2.printItem();