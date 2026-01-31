#include "customer.h"
#include <iostream>
#include <fstream>
#include <list>
#include <deque>
#include <stack>

/* ===================== TASK 1: LIST ===================== */

void taskList()
{
    std::list<int> sourceList, resultList;
    int value;

    std::ifstream fin("InputList.txt");
    std::ofstream fout("OutputList.txt");

    if (!fin.is_open())
    {
        std::cout << "Failed to open InputList.txt" << std::endl;
        return;
    }

    while (fin >> value)
    {
        sourceList.push_back(value);
    }

    for (auto i = sourceList.begin(); i != sourceList.end(); ++i)
    {
        bool isDuplicate = false;
        for (auto j = next(i); j != sourceList.end(); ++j)
        {
            if (*i == *j)
            {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate)
        {
            resultList.push_back(*i);
        }
    }

    for (int x : resultList)
    {
        fout << x << " ";
        std::cout << x << " ";
    }

    fin.close();
    fout.close();
}

/* ===================== TASK 2: QUEUE ===================== */

void taskQueue()
{
    int n, m, k, mt, pt;

    do {
        std::cout << "Enter number of initial customers (max 10): ";
        std::cin >> n;
    } while (n <= 0 || n > 10);

    do {
        std::cout << "Enter number of already served customers (<= n): ";
        std::cin >> m;
    } while (m < 0 || m > n);

    do {
        std::cout << "Enter minutes before break (max 10): ";
        std::cin >> k;
    } while (k <= 0 || k > 10);

    do {
        std::cout << "Enter seconds per item: ";
        std::cin >> mt;
    } while (mt <= 0);

    do {
        std::cout << "Enter receipt processing time (seconds): ";
        std::cin >> pt;
    } while (pt <= 0);

    std::deque<Customer> queue;
    Customer customer;

    std::ifstream fin("InputQueue.txt");
    std::ofstream fout("OutputQueue.txt");

    if (!fin.is_open())
    {
        std::cout << "Failed to open InputQueue.txt" << std::endl;
        return;
    }

    for (int i = 0; i < n + k; i++)
    {
        fin >> customer.id >> customer.purchases;
        queue.push_back(customer);
    }

    fin.close();

    int remainingTime = k * 60;

    for (int i = 0; i < m && !queue.empty(); i++)
    {
        queue.pop_front();
    }

    while (!queue.empty())
    {
        int serviceTime = queue.front().purchases * mt + pt;
        remainingTime -= serviceTime;

        if (remainingTime < 0)
        {
            std::cout << "No" << std::endl;
            fout << "No" << std::endl;

            while (!queue.empty())
            {
                std::cout << "Customer #" << queue.front().id
                     << " Purchases: " << queue.front().purchases << std::endl;

                fout << "Customer #" << queue.front().id
                     << " Purchases: " << queue.front().purchases << std::endl;

                queue.pop_front();
            }
            fout.close();
            return;
        }
        queue.pop_front();
    }

    std::cout << "Yes" << std::endl;
    fout << "Yes" << std::endl;
    fout.close();
}

/* ===================== TASK 3: STACK ===================== */

void taskStack()
{
    std::stack<int> sourceStack, resultStack;
    int value;

    std::ifstream fin("InputStack.txt");
    std::ofstream fout("OutputStack.txt");

    if (!fin.is_open())
    {
        std::cout << "Failed to open InputStack.txt" << std::endl;
        return;
    }

    while (fin >> value)
    {
        sourceStack.push(value);
    }

    while (!sourceStack.empty())
    {
        if (sourceStack.top() % 2 == 0)
        {
            resultStack.push(sourceStack.top());
        }
        sourceStack.pop();
    }

    while (!resultStack.empty())
    {
        fout << resultStack.top() << " ";
        std::cout << resultStack.top() << " ";
        resultStack.pop();
    }

    fin.close();
    fout.close();
}

/* ===================== MAIN ===================== */

int main()
{
    std::cout << "Task 1: List processing" << std::endl;
    taskList();

    std::cout << "\nTask 2: Customer queue" << std::endl;
    taskQueue();

    std::cout << "\nTask 3: Stack processing" << std::endl;
    taskStack();

    return 0;
}