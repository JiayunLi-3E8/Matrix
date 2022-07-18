//@Birth:created by JiayunLi on 2021-06-16
//@Content:分数库，定义分数类型
//@Version:1.0.0
#ifndef _FRACTION_
#define _FRACTION_

#include <iostream>

namespace JoY
{
	// 分数类型
	class Fraction
	{
	public:
		// nmrt:分子，dnmnt:分母
		Fraction(int nmrt = 0, int dnmnt = 1);
		Fraction(double value);
		Fraction operator-();
		Fraction operator~();
		Fraction operator+(const Fraction &fra);
		Fraction operator-(const Fraction &fra);
		Fraction operator*(const Fraction &fra);
		Fraction operator/(const Fraction &fra);
		const Fraction &operator=(const Fraction &fra);
		Fraction operator+=(const Fraction &fra);
		Fraction operator-=(const Fraction &fra);
		Fraction operator*=(const Fraction &fra);
		Fraction operator/=(const Fraction &fra);
		bool operator<(const Fraction &fra);
		bool operator<=(const Fraction &fra);
		bool operator==(const Fraction &fra);
		bool operator!=(const Fraction &fra);
		bool operator>(const Fraction &fra);
		bool operator>=(const Fraction &fra);
		friend std::istream &operator>>(std::istream &input, Fraction &fra);
		friend std::ostream &operator<<(std::ostream &output, Fraction &fra);

	private:
		// nmrt:分子，dnmnt:分母
		int nmrt, dnmnt;
		// 分数化简
		void reduce();
	};
}

#endif