#include <iostream>

void printResult(int isKapr)
{
    if (isKapr) std::cout << "Является числом Капрекара ";
    else std::cout << "Не является числом Капрекара ";
}

int cppKaprekar(int num)
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

int asmKaprekar(int num)
{
    __asm
    {
        mov edi, 1;
        mov esi, num;
        imul esi, num;
        mov ecx, esi;
    beg_:
        cmp esi, 0;
        je end_;
        imul edi, 10;
        mov eax, ecx;
        cdq;
        idiv edi;
        cmp edx, 0;
        je beg_;
        mov ebx, edx;
        add ebx, eax;
        cmp num, ebx;
        je a1;
        mov ebx, 10;
        mov eax, esi
            cdq;
        idiv ebx;
        mov esi, eax;
        jmp beg_;
    a1:
        mov eax, 1;
        mov num, eax;
        jmp end__;
    end_:
        mov eax, 0;
        mov num, eax;
    end__:
    }
    return num;
}

int main()
{
    std::cout << "Результат на C++: " << std::endl;
    for (int i = 0; i < 1000; i++)
    {
        if (cppKaprekar(i))
        {
            printResult(cppKaprekar(i));
            std::cout << i << std::endl;
        }
    }

    std::cout << std::endl << "Результат на Assembler: " << std::endl;
    for (int i = 0; i < 1000; i++)
    {
        if (asmKaprekar(i))
        {
            printResult(asmKaprekar(i));
            std::cout << i << std::endl;
        }
    }
    return 0;
}