#pragma once
#include <iostream>
#include <cstdint>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void ShamirKeygen(int);										//Key generation function for Shamir encryption
int shamir(int, int, int);									//
int gcd(int, int);											//
int Extendedgcd(int, int, int&, int&);						//
bool simplenumberFerma(long long);							//
