#pragma once
#include <iostream>

using namespace std;

enum Ciphers
{
	Morse = 1,
	Shamir,
	Hil
};

enum Principle
{
	Encription = 1,
	Decription
};

void funkTypeName(int);					//The function of writing the encryption type (print in consol what your do(encryption or decription))
void funkPrinciple(int);				//The function of writing the principle of action (print in consol what type of encryption your choose)
