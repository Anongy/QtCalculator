#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <stack>
#include <deque>

using namespace std;

const long long int MAX_SIG_NUM = 999999999; //�����Ч����
const int MAX_DIGIT = 9; //�����Ч��λ

class calculate_number //��������
{
private:
	string significant_number; //��Ч����,�ַ��ͷ�������߾���
	//"!" ��� //"@"������ //"#"�����Ƿ�����
	int digit; //��λ
	bool minus; //�Ƿ���
public:
	//������������������
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
	//��������ת������,��������calculate_number.cpp�ж���
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

class operatestack //����ջ 
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

class operate_bundle //������,�������䲻ͬ����
{
private:
	//˫Ŀ�����ͳһΪ1~30
	calculate_number add(calculate_number cnum1, calculate_number cnum2); //1
	calculate_number subtract(calculate_number cnum1, calculate_number cnum2); //2
	calculate_number multiply(calculate_number cnum1, calculate_number cnum2); //3
	calculate_number divide(calculate_number cnum1, calculate_number cnum2); //4
	calculate_number mod(calculate_number cnum1, calculate_number cnum2); //5
	//��Ŀ�����ͳһΪ31~60
	calculate_number ssqar(calculate_number cnum1); //31
	calculate_number ssqrt(calculate_number cnum1); //32
	calculate_number minus(calculate_number cnum1); //33
	//�߾��ȼ��㺯���ӿ�
	calculate_number hpadd(calculate_number cnum1, calculate_number cnum2); //11
	calculate_number hpsubtract(calculate_number cnum1, calculate_number cnum2); //12
	calculate_number hpmultiply(calculate_number cnum1, calculate_number cnum2); //13
	calculate_number hpdivide(calculate_number cnum1, calculate_number cnum2); //14
public:
	calculate_number operate(int op,calculate_number cnum1, calculate_number cnum2); //˫Ŀ
	calculate_number operate(int op, calculate_number cnum1); //��Ŀ
	//�������ע��Ϊ������ //�������ŵĲ�����Ϊ98��99 #��־�Ų�����Ϊ0
};

class operatedeque //�ݴ����
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
	int isp[100] = { 0 }; //����������,�����±�Ϊ������,��������Ϊ�������ȼ�,�ڹ��캯���ڶ�
	int icp[100] = { 0 };
	deque<bool> iscnum; //��־��������������
	//�������ŵĲ�����Ϊ98��99 #��־�Ų�����Ϊ0
	operate_bundle operators;
	operatedeque Temp_deque; //�ݴ����
	calculate_number answer = {"0",1,0}; //�������
public:
	Calculator();
	void getop(int op = -1); //��ȡ������(������ͼ�ν���Э��)
	void getcnum(calculate_number cnum = { "",0,0 }); //��ȡ������,ͬ��
	void deletenum(); //���ݴ������ɾ������
	void clearnum(); //���ݴ�������������
	void clearans(); //����������������
	calculate_number Cal_operate(); //������
};