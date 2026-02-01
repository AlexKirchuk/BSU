#include <iostream>
#include <cmath>

const double PI = 3.14;
const double EPS = 0.0005;

// =============================
// Trigonometric functions
// =============================

double mySin(double x)
{
    double sum, term;
    int n = 2;

    while (x >= 2 * PI || x < 0)
    {
        if (x < 0)
            x += 2 * PI;
        else
            x -= 2 * PI;
    }

    sum = term = x;
    while (std::fabs(term) > EPS)
    {
        term = -(term * x * x) / (n * (n + 1));
        sum += term;
        n += 2;
    }
    return sum;
}

double myCos(double x)
{
    double sum, term;
    int n = 1;

    while (x >= 2 * PI || x < 0)
    {
        if (x < 0)
            x += 2 * PI;
        else
            x -= 2 * PI;
    }

    sum = term = 1;
    while (std::fabs(term) > EPS)
    {
        term = -(term * x * x) / (n * (n + 1));
        sum += term;
        n += 2;
    }
    return sum;
}

double myTan(double x)
{
    return mySin(x) / myCos(x);
}

// =============================
// Task 1
// =============================

void task1()
{
    int x, a, b;
    int cppResult, asmResult;

    std::cout << "Enter x: ";
    std::cin >> x;
    std::cout << "Enter a: ";
    std::cin >> a;
    std::cout << "Enter b: ";
    std::cin >> b;

    cppResult = (3 + x * x - 7 * x + 10) / (3 + x * x - 7 * a + b) + x;
    std::cout << "C++ result: " << cppResult << std::endl;

    __asm
    {
        mov ecx, 3
        mov eax, x
        imul x
        add ecx, eax
        mov eax, x
        mov ebx, 7
        imul eax, ebx
        sub ecx, eax
        add ecx, 10
        mov asmResult, ecx

        mov ecx, 3
        mov eax, x
        imul x
        add ecx, eax
        mov eax, a
        mov ebx, 7
        imul eax, ebx
        sub ecx, eax
        add ecx, b
        mov eax, asmResult
        idiv ecx
        add eax, x
        mov asmResult, eax
    }

    std::cout << "Assembler result: " << asmResult << std::endl;
}

// =============================
// Task 2
// =============================

void task2()
{
    int x, y;
    int cppResult, asmResult, temp;
    double numerator, denominator;

    std::cout << "Enter x: ";
    std::cin >> x;
    std::cout << "Enter y: ";
    std::cin >> y;

    cppResult = (1 + sin(x + y) * sin(x + y)) /
        (2 + std::fabs(x - 2 * x / (1 + x * x * y * y))) + x;

    std::cout << "C++ result: " << cppResult << std::endl;

    __asm
    {
        mov eax, x
        add eax, y
        mov temp, eax
    }

    numerator = sin(temp) * sin(temp) + 1;

    __asm
    {
        mov ecx, x
        mov temp, ecx
        mov eax, x
        mov ebx, 2
        imul ebx
        mov ecx, 1
        mov ebx, x
        imul ebx, x
        imul ebx, y
        imul ebx, y
        add ecx, ebx
        idiv ecx
        sub temp, ecx
    }

    denominator = std::fabs(temp) + 2;
    numerator /= denominator;
    numerator += x;

    asmResult = static_cast<int>(numerator);
    std::cout << "Assembler result: " << asmResult << std::endl;
}

// =============================
// Task 3
// =============================

void task3()
{
    int x, temp;
    double cppResult, asmResult;

    std::cout << "Enter x: ";
    std::cin >> x;

    cppResult = myTan(x * x / 4.0 + x / 2.0 + 1);
    std::cout << "C++ result: " << cppResult << std::endl;

    __asm
    {
        mov eax, x
        imul x
        mov ebx, 4
        idiv ebx
        mov ecx, eax
        mov eax, x
        mov ebx, 2
        idiv ebx
        add ecx, eax
        add ecx, 1
        mov temp, ecx
    }

    asmResult = myTan(temp);
    std::cout << "Assembler result: " << asmResult << std::endl;
}

// =============================
// Main
// =============================

int main()
{
    std::setlocale(LC_ALL, "");

    std::cout << "\n--- Task 1 ---\n";
    task1();

    std::cout << "\n--- Task 2 ---\n";
    task2();

    std::cout << "\n--- Task 3 ---\n";
    task3();

    return 0;
}
