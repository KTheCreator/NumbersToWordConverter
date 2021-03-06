// Ninety_One_NumberToWords.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Ninety_One_NumberToWords.h"
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
            stemplate = input[0] + "million, " + input[1] + " thousand and " + input[2];

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
            else stemplate = input[0] + " billion, " + input[1] + " million and " + input[3];
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
string wholeProcess(string input) {
    if (input != "") {

        string convertingDigit = "";
        string line = input;
        //Check if it is negative
        

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
        
        //Removes any leading zeros i.e. 0001 becomes 1.
        if (convertingDigit[0] == '0') {
            convertingDigit = removeLeadingZeros(convertingDigit);
        }

        //Checks if the digit has any commas in the format. And Removes them before they are processed.
        int cPRESENT = commasPresent(convertingDigit);
        if (cPRESENT == 1) {
            convertingDigit = removeCommas(convertingDigit);
        }
        else if (cPRESENT == -2) {
            return "Invalid Input! Commas placed in the wrong place!";
        }
        //Limits the number to only 15 digits max or into the trillion range.
        if (convertingDigit.length() > 15) return "Invalid Number! Digit is out of Range!";

        //Place spaces inbetween the certain digits for tokenisation process i.e. 1115631 is 1 115 631
        int numberOfSubSets = 1;
        if (convertingDigit.length() > 3) {
            numberOfSubSets = ceil((float)convertingDigit.length() / (float)3);
           
        }

        vector<string> ans(numberOfSubSets);
        //constructing the ans vector to have the same number of digits
        ans = numberToWordsConverter(convertingDigit, numberOfSubSets);

        string finalStr = formatPrinting(ans, numberOfSubSets);

        return finalStr + "\n";
    }
    else
        return "Invalid Input: No Sentence Detected\n";

}
string processForThrees(char first, char second , char third) {
    
    string strTemp = "";
    if (first == '0' && second == '0' && third == '0') {
        return strTemp = "$";
    }
    else {
        int hundreds = converter(first); //Gets the 100s
        int tens = converter(second);//Gets the 10s
        int units = converter(third);//Gets the 1s

        if (hundreds == 0) {
            if (tens == 0) {
                strTemp += numberToWordMap.at(units);
            }
            else if (units == 0) strTemp += numberToWordMap.at(tens * 10);
            else {
                if (tens == 1) {
                    int newDigit = (tens * 10) + units;
                    strTemp += numberToWordMap.at(newDigit);
                }
                else {
                    strTemp += numberToWordMap.at(tens * 10) + "-" + numberToWordMap.at(units);
                }
            }
        }
        else if (tens == 0) {
            if (units == 0) strTemp += numberToWordMap.at(hundreds) + " hundred";
            else strTemp += numberToWordMap.at(hundreds) + " hundred and  " + numberToWordMap.at(units);
        }
        else if (units == 0) numberToWordMap.at(hundreds) + " hundred and " + numberToWordMap.at(tens * 10);
        else {
            if (tens == 1) {
                int newDigit = (tens * 10) + units;
                strTemp += numberToWordMap.at(hundreds) + " hundred and " + numberToWordMap.at(newDigit);
            }
            else {
                strTemp += numberToWordMap.at(hundreds) + " hundred and " + numberToWordMap.at(tens * 10) + "-" + numberToWordMap.at(units);
            }

        }
        return strTemp;
    }

}
vector<string>numberToWordsConverter(string input,int _noOfSets) {
    vector<string>temp(_noOfSets);
    
    int startingNum = input.length() % 3;
    if (startingNum == 2) {//if there are only 2 numbers ahead i.e. 10,000
        int tens = converter(input[0]);//Gets the 10s
        int units = converter(input[1]);//Gets the 1s
        if (tens == 1) {
            int newDigit = (tens * 10) + units;
            temp[0] += numberToWordMap.at(newDigit);
        }
        else {
            temp[0] += numberToWordMap.at(tens * 10) + "-" + numberToWordMap.at(units);
        }
        for (int i = 1; i < _noOfSets; i++) {
            for (int j = startingNum; j < input.length(); j += 3) {
                temp[i] += processForThrees(input[j],input[j+1],input[j+2]);
            }
        }
    }
    else if (startingNum == 1) {
        int units = converter(input[0]);//Gets the 1s
        temp[0] += numberToWordMap.at(units);
        for (int i = 1; i < _noOfSets; i++) {
            for (int j = startingNum; j < input.length(); j += 3) {
                temp[i] += processForThrees(input[j], input[j + 1], input[j + 2]);
            }
        }
    }
    else {
        for (int i = 0; i < _noOfSets; i++) {
            for (int j = startingNum; j < input.length(); j += 3) {
                temp[i] += processForThrees(input[j], input[j + 1], input[j + 2]);
            }
        }
    }
    return temp;
}
void runProgram() {
    bool running = true;
    while (running) {
        int userType;
        cout << "Main Menu:\n  (1)Using your own sentence/input\n  (2)Import sentences from a text file\n Which One? ";
        cin >> userType; cin.get();
        if (userType == 1) {//Own input
            string userInput;

            cout << "Enter your sentence: ";

            getline(cin, userInput);
            cout << wholeProcess(userInput);

            running = false;
        }
        else if (userType == 2) {//Text file input
            string userFilename;
            cout << "Enter The Path To The TextFile: " << endl;
            cin >> userFilename;
            vector<string>inputFromFile = getInputFromFile(userFilename);
            for (auto& i : inputFromFile) {
                cout << "Current Sentence being processed: " << i << endl;
                cout << "Converted Number Answer: " << wholeProcess(i) << endl;
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
                return;
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
int main() {
    runProgram();
}



