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

vector<int> generateKey(const vector<char>& alf)
{
    vector<int> codByAlfKey;
    string someKey = "";

    while (1)
    {
        codByAlfKey.clear();
        someKey = "";
        for (int i = 0; i < 9; i++)
        {
            someKey += alf[rand() % alf.size()];
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

        // Проверка детерминанта
        vector<vector<int>> matrixKey = generateMatrixKey(codByAlfKey);
        int detMatrixKey = determCalk(matrixKey, matrixKey.size());
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

        if (obrEl < 97)
        {
            break;
        }
    }

    return codByAlfKey;
}

vector<vector<int>> generateMatrixKey(const vector<int>& codByAlfKey)
{
    vector<vector<int>> matrixKey;
    int g = 0;

    for (int i = 0; i < (int)rint(sqrt(codByAlfKey.size())); i++)
    {
        vector<int> m;
        matrixKey.push_back(m);
    }

    g = 0;
    for (int i = 0; i < (int)rint(sqrt(codByAlfKey.size())); i++)
    {
        for (int j = 0; j < (int)rint(sqrt(codByAlfKey.size())); j++)
        {
            matrixKey[i].push_back(codByAlfKey[g++]);
        }
    }

    return matrixKey;
}

vector<vector<int>> encryptString(const string& inputString, const vector<vector<int>>& matrixKey, const vector<char>& alf)
{
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

    if ((codByAlfStr.size() % (int)rint(sqrt(matrixKey.size()))) != 0)
    {
        crat = 1;
    }

    for (int i = 0; i < codByAlfStr.size() / (int)rint(sqrt(matrixKey.size())) + crat; i++)
    {
        vector<int> m;
        matrixStr.push_back(m);
    }

    int g = 0;
    for (int i = 0; i < codByAlfStr.size() / (int)rint(sqrt(matrixKey.size())) + crat; i++)
    {
        if (g < codByAlfStr.size())
        {
            for (int j = 0; j < (int)rint(sqrt(matrixKey.size())); j++)
            {
                matrixStr[i].push_back(codByAlfStr[g++]);
                if (g >= codByAlfStr.size())
                {
                    while (matrixStr[i].size() < (int)rint(sqrt(matrixKey.size())))
                    {
                        matrixStr[i].push_back(0);
                    }
                    break;
                }
            }
        }
        else
        {
            while (matrixStr[i].size() < (int)rint(sqrt(matrixKey.size())))
            {
                matrixStr[i].push_back(0);
            }
        }
    }

    vector<vector<int>> encryptStr;
    for (int i = 0; i < matrixStr.size(); i++)
    {
        vector<int> m;
        encryptStr.push_back(m);
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
                mnog += blok[j] * matrixKey[j][i];
            }
            encryptStr[g].push_back(mnog);
        }
    }

    return encryptStr;
}
