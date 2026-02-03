#include <iostream>

void printAsmResult(int a)
{
	std::cout << "Assembler result: " << a << std::endl;
}

int main()
{
	int x, y, cppResult, asmResult;
	char operation;

	std::cout << "Enter x ";
	std::cin >> x;

	std::cout << "Enter y ";
	std::cin >> y;

	std::cout << "Enter Operation (+,-,*,/) ";
	std::cin >> operation;

	if (operation == '+')
	{
		cppResult = x + y;
	}
	else if (operation == '-')
	{
		cppResult = x - y;
	}
	else if (operation == '*')
	{
		cppResult = x * y;
	}
	else if (operation == '/')
	{
		cppResult = x / y;
	}
	else
	{
		cppResult = 0;
		std::cout << "Wrong Operation!" << std::endl;
	}
	std::cout << "C++ result: " << cppResult << std::endl;

	__asm
	{
		mov al, '+'
		cmp operation, al
		je a1
		jne a2
	a1: mov ecx, x
		add ecx, y
		mov asmResult, ecx
		jmp end1
	a2: mov al, '-'
		cmp operation, al
		je a3
		jne a4
	a3: mov ecx, x
		sub ecx, y
		mov asmResult, ecx
		jmp end1
	a4: mov al, '*'
		cmp operation, al
		je a5
		jne a6
	a5: mov ecx, x
		mov ebx, y
		imul ecx, ebx
		mov asmResult, ecx
		jmp end1
	a6: mov al, '/'
		cmp operation, al
		je a7
		jne els
	a7: mov eax, x
		mov ecx, y
		cdq
		idiv ecx
		mov asmResult, eax
		jmp end1
	els: xor ecx, ecx
		mov asmResult, ecx
		jmp end1
	end1:
		mov eax, asmResult
		push eax
		call printAsmResult
		pop eax
	}

	return 0;
}