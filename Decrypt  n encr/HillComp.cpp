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