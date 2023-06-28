#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtCalculator.h"
#include "Calculator.h"
#include <QString>
#include <qvector.h>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class QtCalculatorClass; };
QT_END_NAMESPACE

class QtCalculator : public QWidget
{
    Q_OBJECT

public:
    QtCalculator(QWidget *parent = nullptr);
    ~QtCalculator();
    void iniUI();
public slots:
    void Numberbutton_move();
    void Operatebutton_move();
    void Clearbutton_move();
private:
    Ui::QtCalculatorClass *ui;
    bool pointflag = false; //有小数点
    bool willcalculate = false; //将要进行运算
    bool iscalculated = false; //已经按过等号得到答案了
    bool haderror = false; //发生错误
    bool operatelater = false; //处理乘除和加减的优先级问题
    //bool rightbracket = false; //标志右括号
    int unpairednum = 0; //匹配的括号数目,所有括号都闭合时才可以运算
    int preop = 0; //用于处理连按等号
    QString preoprint; //同上
    string downnum = "0";
    Calculator main_calculator;
};
