#include "deposit.h"

Deposit::Deposit()
{
    money = 0;
    percent = 0;
    profit = 0;
}

Deposit::Deposit(const int money, const int percent)
{
    this->money = money;
    this->percent = percent;
    profit = money * percent / 100.;
}

Deposit::Deposit(const Deposit& other)
{
    this->money = other.money;
    this->percent = other.percent;
    this->profit = other.profit;
}

Deposit::~Deposit()
{
    std::cout << std::endl << "(Destructor called for Deposit class)" << std::endl;
}

int Deposit::getMoney() const
{
    return money;
}

int Deposit::getPercent() const
{
    return percent;
}

double Deposit::getProfit() const
{
    return profit;
}

void Deposit::setMoney(const int yourMoney)
{
    this->money = yourMoney;
}

void Deposit::setPercent(const int yourPercent)
{
    this->percent = yourPercent;
}

Deposit Deposit::operator+(const Deposit& other) const
{
    Deposit temp;
    temp.profit = this->profit + other.profit;
    return temp;
}

Deposit Deposit::operator-(const Deposit& other) const
{
    Deposit temp;
    temp.profit = this->profit - other.profit;
    return temp;
}

Deposit Deposit::operator*(const Deposit& other) const
{
    Deposit temp;
    temp.profit = this->profit * other.profit;
    return temp;
}

Deposit Deposit::operator/(const Deposit& other) const
{
    Deposit temp;
    temp.profit = this->profit / other.profit;
    return temp;
}

Deposit& Deposit::operator++()
{
    this->money++;
    this->profit = this->money * this->percent / 100.;
    return *this;
}

Deposit& Deposit::operator--()
{
    this->money--;
    this->profit = this->money * this->percent / 100.;
    return *this;
}

Deposit& Deposit::operator=(const Deposit& other)
{
    if (this != &other)
    {
        this->money = other.money;
        this->percent = other.percent;
        this->profit = other.profit;
    }
    return *this;
}

bool Deposit::operator==(const Deposit& other) const
{
    return this->profit == other.profit;
}

bool Deposit::operator!=(const Deposit& other) const
{
    return this->profit != other.profit;
}

bool Deposit::operator>(const Deposit& other) const
{
    return this->profit > other.profit;
}

bool Deposit::operator<(const Deposit& other) const
{
    return this->profit < other.profit;
}

bool Deposit::operator>=(const Deposit& other) const
{
    return this->profit >= other.profit;
}

bool Deposit::operator<=(const Deposit& other) const
{
    return this->profit <= other.profit;
}

double Deposit::taskEveryDay() const
{
    double profitDays = money;
    for (int i = 0; i < 365; i++)
    {
        profitDays += profitDays * percent / (365 * 100.);
    }
    return profitDays;
}

double Deposit::taskEveryHour() const
{
    double profitDays = money;
    for (int i = 0; i < 8760; i++)
    {
        profitDays += profitDays * percent / (8760 * 100.);
    }
    return profitDays;
}

std::istream& operator>>(std::istream& in, Deposit& dep)
{
    std::cout << "Enter deposit: " << std::endl;
    in >> dep.money >> dep.percent;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Deposit& dep)
{
    out << "Amount of money: " << dep.money
        << " Annual interest rate: " << dep.percent
        << " Profit: " << dep.profit << std::endl;
    return out;
}