#include "HillComp.h"

int rasAlgEvkl(int detMatrixKey, int alfLen)
{
	if (detMatrixKey < alfLen)
	{
		int p = detMatrixKey;
		detMatrixKey = alfLen;
		alfLen = p;
	}
	int r = 1, q = 0;
	int x1 = 1, y1 = 0;
	int x2 = 0, y2 = 1;
	int x3 = 0, y3 = 0;
	while (r != 0)
	{
		r = detMatrixKey % alfLen;
		q = detMatrixKey / alfLen;

		x3 = x1 - q * x2;
		y3 = y1 - q * y2;

		x1 = x2;
		x2 = x3;
		y1 = y2;
		y2 = y3;

		detMatrixKey = alfLen;
		alfLen = r;
	}
	return x1;
}

void minorCreat(vector<vector<int>>& matrix, vector<vector<int>>& minor, int i, int m)
{
	int di = 0;
	for (int ki = 0; ki < m - 1; ki++)
	{										// проверка индекса строки
		if (ki == i)
		{
			di = 1;
		}
		int dj = 0;
		for (int kj = 0; kj < m - 1; kj++)
		{									// проверка индекса столбца
			if (kj == 0)
			{
				dj = 1;
			}
			minor[ki][kj] = matrix[ki + di][kj + dj];
		}
	}
}

int determCalk(vector<vector<int>> matrix, int m)
{
	vector<vector<int>> newMatrix;
	for (int i = 0; i < m; i++)
	{
		vector<int> mat(m);
		newMatrix.push_back(mat);
	}
	int j = 0, det = 0, k = 1, n = m - 1;
	if (m == 1)
	{
		return matrix[0][0];
	}
	if (m == 2)
	{
		return matrix[0][0] * matrix[1][1] - (matrix[1][0] * matrix[0][1]);
	}
	if (m > 2)
	{
		for (int i = 0; i < m; i++)
		{
			minorCreat(matrix, newMatrix, i, m);
			det = det + k * matrix[i][0] * determCalk(newMatrix, n);
			k = -k;
		}
	}
	return det;
}

void initializeAlphabet(vector<char>& alf)
{
    for (int i = 32; i < 127; i++)
    {
        alf.push_back((char)i);
    }
    alf.push_back('№');
    alf.push_back((char)181);
}

void codbyStr(string x, vector<int>& str, vector<char> alf) {
	for (char i : x)
	{
		for (int j = 0; j < alf.size(); j++)
		{
			if (i == alf[j])
			{
				str.push_back(j);
			}
		}
	}
}

void processMatrix(vector<vector<int>>& matrixStr, vector<int>& codByAlfStr, string& key) {
	int crat = 0;
	if ((codByAlfStr.size() % static_cast<int>(rint(sqrt(key.length())))) != 0) {
		crat = 1;
	}
	for (int i = 0; i < codByAlfStr.size() / static_cast<int>(rint(sqrt(key.length()))) + crat; i++) {
		vector<int> m;
		matrixStr.push_back(m);
	}
	int g = 0;
	for (int i = 0; i < codByAlfStr.size() / static_cast<int>(rint(sqrt(key.length()))) + crat; i++) {
		if (g < codByAlfStr.size()) {
			for (int j = 0; j < static_cast<int>(rint(sqrt(key.length()))); j++) {
				matrixStr[i].push_back(codByAlfStr[g++]);
				if (g >= codByAlfStr.size()) {
					while (matrixStr[i].size() < static_cast<int>(rint(sqrt(key.length())))) {
						matrixStr[i].push_back(0);
					}
					break;
				}
			}
		}
		else {
			while (matrixStr[i].size() < static_cast<int>(rint(sqrt(key.length())))) {
				matrixStr[i].push_back(0);
			}
		}
	}
}

string encryptMatrix(const vector<vector<int>>& matrixStr, const vector<vector<int>>& matrixKey, vector<char>& alf) {
	vector<vector<int>> encryptStr;
	for (int i = 0; i < matrixStr.size(); i++) {
		vector<int> m;
		encryptStr.push_back(m);
	}
	int mnog = 0;
	int g = -1;
	for (vector<int> blok : matrixStr) {
		g++;
		for (int i = 0; i < blok.size(); i++) {
			mnog = 0;
			for (int j = 0; j < blok.size(); j++) {
				mnog += blok[j] * matrixKey[j][i];
			}
			encryptStr[g].push_back(mnog);
		}
	}
	string outputString = "";
	for (vector<int> blok : encryptStr) {
		for (int i : blok) {
			outputString += alf[i % alf.size()];
		}
	}
	return outputString;
}

