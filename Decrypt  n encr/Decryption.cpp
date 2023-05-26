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
	vector<char> alf; // Латинские буквы и символы

	for (int i = 32; i < 127; i++)
	{
		alf.push_back((char)i);
	}
	alf.push_back('№');
	alf.push_back((char)181);

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
				cout << "Enter the KEY" << endl << ": ";
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
		for (char i : key)
		{
			for (int j = 0; j < alf.size(); j++)
			{
				if (i == alf[j])
				{
					codByAlfKey.push_back(j);
					break;
				}
			}
		}
		for (int i = 0; i < (int)rint(sqrt(key.length())); i++)
		{
			vector<int> m;
			matrixKey.push_back(m);
		}
		g = 0;
		for (int i = 0; i < (int)rint(sqrt(key.length())); i++)
		{
			for (int j = 0; j < (int)rint(sqrt(key.length())); j++)
			{
				matrixKey[i].push_back(codByAlfKey[g++]);
			}
		}
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
		for (char i : inputString)
		{
			for (int j = 0; j < alf.size(); j++)
			{
				if (i == alf[j])
				{
					codByAlfStr.push_back(j);
				}
			}
		}
		vector<vector<int>> matrixStr;

		int crat = 0;
		if (codByAlfStr.size() % (int)rint(sqrt(key.length())) != 0)
		{
			crat = 1;
		}

		for (int i = 0; i < codByAlfStr.size() / (int)rint(sqrt(key.length())) + crat; i++)
		{
			vector<int> m;
			matrixStr.push_back(m);
		}
		g = 0;
		for (int i = 0; i < codByAlfStr.size() / (int)rint(sqrt(key.length())) + crat; i++)
		{
			if (g < codByAlfStr.size())
			{
				for (int j = 0; j < (int)rint(sqrt(key.length())); j++)
				{
					matrixStr[i].push_back(codByAlfStr[g++]);
					if (g >= codByAlfStr.size())
					{
						while (matrixStr[i].size() < (int)rint(sqrt(key.length())))
						{
							matrixStr[i].push_back(0); ///////////////////////////////////////////
						}
						break;
					}
				}
			}
			else
			{
				while (matrixStr[i].size() < (int)rint(sqrt(key.length())))
				{
					matrixStr[i].push_back(0); ////////////////////////////////////////////////////
				}
			}
		}
		int detMatrixKey = determCalk(matrixKey, matrixKey.size());;
		int x = rasAlgEvkl(detMatrixKey, alf.size());
		int obrEl = 0;
		if ((detMatrixKey < 0 && x > 0) || (detMatrixKey > 0 && x > 0))
		{
			obrEl = x;
		}
		if (detMatrixKey < 0 && x < 0)
		{
			obrEl = -x;
		}
		if (detMatrixKey > 0 && x < 0)
		{
			obrEl = alf.size() + x;
		}

		vector<vector<int>> matrixAlgDop;
		for (int i = 0; i < matrixKey.size(); i++)
		{
			vector<int> m;
			matrixAlgDop.push_back(m);
		}
		vector<vector<int>> matMinor;
		for (int i = 0; i < matrixKey.size(); i++)
		{
			for (int j = 0; j < matrixKey.size(); j++)
			{
				matMinor.clear();
				for (int a = 0; a < matrixKey.size() - 1; a++)
				{
					vector<int> m;
					matMinor.push_back(m);
				}
				int lin = 0;
				bool isK = false;
				for (int k = 0; k < matrixKey.size(); k++)
				{
					isK = false;
					for (int f = 0; f < matrixKey.size(); f++)
					{
						if ((k != i) && (f != j))
						{
							matMinor[lin].push_back(matrixKey[k][f]);
							isK = true;
						}
					}
					if (isK == true)
					{
						lin++;
					}
				}
				matrixAlgDop[i].push_back(pow(-1, i + j) * determCalk(matMinor, matMinor.size()));
			}
		}
		for (int i = 0; i < matrixAlgDop.size(); i++)
		{
			for (int j = 0; j < matrixAlgDop.size(); j++)
			{
				if (matrixAlgDop[i][j] < 0)
				{
					int num = abs(matrixAlgDop[i][j]) % alf.size();
					matrixAlgDop[i][j] = -num;
				}
				else
				{
					matrixAlgDop[i][j] = matrixAlgDop[i][j] % alf.size();
				}
			}
		}
		for (int i = 0; i < matrixAlgDop.size(); i++)
		{
			for (int j = 0; j < matrixAlgDop.size(); j++)
			{
				if (matrixAlgDop[i][j] < 0)
				{
					int num = abs(matrixAlgDop[i][j] * obrEl) % alf.size();
					matrixAlgDop[i][j] = -num;
				}
				else
				{
					matrixAlgDop[i][j] = (matrixAlgDop[i][j] * obrEl) % alf.size();
				}
			}
		}

		vector<vector<int>> transpMatr;
		for (int i = 0; i < matrixAlgDop.size(); i++)
		{
			vector<int> m;
			transpMatr.push_back(m);
		}

		for (int i = 0; i < matrixAlgDop.size(); i++)
		{
			for (int j = 0; j < matrixAlgDop.size(); j++)
			{
				transpMatr[i].push_back(matrixAlgDop[j][i]);
			}
		}

		for (int i = 0; i < transpMatr.size(); i++)
		{
			for (int j = 0; j < transpMatr.size(); j++)
			{
				if (transpMatr[i][j] < 0)
				{
					transpMatr[i][j] = alf.size() + transpMatr[i][j];
				}
			}
		}//получии транспонированную матрицу которая является обратной по модулю к матрице ключа.

		vector<vector<int>> decryptStr;
		for (int i = 0; i < matrixStr.size(); i++)
		{
			vector<int> m;
			decryptStr.push_back(m);
		}
		int mnog = 0;
		g = -1;
		for (vector<int> blok : matrixStr)
		{
			g++;
			for (int i = 0; i < blok.size(); i++)
			{
				mnog = 0;
				for (int j = 0; j < blok.size(); j++)
				{
					mnog += blok[j] * transpMatr[j][i];
				}
				decryptStr[g].push_back(mnog);
			}
		}
		string outputString = "";
		for (vector<int> blok : decryptStr)
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
	cout << endl;
	system("PAUSE");
	system("CLS");
}
