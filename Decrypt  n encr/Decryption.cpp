#include "Decryption.h"
#include "HillComp.h"

//Decryption with Morse cipher
void MorseDecode()
{
	string inputString = "";                                         //input string
	string outputString = "";										//output string
	ifstream fout1("Some_text.txt"); //читает файл с ключом и нашим текстом
	ofstream fin2("Str_aft_proc.txt");
	map <string, char> alfForDecode = { {"._",'A'}, {"_...",'B'}, {"_._.",'C'}, {"_..",'D'}, {".",'E'}, {".._.",'F'}, {"__.",'G'}, {"....",'H'}, {"..",'I'}, {".___",'J'},{"_._",'K'}, {"._..",'L'}, {"__",'M'},
										{"_.",'N'}, {"___",'O'}, {".__.",'P'}, {"__._",'Q'}, {"._.",'R'}, {"...",'S'}, {"_",'T'}, {".._",'U'}, {"..._",'V'}, {".__",'W'}, {"_.._",'X'}, {"_.__",'Y'}, {"__..",'Z'},
										{".____",'1'}, {"..___",'2'}, {"...__",'3'}, {"...._",'4'}, {".....",'5'}, {"_....",'6'}, {"__...",'7'}, {"___..",'8'}, {"____.",'9'}, {"_____",'0'}, {"______",' '},
										{"____..",'\\'}, {"....__",'/'}, {".__...",'['}, {"_..___",']'}, {"__..__",'<'}, {"..__..",'>'}, {"___...",'('}, {"...___",')'}, {"..__.",'{'}, {"__.._",'}'},
										{"._____",'.'}, {"_.....",','}, {"____._",'_'}, {"...._.",'|'}, {"_.____",'?'}, {"._....",'!'}, {"_...._",';'}, {".____.",':'}, {".___.",'-'}, {"..____",'$'}, {"..._._",'%'},
										{"...__.",'\"'}, {"___.._",'@'}, {".._...",'\''}, {"__.___",'`'}, {"_...__",'^'}, {"___.__",'~'}, {"..___.",'#'}, {".___..",'&'}, {"_..._",'+'}, {"___._",'='}, {"_..__",'*'} };


	funkPrinciple(2);
	funkTypeName(1);
	cout << "Расшифрованная строка: " << endl;
	while (!fout1.eof())
	{
		inputString = "";
		outputString = "";
		getline(fout1, inputString);
		for (int i = 0; i < inputString.length(); i++)
		{
			string dotTirWord = "";
			for (int j = i; inputString[j] != ' '; j++)
			{
				dotTirWord += inputString[j];
				i = j;
			}
			i++;
			outputString += alfForDecode[dotTirWord];
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

//Decryption with Shamir cipher
void ShamirDecode() {
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

	funkPrinciple(2);
	funkTypeName(2);
	cout << "Расшифрованная строка: " << endl;
	int bufer = 0;
	int shag;
	while (!fout.eof())
	{
		getline(fout, input);
		bufer = 0;
		for (uint64_t i = 0; i < input.length(); ++i)
		{
			if ((input[i] == ' ') || (input[i] == '\0')) {
				shag = shamir(bufer, Da, p);
				shag = shamir(shag, Db, p);
				char out = shag;
				fin << out;
				cout << out;
				bufer = 0;
			}
			else {
				bufer = bufer * 10 + (input[i] - 48);
			}
		}
		shag = shamir(bufer, Da, p);
		shag = shamir(shag, Db, p);
		char out = shag;
		fin << out;
		cout << out;
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

//Decryption with Hill cipher
void HillDecode(int codeCheck)
{
	vector<char> alf;
	initializeAlphabet(alf);

	vector<int> codByAlfKey;
	vector<vector<int>> matrixKey;
	int g = 0;
	if (codeCheck != 1)
	{
		string someKey = "";
		bool isGood = false;
		do
		{
			try
			{
				codByAlfKey.clear();
				matrixKey.clear();
				cout << "Введите КЛЮЧ:" << endl;
				getline(cin, someKey);
				for (int i = 2; i < someKey.length(); i++)
				{
					if (someKey.length() == pow(i, 2))
					{
						isGood = true;
						break;
					}
				}
				if (isGood == false)
				{
					throw runtime_error("Ключ некорректен.\nДлина ключа должна быть равна квадрату целого числа.\n");
				}
				for (char i : someKey)
				{
					for (int j = 0; j < alf.size(); j++)
					{
						if (i == alf[j])
						{
							codByAlfKey.push_back(j);
						}
					}
				}
				for (int i = 0; i < (int)sqrt(someKey.length()); i++)
				{
					vector<int> m;
					matrixKey.push_back(m);
				}
				g = 0;
				for (int i = 0; i < (int)sqrt(someKey.length()); i++)
				{
					for (int j = 0; j < (int)sqrt(someKey.length()); j++)
					{
						matrixKey[i].push_back(codByAlfKey[g++]);
					}
				}
				if (determCalk(matrixKey, matrixKey.size()) == 0)
				{
					throw runtime_error("Ключ некорректен.\nВ ходе вычислений определитель ключевой матрицы оказался равным нулю.n");
				}
			}
			catch (const exception& error)
			{
				system("CLS");
				isGood = false;
				cout << error.what();
			}
		} while (isGood == false);
		ofstream fin1("keys.txt");
		fin1 << someKey << endl;
		fin1.close();
	}

	ifstream fout("Some_text.txt");//читает файл с нашим текстом
	ofstream fin("Str_aft_proc.txt"); //очищает файл Str_aft_proc.txt куда записывает зашифрованный текст

	ifstream fout1("keys.txt");//читает файл с нашим key
	string key = "";
	getline(fout1, key);
	fout1.close();

	if (codeCheck == 1)
	{
		processKeyMatrix(matrixKey, key, alf);
	}

	system("CLS");
	funkPrinciple(2);   //есть codByAlfKey matrixKey
	funkTypeName(3);
	cout << "Ваш КЛЮЧ: " << key << endl;
	cout << "Расшифрованная строка: " << endl;

	while (!fout.eof())
	{
		string inputString = "";
		getline(fout, inputString);

		vector<int> codByAlfStr;
		codbyStr(inputString, codByAlfStr, alf);

		vector<vector<int>> matrixStr;
		processMatrix(matrixStr, codByAlfStr, key);

		int detMatrixKey = determCalk(matrixKey, matrixKey.size());;
		int x = rasAlgEvkl(detMatrixKey, alf.size());
		int obrEl = calculateObrEl(detMatrixKey, x, alf); //обратный детерминанту элемент

		vector<vector<int>> matrixAlgDop;
		AlgDop(matrixKey, matrixAlgDop);

		vector<vector<int>> matMinor;
		processMatrixAlgDop(matrixAlgDop, matrixKey, alf, obrEl);

		vector<vector<int>> transpMatr;
		Transp(matrixAlgDop, alf, transpMatr);

		string outputString = decryptString(matrixStr, transpMatr, alf);

		fin << outputString;
		cout << outputString << endl;
		if (!fout.eof())
		{
			fin << endl;
		}
	}
	fout.close();
	fin.close();
	cout << endl;
	system("PAUSE");
	system("CLS");
}
