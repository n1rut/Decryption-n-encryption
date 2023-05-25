#include "ShamirKeygen.h"
#include "helpFunc.h"

int shamir(int m, int c, int p) {
    int x;
    x = m * m % p;
    for (int i = 3; i <= c; i++) {
        x = m * x % p;
    }
    return x;
}

int gcd(int a, int b) {
	if (b == 0) {
		return a;
	}
	return gcd(b, a % b);
}

int Extendedgcd(int a, int b, int& x, int& y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	int x1, y1;
	int d = Extendedgcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

bool simplenumberFerma(long long x) {
	if (x == 2) {
		return true;
	}
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		long long a = (rand() % (x - 2)) + 2;
		if (gcd(a, x) != 1) {
			return false;
		}
		if (shamir(a, x - 1, x) != 1) {
			return false;
		}
	}
	return true;
}

void ShamirKeygen(int code) {
	int p, Ca, Cb, Da, Db;
	string publicp = "";
	string publicCa = "";
	string publicCb = "";
	string privateDa = "";
	string privateDb = "";
	if (code != 1) {
		srand(time(NULL));
		int x, y;
		int local = 4;
		bool flag = true;
		while (simplenumberFerma(local) != true) {
			local = 255 + rand() % (1000 - 255);
		}
		p = local;
		local = 4;
		while (flag == true) {
			while (simplenumberFerma(local) != true) {
				local = 1 + rand() % (p - 1);
				if (local == p) {
					local = 4;
				}
			}
			Ca = local;
			Extendedgcd(Ca, p - 1, x, y);
			if (x < 0) {
				x = (p - 1) + x;
			}
			Da = x;
			if (Ca * Da % (p - 1) == 1) {
				flag = false;
			}
		}
		flag = true;
		local = 4;
		while (flag == true) {
			while (simplenumberFerma(local) != true) {
				local = 1 + rand() % (p - 1);
				if (local == Ca) {
					local = 4;
				}
			}
			Cb = local;
			Extendedgcd(Cb, p - 1, x, y);
			if (x < 0) {
				x = (p - 1) + x;
			}
			Db = x;
			if (Cb * Db % (p - 1) == 1) {
				flag = false;
			}
		}
		cout << "PUBLIC KEY P: {" << p << "}" << endl;
		cout << "PUBLIC KEYS: {" << Ca << "," << Cb << "}" << endl;
		cout << "PRIVATE KEYS: {" << Da << "," << Db << "}" << endl;
	}
	else {
		cout << "Enter public key p" << endl << ": ";
		getline(cin, publicp);
		cout << "Enter public key Ca" << endl << ": ";
		getline(cin, publicCa);
		cout << "Enter public key Cb" << endl << ": ";
		getline(cin, publicCb);
		cout << "Enter private key Da" << endl << ": ";
		getline(cin, privateDa);
		cout << "Enter private key Db" << endl << ": ";
		getline(cin, privateDb);

		system("CLS");

		cout << "PUBLIC KEY P: {" << publicp << "}" << endl;
		cout << "PUBLIC KEYS: {" << publicCa << "," << publicCb << "}" << endl;
		cout << "PRIVATE KEYS: {" << privateDa << "," << privateDb << "}" << endl;
	}

	ofstream fin("keys.txt");	 //очищает файл keys.txt куда сначала записывается ключ, а затем исходный текст
	if (code != 1)
	{
		fin << p << endl;
		fin << Ca << endl;
		fin << Cb << endl;
		fin << Da << endl;
		fin << Db << endl;
	}
	else if (code == 1)
	{

		fin << publicp << endl;
		fin << publicCa << endl;
		fin << publicCb << endl;
		fin << privateDa << endl;
		fin << privateDb << endl;
	}
	fin.close();
	cout << endl;
	system("PAUSE");
	system("CLS");
}