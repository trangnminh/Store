//
// Created by Trần Mạch Sở Hân on 12/20/19.
//

#include "item.h"

// Item setter
inline void item::setItem() {
    setId();
    setTitle();
    setLoanType();
    setNumOfCopies();
    setRentalFee();
}

// Print item's info
inline void item::printItem() {
    cout << this->id << ", " << this->title << ", " << this->rentalType << ", "
         << this->loanType << ", " << this->numOfCopies << ", " << this->rentalFee << endl;
}


// Set item id
inline void item::setId() {
    cout << "Enter item's ID: ";
    while (true) {
        string s;
        getline(cin, s);
        // Validate id input
        bool valid = true;
        for (int i = 0; i < s.length(); i++) {
            if (i == 0 || i == 4) continue;
            if (!isdigit(s[i])) {
                valid = false;
                break;
            }
        }
        if (valid && s.length() == 9 && s[0] == 'I' && s[4] == '-') {
            this -> id = s;
            break;
        }
        else {
            cout << "Error: invalid ID. Valid ID: Ixxx-yyyy (x: digit, yyyy: published year)" << endl;
            cout << "Enter again: ";
        }
    }
}

// Set item title
inline void item::setTitle() {
    cout << "Enter item's title: ";
    while (true) {
        string s;
        getline(cin, s);
        if (!s.empty()) {
            this->title = s;
            break;
        }
        else
            cout << "Error: invalid title. Enter again: ";
    }
}

// Set item loan type
inline void item::setLoanType() {
    cout << "Enter item's loan type: ";
    while (true) {
        string s;
        getline(cin, s);
        // Validate loan type input
        if (s == "1-week" || s == "2-day") {
            this->loanType = s;
            break;
        }
        else {
            cout << "Error: invalid loan type. Valid loan type: 1-week or 2-day" << endl;
            cout << "Enter again: ";
        }
    }
}

// Set number of copies
inline void item::setNumOfCopies() {
    cout << "Enter item's number of copies: ";
    while (true) {
        string num;
        getline(cin, num);
        // Validate integer input
        if (!num.empty() && num.find_first_not_of("0123456789") == string::npos) {
            this->numOfCopies = stoi(num);
            break;
        }
        else
            cout << "Error: invalid input. Enter again: ";
    }
}

// Set rental fee
inline void item::setRentalFee() {
    cout << "Enter item's rental fee: ";
    while (true) {
        string fee;
        getline(cin, fee);
        // Validate double input
        size_t foundDot = fee.find('.');
        if (foundDot != string::npos) {
            int firstDotPosition = foundDot;    // Dot found, find if there's a second dot
            foundDot = fee.find('.', firstDotPosition + 1);

            if (!fee.empty() && fee.find_first_not_of("0123456789.") == string::npos && foundDot == string::npos) {
                this->rentalFee = stod(fee);
                break;
            }
        } // No dot
        else if (!fee.empty() && fee.find_first_not_of("0123456789") == string::npos) {
            this->rentalFee = stod(fee);
            break;
        }
        else
            cout << "Error: invalid input. Enter again: ";
    }
}

inline void item::setAll(const string &id, const string &title, const string &rentalType, const string &loanType, int numOfCopies,
           double rentalFee) {
    this -> id = id;
    this -> title = title;
    this -> rentalType = rentalType;
    this -> loanType = loanType;
    this -> numOfCopies = numOfCopies;
    this -> rentalFee = rentalFee;
}

inline string item::toString() {
    return this->id+","+this->title+","+this->rentalType+","+this->loanType
           +","+to_string(this->numOfCopies)+","+to_string(this->rentalFee);
}


// Set genre
inline void itemWithGenre::setGenre() {
    cout << "Enter item's genre: ";
    while (true) {
        string s;
        getline(cin, s);
        // Validate genre input
        if (s == "Action" || s == "Horror" || s == "Drama" || s == "Comedy") {
            this->genre = s;
            break;
        }
        else {
            cout << "Error: invalid genre. Valid genres: Action, Horror, Drama, Comedy" << endl;
            cout << "Enter again: ";
        }
    }
}

// Print item's info (with genre)
inline void itemWithGenre::printItemWithGenre() {
    cout << this->id << ", " << this->title << ", " << this->rentalType << ", "
         << this->loanType << ", " << this->numOfCopies << ", "
         << this->rentalFee << ", " << this->genre << endl;
}

inline void itemWithGenre::setGenre1(const string &genre) {
    itemWithGenre::genre = genre;
}

inline string itemWithGenre::toString() {
    return this->id+","+this->title+","+this->rentalType+","+this->loanType
    +","+to_string(this->numOfCopies)+","+to_string(this->rentalFee)+","+this->genre;
}

