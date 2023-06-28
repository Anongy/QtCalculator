#include <iostream>
#include <string>
#include <sstream>
#include "Calculator.h"

using namespace std;

Calculator::Calculator()
{
	isp[0] = 0; isp[98] = 1; isp[1] = isp[2] = 3; isp[3] = isp[4] = isp[5] = 5; isp[99] = 8;
	icp[0] = 0; icp[98] = 8; icp[1] = icp[2] = 2; icp[3] = icp[4] = icp[5] = 4; icp[99] = 1;
}

void Calculator::getop(int op) 
{
	Temp_deque.push(op);
	iscnum.push_back(false);
}

void Calculator::getcnum(calculate_number cnum)
{
	Temp_deque.push(cnum);
	iscnum.push_back(true);
}

void Calculator::deletenum()
{
	if (iscnum.back()) {
		Temp_deque.cnumdelete();
		iscnum.pop_back();
	}
	else if (!iscnum.back()) {
		Temp_deque.opdelete();
		iscnum.pop_back();
	}
}

void Calculator::clearnum()
{
	Temp_deque.dequeclear();
	iscnum.clear();
}

void Calculator::clearans()
{
	answer = calculate_number("0", 0, 0);
}

calculate_number Calculator::Cal_operate()
{
	deque<bool> operatetype;
	stack<int> Temp1; //后缀表达式转换栈
	operatedeque Tempdeque; //暂存后缀表达式
	stack<calculate_number> Temp2; //计算栈
	Temp_deque.push(0);
	iscnum.push_back(false);
	Temp1.push(0);
	//前缀表达式向后缀表达式的转化
	while (!iscnum.empty()) {
		if (iscnum.front()) {
			operatetype.push_back(true);
			Tempdeque.push(Temp_deque.cnumtop());
			Temp_deque.cnumpop();
		}
		else if (!iscnum.front()) {
			int op = Temp_deque.optop();
			if (op>30&&op<=60) { //单目运算符直接将操作数参与运算后返回 //另一种方法是把单目运算符当特殊括号
				calculate_number temp("0",0,0);
				if (Temp_deque.cnumempty()) {
					temp = operators.operate(op, answer);
					answer = temp;
				}
				else {
					temp = operators.operate(op, Temp_deque.cnumtop());
					answer = temp;
				}
				if (temp.iserror())return temp;
				//Tempdeque.push(temp);
				//operatetype.push_back(true);
				if(!Temp_deque.cnumempty())Temp_deque.cnumpop();
				Temp_deque.oppop();
				Temp_deque.push(temp);
				return temp;
			}
			else if ((op >= 0 && op <= 30)||op==98||op==99) {
				if (icp[op] > isp[Temp1.top()]) {
					Temp1.push(op);
				}
				else if (icp[op] < isp[Temp1.top()]) {
					for (;;)
					{
						if (icp[op] > isp[Temp1.top()]) { Temp1.push(op); break;}
						if ((icp[op] == isp[Temp1.top()])||Temp1.top()==98) { Temp1.pop(); break; }
						Tempdeque.push(Temp1.top());
						Temp1.pop();
						operatetype.push_back(false);
					}
				}
				else if (icp[op] == isp[Temp1.top()]) {
					if (op == 0)break;
					else {
						Temp1.pop();
					}
				}
				Temp_deque.oppop();
			}
			else {
				Temp_deque.oppop();
			}
		}
		iscnum.pop_front();
	}
	//后缀表达式的计算
	Temp2.push(answer);
	while (!operatetype.empty()) {
		if (operatetype.front()) {
			Temp2.push(Tempdeque.cnumtop());
			Tempdeque.cnumpop();
		}
		else if(!operatetype.front()) {
			int op = Tempdeque.optop(); Tempdeque.oppop();
			calculate_number cnum2 = Temp2.top(); Temp2.pop();
			calculate_number cnum1 = Temp2.top(); Temp2.pop();
			answer = operators.operate(op, cnum1, cnum2);
			if (answer.iserror())return answer;
			Temp2.push(answer);
		}
		operatetype.pop_front();
	}
	return answer;
}