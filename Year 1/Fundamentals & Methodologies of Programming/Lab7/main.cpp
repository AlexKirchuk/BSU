#include "person.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

double Avg(const int mat, const int geo, const int progr)
{
	const double avg = (mat + geo + progr) / 3.;
	return avg;
}

double OverallAvg(const vector <Person>& stud, const int count)
{
	double sum = 0;
	const double countDouble = count;
	for (int i = 0; i < count; i++)
	{
		sum += stud[i].avg;
	}
	const double overall = sum / countDouble;
	return overall;
}

void Swap(Person& stud1, Person& stud2)
{
	const string tempStr = stud1.surname;
	stud1.surname = stud2.surname;
	stud2.surname = tempStr;

	int temp = stud1.group;
	stud1.group = stud2.group;
	stud2.group = temp;

	temp = stud1.number;
	stud1.number = stud2.number;
	stud2.number = temp;

	temp = stud1.mat;
	stud1.mat = stud2.mat;
	stud2.mat = temp;

	temp = stud1.geo;
	stud1.geo = stud2.geo;
	stud2.geo = temp;

	temp = stud1.progr;
	stud1.progr = stud2.progr;
	stud2.progr = temp;

	const double tempAvg = stud1.avg;
	stud1.avg = stud2.avg;
	stud2.avg = tempAvg;
}

void Sort(vector <Person>& stud, const int count)
{
	Person temp;
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count - 1; j++)
		{
			if (stud[j].group > stud[j + 1].group) Swap(stud[j], stud[j + 1]);
		}
	}
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count - 1; j++)
		{
			if (stud[j].group == stud[j + 1].group && stud[j].surname > stud[j + 1].surname) Swap(stud[j], stud[j + 1]);
		}
	}
}

int main()
{
	string str1;
	vector <string> str(100);
	vector <Person> stud(100);
	ifstream fin;
	fin.open("Input.txt");
	if (!fin.is_open())  cout << "Error opening Input.txt file" << endl;
	else
	{
		ofstream fn, fo, fall;
		double overall;
		int count = 0;
		while (!fin.eof())
		{
			getline(fin, str[count]);
			count++;
		}
		fin.close();
		fin.open("Input.txt");
		for (int i = 0; i < count; i++) // write to variable
		{
			fin >> stud[i].surname >> stud[i].group >> stud[i].number >> stud[i].mat >> stud[i].geo >> stud[i].progr;
			stud[i].avg = Avg(stud[i].mat, stud[i].geo, stud[i].progr);
		}
		fin.close();

		overall = OverallAvg(stud, count);

		cout << "Overall average grade: " << overall << endl;
		for (int i = 0; i < count; i++) cout << ' ' << stud[i].surname << ' ' << stud[i].group << ' ' << stud[i].number << ' ' << stud[i].avg << endl;

		Sort(stud, count);

		cout << "Sorted list: " << endl;
		for (int i = 0; i < count; i++) cout << ' ' << stud[i].surname << ' ' << stud[i].group << ' ' << stud[i].number << ' ' << stud[i].avg << endl;
		cout << "List of excellent students: " << endl;
		for (int i = 0; i < count; i++)
		{
			if (stud[i].avg == 5) cout << ' ' << stud[i].surname << ' ' << stud[i].group << ' ' << stud[i].number << endl;
		}
		cout << "List of students with unsatisfactory grades: " << endl;
		for (int i = 0; i < count; i++)
		{
			if (stud[i].mat < 4 || stud[i].geo < 4 || stud[i].progr < 4) cout << ' ' << stud[i].surname << ' ' << stud[i].group << ' ' << stud[i].number << endl;
		}

		fall.open("OutAll.bin");
		fo.open("OutO.bin");
		fn.open("OutN.bin");
		fall << "Overall average grade: " << overall << endl << "Sorted list: " << endl;
		for (int i = 0; i < count; i++) fall << ' ' << stud[i].surname << ' ' << stud[i].group << ' ' << stud[i].number << ' ' << stud[i].avg << endl;
		fo << "List of excellent students: " << endl;
		for (int i = 0; i < count; i++)
		{
			if (stud[i].avg == 5) fo << ' ' << stud[i].surname << ' ' << stud[i].group << ' ' << stud[i].number << endl;
		}
		fn << "List of students with unsatisfactory grades: " << endl;
		for (int i = 0; i < count; i++)
		{
			if (stud[i].mat < 4 || stud[i].geo < 4 || stud[i].progr < 4) fn << ' ' << stud[i].surname << ' ' << stud[i].group << ' ' << stud[i].number << endl;
		}
		fall.close();
		fo.close();
		fn.close();

		fall.open("OutAll.txt");
		fo.open("OutO.txt");
		fn.open("OutN.txt");
		fall << "Overall average grade: " << overall << endl << "Sorted list: " << endl;
		for (int i = 0; i < count; i++) fall << ' ' << stud[i].surname << ' ' << stud[i].group << ' ' << stud[i].number << ' ' << stud[i].avg << endl;
		fo << "List of excellent students: " << endl;
		for (int i = 0; i < count; i++)
		{
			if (stud[i].avg == 5) fo << ' ' << stud[i].surname << ' ' << stud[i].group << ' ' << stud[i].number << endl;
		}
		fn << "List of students with unsatisfactory grades: " << endl;
		for (int i = 0; i < count; i++)
		{
			if (stud[i].mat < 4 || stud[i].geo < 4 || stud[i].progr < 4) fn << ' ' << stud[i].surname << ' ' << stud[i].group << ' ' << stud[i].number << endl;
		}
		fall.close();
		fo.close();
		fn.close();
	}
	return 0;
}