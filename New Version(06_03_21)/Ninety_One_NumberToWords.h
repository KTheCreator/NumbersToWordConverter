#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <math.h>
using namespace std;
unordered_map<int, string>numberToWordMap = {
          {1,"One"},{2,"Two"},{3,"Three"},{4,"Four"},{5,"Five"},{6,"Six"},{7,"Seven"},{8,"Eight"},{9,"Nine"},{0,"and"},
          {10,"Ten"},{11,"Eleven"},{12,"Twelve"},{13,"Thirteen"},{14,"Fourteen"},{15,"Fifteen"},{16,"Sixteen"},{17,"Seventeen"},{18,"Eighteen"},{19,"Nineteen"},
          {20,"Twenty"},{30,"Thirty"},{40,"Forty"},{50,"Fifty"},{60,"Sixty"},{70,"Seventy"},{80,"Eighty"},{90,"Ninety"}

};
bool isNegative = false;
vector<string> tokenise(string uInput);
bool validCommaPos(string x);
bool isNumber(string x);
int findDigit(vector<string> x);
int converter(char input);
string removeLeadingZeros(string uInput);
string formatPrinting(vector<string> input, int size);
vector<string> getInputFromFile(string filename);
string removeCommas(string input);
int commasPresent(string input);
string wholeProcess(string input);
string processForThrees(char first, char second, char third);
vector<string> numberToWordsConverter(string input, int _noOfSets);
