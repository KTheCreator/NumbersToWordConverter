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
string formatPrinting(vector<string> input, int size) {
    string stemplate;
    if (size == 1) {
        return input[0];
    }
    else if (size == 2) {
        stemplate = input[0] + " thousand, " + input[1];
    }
    else if (size == 3) {
        if (input[1] == "$")
            stemplate = input[0] + " million and " + input[2];
        else if (input[2] == "$")
            stemplate = input[0] + "million and " + input[1] + "thousand";
        
    }
        
    return stemplate;
}
vector<string> numberToWordsMachine(vector<string> input,int _noOfSets) {
    unordered_map<int, string>numberToWordMap = {
          {1,"One"},{2,"Two"},{3,"Three"},{4,"Four"},{5,"Five"},{6,"Six"},{7,"Seven"},{8,"Eight"},{9,"Nine"},{0,"and"},
          {10,"Ten"},{11,"Eleven"},{12,"Twelve"},{13,"Thirteen"},{14,"Fourteen"},{15,"Fifteen"},{16,"Sixteen"},{17,"Seventeen"},{18,"Eighteen"},{19,"Nineteen"},
          {20,"Twenty"},{30,"Thirty"},{40,"Forty"},{50,"Fifty"},{60,"Sixty"},{70,"Seventy"},{80,"Eighty"},{90,"Ninety"}

    };
    vector<string>temp(_noOfSets);
    for (int i = 0; i < _noOfSets; i++) {
        
        if (input[i].size() == 3) {
            if (input[i][0] == '0') {
                if (input[i][1] == '0' && input[i][2] == '0') {

                    temp[i] += "$";
                    continue;
                }

            }
            int hundreds = converter(input[i][0]); //Gets the 100s
            int tens = converter(input[i][1]);//Gets the 10s
            int units = converter(input[i][2]);//Gets the 1s

            temp[i] += numberToWordMap.at(hundreds) + " hundred";
            if (tens == 0 && units == 0) continue;
            else {

                temp[i] += " and ";
                if (tens != 0) {
                    if (tens == 1) {
                        int newDigit = (tens * 10) + units;

                        temp[i] += numberToWordMap.at(newDigit);
                    }
                    else {

                        temp[i] += numberToWordMap.at(tens * 10) + numberToWordMap.at(units);;


                    }

                }
                else {
                    if (units != 0)
                        temp[i] += numberToWordMap.at(units);


                }
            }


        }
        else if (input[i].size() == 2) {
            int tens = converter(input[i][0]);//Gets the 10s
            int units = converter(input[i][1]);//Gets the 1s
            if (tens != 0) {
                if (tens == 1) {
                    int newDigit = (tens * 10) + units;

                    temp[i] += numberToWordMap.at(newDigit);
                }
                else {

                    temp[i] += numberToWordMap.at(tens * 10) + numberToWordMap.at(units);
                }

            }

        }
        else if (input[i].size() == 1) {
            int units = converter(input[i][0]);//Gets the 1s

            temp[i] += numberToWordMap.at(units);
        }
    }
    return temp;
}

int main()
{
    
    string convertingDigit = "";
    string line = "The pump is 1000536 deep underground";
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
   
    // Step 7: Uses the map to return a 2D vector of the numbers converted to words
    
    vector<string> ans(numberOfSubSets);
    //constructing the ans vector to have the same number of digits
    ans = numberToWordsMachine(numberInSets, numberOfSubSets);
    

    string finalOut = formatPrinting(ans, numberOfSubSets);
    cout << finalOut << endl;
    

    
    
}


