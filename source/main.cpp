#include <iostream>
#include "Matrix"

using namespace std;
using namespace JoY;

int main()
{
	int m, n;

	cout << "Matrix calculation, please separate input with spaces." << endl
		 << "Input the m,n of matrix [a]:" << endl
		 << endl;
	cin >> m >> n;
	Matrix a(m, n);

	cout << endl
		 << "----------------Input items of [a]-----------------" << endl;
	for (m = 0; m < a.getMN().m; m++)
	{
		for (n = 0; n < a.getMN().n; n++)
		{
			cin >> a.useA()[m][n];
		}
		cout << endl;
	}

	cout << "m,n of [a]: " << a.getMN().m << "," << a.getMN().n << endl
		 << "[a]:"
		 << endl;
	for (m = 0; m < a.getMN().m; m++)
	{
		for (n = 0; n < a.getMN().n; n++)
		{
			cout << a.useA()[m][n] << "\t";
		}
		cout << endl
			 << endl;
	}

	Matrix aT(a.getAT());
	cout << "m,n of [aT]: " << aT.getMN().m << "," << aT.getMN().n << endl
		 << "[aT]:"
		 << endl;
	for (m = 0; m < aT.getMN().m; m++)
	{
		for (n = 0; n < aT.getMN().n; n++)
		{
			cout << aT.useA()[m][n] << "\t";
		}
		cout << endl
			 << endl;
	}

	Matrix aSL(a.getSimplestLine());
	cout << "m,n of [aSL]: " << aSL.getMN().m << "," << aSL.getMN().n << endl
		 << "[aSL]:"
		 << endl;
	for (m = 0; m < aSL.getMN().m; m++)
	{
		for (n = 0; n < aSL.getMN().n; n++)
		{
			cout << aSL.useA()[m][n] << "\t";
		}
		cout << endl
			 << endl;
	}

	return 0;
}