#pragma once
#include <iostream>
#include <vector>

using namespace std;

int rasAlgEvkl(int, int);
void minorCreat(vector<vector<int>>&, vector<vector<int>>&, int, int);
int determCalk(vector<vector<int>>, int);
void initializeAlphabet(vector<char>& alf);
vector<int> generateKey(const vector<char>& alf);
vector<vector<int>> generateMatrixKey(const vector<int>& codByAlfKey);
vector<vector<int>> encryptString(const string& inputString, const vector<vector<int>>& matrixKey, const vector<char>& alf);