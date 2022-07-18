//@Birth:created by JiayunLi on 2021-06-16
//@Content:矩阵库，定义矩阵类型及其运算
//@Version:1.0.0
#ifndef _MATRIX_
#define _MATRIX_

#include <iostream>

namespace JoY
{
	// 定义矩阵的m行和n列
	struct MN
	{
		int m, n;
		bool operator==(const MN &mn) {
			return mn.m == m && mn.n == n;
		}
		bool operator!=(const MN &mn) {
			return !(*this == mn);
		}
	};

	template<typename T>
	class Matrix;
	template<typename T>
	class SquareMatrix;
	// template<typename T>
	// Matrix<T> operator*(const T &a, const Matrix<T> &A);
	template<typename T>
	std::istream &operator>>(std::istream &input, Matrix<T> &a);
	template<typename T>
	std::ostream &operator<<(std::ostream &output, Matrix<T> &a);
	template<typename T>
	std::istream &operator>>(std::istream &input, SquareMatrix<T> &a);

	// 矩阵类
	template<typename T>
	class Matrix
	{
	public:
		// m：行数，n：列数
		explicit Matrix(int m = 3, int n = 3);
		Matrix(const Matrix &o);
		~Matrix();
		// 行列数
		const MN &getMN() const;
		// 矩阵的转置
		Matrix getAT();
		// 阶梯型矩阵
		Matrix getLadder();
		// 矩阵的行最简型
		Matrix getSimplestLine();
		// 矩阵的秩
		int r();
		const Matrix &operator=(const Matrix &a);
		Matrix operator+(Matrix &a);
		Matrix operator-(Matrix &a);
		void operator+=(Matrix &a);
		void operator-=(Matrix &a);
		Matrix operator*(const Matrix &a);
		Matrix operator/(const T &a);
		Matrix operator*(const T &a);
		// friend Matrix<T> operator* <T>(const T &a, const Matrix<T> &A);
		friend std::istream &operator>> <T>(std::istream &input, Matrix<T> &a);
		friend std::ostream &operator<< <T>(std::ostream &output, Matrix<T> &a);

	protected:
		// 行列数
		MN mn;
		// 矩阵单元的二维数组指针
		T **A;
		// 根据行列数动态构造数组
		void New();
		// 释放数组内存
		void Del();
		// 重新构造m行n列的矩阵
		void Renew(int m = 3, int n = 3);
	};

	// 方阵类
	template<typename T>
	class SquareMatrix : public Matrix<T>
	{
	public:
		// n：构造方阵的阶数
		explicit SquareMatrix(int n = 3);
		SquareMatrix(Matrix<T> src);
		const Matrix<T> &operator=(const Matrix<T> &a);
		// 方阵的行列式结果
		T getDeterminant();
		// 对应index(从0开始)位置的余子阵
		SquareMatrix getComplementarySubmatrix(int mIndex, int nIndex);
		// 余子式
		T getMinor(int mIndex, int nIndex);
		// 代数余子式
		T getCofactor(int mIndex, int nIndex);
		// 伴随矩阵
		SquareMatrix getAdjoint();
		// 逆矩阵
		SquareMatrix getInverse();
		friend std::istream &operator>> <T>(std::istream &input, SquareMatrix<T> &a);
	};
}

#endif