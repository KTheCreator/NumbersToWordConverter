#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;


vector<string> tokenise(string uInput);
bool validCommaPos(string x);
bool isNumber(string x);
int findDigit(vector<string>x);
int converter(char input);
string removeLeadingZeros(string uInput);
string formatPrinting(vector<string> input, int size);
vector<string> numberToWordsMachine(vector<string> input, int _noOfSets);
vector<string> getInputFromFile(string filename);
string removeCommas(string input);
int commasPresent(string input);
string numberToWordProcess(string input);

void runProgram();



