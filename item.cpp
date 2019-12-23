#include "Item.h"
#include "public.h"

string Item::getId() {
    return this->id;
}

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

// Edit item by single field
void Item::editItem(int field) {
    switch (field) {
        case 1: {
            setId();
            cout << "Edited item: ";
            display();
            break;
        }
        case 2: {
            setTitle();
            cout << "Edited item: ";
            display();
            break;
        }
        case 3: {
            setLoanType();
            cout << "Edited item: ";
            display();
            break;
        }
        case 4: {
            setNumOfCopies();
            cout << "Edited item: ";
            display();
            available = numOfCopies > 0;
            break;
        }
        case 5: {
            setRentalFee();
            cout << "Edited item: ";
            display();
            break;
        }
        default:;
    }
}

void Record::editItem(int field) {
    switch (field) {
        case 1: {
            setId();
            cout << "Edited item: ";
            display();
            break;
        }
        case 2: {
            setTitle();
            cout << "Edited item: ";
            display();
            break;
        }
        case 3: {
            setLoanType();
            cout << "Edited item: ";
            display();
            break;
        }
        case 4: {
            setNumOfCopies();
            cout << "Edited item: ";
            display();
            available = numOfCopies > 0;
            break;
        }
        case 5: {
            setRentalFee();
            cout << "Edited item: ";
            display();
            break;
        }
        case 6: {
            setGenre();
            cout << "Edited item: ";
            display();
            break;
        }
        default:;
    }
}

void DVD::editItem(int field) {
    switch (field) {
        case 1: {
            setId();
            cout << "Edited item: ";
            display();
            break;
        }
        case 2: {
            setTitle();
            cout << "Edited item: ";
            display();
            break;
        }
        case 3: {
            setLoanType();
            cout << "Edited item: ";
            display();
            break;
        }
        case 4: {
            setNumOfCopies();
            cout << "Edited item: ";
            display();
            available = numOfCopies > 0;
            break;
        }
        case 5: {
            setRentalFee();
            cout << "Edited item: ";
            display();
            break;
        }
        case 6: {
            setGenre();
            cout << "Edited item: ";
            display();
            break;
        }
        default:;
    }
}

// Helper to print edit menu
void Item::getEditFieldMenu() {
    while (true) {
        cout << "Enter an option:" << endl
             << "1. Edit ID" << endl
             << "2. Edit title" << endl
             << "3. Edit loan type" << endl
             << "4. Edit number of copies" << endl
             << "5. Edit rental fee" << endl
             << "6. Quit editing" << endl;

        int field = getFunction(getItemField);
        if (field == 6) break;
        editItem(field);
    }
}

void Record::getEditFieldMenu() {
    while (true) {
        cout << "Enter an option:" << endl
             << "1. Edit ID" << endl
             << "2. Edit title" << endl
             << "3. Edit loan type" << endl
             << "4. Edit number of copies" << endl
             << "5. Edit rental fee" << endl
             << "6. Edit genre" << endl
             << "7. Quit editing" << endl;

        int field = getFunction(getItemFieldWithGenre);
        if (field == 7) break;
        editItem(field);
    }
}

void DVD::getEditFieldMenu() {
    while (true) {
        cout << "Enter an option:" << endl
             << "1. Edit ID" << endl
             << "2. Edit title" << endl
             << "3. Edit loan type" << endl
             << "4. Edit number of copies" << endl
             << "5. Edit rental fee" << endl
             << "6. Edit genre" << endl
             << "7. Quit editing" << endl;

        int field = getFunction(getItemFieldWithGenre);
        if (field == 7) break;
        editItem(field);
    }
}

bool Item::isAvailable() const {
    return available;
}

// Print Item's info
void Item::display() {
    cout.precision(2);
    cout << this->id << ", " << this->title << ", " << this->rentalType << ", "
         << this->loanType << ", " << this->numOfCopies << ", "
         << fixed << this->rentalFee << endl;
}


void Record::display() {
    cout.precision(2);
    cout << this->id << ", " << this->title << ", " << this->rentalType << ", "
         << this->loanType << ", " << this->numOfCopies << ", "
         << fixed << this->rentalFee << ", " << this->genre << endl;
}

void DVD::display() {
    cout.precision(2);
    cout << this->id << ", " << this->title << ", " << this->rentalType << ", "
         << this->loanType << ", " << this->numOfCopies << ", "
         << fixed << this->rentalFee << ", " << this->genre << endl;
}



