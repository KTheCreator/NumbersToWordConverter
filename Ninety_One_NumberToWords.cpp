// Ninety_One_NumberToWords.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <vector>
#include <iostream>
#include <cstring>
#include <unordered_map>
using namespace std;
vector<string> tokenise(string uInput) {
    if (uInput[uInput.size() - 1] != '.') uInput.push_back('.');

    string word = "";
    vector<string> tokens;
    for (auto& i : uInput) {
        if (i == ' ' || i == '.') { tokens.push_back(word); word = ""; }
        else word.push_back(i);
    }
    return tokens;
}
bool isNumber(string x) {
    for (int i = 0; i < x.length(); i++) {
        if (!isdigit(x[i])) return false;
    }
    return true;
}
int findDigit(vector<string> x) {
    int tempCounter = 0;
    int digitPos;
    string temp = "";
    for (int i = 0; i < x.size(); i++) {
        if (isNumber(x[i])) {
            tempCounter++;
            digitPos = i;
        }
        else
            continue;
    }
    if (tempCounter == 1) return digitPos;
    else return -1;
}
int converter(char input) {
    return (int)input - 48;
}
string removeLeadingZeros(string uInput) {
    string temp = uInput;
    int zeroCount = 0;
    //checking how many leading zeros there are
    for (int i = 0; i < temp.size(); i++) {
        if (temp[i] == '0')
            zeroCount++;
        else
            break;
    }
    temp.erase(0, zeroCount);
    return temp;
}

int main()
{
    
    string convertingDigit = "";
    string line = "The pump is 1111536 deep underground";
    //Step 1: Tokenise the input.
    vector<string>newInput = tokenise(line);
    /*for (int i = 0; i < newInput.size(); i++)
        cout << newInput[i] << endl;*/

    //Step 2: Find the digit in the sentence
    int final = findDigit(newInput);
    if (final > -1) {
        convertingDigit = newInput[final];
    }
    //Step 3: See if the number begins with 0 i.e. 000001 is 1;
    if (convertingDigit[0] == '0') {
        convertingDigit=removeLeadingZeros(convertingDigit);
    }
    else cout << "Too many" << endl;

    //Step 4: Place spaces inbetween the certain digits for tokenisation process i.e. 1115631 is 1 115 631
    int numberOfSubSets = 1;
    if (convertingDigit.length() > 3) {
        int digitRange = convertingDigit.length() + (convertingDigit.length() / 3);
        int spaceCounter = 1; int oldWordCon = convertingDigit.length() - 1;

        vector<char>test(digitRange);
        for (int i = digitRange - 1; i > -1; i--) {
            if (spaceCounter % 4 != 0) {
                test[i] = convertingDigit[oldWordCon];
                oldWordCon--;
            }
            else { test[i] = ' '; numberOfSubSets++; };

            spaceCounter++;

        }
        
        string s(test.begin(), test.end());
        convertingDigit = s;
       
        
    }
    cout << convertingDigit << endl;
    cout << numberOfSubSets;

    //Step 5: Tokenises the string into separate strings
    vector<string>numberInSets(numberOfSubSets);
    if (numberOfSubSets != 1) {
        
        numberInSets = tokenise(convertingDigit);
        for (auto& i : numberInSets)
            cout << i << endl;
    }
    else numberInSets[0] = convertingDigit;

    
    
    
    


    //Step 6: Create a map that has contains all the unique instances/combos of numbers.
    unordered_map<int, string>numberToWordMap = {
           {1,"One"},{2,"Two"},{3,"Three"},{4,"Four"},{5,"Five"},{6,"Six"},{7,"Seven"},{8,"Eight"},{9,"Nine"},{0,"and"},
           {10,"Ten"},{11,"Eleven"},{12,"Twelve"},{13,"Thirteen"},{14,"Fourteen"},{15,"Fifteen"},{16,"Sixteen"},{17,"Seventeen"},{18,"Eighteen"},{19,"Nineteen"},
           {20,"Twenty"},{30,"Thirty"},{40,"Forty"},{50,"Fifty"},{60,"Sixty"},{70,"Seventy"},{80,"Eighty"},{90,"Ninety"}

    };
    // Step 7: Uses the map to return a 2D vector of the numbers converted to words
    vector<vector<const char*>> ans(numberOfSubSets);
    //constructing the ans vector to have the same number of digits
    
    for (int i = 0; i < numberOfSubSets; i++) {
        if (numberInSets[i].size() == 3) {
            int hundreds = converter(numberInSets[i][0]); //Gets the 100s
            int tens = converter(numberInSets[i][1]);//Gets the 10s
            int units = converter(numberInSets[i][2]);//Gets the 1s
            ans[i].push_back(numberToWordMap.at(hundreds).c_str());
            if (tens != 0) {
                if (tens == 1) {
                    int newDigit = (tens * 10) + units;
                    ans[i].push_back(numberToWordMap.at(newDigit).c_str());
                }
                else {
                    ans[i].push_back(numberToWordMap.at(tens * 10).c_str());
                    ans[i].push_back(numberToWordMap.at(units).c_str());
                }

            }
            else { 
                if(units != 0)
                ans[i].push_back(numberToWordMap.at(units).c_str());
            }
        }
        else if (numberInSets[i].size() == 2) {
            int tens = converter(numberInSets[i][0]);//Gets the 10s
            int units = converter(numberInSets[i][1]);//Gets the 1s
            if (tens != 0) {
                if (tens == 1) {
                    int newDigit = (tens * 10) + units;
                    ans[i].push_back(numberToWordMap.at(newDigit).c_str());
                }
                else {
                    ans[i].push_back(numberToWordMap.at(tens * 10).c_str());
                    ans[i].push_back(numberToWordMap.at(units).c_str());
                }

            }
            else {
                
            }
        }
        else if (numberInSets[i].size() == 1) {
            int units = converter(numberInSets[i][0]);//Gets the 1s
            ans[i].push_back(numberToWordMap.at(units).c_str());
        }
    }
    
    for (int i = 0; i < numberOfSubSets; i++) {
        for (int j = 0; j < ans[i].size(); j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
}


