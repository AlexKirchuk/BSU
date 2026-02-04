#ifndef LAB8_NUMBER_H
#define LAB8_NUMBER_H

#include <QTextStream>

class Number {
    int num;
public:
    Number();
    explicit Number(int num);
    ~Number();
    static void printTasks();
    void sumCube() const;
    static void pairOf5();
    void dividers() const;
    void pairProd() const;
    void kaprekar();
    friend QTextStream& operator>>(QTextStream& in, Number& P);
    friend QTextStream& operator<<(QTextStream& out, const  Number& P);
};

#endif //LAB8_NUMBER_H