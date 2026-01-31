#include "number.h"

Number::Number()
{
	num = 0;
}

Number::Number(const int num)
{
	this->num = num;
}

Number::~Number()
{
	std::cout << std::endl << "(Destructor was called)" << std::endl;
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
		std::cout << "No such number" << std::endl;
	}
	else
	{
		std::cout << "Min = " << min << std::endl;
		std::cout << "Max = " << max << std::endl;
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
					std::cout << b << " " << c << std::endl;
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
			std::cout << i << " ";
		}
	}
	std::cout << std::endl;
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
				std::cout << n << " " << k << std::endl;
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
			std::cout << "The number is a Kaprekar number" << std::endl;
			Anew = -1;
			break;
		}
	}
	if (Anew != -1)
	{
		std::cout << "The number is not a Kaprekar number" << std::endl;
	}
}

std::istream& operator>>(std::istream& in, Number& n)
{
	std::cout << "Enter a number: " << std::endl;
	in >> n.num;
	return in;
}

std::ostream& operator<<(std::ostream& out, const Number& n)
{
	out << "Number ";
	std::cout << n.num << std::endl;
	return out;
}