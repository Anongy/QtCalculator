#include <iostream>
#include <string>
#include <sstream>
#include "Calculator.h"

using namespace std;

calculate_number::calculate_number(long long int t) {
	if (t < 0)minus = true;
	else minus = false;
	ostringstream os;
	os << t;
	significant_number = os.str();
	int i = 0;
	while (t != 0) { t /= 10; i++; }
	digit = i;
}

calculate_number::calculate_number(string t) {
	string temp;
	int i = 0;
	bool flag = true;
	bool pointflag = false;
	digit = 0;
	minus = false;
	if (t[0] == '-')minus = true;
	for (i = 0+minus; i<t.length(); i++)
	{
		if (t[i] == '0' && flag) digit--;
		if (t[i] != '0'&&t[i]!='.')flag = false;
		if (t[i] == '.') {
			digit += i-minus;
			pointflag = true;
			continue;
		}
		if (!flag&&t[i] != '.')temp += t[i];
	}
	int j = 0;
	if (!pointflag)digit += i-minus;
	for (int i = temp.size()-1; i >= digit; i--,j++) {
		if (temp[i] != '0')break;
	}
	for (int i = 0; i < temp.size() - j; i++)
	{
		significant_number += temp[i];
	}
}

calculate_number::calculate_number(double t) {
	ostringstream os;
	os.setf(ios::fixed);
	os.precision(15);
	os << t;
	calculate_number temp(os.str());
	significant_number = temp.significant_number;
	digit = temp.digit;
	minus = temp.minus;
	os.clear();
}

const long long int calculate_number::cnumtoi() {
	long long int temp = 0;
	for (int i = 0; i < 15 && i < digit; i++)
	{
		temp *= 10;
		temp += significant_number[i] - '0';
	}
	if (minus)temp = -temp;
	return temp;
}

const double calculate_number::cnumtod() {
	double temp = 0;
	for (int i = 0; i < 300 && i < significant_number.size(); i++)
	{
		temp *= 10;
		temp += significant_number[i] - '0';
	}
	for (int i = 0; i < significant_number.size()-digit; i++)
	{
		temp /= 10;
	}
	if (minus)temp = -temp;
	return temp;
}

const string calculate_number::cnumtos() {
	string temp;
	if (minus)temp += '-';
	bool flag = true;
	for (int i = digit; i <= 0; i++)
	{
		temp += '0';
		if (flag) { temp += '.'; flag = false; }
	}
	for (int i = 0; i < max((int)significant_number.size(),digit); i++)
	{
		if (i == digit&&digit>0)temp += '.';
		if (i >= significant_number.size())temp += '0';
		else temp += significant_number[i];
	}
	return temp;
}