#include "number.h"
#include <iostream>

void printTasks()
{
	std::cout << "Task conditions:" << std::endl;
	std::cout << "1. Find the smallest (largest) three-digit number whose sum of cubes of digits is equal to the given M." << std::endl;
	std::cout << "2. If you multiply two five-digit numbers, you can get the result 123456789. Find these two numbers." << std::endl;
	std::cout << "2.1. Find the divisors of a number." << std::endl;
	std::cout << "3. Find pairs of natural numbers not exceeding N whose product contains the digits of the larger multiplier separated by zeros. For example, 111 * 91 = 10101." << std::endl;
	std::cout << "4. A number A is given. Determine whether it is a Kaprekar number. A Kaprekar number for a given numeral system is a non-negative integer whose square in this system can be split into two parts whose sum equals the original number.\n For example, 45 is a Kaprekar number because 45^2 = 2025 and 20 + 25 = 45. Kaprekar numbers are named after D. R. Kaprekar." << std::endl;
}

int main()
{
	printTasks();
	Number num1, num21, num3, num4;
	std::cout << "1. ";
	std::cin >> num1;
	num1.sumCube();
	std::cout << "2. No input required ";
	Number::pairOf5();
	std::cout << "2.1. ";
	std::cin >> num21;
	num21.dividers();
	std::cout << "3. ";
	std::cin >> num3;
	num3.pairProd();
	std::cout << "4. ";
	std::cin >> num4;
	num4.kaprekar();
	return 0;
}