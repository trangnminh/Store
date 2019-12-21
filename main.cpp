#include <iostream>
#include <fstream>
#include "item.cpp"
#include "LinkedList.h"
using namespace std;

//Declare method

//get line from the input file and seperate them by comma
void getInput(item *item, string line, string* genre);

//Read file using ifstream
void readItem(LinkedList<movie>* movieList, LinkedList<dvd>* dvdList
        ,LinkedList<game>* gameList);

void outputFile(LinkedList<movie>* movieList, LinkedList<dvd>* dvdList
        ,LinkedList<game>* gameList);

//main function
int main() {
    auto *movieList = new LinkedList<movie>();
    auto *dvdList = new LinkedList<dvd>();
    auto *gameList = new LinkedList<game>();
    readItem(movieList,dvdList,gameList);
    outputFile(movieList,dvdList,gameList);
    return 0;
}

void readItem(LinkedList<movie>* movieList, LinkedList<dvd>* dvdList
                ,LinkedList<game>* gameList){
    ifstream inFile;
    inFile.open("items.txt", ios :: in);
    if (!inFile){
        cerr << "Cannot open file" << endl;
        return;
    }

    int a = 0;
    while(inFile.good()){
        string line;
        string genre = "";
        getline(inFile, line);
        if  (line.find("Record") != string::npos){
            movie movie ;
            getInput(&movie, line,&genre);
            movie . setGenre1(genre);
            movieList -> insert(a , movie);
        }
        if (line.find("DVD")!= string::npos){
            dvd dvd;
            getInput(&dvd,line,&genre);
            dvd.setGenre1(genre);
            dvdList -> insert(a, dvd);
        }
        if (line.find("Game")!= string::npos){
            game game;
            getInput(&game,line,&genre);
            gameList -> insert(a,game);
        }
        a++;
    }

//    Print movieList
    cout << " Movie list : " <<endl;
    for (int i = 0; i < movieList->size(); i++) {
        movieList->get(i).printItemWithGenre();
    }
    cout <<"\n Dvd list: " <<endl;
    for (int i = 0; i < movieList->size(); i++) {
        dvdList->get(i).printItemWithGenre();
    }
    cout <<"\n Game list: " <<endl;
    for (int i = 0; i < movieList->size(); i++) {
        gameList->get(i).printItem();
    }
}

void getInput(item *item, string line, string* genre){
    //Create a string with empty string to store data and check if it is empty
    string id = "",title = "",renatl_type = "",loan_type = "";

    //Store the substr of line after and before comma
    string tempt;

    int number_copies = 0;
    double rental_fee = 0;

    //Get the index and first index after a comma to proceed the substr

    int a = 0, first = 0;
    while (a < line.size()){
        //Once find the comma
        if (line[a] == ','){
            tempt = line.substr(first, a - first);
            first = a + 1;
            a++;
            if (id == ""){
                id = tempt;
                continue;
            }
            if (title == ""){
                title = tempt;
                continue;
            }
            if (renatl_type == ""){
                renatl_type = tempt;
                continue;
            }
            if (loan_type == ""){
                loan_type = tempt;
                continue;
            }
            if (number_copies == 0){
                number_copies += stoi(tempt);
                if (line.substr(a,line.size() - a).find(",") != string::npos){
                    continue;
                }
                else{
                    rental_fee += stod(line.substr(a,line.size() - a));
                    break;
                }
            }
            if (rental_fee == 0){
                rental_fee += stod(tempt);
                *genre = line.substr(a, line.size()-a);
                break;
            }
        }
        a++;
    }
    item->setAll(id,title,renatl_type,loan_type,number_copies,rental_fee);
}

void outputFile(LinkedList<movie>* movieList, LinkedList<dvd>* dvdList
        ,LinkedList<game>* gameList){
    ofstream outFile ("items.txt", ios :: out);
    for (int i = 0; i < movieList->size(); i++) {
        outFile << movieList->get(i).toString() <<endl;
        outFile << dvdList -> get(i).toString() << endl;
        outFile << gameList -> get(i).toString() << endl;
    }
    outFile.close();
}