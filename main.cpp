#include <iostream>
#include <fstream>
#include "item.cpp"
#include "string.h"
#include "LinkedList.cpp"
using namespace std;

void getInput(item *item, string line){
    string id = "",title = "",renatl_type = "",loan_type = "",genre = "";
    string subStr;
    int number_copies = 0;
    double rental_fee = 0;
    int a = 0;
    int first = 0;
    while (a < line.size()){
        if (line[a] == ','){
            subStr = line.substr(first,a-first);
            first = a + 1;
            a++;
            if (id == ""){
                id = subStr;
                continue;
            }
            if (title == ""){
                title = subStr;
                continue;
            }
            if (renatl_type == ""){
                renatl_type = subStr;
                continue;
            }
            if (loan_type == ""){
                loan_type = subStr;
                continue;
            }
            if (number_copies == 0){
                number_copies += stoi(subStr);
                if (line.substr(a + 1,line.size() - (a+1)).find(',') == 1 ){
                    cout << "genre";
                    continue;
                }
                else
                    rental_fee += stod(line.substr(a,line.size() - a));
            }
            if (rental_fee == 0){
                rental_fee += stod(subStr);
                continue;
            }
        }
        a++;
    }
    item->setAll(id,title,renatl_type,loan_type,number_copies,rental_fee);
}
int main() {
    ifstream inFile;
    inFile.open("items.txt", ios :: in);
    if (!inFile){
        cerr << "Cannot open file" << endl;
        return 0;
    }

    int a = 0;
    auto *movieList = new LinkedList<movie>();
    auto *dvdList = new LinkedList<dvd>();
    auto *gameList = new LinkedList<game>();
    while(inFile.good()){
        string line;
        getline(inFile, line);
        if  (line.find("Record") != string::npos){
            movie movie ;
            getInput(&movie, line);
            movieList -> insert(a , movie);
        }
        if (line.find("DVD")!= string::npos){
            dvd dvd;
            getInput(&dvd,line);
            dvdList -> insert(a, dvd);
        }
    }

//    Print movieList
    cout << " Movie list : " <<endl;
    for (int i = 0; i < movieList->size(); i++) {
        movieList->get(i).printItem();
    }
    cout <<"\n Dvd list: " <<endl;
    for (int i = 0; i < movieList->size(); i++) {
        dvdList->get(i).printItem();
    }
    return 0;
}