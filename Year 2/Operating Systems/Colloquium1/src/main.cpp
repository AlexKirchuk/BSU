#include <factorial.h>
#include <unique.h>
#include <linked_list.h>
#include <iostream>
#include <vector>
#include <limits>

void runFactorialDemo()
{
    std::cout << std::endl << "Task 1: Factorials" << std::endl;
    std::cout << "Enter a natural number n: ";

    int n;
    while (!(std::cin >> n))
    {
        std::cout << "Invalid input. Please enter a natural number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    try
    {
        auto factorials = generateFactorials(n);
        std::cout << "First " << n << " factorials:" << std::endl;
        for (int i = 0; i < factorials.size(); ++i)
            std::cout << (i + 1) << "! = " << factorials[i] << std::endl;
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    catch (const std::overflow_error& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unexpected error." << std::endl;
    }
}

void runUniqueDemo()
{
    std::cout << std::endl << "Task 2: Remove Duplicates" << std::endl;
    std::cout << "Enter integers separated by spaces (end with non-number): ";

    std::vector<int> numbers;
    int value;
    while (std::cin >> value)
        numbers.push_back(value);

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (numbers.empty())
    {
        std::cout << "No valid numbers entered." << std::endl;
        return;
    }

    auto uniqueNumbers = removeDuplicates(numbers);

    std::cout << "Without duplicates: ";
    for (const auto& num : uniqueNumbers)
        std::cout << num << " ";
    std::cout << std::endl;
}

void runLinkedListDemo()
{
    std::cout << "Task 3: Reverse Linked List (Recursion)" << std::endl;
    std::cout << "Enter integers separated by spaces (end with non-number): ";

    std::vector<int> values;
    int val;
    while (std::cin >> val)
        values.push_back(val);

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (values.empty())
    {
        std::cout << "Empty list." << std::endl;
        return;
    }

    auto head = std::make_shared<Node>(values[0]);
    auto current = head;
    for (size_t i = 1; i < values.size(); ++i)
    {
        current->next = std::make_shared<Node>(values[i]);
        current = current->next;
    }

    std::cout << "Original list: ";
    for (auto p = head; p; p = p->next)
        std::cout << p->value << " ";
    std::cout << std::endl;

    auto reversed = reverseList(head);

    std::cout << "Reversed list: ";
    for (auto p = reversed; p; p = p->next)
        std::cout << p->value << " ";
    std::cout << std::endl;
}

int main() {
    std::cout << "=============================" << std::endl;
    std::cout << "Three Tasks" << std::endl;
    std::cout << "=============================" << std::endl;

    bool running = true;
    while (running)
    {
        std::cout << std::endl << "Select task:" << std::endl <<
            "1 - Factorials" << std::endl <<
            "2 - Remove duplicates" << std::endl <<
            "3 - Reverse linked list" << std::endl <<
            "0 - Exit" << std::endl <<
            "Your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            runFactorialDemo();
            break;
        case 2:
            runUniqueDemo();
            break;
        case 3:
            runLinkedListDemo();
            break;
        case 0:
            running = false;
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Unknown option." << std::endl;
            break;
        }
    }

    return 0;
}