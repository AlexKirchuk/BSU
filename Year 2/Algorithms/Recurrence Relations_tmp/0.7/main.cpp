/*
Необходимо из заданной числовой последовательности A,
состоящей из n элементов, вычеркнуть минимальное число элементов так,
чтобы оставшиеся элементы образовали строго возрастающую подпоследовательность
элементов. Построенный алгоритм должен иметь трудоёмкость O(n log n).

Note
Возрастание без разрывов подразумевает, что каждый следующий элемент
подпоследовательности строго больше предыдущего.

Input
Первая строка входного файла содержит число n (1 ≤ n ≤ 700 000).
Следующая строка содержит n элементов последовательности A,
которые разделены пробелами (элементы последовательности — целые числа,
не превосходящие по модулю 1 000 000 000).

Output
Выведите одно число — длину строго возрастающей подпоследовательности элементов.
*/

#include <fstream>
#include <vector>

int my_lower_bound(const std::vector<long long>& v, long long x)
{
    long long left = 0, right = v.size(), mid;
    while (left < right)
    {
        mid = (left + right) / 2;
        if (v[mid] < x)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    long long n;
    fin >> n;

    std::vector<long long> x(n);
    for (long long i = 0; i < n; i++)
    {
        fin >> x[i];
    }

    std::vector<long long> f;
    f.reserve(n);

    for (long long i = 0; i < n; i++)
    {
        long long pos = my_lower_bound(f, x[i]);
        if (pos == f.size())
            f.push_back(x[i]);
        else
            f[pos] = x[i];
    }

    fout << f.size();
    return 0;
}