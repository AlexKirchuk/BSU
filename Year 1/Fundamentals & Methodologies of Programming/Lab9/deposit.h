#ifndef LAB9_DEPOSIT_H
#define LAB9_DEPOSIT_H

#include <iostream>

class Deposit
{
	int money, percent;
	double profit;
public:
	Deposit();
	Deposit(int money, int percent);
	Deposit(const Deposit& other);
	~Deposit();
	[[nodiscard]] int getMoney() const;
	[[nodiscard]] int getPercent() const;
	[[nodiscard]] double getProfit() const;
	void setMoney(int yourMoney);
	void setPercent(int yourPercent);
	Deposit operator+(const Deposit& other) const;
	Deposit operator-(const Deposit& other) const;
	Deposit operator*(const Deposit& other) const;
	Deposit operator/(const Deposit& other) const;
	Deposit& operator++();
	Deposit& operator--();
	Deposit& operator=(const Deposit& other);
	bool operator==(const Deposit& other) const;
	bool operator!=(const Deposit& other) const;
	bool operator>(const Deposit& other) const;
	bool operator<(const Deposit& other) const;
	bool operator>=(const Deposit& other) const;
	bool operator<=(const Deposit& other) const;
	[[nodiscard]] double taskEveryDay() const;
	[[nodiscard]] double taskEveryHour() const;
	friend std::istream& operator>>(std::istream& in, Deposit& dep);
	friend std::ostream& operator<<(std::ostream& out, const  Deposit& dep);
};

#endif //LAB9_DEPOSIT_H