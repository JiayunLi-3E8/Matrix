#include <iostream>
#include <string>
#include "Matrix.h"

using namespace std;

namespace JoY
{
	// -------------------------------> Matrix <-------------------------------
	template<typename T>
	Matrix<T>::Matrix(int m, int n)
	{
		mn.m = m;
		mn.n = n;
		New();
	}

	template<typename T>
	Matrix<T>::Matrix(const Matrix &o)
	{
		mn.m = o.mn.m;
		mn.n = o.mn.n;
		New();
		for (int m = 0; m < mn.m; m++)
		{
			for (int n = 0; n < mn.n; n++)
			{
				A[m][n] = o.A[m][n];
			}
		}
	}

	template<typename T>
	Matrix<T>::~Matrix()
	{
		Del();
		// std::cout << "~" << this << std::endl;
	}

	template<typename T>
	const MN &Matrix<T>::getMN() const
	{
		return mn;
	}

	template<typename T>
	Matrix<T> Matrix<T>::getAT()
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

	template<typename T>
	Matrix<T> Matrix<T>::getLadder()
	{
		Matrix aLadder(mn.m, mn.n);
		aLadder = *this;

		int m = 0, n = 0;
		while (m < aLadder.mn.m)
		{
			while (n < aLadder.mn.n)
			{
				if (aLadder.A[m][n] == 0)
				{
					int i = m + 1;
					while (i < aLadder.mn.m)
					{
						if (aLadder.A[i][n] != 0)
						{
							break;
						}
						i++;
					}
					if (i >= aLadder.mn.m)
					{
						n++;
						continue;
					}
					else
					{
						for (int j = n; j < aLadder.mn.n; j++)
						{
							aLadder.A[m][j] += aLadder.A[i][j];
						}
					}
				}
				for (int i = m + 1; i < aLadder.mn.m; i++)
				{
					for (int j = aLadder.mn.n - 1; j >= n; j--)
					{
						aLadder.A[i][j] -= aLadder.A[i][n] * aLadder.A[m][j] / aLadder.A[m][n];
					}
				}
				n++;
				break;
			}
			if (n >= aLadder.mn.n)
			{
				break;
			}
			else
			{
				m++;
			}
		}

		return aLadder;
	}

