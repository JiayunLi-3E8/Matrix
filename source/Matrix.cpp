#include <iostream>
#include <string>
#include "Matrix"

using namespace std;

namespace JoY
{
	Matrix::Matrix(int m, int n)
	{
		mn.m = m;
		mn.n = n;
		A = new Fraction *[mn.m];
		for (int i = 0; i < mn.m; i++)
		{
			A[i] = new Fraction[mn.n];
		}
	}

	Matrix::~Matrix()
	{
		for (int i = 0; i < mn.m; i++)
		{
			delete[] A[i];
		}
		delete[] A;
		// std::cout << "~" << this << std::endl;
	}

	MN Matrix::getMN()
	{
		return mn;
	}

	Fraction **Matrix::useA()
	{
		return A;
	}

	Matrix Matrix::getAT()
	{
		Matrix aT(mn.n, mn.m);
		for (int m = 0; m < mn.m; m++)
		{
			for (int n = 0; n < mn.n; n++)
			{
				aT.A[n][m] = A[m][n];
			}
		}
		return aT;
	}

	Matrix Matrix::getSimplestLine()
	{
		Matrix aSimplestLine(mn.m, mn.n);
		for (int m = 0; m < mn.m; m++)
		{
			for (int n = 0; n < mn.n; n++)
			{
				aSimplestLine.A[m][n] = A[m][n];
			}
		}

		int m = 0, n = 0;
		while (m < aSimplestLine.mn.m)
		{
			while (n < aSimplestLine.mn.n)
			{
				if (aSimplestLine.A[m][n] == 0)
				{
					int i = m + 1;
					while (i < aSimplestLine.mn.m)
					{
						if (aSimplestLine.A[i][n] != 0)
						{
							break;
						}
						i++;
					}
					if (i >= aSimplestLine.mn.m)
					{
						n++;
						continue;
					}
					else
					{
						for (int j = n; j < aSimplestLine.mn.n; j++)
						{
							aSimplestLine.A[m][j] += aSimplestLine.A[i][j];
						}
					}
				}
				if (aSimplestLine.A[m][n] != 1)
				{
					for (int j = aSimplestLine.mn.n - 1; j >= n; j--)
					{
						aSimplestLine.A[m][j] /= aSimplestLine.A[m][n];
					}
				}
				for (int i = m + 1; i < aSimplestLine.mn.m; i++)
				{
					for (int j = aSimplestLine.mn.n - 1; j >= n; j--)
					{
						aSimplestLine.A[i][j] -= aSimplestLine.A[i][n] * aSimplestLine.A[m][j];
					}
				}
				n++;
				break;
			}
			if (n >= aSimplestLine.mn.n)
			{
				break;
			}
			else
			{
				m++;
			}
		}

		if (m >= aSimplestLine.mn.m)
		{
			m = aSimplestLine.mn.m - 1;
		}
		while (m > 0)
		{
			n = 0;
			while (n < aSimplestLine.mn.n)
			{
				if (aSimplestLine.A[m][n] != 0)
				{
					for (int i = m - 1; i >= 0; i--)
					{
						for (int j = aSimplestLine.mn.n - 1; j >= n; j--)
						{
							aSimplestLine.A[i][j] -= aSimplestLine.A[i][n] * aSimplestLine.A[m][j];
						}
					}
					break;
				}
				n++;
			}
			m--;
		}

		return aSimplestLine;
	}
}
