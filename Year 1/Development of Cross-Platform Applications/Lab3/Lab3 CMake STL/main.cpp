#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

class MyException : public std::runtime_error
{
public:
    explicit MyException(const std::string& message) : std::runtime_error(message) {}
};

std::vector<std::string> split(const std::string& str)
{
    std::vector<std::string> words;
    const std::regex wordRegex("[^\s.,;!?/() ]+");
    int count = 0;
    std::smatch match;

    while (std::regex_search(str.begin() + count, str.end(), match, wordRegex))
    {
        words.push_back(match.str());
        count += static_cast<int>(match.position() + match.length());
    }

    return words;
}

std::string remove(const std::string& line, const std::vector<std::string>& wordsRemove)
{
    const std::vector<std::string> words = split(line);
    std::vector<std::string> result;

    for (const std::string& word : words)
    {
        if (std::ranges::find(wordsRemove, word) == wordsRemove.end())
        {
            result.push_back(word);
        }
    }

    std::string str;
    for (int i = 0; i < result.size(); i++)
    {
        str += result[i];
        if (i < result.size() - 1) str += " ";
    }
    return str;
}

int main()
{
    std::ifstream fin("Input.txt");
    std::ofstream fout("Output.txt");

    try
    {
        if (!fin.is_open()) {
            std::cout << "Error opening text file" << std::endl;
            return 1;
        }

        std::string firstLine;
        getline(fin, firstLine);
        std::cout << firstLine << std::endl;
        fout << firstLine << std::endl;
        std::vector<std::string> firstWords = split(firstLine);
        std::string line;

        while (getline(fin, line))
        {
            std::string newStr = remove(line, firstWords);
            std::cout << newStr << std::endl;
            fout << newStr << std::endl;
        }

        fin.close();
        fout.close();
    }
    catch (MyException& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // email
    std::cout << std::endl << "Email check:" << std::endl;
    std::regex reg("(https?:\/\/)?([^-_\n][a-zA-Z0-9-][^-_\n]{2,}\.?[^-_\n][a-zA-Z0-9-][^-_\n]{2,}\.[a-zA-Z]{2,})(:[0-9]+)?(\/[^\s]*)?(\\?[^\s]*)?(#[^\s]*)?$");
    std::vector<std::string> URLs =
    {
        "http://www.zcontest.ru",
        "http://zcontest.ru",
        "http://zcontest.com",
        "https://zcontest.ru",
        "https://sub.zcontest-ru.com:8080",
        "http://zcontest.ru/dir%201/dir_2/program.ext?var1=x&var2=my%20value",
        "zcon.com/index.html#bookmark",
        "Just Text.",
        "http://a.com",
        "http://www.domain-.com",
        "https://sub.z_contest-ru.com:8080",
    };
    for (const auto& url : URLs)
    {
        if (std::regex_match(url, reg)) std::cout << "Valid URL: " << url << std::endl;
        else std::cout << "Invalid URL: " << url << std::endl;
    }

    return 0;
}