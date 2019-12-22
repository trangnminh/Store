#include "Item.h"

void Item::setId() {
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
            this->id = s;
            break;
        }
        else {
            cout << "Error: invalid ID. Valid ID: Ixxx-yyyy (x: digit, yyyy: published year)" << endl;
            cout << "Enter again: ";
        }
    }
}

void Item::setTitle() {
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

void Item::setLoanType() {
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
void Item::setNumOfCopies() {
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
void Item::setRentalFee() {
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

void Item::setGenre() {
    cout << "Enter item's genre: ";
    while (true) {
        string s;
        getline(cin, s);
        // Validate genre input
        if (s == "Action" || s == "Horror" || s == "Drama" || s == "Comedy") {
            this->genre = s;
            break;
        } else {
            cout << "Error: invalid genre. Valid genres: Action, Horror, Drama, Comedy" << endl;
            cout << "Enter again: ";
        }
    }
}