#include "number.h"
#include <QDebug>

Number::Number()
{
	num = 0;
}

Number::Number(const int num)
{
	this->num = num;
}

Number::~Number() = default;

void Number::printTasks()
{
	qDebug() << Qt::endl;
	qDebug() << "Task conditions:" << Qt::endl;
	qDebug() << "1. Find the smallest (largest) three-digit number whose sum of cubes of digits is equal to the given M." << Qt::endl;
	qDebug() << "2. If you multiply two five-digit numbers, you can get the result 123456789. Find these two numbers." << Qt::endl;
	qDebug() << "2.1. Find the divisors of a number." << Qt::endl;
	qDebug() << "3. Find pairs of natural numbers not exceeding N whose product contains the digits of the larger multiplier separated by zeros. For example, 111 * 91 = 10101." << Qt::endl;
	qDebug() << "4. A number A is given. Determine whether it is a Kaprekar number. A Kaprekar number for a given numeral system is a non-negative integer whose square in this system can be split into two parts whose sum equals the original number.\n For example, 45 is a Kaprekar number because 45^2 = 2025 and 20 + 25 = 45. Kaprekar numbers are named after D. R. Kaprekar." << Qt::endl;
}

void Number::sumCube() const
{
	int min = 0, max = 0;
	for (int i = 1, j = 0, k = 0; i < 10 and j < 10 and k < 10; )
	{
		if (i * i * i + j * j * j + k * k * k == num)
		{
			min = i * 100 + j * 10 + k;
			break;
		}
		k++;
		if (k == 10)
		{
			k = 0;
			j++;
		}
		if (j == 10)
		{
			j = 0;
			i++;
		}
		if (i == 10)
		{
			break;
		}
	}
	for (int i = 9, j = 9, k = 9; i > 0 and j >= 0 and k >= 0; )
	{
		if (i * i * i + j * j * j + k * k * k == num)
		{
			max = i * 100 + j * 10 + k;
			break;
		}
		k--;
		if (k == -1)
		{
			k = 9;
			j--;
		}
		if (j == -1)
		{
			j = 9;
			i--;
		}
		if (i == -1)
		{
			break;
		}
	}
	if (min == 0 || max == 0)
	{
		qDebug() << "No such number" << Qt::endl;
	}
	else
	{
		qDebug() << "Min = " << min << Qt::endl;
		qDebug() << "Max = " << max << Qt::endl;
	}
}

void Number::pairOf5()
{
	constexpr int a = 123456789;
	for (int i = 1; i <= a; i++)
	{
		if (a % i == 0)
		{
			if (const int b = i; b / 10000 > 0 && b / 10000 < 10)
			{
				if (const int c = a / b; c / 10000 > 0 && c / 10000 < 10 && c > b)
				{
					qDebug() << b << " " << c << Qt::endl;
				}
			}
		}
	}
}

void Number::dividers() const
{
	for (int i = 1; i <= num; i++)
	{
		if (num % i == 0)
		{
			qDebug() << i << " ";
		}
	}
	qDebug() << Qt::endl;
}

void Number::pairProd() const
{
	for (int i = num; i > 0; i--)
	{
		int n = i;
		int s = 1, m = 1, nWith0 = 0;
		while (n / 10 != 0)
		{
			n = n / 10;
			s++;
		}
		n = i;
		for (int j = 0; j < s; j++)
		{
			nWith0 = nWith0 + (n % 10) * m;
			n = n / 10;
			m = m * 100;
		}
		n = i;
		for (int k = 0; k <= n; k++)
		{
			int prod = n * k;
			if (nWith0 == prod && n >= k)
			{
				qDebug() << n << " " << k << Qt::endl;
			}
		}
	}
}

void Number::kaprekar()
{
	int s = 1, d = 1;
	int a = num;
	num = num * num;
	int Anew = num;
	while (num / 10 != 0)
	{
		num = num / 10;
		s++;
	}
	for (int i = 1; i <= s; i++)
	{
		d = d * 10;
		const int A1 = Anew / d;
		const int A2 = Anew % d;
		if (A2 == 0)
		{
			continue;
		}
		if (const int sum = A1 + A2; a == sum)
		{
			qDebug() << "The number is a Kaprekar number" << Qt::endl;
			Anew = -1;
			break;
		}
	}
	if (Anew != -1)
	{
		qDebug() << "The number is not a Kaprekar number" << Qt::endl;
	}
}

QTextStream& operator>>(QTextStream& in, Number& n)
{
	qDebug() << "Enter a number: " << Qt::endl;
	in >> n.num;
	return in;
}

QTextStream& operator<<(QTextStream& out, const Number& n)
{
	out << "Number ";
	qDebug() << n.num << Qt::endl;
	return out;
}