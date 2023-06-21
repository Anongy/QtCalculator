#include <iostream>
#include <cmath>
#include <string>
#include <stack>
#include <cmath>
#include "Calculator.h"

using namespace std;

calculate_number operate_bundle::operate(int op, calculate_number cnum1, calculate_number cnum2) {
	switch (op) {
	case 1: {
		return add(cnum1, cnum2);
		break;
	}
	case 2:
	{
		return subtract(cnum1, cnum2);
		break;
	}
	case 3:
	{
		return multiply(cnum1, cnum2);
		break;
	}
	case 4:
	{
		return divide(cnum1, cnum2);
		break;
	}
	case 5:
	{
		return mod(cnum1, cnum2);
		break;
	}
	}
}

calculate_number operate_bundle::operate(int op, calculate_number cnum1) {
	switch (op) {
	case 31: 
	{
		return ssqar(cnum1);
		break;
	}
	case 32:
	{
		return ssqrt(cnum1);
		break;
	}
	case 33:
	{
		return minus(cnum1);
		break;
	}
	}
}

calculate_number operate_bundle::add(calculate_number cnum1, calculate_number cnum2){
	return calculate_number(cnum1.cnumtod() + cnum2.cnumtod());
}

calculate_number operate_bundle::subtract(calculate_number cnum1, calculate_number cnum2) {
	return calculate_number(cnum1.cnumtod() - cnum2.cnumtod());
}

calculate_number operate_bundle::multiply(calculate_number cnum1, calculate_number cnum2) {
	if ((cnum1.get_digit() + cnum2.get_digit()) > 300)return calculate_number("!", 0, 0);
	return calculate_number(cnum1.cnumtod() * cnum2.cnumtod());
}

calculate_number operate_bundle::divide(calculate_number cnum1, calculate_number cnum2) {
	if (cnum2.cnumtod() == 0)return calculate_number("@", 0, 0);
	if ((cnum1.get_digit() - cnum2.get_digit()) > 300)return calculate_number("!", 0, 0);
	return calculate_number(cnum1.cnumtod() / cnum2.cnumtod());
}

calculate_number operate_bundle::ssqar(calculate_number cnum1) {
	if ((cnum1.get_digit() + cnum1.get_digit()) > 300)return calculate_number("!", 0, 0);
	return calculate_number(cnum1.cnumtod()* cnum1.cnumtod());
}

calculate_number operate_bundle::ssqrt(calculate_number cnum1) {
	if (cnum1.cnumtod()<0)return calculate_number("#", 0, 0);
	return calculate_number(sqrt(cnum1.cnumtod()));
}

calculate_number operate_bundle::minus(calculate_number cnum1) {
	return calculate_number(cnum1.cnumtod() * (-1));
}

calculate_number operate_bundle::mod(calculate_number cnum1, calculate_number cnum2) {
	if(cnum1.get_digit()!=cnum1.get_sigdigit()|| cnum2.get_digit() != cnum2.get_sigdigit())return calculate_number("#", 0, 0);
	return calculate_number(cnum1.cnumtoi() % cnum2.cnumtoi());
}