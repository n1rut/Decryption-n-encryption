#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

void MorseDecode();								//Decryption with Morse cipher
void ShamirDecode();							//Decryption with Shamir cipher
void HillDecode(int);								//Decryption with Hila cipher

bool checkIfNotANumber(string);			//The function of checking whether the entered string is a number
int shamir(int, int, int);

void funkTypeName(int);					//The function of writing the principle of action (print in consol what type of encryption your choose)
void funkPrinciple(int);				//The function of writing the encryption type (print in consol what your do(encryption or decription))
