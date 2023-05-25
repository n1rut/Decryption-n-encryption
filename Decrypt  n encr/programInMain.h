#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define PASSWORD "222"

using namespace std;

enum Ciphers
{
	Morse = 1,
	Shamir,
	Hill
};

enum Principle
{
	Encription = 1,
	Decription
};

void passwordCheck();					//Password verification function

void inputStrToTxt();					//Entering a string and saving it to a file or copying and encrypting your file

int principleOfOperation();				//Choosing the principle of operation (encription or decryption)
int cryptoTypeSelect(int);				//Encryption type select (Gronsfeld, RSA etc.)

void encryptionStart(int, int);			//Conditions for performing encryption for the selected type and principle of operation
void encryptionCheck(int, int);			//The function of starting the encryption check

void funkPrinciple(int);				//The function of writing the encryption type (print in consol what your do(encryption or decription))


void ShamirKeygen(int);					//Key generation function for Shamir encryption