void generateKey(vector<char>& alf, vector<vector<int>>& matrixKey, string& someKey) {
	vector<int> codByAlfKey;
	while (true) {
		codByAlfKey.clear();
		matrixKey.clear();
		someKey = "";
		for (int i = 0; i < 9; i++) {
			someKey += alf[rand() % alf.size()];
		}
		for (char i : someKey) {
			for (int j = 0; j < alf.size(); j++) {
				if (i == alf[j]) {
					codByAlfKey.push_back(j);
				}
			}
		}
		for (int i = 0; i < static_cast<int>(rint(sqrt(someKey.length()))); i++) {
			vector<int> m;
			matrixKey.push_back(m);
		}
		int g = 0;
		for (int i = 0; i < static_cast<int>(rint(sqrt(someKey.length()))); i++) {
			for (int j = 0; j < static_cast<int>(rint(sqrt(someKey.length()))); j++) {
				matrixKey[i].push_back(codByAlfKey[g++]);
			}
		}
		int detMatrixKey = determCalk(matrixKey, matrixKey.size());
		int x = rasAlgEvkl(detMatrixKey, alf.size());
		int obrEl = 0;
		if ((detMatrixKey < 0 && x > 0) || (detMatrixKey > 0 && x > 0)) {
			obrEl = x;
		}
		if (detMatrixKey < 0 && x < 0) {
			obrEl = -x;
		}
		if (detMatrixKey > 0 && x < 0) {
			obrEl = alf.size() + x;
		}
		if (obrEl < 97) {
			break;
		}
	}
}

void processKeyMatrix(vector<vector<int>>& matrixKey, string& key, vector<char>& alf) {
	vector<int> codByAlfKey;
	for (char i : key) {
		for (int j = 1; j < alf.size(); j++) {
			if (i == alf[j]) {
				codByAlfKey.push_back(j);
			}
		}
	}
	for (int i = 0; i < static_cast<int>(rint(sqrt(key.length()))); i++) {
		vector<int> m;
		matrixKey.push_back(m);
	}
	int g = 0;
	for (int i = 0; i < static_cast<int>(rint(sqrt(key.length()))); i++) {
		for (int j = 0; j < static_cast<int>(rint(sqrt(key.length()))); j++) {
			matrixKey[i].push_back(codByAlfKey[g++]);
		}
	}
}

int calculateObrEl(int detMatrixKey, int x, vector<char>& alf) {
	int obrEl = 0;
	if ((detMatrixKey < 0 && x > 0) || (detMatrixKey > 0 && x > 0)) {
		obrEl = x;
	}
	if (detMatrixKey < 0 && x < 0) {
		obrEl = -x;
	}
	if (detMatrixKey > 0 && x < 0) {
		obrEl = alf.size() + x;
	}
	return obrEl;
}

void AlgDop(vector<vector<int>>& matrixKey, vector<vector<int>>& matrixAlgDop) {
	for (int i = 0; i < matrixKey.size(); i++)
	{
		vector<int> m;
		matrixAlgDop.push_back(m);
	}
}

void processMatrixAlgDop(vector<vector<int>>& matrixAlgDop, vector<vector<int>>& matrixKey, vector<char>& alf, int obrEl) {
	vector<vector<int>> matMinor;
	int matSize = matrixKey.size();

	for (int i = 0; i < matSize; i++) {
		for (int j = 0; j < matSize; j++) {
			matMinor.clear();
			for (int a = 0; a < matSize; a++) {
				if (a != matSize - 1) {
					vector<int> m;
					matMinor.push_back(m);
				}
			}

			int lin = 0;
			bool isK = false;
			for (int k = 0; k < matSize; k++) {
				isK = false;
				for (int f = 0; f < matSize; f++) {
					if ((k != i) && (f != j)) {
						matMinor[lin].push_back(matrixKey[k][f]);
						isK = true;
					}
				}
				if (isK == true) {
					lin++;
				}
			}
			matrixAlgDop[i].push_back(pow(-1, i + j) * determCalk(matMinor, matMinor.size()));
		}
	}

	for (int i = 0; i < matSize; i++) {
		for (int j = 0; j < matSize; j++) {
			if (matrixAlgDop[i][j] < 0) {
				int num = abs(matrixAlgDop[i][j]) % alf.size();
				matrixAlgDop[i][j] = -num;
			}
			else {
				matrixAlgDop[i][j] = matrixAlgDop[i][j] % alf.size();
			}
		}
	}

	for (int i = 0; i < matSize; i++) {
		for (int j = 0; j < matSize; j++) {
			if (matrixAlgDop[i][j] < 0) {
				int num = abs(matrixAlgDop[i][j] * obrEl) % alf.size();
				matrixAlgDop[i][j] = -num;
			}
			else {
				matrixAlgDop[i][j] = (matrixAlgDop[i][j] * obrEl) % alf.size();
			}
		}
	}
}

void Transp(vector<vector<int>>& matrixAlgDop, vector<char>& alf, vector<vector<int>>& transpMatr){
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
	}//получим транспонированную матрицу которая является обратной по модулю к матрице ключа.
}

string decryptString(vector<vector<int>>& matrixStr, vector<vector<int>>& transpMatr, vector<char>& alf) {
	vector<vector<int>> decryptStr;
	for (int i = 0; i < matrixStr.size(); i++) {
		vector<int> m;
		decryptStr.push_back(m);
	}

	int mnog = 0;
	int g = -1;
	for (vector<int> blok : matrixStr) {
		g++;
		for (int i = 0; i < blok.size(); i++) {
			mnog = 0;
			for (int j = 0; j < blok.size(); j++) {
				mnog += blok[j] * transpMatr[j][i];
			}
			decryptStr[g].push_back(mnog);
		}
	}

	string outputString = "";
	for (vector<int> blok : decryptStr) {
		for (int i : blok) {
			outputString += alf[i % alf.size()];
		}
	}

	return outputString;
}
