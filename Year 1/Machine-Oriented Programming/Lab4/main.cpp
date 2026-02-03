#include <iostream>

// =======================================================
// Common input / output helpers
// =======================================================

int inputSize(int min, int max)
{
    int size;
    do
    {
        std::cout << "Enter number of elements (" << min << " < n <= " << max << "): ";
        std::cin >> size;
    } while (size <= min || size > max);
    return size;
}

void inputArray(int* arr, int size, bool nonDecreasing)
{
    std::cout << "Enter array elements:\n";
    std::cin >> arr[0];
    for (int i = 1; i < size; i++)
    {
        do
        {
            std::cin >> arr[i];
            if (nonDecreasing && arr[i] < arr[i - 1])
                std::cout << "Array must be non-decreasing. Enter again:\n";
        } while (nonDecreasing && arr[i] < arr[i - 1]);
    }
}

void printArray(int* arr, int size)
{
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << "\n";
}

// =======================================================
// Task 1 — Progressions (C++)
// =======================================================

void isArithmeticCpp(int* arr, int n)
{
    if (n <= 2)
    {
        std::cout << "Sequence is stationary\n";
        return;
    }

    int d = arr[1] - arr[0];
    for (int i = 0; i < n - 1; i++)
        if (arr[i + 1] - arr[i] != d)
        {
            std::cout << "Is not an arithmetic progression\n";
            return;
        }

    std::cout << "Is an arithmetic progression\n";
    std::cout << "Difference d = " << d << "\n";
}

void isGeometricCpp(int* arr, int n)
{
    if (n <= 2 || arr[0] == 0)
    {
        std::cout << "Sequence is stationary\n";
        return;
    }

    int q = arr[1] / arr[0];
    for (int i = 0; i < n - 1; i++)
        if (arr[i] == 0 || arr[i + 1] / arr[i] != q)
        {
            std::cout << "Is not a geometric progression\n";
            return;
        }

    std::cout << "Is a geometric progression\n";
    std::cout << "Ratio q = " << q << "\n";
}

// =======================================================
// Task 1 — Progressions (Assembly)
// =======================================================

void isArithmeticAsm(int* arr, int n)
{
    int diff = 0;

    __asm
    {
        mov ecx, n
        dec ecx
        mov esi, arr
        mov edi, [esi + 4]
        sub edi, [esi]
    for_:
        mov ebx, [esi + 4]
        sub ebx, [esi]
        cmp ebx, edi
        jne end_
        add esi, 4
        loop for_
        mov diff, edi
    end_:
    }

    if (diff && n > 2)
    {
        std::cout << "Is an arithmetic progression\n";
        std::cout << "Difference d = " << diff << "\n";
    }
    else
        std::cout << "Is not an arithmetic progression\n";
}

void isGeometricAsm(int* arr, int n)
{
    int ratio = 0;

    __asm
    {
        mov ecx, n
        dec ecx
        mov esi, arr
        mov eax, [esi + 4]
        mov ebx, [esi]
        cdq
        idiv ebx
        mov edi, eax
    for_:
        mov eax, [esi + 4]
        mov ebx, [esi]
        cdq
        idiv ebx
        cmp eax, edi
        jne end_
        add esi, 4
        loop for_
        mov ratio, edi
    end_:
    }

    if (ratio && n > 2)
    {
        std::cout << "Is a geometric progression\n";
        std::cout << "Ratio q = " << ratio << "\n";
    }
    else
        std::cout << "Is not a geometric progression\n";
}

// =======================================================
// Task 2 — Intersection (C++)
// =======================================================

void intersectionCpp(int* x, int n, int* y, int m)
{
    int z[10], p = 0;
    for (int i = 0, j = 0; i < n && j < m; )
    {
        if (x[i] < y[j]) i++;
        else if (x[i] > y[j]) j++;
        else
        {
            z[p++] = x[i];
            i++; j++;
        }
    }

    std::cout << "Intersection:\n";
    if (p == 0)
        std::cout << "Empty set (no common elements)\n";
    else
        printArray(z, p);
}

// =======================================================
// Main
// =======================================================

int main()
{
    // -------- Task 1 --------
    std::cout << "--- Task 1: Progressions ---\n";
    int n = inputSize(0, 100);
    int* arr = new int[n];
    inputArray(arr, n, false);

    std::cout << "\nC++ result:\n";
    isArithmeticCpp(arr, n);
    isGeometricCpp(arr, n);

    std::cout << "\nAssembly result:\n";
    isArithmeticAsm(arr, n);
    isGeometricAsm(arr, n);

    delete[] arr;

    // -------- Task 2 --------
    std::cout << "\n--- Task 2: Array Intersection ---\n";
    int n1 = inputSize(0, 10);
    int x[10];
    inputArray(x, n1, true);

    int n2 = inputSize(0, 10);
    int y[10];
    inputArray(y, n2, true);

    std::cout << "\nC++ result:\n";
    intersectionCpp(x, n1, y, n2);

    std::cout << "\nAssembly result:\n";

    // =======================================================
    // Task 2 — Intersection (Assembly)
    // =======================================================

    int z[10], p = 0;

    __asm
    {
        xor esi, esi
        xor edi, edi
        xor edx, edx
    loopi:
        cmp esi, n1
        jge end
        cmp edi, n2
        jge end
        mov eax, x[esi * 4]
        mov ebx, y[edi * 4]
        cmp eax, ebx
        jl incx
        jg incy
        mov z[edx * 4], eax
        inc edx
        inc esi
        inc edi
        jmp loopi
    incx:
        inc esi
        jmp loopi
    incy:
        inc edi
        jmp loopi
    end:
        mov p, edx
    }

    std::cout << "Intersection:\n";
    if (p == 0)
        std::cout << "Empty set (no common elements)\n";
    else
        printArray(z, p);

    return 0;
}