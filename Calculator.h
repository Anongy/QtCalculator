#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <stack>
#include <deque>

using namespace std;

const long long int MAX_SIG_NUM = 999999999; //最大有效数字
const int MAX_DIGIT = 9; //最大有效数位

class calculate_number //计算数字
{
private:
	string significant_number; //有效数字,字符型方便扩充高精度
	//"!" 溢出 //"@"除以零 //"#"其他非法操作
	int digit; //数位
	bool minus; //是否负数
public:
	//基本构造与析构函数
	calculate_number(string sn, int d, bool m) :significant_number(sn), digit(d), minus(m) {}
	calculate_number(const calculate_number& cnum) {
		significant_number = cnum.significant_number;
		digit = cnum.digit;
		minus = cnum.minus;
	}
	~calculate_number() {}
	calculate_number operator=(const calculate_number& cnum) {
		significant_number = cnum.significant_number;
		digit = cnum.digit;
		minus = cnum.minus;
		return *this;
	}
	// void set_digit(int d) { digit = d; }
	//数据类型转换函数,函数体在calculate_number.cpp中定义
	calculate_number(long long int t);
	calculate_number(string t);
	calculate_number(double t);
	int get_digit() { return digit; }
	int get_sigdigit() { return significant_number.size(); }
	char geterror() { return significant_number[0]; }
	bool iserror() { return significant_number[0] == '!' || significant_number[0] == '@' || significant_number[0] == '#'; }
	const long long int cnumtoi();
	const double cnumtod();
	const string cnumtos();
};

class operatestack //操作栈 
{
private:
	stack<int> operatorstack;
	stack<calculate_number> cnumstack;
public:
	int optop();
	calculate_number cnumtop();
	bool opempty();
	bool cnumempty();
	void oppop();
	void cnumpop();
	void push(int op);
	void push(calculate_number cnum);
};

class operate_bundle //操作包,可以扩充不同运算
{
private:
	//双目运算符统一为1~30
	calculate_number add(calculate_number cnum1, calculate_number cnum2); //1
	calculate_number subtract(calculate_number cnum1, calculate_number cnum2); //2
	calculate_number multiply(calculate_number cnum1, calculate_number cnum2); //3
	calculate_number divide(calculate_number cnum1, calculate_number cnum2); //4
	calculate_number mod(calculate_number cnum1, calculate_number cnum2); //5
	//单目运算符统一为31~60
	calculate_number ssqar(calculate_number cnum1); //31
	calculate_number ssqrt(calculate_number cnum1); //32
	calculate_number minus(calculate_number cnum1); //33
	//高精度计算函数接口
	calculate_number hpadd(calculate_number cnum1, calculate_number cnum2); //11
	calculate_number hpsubtract(calculate_number cnum1, calculate_number cnum2); //12
	calculate_number hpmultiply(calculate_number cnum1, calculate_number cnum2); //13
	calculate_number hpdivide(calculate_number cnum1, calculate_number cnum2); //14
public:
	calculate_number operate(int op,calculate_number cnum1, calculate_number cnum2); //双目
	calculate_number operate(int op, calculate_number cnum1); //单目
	//函数后的注释为操作码 //左右括号的操作码为98与99 #标志号操作码为0
};

class operatedeque //暂存队列
{
private:
	deque<int> operatordeque;
	deque<calculate_number> cnumdeque;
public:
	int optop();
	calculate_number cnumtop();
	bool opempty();
	bool cnumempty();
	void oppop();
	void cnumpop();
	void push(int op);
	void push(calculate_number cnum);
	void opdelete();
	void cnumdelete();
	void dequeclear();
};

class Calculator {
private:
	int isp[100] = { 0 }; //操作码数组,数组下标为操作码,数组内容为操作优先级,在构造函数内定
	int icp[100] = { 0 };
	deque<bool> iscnum; //标志队列中数据类型
	//左右括号的操作码为98与99 #标志号操作码为0
	operate_bundle operators;
	operatedeque Temp_deque; //暂存队列
	calculate_number answer = {"0",1,0}; //操作结果
public:
	Calculator();
	void getop(int op = -1); //获取操作码(方便与图形界面协调)
	void getcnum(calculate_number cnum = { "",0,0 }); //获取操作数,同上
	void deletenum(); //从暂存队列中删除数据
	void clearnum(); //从暂存队列中清空数据
	void clearans(); //清除保存的现有数据
	calculate_number Cal_operate(); //主运算
};