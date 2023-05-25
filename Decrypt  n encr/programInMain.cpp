#include "programInMain.h"
#include "Encryption.h"
#include "Decryption.h"

//Password verification function
void passwordCheck()
{
	string password = "";
	cout << "Введите пароль:" << endl;
	getline(cin, password);
	while (password != PASSWORD)
	{
		system("CLS");
		cout << "Неверный пароль!" << endl << "Попробуйте снова." << endl << ": ";
		getline(cin, password);
	}
	system("CLS");
	cout << "Авторизация успешна!" << endl;;
	Sleep(500);
	system("CLS");
}

//Entering a string and saving it to a file or copying and encrypting your file
void inputStrToTxt()
{
	string fileCreate = "";
	bool isGood = false;
	do
	{
		try
		{
			cout << "Вы хотите зашифровать свой файл, создать новый или взять подготовленный?" << endl << "1)Ваш файл" << endl << "2)Создать новый" << endl << "3)Взять подготовленный" << endl << ": ";
			getline(cin, fileCreate);
			if (fileCreate == "")
			{
				throw runtime_error("Введена пустая строка.\nПопробуйте снова.\n");
			}
			if (fileCreate != "1" && fileCreate != "2" && fileCreate != "3")
			{
				string err;
				err = "Неверный ввод.\nВы ввели \"" + fileCreate + "\", когда ожидалось \"1\" или \"2\" или \"3\".\nПопробуйте снова.\n";
				throw runtime_error(err);
			}
			isGood = true;
		}
		catch (const std::exception& error)
		{
			system("CLS");
			cerr << error.what();
		}
	} while (isGood == false);
	system("CLS");
	if (fileCreate == "1")
	{
		ofstream fin("Some_text.txt");
		ifstream fout;
		isGood = false;
		string path = "";
		do
		{
			cout << "Введите путь к файлу (помните, что файл должен быть в кодировке ANSI или Windows-1251)" << endl << ": ";
			getline(cin, path);
			try
			{
				fout.open(path);
				if (!fout.is_open())
				{
					throw runtime_error("Неизвестный путь к файлу.\nПопробуйте снова.\n");
				}
				string bufer = "";
				while (!fout.eof())
				{
					getline(fout, bufer);
					if (bufer == "")
					{
						throw runtime_error("Файл пуст.\nПопробуйте снова.\n");
					}
					for (int i = 0; i < bufer.length(); i++)
					{
						if ((int)bufer[i] < 32 || (int)bufer[i] > 126)
						{
							throw runtime_error("В тексте есть исключенные символы.\nОжидаются символы латинского алфавита знаки препинания и специальные символы.\nПопробуйте снова.\n");
						}
					}
					fin << bufer;
					if (!fout.eof())
					{
						fin << endl;
					}
				}
				isGood = true;
			}
			catch (const exception& error)
			{
				system("CLS");
				cerr << error.what();
			}
		} while (isGood == false);
		fin.close();
		fout.close();
		system("CLS");
	}
	else if (fileCreate == "2")
	{
		isGood = false;
		string inputStr = "";
		do
		{
			cout << "Введите строку для шифрования" << endl << ": ";
			try
			{
				getline(cin, inputStr);
				if (inputStr == "")
				{
					throw runtime_error("Был введен пустой текст.\nПопробуйте снова.\n");
				}
				for (int i = 0; i < inputStr.length(); i++)
				{
					if ((int)inputStr[i] < 32 || (int)inputStr[i] > 126)
					{
						throw runtime_error("В тексте есть исключенные символы.\nОжидаются символы латинского алфавита знаки препинания и специальные символы.\nПопробуйте снова.\n");
					}
				}
				isGood = true;
			}
			catch (const exception& error)
			{
				system("CLS");
				cerr << error.what();
			}
		} while (isGood == false);
		ofstream fin("Some_text.txt");
		fin << inputStr;
		fin.close();
		system("CLS");
	}
	else if (fileCreate == "3")
	{
		srand(time(NULL));
		ifstream fin("RandSkaz.txt");
		string randStr;
		string fileContent;
		while (getline(fin, randStr))
		{
			fileContent += randStr + "\n";
		}
		fin.close();

		ofstream fout("Some_text.txt");
		fout << fileContent;
		fout.close();
	}
	system("notepad Some_text.txt");
}

//Choosing the principle of operation
int principleOfOperation()
{
	string strNumPrinciple = "";
	bool isGood = false;
	do
	{
		//Protection against incorrectly entered operating principle
		cout << "Выберите принцип работы: " << endl << "1)Шифрование" << endl << "2)Расшифровка" << endl << ": ";
		try
		{
			getline(cin, strNumPrinciple);
			if (strNumPrinciple == "")
			{
				throw runtime_error("Была введена пустая строка.\nПопробуйте снова.\n");
			}
			if (strNumPrinciple != "1" && strNumPrinciple != "2")
			{
				string err;
				err = "Недопустимый ввод.\nВы ввели \"" + strNumPrinciple + "\", когда ожидалось \"1\" или \"2\".\nПопробуйте снова.\n";
				throw runtime_error(err);
			}
			isGood = true;
		}
		catch (const exception& error)
		{
			system("CLS");
			cerr << error.what();
		}
	} while (isGood == false);

	int intNumPrinciple = strNumPrinciple[0] - 48;

	system("CLS");
	return intNumPrinciple;
}

