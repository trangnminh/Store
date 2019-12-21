#include <iostream>
#include <string>

#include "item.h"
#include "LinkedList.h"

using namespace std;

// Global list (bad practice, may review later)
static LinkedList<movie> *movieList = new LinkedList<movie>();
static LinkedList<dvd> *dvdList = new LinkedList<dvd>();
static LinkedList<game> *gameList = new LinkedList<game>();

/* SUB-FUNCTIONS INITIALIZATION */
void printMenu();
int getFunction(int type);
void callFunction(int function);

void printListOfItems();
void addItem();
void updateOrDeleteItem();

bool isMovieListEmpty();
bool isDVDListEmpty();
bool isGameListEmpty();
bool isEditItem();

int main() {
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

         << "11. Exit" << endl;
}

// Return user's desired function
int getFunction(int type) {
    const string managerFunctions = "1 2 3 11"; // will be added later
    const string itemFunctions = "1 2 3";
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
        if (type == 2) // Access specific type of item
            foundFunction = itemFunctions.find(function);
        if (type == 3)  // Delete or update an item
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
            if (!isMovieListEmpty()) {
                for (int i = 0; i < movieList->size(); i++)
                    movieList->get(i).printItem();
            } break;
        }
        case 2: {
            if (!isDVDListEmpty()) {
                for (int i = 0; i < dvdList->size(); i++)
                    dvdList->get(i).printItem();
            } break;
        }
        case 3: {
            if (!isGameListEmpty()) {
                for (int i = 0; i < gameList->size(); i++)
                    gameList->get(i).printItem();
            } break;
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

    int function = getFunction(2);

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

// Update a current item
void updateOrDeleteItem() {
    cout << "Enter an option:" << endl
         << "1. Update/delete a movie" << endl
         << "2. Update/delete a DVD" << endl
         << "3. Update/delete a game" << endl;

    int function = getFunction(2);

    string id;
    cout << "Enter the targeted item's ID: ";
    getline(cin, id);

    switch (function) {
        case 1: {
            if (!isMovieListEmpty()) {
                bool found = false;
                for (int i = 0; i < movieList->size(); i++) {
                    movie movie = movieList->get(i);
                    if (movie.getId() == id) {
                        found = true;
                        cout << "Selected item: ";
                        movie.printItem();
                        if (isEditItem()) {
                            movie.setItem();
                            movie.setGenre();
                            movieList->set(i, movie);
                            cout << "Edited item: ";
                            movie.printItem();
                        } else
                            movieList->remove(i);
                        break;
                    }
                }
                if (!found)
                    cout << "Index not found" << endl;
            } break;
        }
        case 2: {
            if (!isDVDListEmpty()) {
                bool found = false;
                for (int i = 0; i < dvdList->size(); i++) {
                    dvd dvd = dvdList->get(i);
                    if (dvd.getId() == id) {
                        found = true;
                        cout << "Selected item: ";
                        dvd.printItem();
                        if (isEditItem()) {
                            dvd.setItem();
                            dvd.setGenre();
                            dvdList->set(i, dvd);
                            cout << "Edited item: ";
                            dvd.printItem();
                        } else
                            dvdList->remove(i);
                        break;
                    }
                }
                if (!found)
                    cout << "Index not found" << endl;
            } break;
        }
        case 3: {
            if (!isGameListEmpty()) {
                bool found = false;
                for (int i = 0; i < gameList->size(); i++) {
                    game game = gameList->get(i);
                    if (game.getId() == id) {
                        found = true;
                        cout << "Selected item: ";
                        game.printItem();
                        if (isEditItem()) {
                            game.setItem();
                            gameList->set(i, game);
                            cout << "Edited item: ";
                            game.printItem();
                        } else
                            gameList->remove(i);
                        break;
                    }
                }
                if (!found)
                    cout << "Index not found" << endl;
            } break;
        }
        default:;
    }
}

// Helper
bool isMovieListEmpty() {
    if (movieList->size() == 0) {
        cout << "Movie list is empty" << endl;
        return true;
    }
    return false;
}

bool isDVDListEmpty() {
    if (dvdList->size() == 0) {
        cout << "DVD list is empty" << endl;
        return true;
    }
    return false;
}

bool isGameListEmpty() {
    if (gameList->size() == 0) {
        cout << "Game list is empty" << endl;
        return true;
    }
    return false;
}

bool isEditItem() {
    cout << "Enter an option:" << endl
         << "1. Update this item" << endl
         << "2. Delete this item" << endl;

    int function = getFunction(3);
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
