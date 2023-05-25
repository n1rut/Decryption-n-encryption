#include "helpFunc.h"

//The function of checking whether the entered string is a number
bool checkIfNotANumber(string intInStr)
{
	if (intInStr == "")   //chek for empety string
	{
		return false;
	}
	for (int i = 0; intInStr[i] != '\0'; i++)  //chek for not a number
	{
		char askii = 0;
		for (int j = 48; j < 58; j++)
		{
			askii = j;
			if (intInStr[i] != askii && j == 57)
			{
				return false;
			}
			else if (intInStr[i] == askii)
			{
				break;
			}
		}
	}
	return true;
}

//8 byte unsigned int exponentiation function
uint64_t stepen(uint64_t x, int y)
{
	if (y == 0)
	{
		return 1;
	}
	uint64_t result = x;
	for (int i = 1; i < y; i++)
	{
		result = result * x;
	}
	return result;
}

//Greatest common divisor search function
uint64_t greatestCommonDivisor(uint64_t expon, uint64_t eiler)
{
	while (expon > 0)
	{
		uint64_t promeg;

		promeg = expon;
		expon = eiler % expon;
		eiler = promeg;
	}

	return eiler;
}