//Encryption type select
int cryptoTypeSelect(int funkType)
{
	funkPrinciple(funkType);
	string strNumType = "";
	bool isGood = false;
	do
	{
		try //Protection against an incorrectly entered encryption type
		{
			cout << "Выберите тип шифрования/дешифрования: " << endl << "1)Шифр Морзе" << endl << "2)Шифр Шамира" << endl << "3)Шифр Хилла"
				<< endl << ": ";
			getline(cin, strNumType);
			if (strNumType == "")
			{
				throw runtime_error("Введена пустая строка.\nПопробуйте снова.\n");
			}
			if (strNumType != "1" && strNumType != "2" && strNumType != "3")
			{
				string err;
				err = "Недопустимый ввод.\nВы ввели \"" + strNumType + "\", когда ожидалось \"1\" или \"2\" или \"3\".\nПопробуйте снова.\n";
				throw runtime_error(err);
			}
			isGood = true;
		}
		catch (const exception& error)
		{
			system("CLS");
			cerr << error.what();
		}
	} while (isGood == false);

	int intNumType = 0;
	for (int i = 0; strNumType[i] != '\0'; i++)
	{
		intNumType = (intNumType * 10) + (strNumType[i] - 48);
	}

	system("CLS");
	return intNumType;
}

//Conditions for performing encryption for the selected type and principle of operation
void encryptionStart(int cryptoType, int funkType)
{
	switch (Ciphers(cryptoType))
	{
	case Ciphers::Morse:
		switch (Principle(funkType))
		{
		case Principle::Encription:
			MorseCode();
			break;
		case Principle::Decription:
			MorseDecode();
			break;
		}
		break;
	case Ciphers::Shamir:
		switch (Principle(funkType))
		{
		case Principle::Encription:
			ShamirKeygen(0);
			ShamirCode();
			break;
		case Principle::Decription:
			ShamirKeygen(1);
			ShamirDecode();
			break;
		}
		break;
	case Ciphers::Hill:
		switch (Principle(funkType))
		{
		case Principle::Encription:
			HillCode(0);
			break;
		case Principle::Decription:
			HillDecode(0);
			break;
		}
		break;
	}
	system("notepad Str_aft_proc.txt");
}

//The function of starting the encryption check
void encryptionCheck(int cryptoType, int funkType)
{
	string codeCheck = "";
	bool isGood = false;
	do
	{
		try
		{
			cout << "Вы хотите проверить расшифровку?" << endl << "1)Да" << endl << "2)Нет" << endl << ":";
			getline(cin, codeCheck);
			if (codeCheck == "")
			{
				throw runtime_error("Введена пустая строка.\nПопробуйте снова.\n");
			}
			if (codeCheck != "1" && codeCheck != "2")
			{
				string err;
				err = "Недопустимый ввод.\nВы ввели \"" + codeCheck + "\", когда ожидалось \"1\" или \"2\".\nПопробуйте снова.\n";
				throw runtime_error(err);
			}
			isGood = true;
		}
		catch (const exception& error)
		{
			system("CLS");
			cerr << error.what();
		}
	} while (isGood == false);
	system("CLS");
	if (codeCheck == "1")
	{
		string bufer = "";
		ofstream fin("Some_text.txt");   //if - ÷òåíèå, of - çàïèñü
		ifstream fout("Str_aft_proc.txt");
		while (!fout.eof())
		{
			getline(fout, bufer);
			fin << bufer;
			if (!fout.eof())
			{
				fin << '\n';
			}
		}
		fin.close();
		fout.close();

		passwordCheck();
		//Conditions for performing encryption for the selected type and principle of operation
		switch (Ciphers(cryptoType))
		{
		case Ciphers::Morse:
			switch (Principle(funkType))
			{
			case Principle::Encription:
				MorseDecode();
				break;
			case Principle::Decription:
				MorseCode();
				break;
			}
			break;
		case Ciphers::Shamir:
			switch (Principle(funkType))
			{
			case Principle::Encription:
				ShamirDecode();
				break;
			case Principle::Decription:
				ShamirCode();
				break;
			}
			break;
		case Ciphers::Hill:
			switch (Principle(funkType))
			{
			case Principle::Encription:
				HillDecode(1);
				break;
			case Principle::Decription:
				HillCode(1);
				break;
			}
			break;
		}
	}
	system("notepad Str_aft_proc.txt");
	system("CLS");
}
