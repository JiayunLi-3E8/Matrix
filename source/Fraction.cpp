#include <iostream>
#include <string>
#include "Fraction"

using namespace std;

namespace JoY
{
	Fraction::Fraction(int nmrt, int dnmnt)
	{
		this->nmrt = nmrt;
		this->dnmnt = dnmnt;
	}

	Fraction::Fraction(double value)
	{
		double nmrt = value;
		this->dnmnt = 1;
		while (((int)nmrt) != nmrt)
		{
			nmrt *= 10;
			this->dnmnt *= 10;
		}
		this->nmrt = nmrt;
		this->reduce();
	}

	Fraction Fraction::operator-()
	{
		Fraction newFra(-nmrt, dnmnt);
		return newFra;
	}

	Fraction Fraction::operator~()
	{
		Fraction newFra(dnmnt, nmrt);
		return newFra;
	}

	Fraction Fraction::operator+(const Fraction &fra)
	{
		Fraction newFra;
		newFra.dnmnt = dnmnt * fra.dnmnt;
		newFra.nmrt = nmrt * fra.dnmnt + fra.nmrt * dnmnt;
		newFra.reduce();
		return newFra;
	}

	Fraction Fraction::operator-(const Fraction &fra)
	{
		Fraction newFra;
		newFra.dnmnt = dnmnt * fra.dnmnt;
		newFra.nmrt = nmrt * fra.dnmnt - fra.nmrt * dnmnt;
		newFra.reduce();
		return newFra;
	}

	Fraction Fraction::operator*(const Fraction &fra)
	{
		Fraction newFra;
		newFra.nmrt = nmrt * fra.nmrt;
		newFra.dnmnt = dnmnt * fra.dnmnt;
		newFra.reduce();
		return newFra;
	}

	Fraction Fraction::operator/(const Fraction &fra)
	{
		Fraction newFra;
		newFra.nmrt = nmrt * fra.dnmnt;
		newFra.dnmnt = dnmnt * fra.nmrt;
		newFra.reduce();
		return newFra;
	}

	const Fraction &Fraction::operator=(const Fraction &fra)
	{
		nmrt = fra.nmrt;
		dnmnt = fra.dnmnt;
		return fra;
	}

	Fraction Fraction::operator+=(const Fraction &fra)
	{
		return *this = *this + fra;
	}

	Fraction Fraction::operator-=(const Fraction &fra)
	{
		return *this = *this - fra;
	}

	Fraction Fraction::operator*=(const Fraction &fra)
	{
		return *this = *this * fra;
	}

	Fraction Fraction::operator/=(const Fraction &fra)
	{
		return *this = *this / fra;
	}

	bool Fraction::operator<(const Fraction &fra)
	{
		if (nmrt * fra.dnmnt < fra.nmrt * dnmnt)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Fraction::operator<=(const Fraction &fra)
	{
		if (nmrt * fra.dnmnt <= fra.nmrt * dnmnt)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Fraction::operator==(const Fraction &fra)
	{
		if (nmrt * fra.dnmnt == fra.nmrt * dnmnt)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Fraction::operator!=(const Fraction &fra)
	{
		return !(*this == fra);
	}

	bool Fraction::operator>(const Fraction &fra)
	{
		if (nmrt * fra.dnmnt > fra.nmrt * dnmnt)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Fraction::operator>=(const Fraction &fra)
	{
		if (nmrt * fra.dnmnt >= fra.nmrt * dnmnt)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	istream &operator>>(istream &input, Fraction &fra)
	{
		string s;
		input >> s;
		try
		{
			size_t idx;
			fra.nmrt = stoi(s, &idx);
			fra.dnmnt = 1;
			if (idx < s.length() - 1)
			{
				if (s[idx] == '/')
				{
					fra.dnmnt = stoi(s.substr(idx + 1));
				}
			}
		}
		catch (const invalid_argument &e)
		{
			string se(e.what());
			if (se.find("stoi") != s.npos)
			{
				cout << endl
					 << "非法输入：" << s << endl;
			}
			else
			{
				cout << endl
					 << "错误：" << e.what() << endl;
			}
			exit(-1);
		}
		fra.reduce();
		return input;
	}

	ostream &operator<<(ostream &output, Fraction &fra)
	{
		switch (fra.dnmnt)
		{
		case 0:
			if (fra.nmrt < 0)
			{
				output << "-∞";
			}
			else if (fra.nmrt == 0)
			{
				output << "0/0";
			}
			else
			{
				output << "+∞";
			}
			break;
		case 1:
			output << fra.nmrt;
			break;
		default:
			output << fra.nmrt << "/" << fra.dnmnt;
			break;
		}
		return output;
	}

	void Fraction::reduce()
	{
		if (nmrt == 0)
		{
			dnmnt = 1;
		}
		else
		{
			if (dnmnt < 0)
			{
				nmrt = -nmrt;
				dnmnt = -dnmnt;
			}
			int i = abs(nmrt) < abs(dnmnt) ? abs(nmrt) : abs(dnmnt);
			while (i > 1)
			{
				if (nmrt % i == 0 && dnmnt % i == 0)
				{
					nmrt /= i;
					dnmnt /= i;
					break;
				}
				i--;
			}
		}
	}
}