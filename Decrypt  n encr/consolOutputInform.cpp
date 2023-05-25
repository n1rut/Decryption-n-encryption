#include "consolOutputInform.h"

//The function of writing the encryption type
void funkTypeName(int cryptoType)
{
	switch (Ciphers(cryptoType))
	{
	case Ciphers::Morse:
		cout << "Шифр Морзе" << endl;
		break;
	case Ciphers::Shamir:
		cout << "Шифр Шамира" << endl;
		break;
	case Ciphers::Hil:
		cout << "Шифр Хила" << endl;
		break;
	}
}

//The function of writing the principle of action
void funkPrinciple(int funkType)
{
	switch (Principle(funkType))
	{
	case Principle::Encription:
		cout << "Шифрование" << endl;
		break;
	case Principle::Decription:
		cout << "Расшифровка" << endl;
		break;
	}
}
