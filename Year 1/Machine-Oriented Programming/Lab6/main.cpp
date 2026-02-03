#include <iostream>
#include <time.h>
#include <iomanip>

void endlOut()
{
    std::cout << std::endl;
}

void printMax()
{
    std::cout << "Maximum number of positive elements is ";
}

void printRows()
{
    std::cout << "Row numbers with the maximum number of positive elements: ";
}

void printNum(int num)
{
    std::cout << num << " ";
}

int inputN(int& n)
{
    do
    {
        std::cout << "Enter number of matrix rows (0 < n <= 100)" << std::endl;
        std::cin >> n;
    } while (n <= 0 || n > 100);
    return n;
}

int inputM(int& m)
{
    do
    {
        std::cout << "Enter number of matrix columns (0 < m <= 100)" << std::endl;
        std::cin >> m;
    } while (m <= 0 || m > 100);
    return m;
}

void randMatrix(int ma[150][150], int n, int m)
{
    srand(0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            ma[i][j] = rand() % 4 - 2;
        }
    }
}

void printMatrix(int ma[150][150], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::cout << std::setw(5) << ma[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void taskCpp(int ma[150][150], int n, int m)
{
    int count[150]{};
    int max = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (ma[i][j] > 0)
            {
                count[i]++;
            }
        }
        if (count[i] > max)
        {
            max = count[i];
        }
    }

    if (max > 0)
    {
        std::cout << "Maximum number of positive elements is " << max << std::endl;
        std::cout << "Row numbers with the maximum number of positive elements: ";
        for (int i = 0; i < n; i++)
        {
            if (count[i] == max)
                std::cout << i + 1 << " ";
        }
    }
    else
    {
        std::cout << "All matrix elements are non-positive";
    }
    std::cout << std::endl;
}

int main()
{
    const int N = 150, M = 150;
    int ma[N][M];
    int n, m;

    inputN(n);
    inputM(m);

    randMatrix(ma, n, m);
    printMatrix(ma, n, m);

    std::cout << "Result in C++:" << std::endl;
    taskCpp(ma, n, m);

    std::cout << std::endl << "Result in Assembler:" << std::endl;

    int count[N]{};

    __asm
    {
        xor esi, esi;
        xor edi, edi;
        xor ebx, ebx;
        mov edx, M;
        imul edx, N;
        imul edx, 4;
        mov ecx, M;
        imul ecx, 4;
        mov eax, M;
        imul eax, 4;
    for_:
        cmp edx, esi;
        je end_;
        cmp eax, esi;
        je a1;
        cmp ma[esi], 0;
        jg a0;
        add esi, 4;
        jmp for_;
    a0:
        add esi, 4;
        inc count[edi];
        jmp for_;
    a1:
        add eax, ecx;
        cmp ebx, count[edi];
        jl a2;
        add edi, 4;
        jmp for_;
    a2:
        mov ebx, count[edi];
        add edi, 4;
        jmp for_;
    end_:
        xor edi, edi;
        call printMax;
        push ebx;
        call printNum;
        pop ebx;
        call endlOut;
        call printRows;
        mov esi, M;
        imul esi, 4;
    for1:
        cmp edi, esi;
        je endend;
        cmp ebx, count[edi];
        jne end1;
        mov eax, edi;
        cdq;
        mov ecx, 4;
        idiv ecx;
        add eax, 1;
        push eax;
        call printNum;
        pop eax;
    end1:
        add edi, 4;
        jmp for1;
    endend:
        call endlOut
    }
    return 0;
}