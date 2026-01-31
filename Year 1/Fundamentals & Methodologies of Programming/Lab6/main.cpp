#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

// ======================================================
// TASK 1
// Find all words with the maximum number of distinct characters
// ======================================================

bool isSeparator(char c, const string& sep)
{
    return sep.find(c) != string::npos;
}

int countUniqueChars(const string& word)
{
    bool used[256]{};
    int count = 0;
    for (const char c : word)
    {
        if (!used[static_cast<unsigned char>(c)])
        {
            used[static_cast<unsigned char>(c)] = true;
            count++;
        }
    }
    return count;
}

string task1_process(const string& input)
{
    const string separators = ".!?,;:()/ ";
    vector<string> words;
    int i = 0;
    const int n = input.length();

    while (i < n)
    {
        while (i < n && isSeparator(input[i], separators))
            i++;

        int start = i;
        while (i < n && !isSeparator(input[i], separators))
            i++;

        if (start < i)
            words.push_back(input.substr(start, i - start));
    }

    int maxUnique = 0;
    vector<int> uniqueCount(words.size());

    for (size_t size = 0; size < words.size(); size++)
    {
        uniqueCount[size] = countUniqueChars(words[size]);
        if (uniqueCount[size] > maxUnique)
            maxUnique = uniqueCount[size];
    }

    string result;
    for (size_t size = 0; size < words.size(); size++)
    {
        if (uniqueCount[size] == maxUnique)
        {
            result += words[size];
            result += ' ';
        }
    }

    return result;
}

// ======================================================
// TASK 2
// File processing and sorting words by number of digits
// ======================================================

int countDigits(const char* word)
{
    int count = 0;
    for (int i = 0; word[i]; i++)
        if (word[i] >= '0' && word[i] <= '9')
            count++;
    return count;
}

string bubbleSortByDigits(char* line, int digitCount[])
{
    vector<string> words;
    constexpr char sep[] = ".,!?;:() ";
    char* token = strtok(line, sep);

    while (token)
    {
        words.emplace_back(token);
        token = strtok(nullptr, sep);
    }

    const int n = words.size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - 1; j++)
            if (digitCount[j] > digitCount[j + 1])
            {
                swap(digitCount[j], digitCount[j + 1]);
                swap(words[j], words[j + 1]);
            }

    string result;
    for (const auto& w : words)
        result += w + " ";

    return result;
}

void task2_processFiles()
{
    ifstream fin("Input.txt");
    ofstream fout("Output.txt");
    ofstream fsort("Out_sort.txt");

    if (!fin.is_open())
    {
        cout << "Error opening Input.txt file" << endl;
        return;
    }

    char firstLine[100];
    fin.getline(firstLine, 100);
    strcat(firstLine, " ");
    fout << firstLine << endl;

    char sep[] = ".,!?;:() ";

    while (!fin.eof())
    {
        char line[100];
        fin.getline(line, 100);
        strcat(line, " ");

        char temp[100];
        strcpy(temp, line);

        char* word = strtok(firstLine, sep);
        while (word)
        {
            char* pos = strstr(temp, word);
            while (pos)
            {
                char before[100];
                strncpy(before, temp, strlen(temp) - strlen(pos));
                before[strlen(temp) - strlen(pos)] = '\0';

                if (char* after = strpbrk(pos, sep))
                    strcat(before, after);

                strcpy(temp, before);
                pos = strstr(temp, word);
            }
            word = strtok(nullptr, sep);
        }
        fout << temp << endl;
    }

    fin.close();
    fin.open("Input.txt");

    while (!fin.eof())
    {
        char line[100];
        fin.getline(line, 100);
        strcat(line, " ");

        char copy[100];
        strcpy(copy, line);

        int digitCount[100]{};
        char* word = strtok(line, sep);
        int idx = 0;

        while (word)
        {
            digitCount[idx++] = countDigits(word);
            word = strtok(nullptr, sep);
        }

        fsort << bubbleSortByDigits(copy, digitCount) << endl;
    }

    fin.close();
}

// ======================================================
// MAIN
// ======================================================

int main()
{
    setlocale(LC_ALL, "English");

    // ---------- TASK 1 ----------
    cout << "Enter a string:" << endl;
    string input;
    getline(cin, input);

    cout << "Words with the maximum number of distinct characters:" << endl;
    cout << task1_process(input) << endl;

    // ---------- TASK 2 ----------
    task2_processFiles();

    return 0;
}