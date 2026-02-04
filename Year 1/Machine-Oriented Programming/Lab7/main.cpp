#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

int uniqueCount(char* str, char* str1)
{
    int unC = -1;
    strcat(str, " ");
    __asm
    {
        xor edx, edx
        mov cl, '\0'
        mov esi, str
        mov al, [esi]
        xor ebx, ebx
        mov edi, str1
    for1:
        cmp al, cl
        je end_
        cld
        movs
        mov bl, [esi]
        cmp bl, al
        je a2
        cmp bl, cl
        je a1
        jmp for1
    a1:
        mov eax, 1
        add unC, eax
    a2:
        add edx, 1
        mov ecx, edx
        mov esi, str
        mov edi, str1
        cld
        rep movs
        mov al, [esi]
        jmp for1
    end_:
    }
    return unC;
}

int main()
{
    const char* sep = ".!?,;:()/ ";
    char str[1000];
    char* word[100];
    char newstr[1000] = "";
    char temp[100], temp1[100];
    int max = 0, count = 1, Un;

    std::cout << "Enter string: ";
    gets_s(str);
    strcat(str, " ");

    word[0] = strtok(str, sep);
    while (true)
    {
        word[count] = strtok(NULL, sep);
        if (word[count] == NULL) break;
        count++;
    }

    for (int i = 0; i < count; i++)
    {
        if (!(i == count - 1))
        {
            strcpy(temp, word[i + 1]);
            strcpy(temp1, word[i]);
            Un = uniqueCount(word[i], word[i]);
            strcpy(word[i + 1], temp);
            strcpy(word[i], temp1);
        }
        else
        {
            strcpy(temp1, word[i]);
            Un = uniqueCount(word[i], word[i]);
            strcpy(word[i], temp1);
        }

        if (Un == max)
        {
            strcat(newstr, " ");
            strcat(newstr, word[i]);
        }
        else if (Un > max)
        {
            max = Un;
            strcpy(newstr, "");
            strcat(newstr, word[i]);
        }
    }

    std::cout << "Result string: " << newstr;
    return 0;
}