	template<typename T>
	Matrix<T> Matrix<T>::getSimplestLine()
	{
		Matrix aSimplestLine = this->getLadder();

		int m = 0, n = 0;
		while (m < aSimplestLine.mn.m)
		{
			while (n < aSimplestLine.mn.n)
			{
				if (aSimplestLine.A[m][n] == 0)
				{
					n++;
					continue;
				}
				if (aSimplestLine.A[m][n] != 1)
				{
					for (int j = aSimplestLine.mn.n - 1; j >= n; j--)
					{
						aSimplestLine.A[m][j] /= aSimplestLine.A[m][n];
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

	template<typename T>
	int Matrix<T>::r()
	{
		Matrix asl = this->getSimplestLine();
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

	template<typename T>
	const Matrix<T> &Matrix<T>::operator=(const Matrix &a)
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

	template<typename T>
	Matrix<T> Matrix<T>::operator+(Matrix &a)
	{
		if (a.mn == mn)
		{
			Matrix newA(mn.m, mn.n);
			for (int m = 0; m < mn.m; m++)
			{
				for (int n = 0; n < mn.n; n++)
				{
					newA.A[m][n] = A[m][n] + a.A[m][n];
				}
			}
			return newA;
		}
		else
		{
			domain_error e("The 'm,n' of the two matrices are different and cannot be added.");
			throw e;
		}
	}

	template<typename T>
	Matrix<T> Matrix<T>::operator-(Matrix &a)
	{
		if (a.mn == mn)
		{
			Matrix newA(mn.m, mn.n);
			for (int m = 0; m < mn.m; m++)
			{
				for (int n = 0; n < mn.n; n++)
				{
					newA.A[m][n] = A[m][n] - a.A[m][n];
				}
			}
			return newA;
		}
		else
		{
			domain_error e("The 'm,n' of the two matrices are different and cannot be subtracted.");
			throw e;
		}
	}

	template<typename T>
	void Matrix<T>::operator+=(Matrix &a)
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
			domain_error e("The 'm,n' of the two matrices are different and cannot be added.");
			throw e;
		}
	}

	template<typename T>
	void Matrix<T>::operator-=(Matrix &a)
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
			domain_error e("The 'm,n' of the two matrices are different and cannot be subtracted.");
			throw e;
		}
	}

	template<typename T>
	Matrix<T> Matrix<T>::operator*(const Matrix &a)
	{
		if (mn.n == a.mn.m)
		{
			Matrix newA(mn.m, a.mn.n);
			for (int m = 0; m < mn.m; m++)
			{
				for (int n = 0; n < a.mn.n; n++)
				{
					for (int i = 0; i < mn.n; i++)
					{
						newA.A[m][n] += A[m][i] * a.A[i][n];
					}
				}
			}
			return newA;
		}
		else
		{
			domain_error e("The 'n' of the left matrix is different from the 'm' of the right and cannot be multiplied.");
			throw e;
		}
	}

	template<typename T>
	Matrix<T> Matrix<T>::operator/(const T &a)
	{
		Matrix newA(mn.m, mn.n);
		for (int m = 0; m < mn.m; m++)
		{
			for (int n = 0; n < mn.n; n++)
			{
				newA.A[m][n] = A[m][n] / a;
			}
		}
		return newA;
	}

	template<typename T>
	Matrix<T> Matrix<T>::operator*(const T &a)
	{
		Matrix newA(mn.m, mn.n);
		for (int m = 0; m < mn.m; m++)
		{
			for (int n = 0; n < mn.n; n++)
			{
				newA.A[m][n] = A[m][n] * a;
			}
		}
		return newA;
	}

	// template<typename T>
	// Matrix<T> operator*(const T &a, const Matrix<T> &A)
	// {
	// 	return A * a;
	// }

	template<typename T>
	istream &operator>>(istream &input, Matrix<T> &a)
	{
		int m, n;
		cout << endl
			<< "Input m,n of the matrix(Separate by space):" << endl;
		input >> m >> n;
		a.Renew(m, n);
		cout << "---------Input items of the matrix---------" << endl;
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

	template<typename T>
	ostream &operator<<(ostream &output, Matrix<T> &a)
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

	template<typename T>
	void Matrix<T>::New()
	{
		A = new T *[mn.m];
		for (int i = 0; i < mn.m; i++)
		{
			A[i] = new T[mn.n];
		}
	}

	template<typename T>
	void Matrix<T>::Del()
	{
		for (int i = 0; i < mn.m; i++)
		{
			delete[] A[i];
		}
		delete[] A;
	}

	template<typename T>
	void Matrix<T>::Renew(int m, int n)
	{
		if (mn.m != m || mn.n != n)
		{
			Del();
			mn.m = m;
			mn.n = n;
			New();
		}
	}

	// -------------------------------> SquareMatrix <-------------------------------
	template<typename T>
	SquareMatrix<T>::SquareMatrix(int n) : Matrix<T>(n, n) {}

	template<typename T>
	SquareMatrix<T>::SquareMatrix(Matrix<T> src)
	{
		*this = src;
	}

	template<typename T>
	const Matrix<T> &SquareMatrix<T>::operator=(const Matrix<T> &a)
	{
		if (a.getMN().m == a.getMN().n)
		{
			Matrix<T> *pp = this;
			return *pp = a;
		}
		else
		{
			domain_error e("The m and n of the source are not equal, so it cannot be defined as a square matrix.");
			throw e;
		}
	}

	template<typename T>
	T SquareMatrix<T>::getDeterminant()
	{
		SquareMatrix ladder = this->getLadder();
		T result = 1;
		for (int i = 0; i < this->mn.n; i++)
		{
			result *= ladder.A[i][i];
		}
		return result;
	}

	template<typename T>
	SquareMatrix<T> SquareMatrix<T>::getComplementarySubmatrix(int mIndex, int nIndex)
	{
		if (this->mn.n >= 2)
		{
			SquareMatrix minor(this->mn.n - 1);
			for (int m = 0; m < minor.mn.m; m++)
			{
				int sm = m;
				if (sm >= mIndex)
				{
					sm++;
				}
				for (int n = 0; n < minor.mn.n; n++)
				{
					int sn = n;
					if (sn >= nIndex)
					{
						sn++;
					}
					minor.A[m][n] = this->A[sm][sn];
				}
			}
			return minor;
		}
		else
		{
			domain_error e("At least a second-order square matrix is required to find the minor.");
			throw e;
		}
	}

	template<typename T>
	T SquareMatrix<T>::getMinor(int mIndex, int nIndex)
	{
		SquareMatrix submatrix = this->getComplementarySubmatrix(mIndex, nIndex);
		return submatrix.getDeterminant();
	}

	template<typename T>
	T SquareMatrix<T>::getCofactor(int mIndex, int nIndex)
	{
		T minor = this->getMinor(mIndex, nIndex);
		int sumMN = mIndex + nIndex + 2;
		if (sumMN % 2)
		{
			return -minor;
		}
		else
		{
			return minor;
		}
	}

	template<typename T>
	SquareMatrix<T> SquareMatrix<T>::getAdjoint()
	{
		SquareMatrix adjoint(this->mn.n);
		for (int m = 0; m < adjoint.mn.m; m++)
		{
			for (int n = 0; n < adjoint.mn.n; n++)
			{
				adjoint.A[n][m] = this->getCofactor(m, n);
			}
		}
		return adjoint;
	}

	template<typename T>
	SquareMatrix<T> SquareMatrix<T>::getInverse()
	{
		T a = this->getDeterminant();
		if (a != 0)
		{
			return this->getAdjoint() / a;
		}
		else
		{
			domain_error e("Non-invertible matrix.");
			throw e;
		}
	}

	template<typename T>
	istream &operator>>(istream &input, SquareMatrix<T> &a)
	{
		int n;
		cout << endl
			<< "Input n of the square matrix:" << endl;
		input >> n;
		a.Renew(n, n);
		cout << "------Input items of the square matrix------" << endl;
		for (int m = 0; m < a.mn.m; m++)
		{
			for (n = 0; n < a.mn.n; n++)
			{
				input >> a.A[m][n];
			}
			cout << endl;
		}
		return input;
	}
}
