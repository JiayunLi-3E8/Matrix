#include <iostream>
#include "Matrix"
#include "Fraction"

using namespace std;
using namespace JoY;

int main()
{
	cout << "----------------> Matrix calculation <----------------" << endl;

	// Matrix b;
	SquareMatrix a;

	cin >> a /* >> b */;

	// cout << "[a*b]:" << a * b << endl;

	cout << "m,n of [a]: " << a.getMN().m << "," << a.getMN().n << endl
		 << "[a]:" << a << "r(a)=" << a.r() << endl
		 << endl;

	SquareMatrix aT = a.getAT();
	cout << "[aT]:" << aT << endl;

	SquareMatrix ald = a.getLadder();
	cout << "[ald]:" << ald << endl;

	SquareMatrix aSL = a.getSimplestLine();
	cout << "[aSL]:" << aSL << endl;

	Fraction dmt = a.getDeterminant();
	cout << "dmt:" << dmt << endl;

	SquareMatrix adj = a.getAdjoint();
	cout << "[adj]:" << adj << endl;

	SquareMatrix inv = a.getInverse();
	cout << "[inv]:" << inv << endl;

	return 0;
}