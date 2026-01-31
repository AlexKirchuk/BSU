#include "my_array.h"
#include "deposit.h"
#include <iostream>

void Test(int a)
{
	if (a < 1)
	{
		throw a;
	}
}

int main()
{
	int size;
	std::cout << "Enter array size: ";
	std::cin >> size;
	try
	{
		Test(size);
	}
	catch ([[maybe_unused]] const int ex)
	{
		std::cout << "You entered a non-positive number! ERROR!";
	}
	const MyArray arr(size);
	std::cin >> arr;
	arr.shellSort();
	std::cout << arr;

	int money, percent;
	std::cout << "Enter amount of money and percent: ";
	std::cin >> money >> percent;
	try
	{
		Test(money);
		Test(percent);
	}
	catch ([[maybe_unused]] const int ex)
	{
		std::cout << "You entered a non-positive number! ERROR!";
	}
	Deposit dep1, dep2, dep3;
	const Deposit depHours(1, 100);
	const Deposit depDays(1, 100);
	std::cin >> dep1 >> dep2 >> dep3;
	std::cout << dep1 << dep2 << dep3;
	const double profitDays = depDays.taskEveryDay();
	std::cout << "Every day: " << profitDays << std::endl;
	const double profitHours = depHours.taskEveryHour();
	std::cout << "Every hour: " << profitHours << std::endl;
	return 0;
}