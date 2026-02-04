#include <iostream>
#include <bitset>

extern "C" int sum(int a, int b);
extern "C" int kaprekar(int a);
extern "C" int isArithmetic(int n, int* arr);
extern "C" int isGeometric(int n, int* arr);
extern "C" int removeZeros(int a);
extern "C" int twoToN(int n);

void printRes(int res)
{
	if (res == 1) std::cout << "YES";
	else std::cout << "NO";
}

int main()
{
	int a, b, kapr, size, * arr, num, n;
	std::cout << "Tasks:" << std::endl << "1. Sum of two numbers." << std::endl << "2. Is a Kaprekar number?" << std::endl << "3. Is ar/geom progression?" << std::endl << "4. Remove zeros from a number in binary system." << std::endl << "5. Raise 2 to the nth power." << std::endl << "--------------------------------------------------------------------------------" << std::endl;

	std::cout << "1. Enter two numbers:" << std::endl;
	std::cin >> a >> b;
	std::cout << "Sum: " << sum(a, b) << std::endl << "================================================================================" << std::endl;

	std::cout << "2. Enter number:" << std::endl;
	std::cin >> kapr;
	std::cout << "Kaprekar number?: ";
	printRes(kaprekar(kapr));
	std::cout << std::endl << "================================================================================" << std::endl;

	std::cout << "3. Enter sequence size:" << std::endl;
	std::cin >> size;
	arr = new int[size];
	std::cout << "Enter elements:" << std::endl;
	for (int i = 0; i < size; i++)
	{
		std::cin >> arr[i];
	}
	std::cout << "Is arithmetic?: ";
	printRes(isArithmetic(size, arr));
	std::cout << std::endl << "Is geometric?: ";
	printRes(isGeometric(size, arr));
	std::cout << std::endl << "================================================================================" << std::endl;

	std::cout << "4. Enter number:" << std::endl;
	std::cin >> num;
	std::cout << "Entered number in binary system: " << std::bitset<16>(num) << std::endl << "Entered number without zeros in binary system: " << std::bitset<16>(removeZeros(num)) << std::endl << "================================================================================" << std::endl;

	std::cout << "5. Enter power:" << std::endl;
	std::cin >> n;
	std::cout << "2^" << n << " = " << twoToN(n) << std::endl << "================================================================================" << std::endl;
	return 0;
}