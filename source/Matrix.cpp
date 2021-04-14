#include <iostream>
#include <string>
#include "Matrix"

using namespace std;

namespace JoY
{
	bool MN::operator==(const MN &mn)
	{
		return mn.m == m && mn.n == n;
	}

	bool MN::operator!=(const MN &mn)
	{
		return !(*this == mn);
	}

	void Matrix::New()
	{
		A = new Fraction *[mn.m];
		for (int i = 0; i < mn.m; i++)
		{
			A[i] = new Fraction[mn.n];
		}
	}

	void Matrix::Del()
	{
		for (int i = 0; i < mn.m; i++)
		{
			delete[] A[i];
		}
		delete[] A;
	}

	void Matrix::Renew(int m, int n)
	{
		Del();
		mn.m = m;
		mn.n = n;
		New();
	}

	Matrix::Matrix(int m, int n)
	{
		mn.m = m;
		mn.n = n;
		New();
	}

	Matrix::~Matrix()
	{
		Del();
		std::cout << "~" << this << std::endl;
	}

	MN Matrix::getMN()
	{
		return mn;
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

	int Matrix::r()
	{
		Matrix asl(getSimplestLine());
		int m = 0;
		while (m < asl.mn.m)
		{
			int n = 0;
			while (n < asl.mn.n)
			{
				if (asl.A[m][n] != 0)
				{
					break;
				}
				n++;
			}
			if (n >= asl.mn.n)
			{
				break;
			}
			m++;
		}
		return m;
	}

	const Matrix &Matrix::operator=(const Matrix &a)
	{
		this->Renew(a.mn.m, a.mn.n);
		for (int m = 0; m < mn.m; m++)
		{
			for (int n = 0; n < mn.n; n++)
			{
				A[m][n] = a.A[m][n];
			}
		}
		return a;
	}

	Matrix Matrix::operator+(Matrix &a)
	{
		Matrix newA(mn.m, mn.n);
		if (a.mn == mn)
		{
			for (int m = 0; m < mn.m; m++)
			{
				for (int n = 0; n < mn.n; n++)
				{
					newA.A[m][n] = A[m][n] + a.A[m][n];
				}
			}
		}
		else
		{
			invalid_argument e("The 'm,n' of the two matrices are different and cannot be added.");
			throw e;
		}
		return newA;
	}

	Matrix Matrix::operator-(Matrix &a)
	{
		Matrix newA(mn.m, mn.n);
		if (a.mn == mn)
		{
			for (int m = 0; m < mn.m; m++)
			{
				for (int n = 0; n < mn.n; n++)
				{
					newA.A[m][n] = A[m][n] - a.A[m][n];
				}
			}
		}
		else
		{
			invalid_argument e("The 'm,n' of the two matrices are different and cannot be subtracted.");
			throw e;
		}
		return newA;
	}

	void Matrix::operator+=(Matrix &a)
	{
		if (a.mn == mn)
		{
			for (int m = 0; m < mn.m; m++)
			{
				for (int n = 0; n < mn.n; n++)
				{
					A[m][n] += a.A[m][n];
				}
			}
		}
		else
		{
			invalid_argument e("The 'm,n' of the two matrices are different and cannot be added.");
			throw e;
		}
	}

	void Matrix::operator-=(Matrix &a)
	{
		if (a.mn == mn)
		{
			for (int m = 0; m < mn.m; m++)
			{
				for (int n = 0; n < mn.n; n++)
				{
					A[m][n] -= a.A[m][n];
				}
			}
		}
		else
		{
			invalid_argument e("The 'm,n' of the two matrices are different and cannot be subtracted.");
			throw e;
		}
	}

	Matrix Matrix::operator*(const Matrix &a)
	{
		Matrix newA(mn.m, a.mn.n);
		if (mn.n == a.mn.m)
		{
			for (int m = 0; m < mn.m; m++)
			{
				for (int n = 0; n < a.mn.n; n++)
				{
					Fraction sum;
					for (int i = 0; i < mn.n; i++)
					{
						sum += A[m][i] * a.A[i][n];
					}
					newA.A[m][n] = sum;
				}
			}
		}
		else
		{
			invalid_argument e("The 'n' of the left matrix is different from the 'm' of the right and cannot be multiplied.");
			throw e;
		}
		return newA;
	}

	istream &operator>>(istream &input, Matrix &a)
	{
		int m, n;
		cout << endl
			 << "Input m,n of matrix(Separate by space):" << endl;
		input >> m >> n;
		a.Renew(m, n);
		cout << "----------------Input items of matrix----------------" << endl;
		for (m = 0; m < a.mn.m; m++)
		{
			for (n = 0; n < a.mn.n; n++)
			{
				input >> a.A[m][n];
			}
			cout << endl;
		}
		return input;
	}

	ostream &operator<<(ostream &output, Matrix &a)
	{
		for (int m = 0; m < a.mn.m; m++)
		{
			output << endl;
			for (int n = 0; n < a.mn.n; n++)
			{
				output << a.A[m][n] << "\t";
			}
			output << endl;
		}
		return output;
	}
}
