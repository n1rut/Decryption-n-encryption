#pragma once
#include <iostream>
#include <vector>

using namespace std;

int rasAlgEvkl(int, int);
void minorCreat(vector<vector<int>>&, vector<vector<int>>&, int, int);
int determCalk(vector<vector<int>>, int);
void initializeAlphabet(vector<char>& alf);
void codbyStr(string x, vector<int>& str, vector<char> alf);
void processMatrix(vector<vector<int>>& matrixStr, vector<int>& codByAlfStr, string& key);
string encryptMatrix(const vector<vector<int>>& matrixStr, const vector<vector<int>>& matrixKey, vector<char>& alf);
void generateKey(vector<char>& alf, vector<vector<int>>& matrixKey, string& someKey);
void processKeyMatrix(vector<vector<int>>& matrixKey, string& key, vector<char>& alf);
int calculateObrEl(int detMatrixKey, int x, vector<char>& alf);
void AlgDop(vector<vector<int>>& matrixKey, vector<vector<int>>& matrixAlgDop);
void processMatrixAlgDop(vector<vector<int>>& matrixAlgDop, vector<vector<int>>& matrixKey, vector<char>& alf, int obrEl);
void Transp(vector<vector<int>>& matrixAlgDop, vector<char>& alf, vector<vector<int>>& transpMatr);
string decryptString(vector<vector<int>>& matrixStr, vector<vector<int>>& transpMatr, vector<char>& alf);