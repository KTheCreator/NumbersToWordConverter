// Ninety_One_NumberToWords.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<string> tokenise(string uInput) {
    /*
    * Purpose: Takes a given sequence, separates the sequence into a vector and returns
    */
    if (uInput[uInput.size() - 1] != '.') uInput.push_back('.');//Ensures that the last word is included by adding a full stop if needs be.

    string word = "";
    vector<string> tokens;
    //Iterates through the characters and pushes them into a string stack. The space or fullstop indicates the end of the word. The process is repeated till the end.
    for (auto& i : uInput) {
        if (i == ' ' || i == '.') { tokens.push_back(word); word = ""; }
        else word.push_back(i);
    }
    return tokens;
}
bool validCommaPos(string x) {
    /*
    * Purpose:Checks if the user has placed the commas in the correct place
    * i.e. 1,234 is valid but 12,34 is not valid
    */
    int commaPosCheck = 1;
    for (int i = x.length() - 1; i > -1; i--) {
        if (commaPosCheck % 4 == 0) {
            if (x[i] != ',') return false;
        }
        else if (x[i] == ',') return false;
        commaPosCheck++;
    }
    return true;
}
bool isNumber(string x) {
    /*
    * Purpose: Checks if the given string is a number.
    */
    for (int i = 0; i < x.length(); i++) {
        if (x[i] == ',') continue;//Allows for commas to be present in the string and classes it as a number
        else if (!isdigit(x[i])) return false;
    }
    return true;
}
int findDigit(vector<string> x) {
    /*
    * Purpose: Finds the set of digits in the vector of strings.
    * If no number is present, will return failed state
    * If more than one number is present, will return failed state.
    * If one is present, will return the number that was found.
    */
    int tempCounter = 0;
    int digitPos;
    string temp = "";
    bool found = false;
    for (int i = 0; i < x.size(); i++) {
        if (isNumber(x[i])) {
            tempCounter++;
            digitPos = i;
            found = true;
        }
        else
            continue;
    }
    if (found) {
        if (tempCounter == 1) return digitPos;
        else return -2;
    }
    else return -1;

}
int converter(char input) {
    //Purpose: A function that will return the numeric value of the given character from ASCII to numerical.
    return (int)input - 48;
}
string removeLeadingZeros(string uInput) {
    /*
    * Purpose: Removes any proceeding 0 from the number
    * i.e. 000111 would be 111
    */
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
        if (input[1] == "$")stemplate = input[0] + " thousand";
        else stemplate = input[0] + " thousand, " + input[1];

    }
    else if (size == 3) {
        if (input[1] == "$" && input[2] == "$") stemplate = input[0] + "million";
        else if (input[1] == "$")
            stemplate = input[0] + " million and " + input[2];
        else if (input[2] == "$")
            stemplate = input[0] + " million and " + input[1] + " thousand";
        else
            stemplate = input[0] + "million, " + input[1] + " thousand, " + input[2];

    }
    else if (size == 4) {
        if (input[1] == "$" && input[2] == "$" && input[3] == "$") stemplate = input[0] + " billion";
        else if (input[1] == "$") {
            if (input[2] == "$")
                stemplate = input[0] + " billion and " + input[3];
            else if (input[3] == "$")
                stemplate = input[0] + " billion and" + input[2] + " thousand";
            else stemplate = input[0] + " billion, " + input[2] + "thousand and " + input[3];
        }
        else if (input[2] == "$") {
            if (input[3] == "$") {
                stemplate = input[0] + " billion and " + input[1] + " million";
            }
            else stemplate = input[0] + " billion, " + input[1] + " million and" + input[3];
        }
        else if (input[3] == "$") {
            stemplate = input[0] + " billion, " + input[1] + " million and " + input[2];
        }
        else stemplate = input[0] + " billion, " + input[1] + " million, " + input[2] + " thousand and " + input[3];
    }
    else if (size == 5) {
        if (input[1] == "$" && input[2] == "$" && input[3] == "$" && input[4] == "$") stemplate = input[0] + " trillion";
        else if (input[1] == "$") {
            if (input[2] == "$" && input[3] == "$") stemplate = input[0] + " trillion and " + input[4];
            else if (input[4] == "$") stemplate = input[0] + " trillion, " + input[2] + " million and " + input[3] + "thousand";
            else if (input[3] == "$") stemplate = input[0] + " trillion, " + input[2] + " million and " + input[4];
            else if (input[2] == "$") stemplate = input[0] + " trillion, " + input[3] + " thousand and " + input[4];
            else stemplate = input[0] + " trillion, " + input[2] + " million, " + input[3] + "thousand and " + input[4];

        }
        else if (input[2] == "$") {
            if (input[3] == "$" && input[4] == "$") stemplate = input[0] + " trillion and " + input[1] + " billion";
            else if (input[4] == "$")stemplate = input[0] + " trillion, " + input[1] + " billion and " + input[3] + " thosuand";
            else if (input[3] == "$")stemplate = input[0] + " trillion, " + input[1] + " billion and " + input[4];
            else stemplate = input[0] + " trillion, " + input[1] + " billion, " + input[3] + " thousand and " + input[4];
        }
        else if (input[3] == "$") {
            if (input[4] == "$") stemplate = input[0] + " trillion, " + input[1] + " billion and " + input[2] + "million";
            else stemplate = input[0] + " trillion, " + input[1] + " billion, " + input[2] + " million and " + input[4];
        }
        else if (input[4] == "$")stemplate = input[0] + " trillion, " + input[1] + " billion, " + input[2] + " million and " + input[3] + " thousand";
        else stemplate = input[0] + " trillion, " + input[1] + " billion, " + input[2] + " million, " + input[3] + " thousand and " + input[4];
    }

    return stemplate;
}
vector<string> numberToWordsMachine(vector<string> input, int _noOfSets) {
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

                        temp[i] += numberToWordMap.at(tens * 10) + "-" + numberToWordMap.at(units);


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

                    temp[i] += numberToWordMap.at(tens * 10) + "-" + numberToWordMap.at(units);
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
vector<string> getInputFromFile(string filename) {
    vector<string> testStr;
    ifstream file(filename);
    string content;
    while (getline(file, content)) {
        testStr.push_back(content);
    }
    return testStr;
}
string removeCommas(string input) {
    string temp = input;
    temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
    return temp;
}
int commasPresent(string input) {
    for (auto& i : input) {
        if (i == ',') {
            if (validCommaPos(input))return 1;
            else return -2;
        }

    }
    return -1;
}
string numberToWordProcess(string input) {
    if (input != "") {

        string convertingDigit = "";
        string line = input;
        //Step 1: Tokenise the input.
        vector<string>newInput = tokenise(line);

        //Step 2: Find the digit in the sentence
        int final = findDigit(newInput);
        if (final > -1) {
            convertingDigit = newInput[final];
        }
        else {
            if (final == -1) return "Invalid Input! No Digit Detected!\n";
            else return "Invalid Input! Multiple Digits Detected!\n";
        }
        //Step 3: See if the number begins with 0 i.e. 000001 is 1;
        if (convertingDigit[0] == '0') {
            convertingDigit = removeLeadingZeros(convertingDigit);
        }
        int cPRESENT = commasPresent(convertingDigit);
        if (cPRESENT == 1) {
            convertingDigit = removeCommas(convertingDigit);
        }
        else if (cPRESENT == -2) {
            return "Invalid Input! Commas placed in the wrong place!";
        }

        //Step 4: Place spaces inbetween the certain digits for tokenisation process i.e. 1115631 is 1 115 631
        int numberOfSubSets = 1;
        if (convertingDigit.length() > 3) {
            int digitRange;
            if (convertingDigit.length() % 3 != 0) {
                digitRange = convertingDigit.length() + (convertingDigit.length() / 3);
            }
            else
                digitRange = convertingDigit.length() + (convertingDigit.length() / 3) - 1;
            int spaceCounter = 1; int oldWordCon = convertingDigit.length() - 1;

            vector<char>test(digitRange);
            for (int i = digitRange - 1; i > -1; i--) {
                if (spaceCounter % 4 != 0) {
                    test[i] = convertingDigit[oldWordCon];
                    oldWordCon--;

                }
                else {
                    test[i] = ' ';
                    numberOfSubSets++;
                }

                spaceCounter++;

            }

            string s(test.begin(), test.end());
            convertingDigit = s;


        }


        //Step 5: Tokenises the string into separate strings
        vector<string>numberInSets(numberOfSubSets);
        if (numberOfSubSets != 1) {

            numberInSets = tokenise(convertingDigit);

        }
        else numberInSets[0] = convertingDigit;



        vector<string> ans(numberOfSubSets);
        //constructing the ans vector to have the same number of digits
        ans = numberToWordsMachine(numberInSets, numberOfSubSets);

        string finalStr = formatPrinting(ans, numberOfSubSets);

        return finalStr + "\n";
    }
    else
        return "Invalid Input: No Sentence Detected\n";

}
int main()
{

    bool running = true;
    while (running) {
        int userType;
        cout << "Main Menu:\n  (1)Using your own sentence/input\n  (2)Import sentences from a text file\n Which One? ";
        cin >> userType;
        if (userType == 1) {//Own input
            string userInput;
            cout << "Enter your sentence: ";
            cin >> userInput;
            cout << numberToWordProcess(userInput);
            running = false;
        }
        else if (userType == 2) {//Text file input
            string userFilename;
            cout << "Enter Filename: " << endl;
            cin >> userFilename;
            vector<string>inputFromFile = getInputFromFile(userFilename);
            for (auto& i : inputFromFile) {
                cout << "Current Sentence being processed: " << i << endl;
                cout << "Converted Number Answer: " << numberToWordProcess(i) << endl;
            }
            running = false;
        }
        else cout << "Invalid Response: Please Try Again!" << endl;

        string userAnswer;
        while (true) {
            cout << "Want To Try Again?(Y/y for Yes, N/n for No): ";
            cin >> userAnswer;
            if (userAnswer == "N" || userAnswer == "n") {

                cout << "Closing Application GoodBye!" << endl;
                return 0;
            }
            else if (userAnswer == "Y" || userAnswer == "y") {
                cout << "Loading up Again...\n********************************************" << endl;
                running = true;
                break;
            }
            else cout << "Invalid Response! Please Try again" << endl;
        }

    }



}


