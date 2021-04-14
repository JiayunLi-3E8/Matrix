#include <iostream>
#include "Matrix"

using namespace std;
using namespace JoY;

int main()
{
	cout << "----------------> Matrix calculation <----------------" << endl;

	SquareMatrix a;
	cout << a;

	// int m, n;
	// Matrix a, b;

	// cin >> a >> b;
	// Matrix c(a * b);
	// cout << c;

	// cin >> a;
	// cout
	// 	<< "m,n of [a]: " << a.getMN().m << "," << a.getMN().n << endl
	// 	<< "[a]:" << a << "r(a)=" << a.r() << endl
	// 	<< endl;

	// Matrix aT(a.getAT());
	// cout << "m,n of [aT]: " << aT.getMN().m << "," << aT.getMN().n << endl
	// 	 << "[aT]:" << aT << endl;

	// Matrix aSL(a.getSimplestLine());
	// cout << "m,n of [aSL]: " << aSL.getMN().m << "," << aSL.getMN().n << endl
	// 	 << "[aSL]:" << aSL << endl;

	return 0;
}