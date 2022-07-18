#include <iostream>
#include "Matrix.h"
#include "Matrix.cpp"
#include "Fraction.h"

using namespace std;
using namespace JoY;

int main()
{
	cout << "----------------> Matrix calculation <----------------" << endl;

	// Matrix b;
	SquareMatrix<Fraction> a;

	cin >> a /* >> b */;

	// cout << "[a*b]:" << a * b << endl;

	cout << "m,n of [a]: " << a.getMN().m << "," << a.getMN().n << endl
		 << "[a]:" << a << "r(a)=" << a.r() << endl
		 << endl;

	SquareMatrix<Fraction> aT = a.getAT();
	cout << "[aT]:" << aT << endl;

	SquareMatrix<Fraction> ald = a.getLadder();
	cout << "[ald]:" << ald << endl;

	SquareMatrix<Fraction> aSL = a.getSimplestLine();
	cout << "[aSL]:" << aSL << endl;

	Fraction dmt = a.getDeterminant();
	cout << "dmt:" << dmt << endl;

	SquareMatrix<Fraction> adj = a.getAdjoint();
	cout << "[adj]:" << adj << endl;

	SquareMatrix<Fraction> inv = a.getInverse();
	cout << "[inv]:" << inv << endl;

	return 0;
}