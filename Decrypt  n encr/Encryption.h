#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

void MorseCode();								//Encryption with Morse cipher
void ShamirCode();								//Encryption with Shamir cipher
void HillCode(int);								//Encryption with Hila cipher


bool checkIfNotANumber(string);					//The function of checking whether the entered string is a number
int shamir(int, int, int);

void funkTypeName(int);							//The function of writing the principle of action (print in consol what type of encryption your choose)
void funkPrinciple(int);						//The function of writing the 