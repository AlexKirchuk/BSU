#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double e = 0.0005;
constexpr double pi = 3.141592;

// Custom sine function
double Sin(double y)
{
	double sumSin;
	int n = 2;
	// Remove the period
	while ((y >= 2 * pi) || (y < 0))
	{
		if (y < 0) y = y + 2 * pi;
		else y = y - 2 * pi;
	}
	double seqMemberSin = sumSin = y;
	// Continue until a given accuracy is reached
	while (fabs(seqMemberSin) > e)
	{
		// As mentioned in the algorithm idea, each term of the series is obtained from the previous one and added to the sum
		seqMemberSin = -(seqMemberSin * y * y) / (n * (n + 1));
		sumSin += seqMemberSin;
		n += 2;
	}
	return sumSin;
}

// Here we calculate the value of the series
double SeriesSin(const double x, const int m)
{
	double sum = 0, seqMember = 0;
	int n = 5;
	// Assign x to the 9th power
	double pow = x * x * x * x * x * x * x * x * x;
	while (m >= n)
	{
		// Variable pow is used to compute x to the power of 2n + 1
		pow = pow * x * x;
		seqMember = (pow * Sin(n * x)) / (2 * n + 1);
		sum += seqMember;
		n++;
	}
	return sum;
}

// The same series, but using the built-in sine function from <math.h>
double seriesSin(const double x, const int m)
{
	double sum = 0, seqMember = 0;
	int n = 5;
	double pow = x * x * x * x * x * x * x * x * x;
	while (m >= n)
	{
		pow = pow * x * x;
		seqMember = (pow * sin(n * x)) / (2 * n + 1);
		sum += seqMember;
		n++;
	}
	return sum;
}

int main()
{
	int a, b, h, m;
	cout << "Enter the lower bound a: ";
	cin >> a;
	do
	{
		cout << "Enter the upper bound b (b > a): ";
		cin >> b;
	} while (b <= a);
	do
	{
		cout << "Enter the step h (h > 0): ";
		cin >> h;
	} while (h <= 0);
	do
	{
		cout << "Enter the upper limit of summation m (m > 5): ";
		cin >> m;
	} while (m <= 5);
	// On the left using the custom sine function, on the right — the built-in one from <math.h>
	cout << "------------------------------------------------------" << endl;
	cout << "|" << setw(5) << "x" << "|" << setw(23) << "Using  Sin(x)" << "|" << setw(22) << "Using sin(x)" << "|" << endl;
	cout << "------------------------------------------------------" << endl;
	for (double x = a; x <= b; x += h)
	{
		cout << "|" << setw(5) << x << "|" << setw(23) << SeriesSin(x, m) << "|" << setw(22) << seriesSin(x, m) << "|" << endl;
	}
	cout << "------------------------------------------------------";
	return 0;
}