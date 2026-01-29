#include <iostream>
using namespace std;

void printTasks()
{
	cout << "Task descriptions:" << endl;
	cout << "1. Find the smallest (largest) three-digit number whose sum of the cubes of its digits is equal to a given M." << endl;
	cout << "2. If you multiply two five-digit numbers, you can get the result 123456789. Find these two numbers." << endl;
	cout << "3. Find pairs of natural numbers not exceeding N whose product contains the digits of the larger multiplier separated by zeros. For example, 111*91=10101" << endl;
	cout << "4. Given a number A. Determine whether it is a Kaprekar number. A Kaprekar number for a given numeral system is a non-negative integer whose square in this system can be split into two parts whose sum gives the original number.\n For example, 45 is a Kaprekar number, since 45^2 = 2025 and 20 + 25 = 45. Kaprekar numbers are named after D. R. Kaprekar." << endl;
	cout << "Select the task number you want to work with" << endl;
}

// task 1

void printTask1()
{
	cout << "1. Find the smallest (largest) three-digit number whose sum of the cubes of its digits is equal to a given M." << endl;
	cout << "Enter M, where 0 < M < 2188" << endl;
}

void printRes1(const int min, const int max)
{
	if (min == 0 || max == 0)
	{
		cout << "No such number exists" << endl;
	}
	else
	{
		cout << "Min = " << min << endl;
		cout << "Max = " << max << endl;
	}
}

int work1(const int M)
{
	int min = 0, max = 0;
	for (int i = 1, j = 0, k = 0; i < 10 && j < 10 && k < 10; )
	{
		if (i * i * i + j * j * j + k * k * k == M)
		{
			min = i * 100 + j * 10 + k;
			break;
		}
		else
		{
			k++;
		}
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
	for (int i = 9, j = 9, k = 9; i > 0 && j >= 0 && k >= 0; )
	{
		if (i * i * i + j * j * j + k * k * k == M)
		{
			max = i * 100 + j * 10 + k;
			break;
		}
		else
		{
			k--;
		}
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
	printRes1(min, max);
	return 0;
}

int task1()
{
	printTask1();
	int M;
	cin >> M;
	work1(M);
	return 0;
}

// task 2

void printTask2()
{
	cout << "2. If you multiply two five-digit numbers, you can get the result 123456789. Find these two numbers." << endl;
}

void printRes2(int b, int c)
{
	cout << b << ' ' << c << endl;
}

int work2()
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
					printRes2(b, c);
				}
			}
		}
	}
	return 0;
}

int task2()
{
	printTask2();
	work2();
	return 0;
}

// task 3

void printTask3()
{
	cout << "3. Find pairs of natural numbers not exceeding N whose product contains the digits of the larger multiplier separated by zeros. For example, 111*91=10101" << endl;
	cout << "Enter N" << endl;
}

void printRes3(int n, int k)
{
	cout << n << ' ' << k << endl;
}

int work3(int N)
{
	for (int i = N; i > 0; i--)
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
			if (const int prod = n * k; nWith0 == prod && n >= k)
			{
				printRes3(n, k);
			}
		}
	}
	return 0;
}

int task3()
{
	printTask3();
	int N;
	cin >> N;
	work3(N);
	return 0;
}

// task 4

void printTask4()
{
	cout << "4. Given a number A. Determine whether it is a Kaprekar number. A Kaprekar number for a given numeral system is a non-negative integer whose square in this system can be split into two parts whose sum gives the original number.\n For example, 45 is a Kaprekar number, since 45^2 = 2025 and 20 + 25 = 45. Kaprekar numbers are named after D. R. Kaprekar." << endl;
	cout << "Enter number A" << endl;
}

void printRes4(const bool isIt, const int a)
{

	if (isIt == true)
	{
		cout << "Number " << a << " is a Kaprekar number";
	}
	else
	{
		cout << "Number " << a << " is not a Kaprekar number";
	}
}

int work4(int A)
{
	int s = 1, d = 1;
	bool isIt = false;
	const int a = A;
	A = A * A;
	const int Anew = A;
	while (A / 10 != 0)
	{
		A = A / 10;
		s++;
	}
	for (int i = 1; i <= s; i++)
	{
		d = d * 10;
		const int A1 = Anew / d;
		int A2 = Anew % d;
		if (A2 == 0)
		{
			continue;
		}
		if (const int sum = A1 + A2; a == sum)
		{
			isIt = true;
			break;
		}
	}
	printRes4(isIt, a);
	return 0;
}

int task4()
{
	printTask4();
	int N;
	cin >> N;
	work4(N);
	return 0;
}

// main function

int main()
{
	printTasks();
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
		task1();
		break;
	case 2:
		task2();
		break;
	case 3:
		task3();
		break;
	case 4:
		task4();
		break;
	default:
		cout << "You entered an invalid task number" << endl;
		break;
	}
	return 0;
}