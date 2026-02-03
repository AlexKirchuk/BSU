#include <iostream>

void printResult(int isKapr)
{
    if (isKapr) std::cout << "This number is a Kaprekar number: ";
    else std::cout << "This number is not a Kaprekar number: ";
}

int kaprekarCpp(int num)
{
    int sqcopy, sq;
    int d = 1;
    sq = num * num;
    sqcopy = sq;
    while (sq > 0)
    {
        d *= 10;
        if ((sqcopy % d) == 0) continue;
        if (num == (sqcopy / d) + (sqcopy % d))
        {
            return 1;
            sqcopy = -1;
            break;
        }
        sq /= 10;
    }
    if (sqcopy != -1) return 0;
}

int kaprekarAsm(int num)
{
    __asm
    {
        mov edi, 1
        mov esi, num
        imul esi, num
        mov ecx, esi
    beg_:
        cmp esi, 0
        je end_
        imul edi, 10
        mov eax, ecx
        cdq
        idiv edi
        cmp edx, 0
        je beg_
        mov ebx, edx
        add ebx, eax
        cmp num, ebx
        je a1
        mov ebx, 10
        mov eax, esi
        cdq
        idiv ebx
        mov esi, eax
        jmp beg_
    a1:
        mov eax, 1
        mov num, eax
        jmp end__
    end_:
        mov eax, 0
        mov num, eax
    end__:
    }
    return num;
}

int main()
{
    std::cout << "C++ result: " << std::endl;
    for (int i = 0; i < 1000; i++)
    {
        if (kaprekarCpp(i))
        {
            printResult(kaprekarCpp(i));
            std::cout << i << std::endl;
        }
    }

    std::cout << std::endl << "Assembler result: " << std::endl;
    for (int i = 0; i < 1000; i++)
    {
        if (kaprekarAsm(i))
        {
            printResult(kaprekarAsm(i));
            std::cout << i << std::endl;
        }
    }
    return 0;
}