//Draft 6, Date 06/21/2024
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string>
#include <sstream>
#include <array>
#include <cctype>
#include <string>

using namespace std;

void lineDelete(ifstream&, string);
void countRows(ifstream&, string, int&);
void variableAssigner(string, string&, string&, int&, int&, int&, int&, int&);
void isValid(string[], int, int&);
void sortSelection(string[], int);
int tickerFinder(string[], int, string);

int main(){
    ifstream revenue;
    string fileName;

    cout << "Enter name of file to open (make sure the file is a .csv file): \n";
    cin >> fileName;
    fileName.append(".csv");
    cout << endl;
    
    revenue.open(fileName);
    
    if(!revenue){
        cout << "File failed to open.\n";
    }
    
    else{
        string line;
        int rows;
        int countP;
        int countF;

        lineDelete(revenue, line);
        countRows(revenue, line, rows);
        
        string passTest[rows];
        string failTest[rows];
        for(int x = 0; x < rows; ++x){
            passTest[x] = "";
            failTest[x] = "";
        }
        
        revenue.clear();
        revenue.seekg(0);
        lineDelete(revenue, line);
        
        int i = 0;
        int j = 0;
        
        while(getline(revenue, line)){
            string ticker;
            string temporary;
            int firstYear;
            int secYear;
            int thirdYear;
            int fourthYear;
            int fifthYear;
            
            variableAssigner
            (line,ticker,temporary,firstYear,secYear,thirdYear,fourthYear,fifthYear);
            
            if(firstYear > secYear && secYear > thirdYear && thirdYear > fourthYear && fourthYear > fifthYear){
                passTest[i] = ticker;
                ++i;
            }
            else{
                failTest[j] = ticker;
                ++j;
            }
        }
        revenue.close();
        
        isValid(passTest, rows, countP);
        sortSelection(passTest, countP);
        isValid(failTest, rows, countF);
        sortSelection(failTest, countF);
        
        cout << "Companies that passed the test: " << endl;
        for(int i = 0; i < countP; ++i){
            cout << i + 1 << "." << passTest[i] << endl;
        }
        cout << "\nCompanies that failed the test: " << endl;
        for(int i = 0; i < countF; ++i){
            cout << i + 1 << "." << failTest[i] << endl;
        }
        cout << endl;
        
        while(true){
            string searchVal;
            cout << "Search for ticker, type q to end the program: ";
            cin >> searchVal;
            transform(searchVal.begin(), searchVal.end(), searchVal.begin(), ::toupper);
            int passValIndex = tickerFinder(passTest, countP, searchVal);
            int failValIndex = tickerFinder(failTest, countF, searchVal);
            
            if(searchVal == "Q"){
                break;
            }
            else if(passValIndex == -1){
                if(failValIndex != -1){
                    failValIndex += 1;
                    cout << searchVal << " is located at position " << failValIndex 
                    << " in the FAIL list." << endl;
                }
                else{
                    cout << "Company is not in either list." << endl;
                }
            }
            else{
                passValIndex += 1;
                cout << searchVal << " is located at position " << passValIndex
                << " in the PASS list." << endl;
            }
        }
    }
}

//Functions:

void lineDelete(ifstream& revenue, string line){
    getline(revenue, line);
}

void countRows(ifstream& revenue, string line, int& numOfRows){
    while(getline(revenue, line)){
        numOfRows++;
    }
}

void variableAssigner(string line, string& tkr, string& temp, int& y1, int& y2, int& y3, int& y4, int& y5){
    
    istringstream iss(line);
    
    getline(iss, tkr, ',');
    getline(iss, temp, ',');
    y1 = atoi(temp.c_str());
    getline(iss, temp, ',');
    y2 = atoi(temp.c_str());
    getline(iss, temp, ',');
    y3 = atoi(temp.c_str());
    getline(iss, temp, ',');
    y4 = atoi(temp.c_str());
    getline(iss, temp, ',');
    y5 = atoi(temp.c_str());
}

void isValid(string array[], int rows, int& count){
    count = 0;
    for(int i = 0; i < rows; i++){
        if(array[i] != ""){
            count++;
        }
    }
}

void sortSelection(string array[], int count){
    int i, j, smallest;
    for(i = 0; i < count - 1; ++i){
        smallest = i;
        for(j = i + 1; j < count; ++j){
            if(array[smallest] > array[j]){
                smallest = j;
            }
        }
        if(smallest != i){
            swap(array[i], array[smallest]);
        }
    }
}

int tickerFinder(string array[], int count, string searchVal){
    int low, mid, high;
    low = 0;
    high = count - 1;
    
    while(high >= low){
        mid = (high + low) / 2;
        
        if(array[mid] < searchVal){
            low = mid + 1;
        }
        else if(array[mid] > searchVal){
            high = mid - 1;
        }
        else{
            return mid;
        }
    }
    return -1;
}
