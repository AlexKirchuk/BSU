#ifndef LAB8_NUMBER_H
#define LAB8_NUMBER_H

#include <iostream>

class Number {
	int num;
public:
	Number();
	explicit Number(int num);
	~Number();
	void sumCube() const;
	static void pairOf5();
	void dividers() const;
	void pairProd() const;
	void kaprekar();
	friend std::istream& operator>>(std::istream& in, Number& P);
	friend std::ostream& operator<<(std::ostream& out, const  Number& P);
};

#endif //LAB8_NUMBER_H