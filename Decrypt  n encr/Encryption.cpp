#include "Encryption.h"
#include "HillComp.h"

//Encryption with Morse cipher
void MorseCode()
{
	string inputString = "";                                         //input string
	string outputString = "";										//output string
	ifstream fout1("Some_text.txt"); //читает файл с нашим текстом
	ofstream fin2("Str_aft_proc.txt");
	map <char, string> alfForCode = { {'A',"._"}, {'B',"_..."}, {'C',"_._."}, {'D',"_.."}, {'E',"."}, {'F',".._."}, {'G',"__."}, {'H',"...."}, {'I',".."}, {'J',".___"},{'K',"_._"}, {'L',"._.."}, {'M',"__"},
									  {'N',"_."}, {'O',"___"}, {'P',".__."}, {'Q',"__._"}, {'R',"._."}, {'S',"..."}, {'T',"_"}, {'U',".._"}, {'V',"..._"}, {'W',".__"}, {'X',"_.._"}, {'Y',"_.__"}, {'Z',"__.."},
									  {'a',"._"}, {'b',"_..."}, {'c',"_._."}, {'d',"_.."}, {'e',"."}, {'f',".._."}, {'g',"__."}, {'h',"...."}, {'i',".."}, {'j',".___"},{'k',"_._"}, {'l',"._.."}, {'m',"__"},
									  {'n',"_."}, {'o',"___"}, {'p',".__."}, {'q',"__._"}, {'r',"._."}, {'s',"..."}, {'t',"_"}, {'u',".._"}, {'v',"..._"}, {'w',".__"}, {'x',"_.._"}, {'y',"_.__"}, {'z',"__.."},
									  {'1',".____"}, {'2',"..___"}, {'3',"...__"}, {'4',"...._"}, {'5',"....."}, {'6',"_...."}, {'7',"__..."}, {'8',"___.."}, {'9',"____."}, {'0',"_____"}, {' ',"______"},
									  {'\\',"____.."}, {'/',"....__"}, {'[',".__..."}, {']',"_..___"}, {'<',"__..__"}, {'>',"..__.."}, {'(',"___..."}, {')',"...___"}, {'{',"..__."}, {'}',"__.._"},
									  {'.',"._____"}, {',',"_....."}, {'_',"____._"}, {'|',"...._."}, {'?',"_.____"}, {'!',"._...."}, {';',"_...._"}, {':',".____."}, {'-',".___."}, {'$',"..____"}, {'%',"..._._"},
									  {'\"',"...__."}, {'@',"___.._"}, {'\'',".._..."}, {'`',"__.___"}, {'^',"_...__"}, {'~',"___.__"}, {'#',"..___."}, {'&',".___.."}, {'+',"_..._"}, {'=',"___._"}, {'*',"_..__"} };

	funkPrinciple(1);
	funkTypeName(1);
	cout << "Зашифрованная строка: " << endl;
	while (!fout1.eof())
	{
		inputString = "";
		outputString = "";
		getline(fout1, inputString);
		for (int i = 0; i < inputString.length(); i++)
		{
			outputString = outputString + alfForCode[inputString[i]] + ' ';
		}
		fin2 << outputString;
		cout << outputString << endl;
		if (!fout1.eof())
		{
			fin2 << endl;
		}
	}
	fout1.close();
	fin2.close();
	cout << endl;
	system("PAUSE");
	system("CLS");
}

//Encryption with Shamir cipher
void ShamirCode() {
	string publicp = "";
	string publicCa = "";
	string publicCb = "";
	string privateDa = "";
	string privateDb = "";
	string input = "";

	ifstream fout1("keys.txt");
	getline(fout1, publicp);
	getline(fout1, publicCa);
	getline(fout1, publicCb);
	getline(fout1, privateDa);
	getline(fout1, privateDb);
	fout1.close();

	int p = stoi(publicp);
	int Ca = stoi(publicCa);
	int Cb = stoi(publicCb);
	int Da = stoi(privateDa);
	int Db = stoi(privateDb);

	ifstream fout("Some_text.txt");
	ofstream fin("Str_aft_proc.txt");

	funkPrinciple(1);
	funkTypeName(2);
	cout << "Зашифрованная строка: " << endl;

	while (!fout.eof())
	{
		getline(fout, input);
		for (int i = 0; input[i] != '\0'; i++)
		{
			int el = input[i];
			int shag;
			shag = shamir(el, Ca, p);
			shag = shamir(shag, Cb, p);
			fin << shag << ' ';
			cout << shag << ' ';
		}
		if (!fout.eof())
		{
			cout << '\n';
			fin << '\n';
		}
	}
	fout.close();
	fin.close();
	cout << endl << endl;
	system("PAUSE");
	system("CLS");
}

//Encryption with Hill cipher
void HillCode(int codeCheck)
{
	vector<char> alf;
	initializeAlphabet(alf);

	vector<int> codByAlfKey;
	vector<vector<int>> matrixKey;
	string someKey = "";
	int obrEl = 100;

	if (codeCheck != 1)
	{
		codByAlfKey = generateKey(alf);
		matrixKey = generateMatrixKey(codByAlfKey);

		ofstream fin1("keys.txt");
		fin1 << someKey << endl;
		fin1.close();
	}

	ifstream fout("Some_text.txt");
	ofstream fin("Str_aft_proc.txt");

	string key = "";
	ifstream fout1("keys.txt");
	getline(fout1, key);
	fout1.close();

	if (codeCheck == 1)
	{
		codByAlfKey = generateKey(alf);
		matrixKey = generateMatrixKey(codByAlfKey);
	}

	system("CLS");
	funkPrinciple(1);
	funkTypeName(3);
	cout << "Ваш КЛЮЧ: " << key << endl;
	cout << "Зашифрованная строка: " << endl;

	while (!fout.eof())
	{
		string inputString = "";
		getline(fout, inputString);

		vector<vector<int>> encryptStr = encryptString(inputString, matrixKey, alf);

		string outputString = "";
		for (vector<int> blok : encryptStr)
		{
			for (int i : blok)
			{
				outputString += alf[i % alf.size()];
			}
		}

		fin << outputString;
		cout << outputString << endl;

		if (!fout.eof())
		{
			fin << endl;
		}
	}

	fout.close();
	fin.close();
	system("PAUSE");
	system("CLS");
}