#include <iostream>
#include <bitset>

int removeZeros(int num)
{
    __asm
    {
        mov eax, num
        mov ecx, 1
        mov edi, 2
    a1:
        cmp eax, 0
        je end_
        cdq
        idiv edi
        cmp edx, 0
        je a1
        imul ecx, edi
        jmp a1
    end_:
        sub ecx, 1
        mov num, ecx
    }
    return num;
}

int reverse(int num)
{
    int A[16]{};
    __asm
    {
        mov eax, num
        mov ebx, 1
        mov edi, 2
        xor esi, esi
    a1:
        cmp eax, 0
        je a2
        cdq
        idiv edi
        mov A[esi], edx
        add esi, 4
        jmp a1
    a2:
        sub esi, 4
    a3:
        cmp esi, 0
        jl end_
        mov eax, A[esi]
        imul eax, ebx
        add ecx, eax
        imul ebx, edi
        sub esi, 4
        jmp a3
    end_:
        mov num, ecx
    }
    return num;
}

void palindrome(int num)
{
    if (num == reverse(num))
        std::cout << "Is a palindrome" << std::endl;
    else
        std::cout << "Is not a palindrome" << std::endl;
}

int twoToN(int n)
{
    __asm
    {
        mov esi, 1
        mov ecx, n
    for_:
        imul esi, 2
        loop for_
        mov n, esi
    }
    return n;
}

int main()
{
    int num, n;

    std::cout << "Enter number: ";
    std::cin >> num;

    std::cout << "Input number in binary: "
        << std::bitset<16>(num) << std::endl;

    std::cout << "Binary number without zeros: "
        << std::bitset<16>(removeZeros(num)) << std::endl;

    std::cout << "Reversed binary number: "
        << std::bitset<16>(reverse(num)) << std::endl;

    palindrome(num);

    std::cout << "Enter power: ";
    std::cin >> n;

    std::cout << "2^n = " << twoToN(n) << std::endl;

    return 0;
}