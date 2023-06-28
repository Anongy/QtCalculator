#include <iostream>
#include <cmath>
#include <string>
#include <stack>
#include <deque>
#include "Calculator.h"

using namespace std;

int operatestack::optop() {
	int temp = operatorstack.top();
	return temp;
}

calculate_number operatestack::cnumtop() {
	calculate_number temp = cnumstack.top();
	return temp;
}

bool operatestack::opempty() {
	return operatorstack.empty();
}

bool operatestack::cnumempty() {
	return cnumstack.empty();
}

void operatestack::push(int op) {
	operatorstack.push(op);
}

void operatestack::push(calculate_number cnum) {
	cnumstack.push(cnum);
}

void operatestack::oppop() {
	operatorstack.pop();
}

void operatestack::cnumpop() {
	cnumstack.pop();
}

int operatedeque::optop() {
	int temp = operatordeque.front();
	return temp;
}

calculate_number operatedeque::cnumtop() {
	calculate_number temp = cnumdeque.front();
	return temp;
}

bool operatedeque::opempty() {
	return operatordeque.empty();
}

bool operatedeque::cnumempty() {
	return cnumdeque.empty();
}

void operatedeque::push(int op) {
	operatordeque.push_back(op);
}

void operatedeque::push(calculate_number cnum) {
	cnumdeque.push_back(cnum);
}

void operatedeque::oppop() {
	operatordeque.pop_front();
}

void operatedeque::cnumpop() {
	cnumdeque.pop_front();
}

void operatedeque::opdelete(){
	operatordeque.pop_back();
}

void operatedeque::cnumdelete() {
	cnumdeque.pop_back();
}

void operatedeque::dequeclear() {
	cnumdeque.clear();
	operatordeque.clear();
}