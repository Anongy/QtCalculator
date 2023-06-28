#include "QtCalculator.h"
#include "Calculator.h"
#include <qbuttongroup.h>
#include <qdebug.h>
#include <string>

QtCalculator::QtCalculator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QtCalculatorClass())
{
    ui->setupUi(this);
    ui->lineEditup->setAlignment(Qt::AlignRight);
    ui->lineEditdown->setAlignment(Qt::AlignRight);
    ui->toolButton_answer->setShortcut(Qt::Key_Return);
    iniUI();
}

QtCalculator::~QtCalculator()
{
    delete ui;
}

void QtCalculator::iniUI()
{
    //绑定数字按钮的操作
    connect(ui->toolButton_0, SIGNAL(clicked()), this, SLOT(Numberbutton_move()));
    connect(ui->toolButton_1, SIGNAL(clicked()), this, SLOT(Numberbutton_move()));
    connect(ui->toolButton_2, SIGNAL(clicked()), this, SLOT(Numberbutton_move()));
    connect(ui->toolButton_3, SIGNAL(clicked()), this, SLOT(Numberbutton_move()));
    connect(ui->toolButton_4, SIGNAL(clicked()), this, SLOT(Numberbutton_move()));
    connect(ui->toolButton_5, SIGNAL(clicked()), this, SLOT(Numberbutton_move()));
    connect(ui->toolButton_6, SIGNAL(clicked()), this, SLOT(Numberbutton_move()));
    connect(ui->toolButton_7, SIGNAL(clicked()), this, SLOT(Numberbutton_move()));
    connect(ui->toolButton_8, SIGNAL(clicked()), this, SLOT(Numberbutton_move()));
    connect(ui->toolButton_9, SIGNAL(clicked()), this, SLOT(Numberbutton_move()));
    connect(ui->toolButton_point, SIGNAL(clicked()), this, SLOT(Numberbutton_move()));
    //绑定运算按钮的操作
    connect(ui->toolButton_answer, SIGNAL(clicked()), this, SLOT(Operatebutton_move()));
    connect(ui->toolButton_plus, SIGNAL(clicked()), this, SLOT(Operatebutton_move()));
    connect(ui->toolButton_sub, SIGNAL(clicked()), this, SLOT(Operatebutton_move()));
    connect(ui->toolButton_multi, SIGNAL(clicked()), this, SLOT(Operatebutton_move()));
    connect(ui->toolButton_divide, SIGNAL(clicked()), this, SLOT(Operatebutton_move()));
    connect(ui->toolButton_mod, SIGNAL(clicked()), this, SLOT(Operatebutton_move()));
    connect(ui->toolButton_sqrt, SIGNAL(clicked()), this, SLOT(Operatebutton_move()));
    connect(ui->toolButton_minus, SIGNAL(clicked()), this, SLOT(Operatebutton_move()));
    connect(ui->toolButton_left, SIGNAL(clicked()), this, SLOT(Operatebutton_move()));
    connect(ui->toolButton_right, SIGNAL(clicked()), this, SLOT(Operatebutton_move()));
    //绑定删除等按钮的操作
    connect(ui->toolButton_C, SIGNAL(clicked()), this, SLOT(Clearbutton_move()));
    connect(ui->toolButton_CE, SIGNAL(clicked()), this, SLOT(Clearbutton_move()));
    connect(ui->toolButton_del, SIGNAL(clicked()), this, SLOT(Clearbutton_move()));
}

void QtCalculator::Numberbutton_move()
{
    QToolButton* btn = qobject_cast<QToolButton*>(sender());
    if (!ui->lineEditup->text().isEmpty()) {
        QChar c = *(ui->lineEditup->text().end() - 1);
        if (c.toLatin1() == ' ')return;
    }
    if (haderror) { //错误处理
        ui->lineEditdown->clear();
        ui->lineEditup->clear();
        main_calculator.clearans();
        main_calculator.clearnum();
        downnum.clear();
        haderror = false;
    }
    if (iscalculated) {
        downnum.clear();
        ui->lineEditup->clear();
        ui->lineEditdown->clear();
        main_calculator.clearnum();
        main_calculator.clearans();
        willcalculate = false;
        iscalculated = false;
        preop = 0;
        preoprint.clear();
    }
    if (btn->text() == ".") {
        if (pointflag) {
            return;
        }
        if (downnum.empty()) { //运算后输入数据将清除原来显示的数据
            ui->lineEditdown->clear();
            downnum.clear();
            ui->lineEditdown->insert("0");
            downnum += "0";
        }
        pointflag = true; //保证只有一个小数点
    }
    else {
        if (ui->lineEditdown->text() == "0") { //输入数据清除原始0
            ui->lineEditdown->clear();
            downnum.clear();
        }
        if (downnum.empty()) {
            ui->lineEditdown->clear();
            downnum.clear();
        }
    }
    string temp = btn->text().toStdString();
    downnum += temp;
    ui->lineEditdown->insert(btn->text());
}

void QtCalculator::Operatebutton_move()
{
    pointflag = false;
    QToolButton* btn = qobject_cast<QToolButton*>(sender());
    if (haderror)return; //错误时无法进行操作
    if (btn->text() == "=") {
        bool flag = false; //标志括号
        if (!willcalculate) return; //防止空按等于号
        if (!ui->lineEditup->text().isEmpty()) {
            QChar c = *(ui->lineEditup->text().end() - 1);
            if (c.toLatin1() == ' ')flag = true;
        }
        if (downnum.empty()&&!flag)return; //防止只有运算时候按等号
        // 
        if (iscalculated) main_calculator.getop(preop);
        //
        if(!flag)main_calculator.getcnum(downnum); //操作数入栈
        if(!flag)ui->lineEditup->insert(QString::fromStdString(downnum));
        if (unpairednum != 0) { //按等号时补全所有括号
            for (int i = 0; i < unpairednum; i++)
            {
                main_calculator.getop(99);
                ui->lineEditup->insert(")");
            }
            unpairednum = 0;
            ui->toolButton_left->setText("(");
        }
        calculate_number temp = main_calculator.Cal_operate();
        string stemp = temp.printcnum(haderror);
        ui->lineEditdown->clear();
        ui->lineEditdown->insert(QString::fromStdString(stemp)); //打印结果
        main_calculator.clearnum();
        if (iscalculated) {
            ui->lineEditup->clear();
            ui->lineEditup->insert(QString::fromStdString(stemp));
            ui->lineEditup->insert(preoprint);
            ui->lineEditup->insert(QString::fromStdString(downnum));
            ui->lineEditup->insert(btn->text());
        }
        else ui->lineEditup->insert(btn->text());
        iscalculated = true;
    }else if (btn->text() == "+") {
        if (iscalculated) { //按过等号了就把结果参加运算
            ui->lineEditup->clear();
            ui->lineEditup->insert(ui->lineEditdown->text());
            main_calculator.getop(1);
            preop = 1;
            preoprint = btn->text();
            ui->lineEditup->insert(btn->text());
            downnum.clear();
            iscalculated = false;
        }
        if (downnum.empty()) { //覆盖前一个运算符
            ui->lineEditup->setCursorPosition(ui->lineEditup->cursorPosition() - 1);
            ui->lineEditup->del();
            main_calculator.deletenum();
            main_calculator.getop(1);
            preop = 1;
            preoprint = btn->text();
        }
        if (!willcalculate || unpairednum!=0) { //只有一个数时按下运算符不运算
            willcalculate = true;
            bool flag = false; //标志括号
            if (!ui->lineEditup->text().isEmpty()) {
                QChar c = *(ui->lineEditup->text().end() - 1);
                if (c.toLatin1() == ')')flag = true;
            }
            if(!flag)main_calculator.getcnum(downnum);
            if(!flag)ui->lineEditup->insert(QString::fromStdString(downnum));
            if (!flag)main_calculator.getop(1);
            if (!flag)preop = 1;
            if (!flag)preoprint = btn->text();
            downnum.clear();
            ui->lineEditup->insert(btn->text());
        }
        else if (willcalculate && (!downnum.empty())) { //运算数多时按下运算符直接运算
            operatelater = false;
            main_calculator.getcnum(downnum);
            calculate_number temp = main_calculator.Cal_operate();
            string stemp = temp.printcnum(haderror);
            ui->lineEditdown->clear();
            ui->lineEditdown->insert(QString::fromStdString(stemp));
            ui->lineEditup->insert(QString::fromStdString(downnum));
            main_calculator.getop(1);
            preop = 1;
            preoprint = btn->text();
            downnum.clear();
            ui->lineEditup->insert(btn->text());
        }
        else ui->lineEditup->insert(btn->text()); 
    }else if (btn->text() == "-") {
        if (iscalculated) { //按过等号了就把结果参加运算
            ui->lineEditup->clear();
            ui->lineEditup->insert(ui->lineEditdown->text());
            main_calculator.getop(2);
            preop = 2;
            preoprint = btn->text();
            ui->lineEditup->insert(btn->text());
            downnum.clear();
            iscalculated = false;
        }
        if (downnum.empty()) { //覆盖前一个运算符
            ui->lineEditup->setCursorPosition(ui->lineEditup->cursorPosition() - 1);
            ui->lineEditup->del();
            main_calculator.deletenum();
            main_calculator.getop(2);
            preop = 2;
            preoprint = btn->text();
        }
        if (!willcalculate || unpairednum != 0) { //只有一个数时按下运算符不运算
            willcalculate = true;
            bool flag = false; //标志括号
            if (!ui->lineEditup->text().isEmpty()) {
                QChar c = *(ui->lineEditup->text().end() - 1);
                if (c.toLatin1() == ')')flag = true;
            }
            if (!flag)main_calculator.getcnum(downnum);
            if (!flag)ui->lineEditup->insert(QString::fromStdString(downnum));
            if (!flag)main_calculator.getop(2);
            if (!flag)preop = 2;
            if (!flag)preoprint = btn->text();
            downnum.clear();
            ui->lineEditup->insert(btn->text());
        }
        else if (willcalculate && (!downnum.empty())) { //运算数多时按下运算符直接运算
            operatelater = false;
            main_calculator.getcnum(downnum);
            calculate_number temp = main_calculator.Cal_operate();
            string stemp = temp.printcnum(haderror);
            ui->lineEditdown->clear();
            ui->lineEditdown->insert(QString::fromStdString(stemp));
            ui->lineEditup->insert(QString::fromStdString(downnum));
            main_calculator.getop(2);
            preop = 2;
            preoprint = btn->text();
            downnum.clear();
            ui->lineEditup->insert(btn->text());
        }
        else ui->lineEditup->insert(btn->text());

    }else if (btn->text() == "×") {
        if (iscalculated) { //按过等号了就把结果参加运算
            ui->lineEditup->clear();
            ui->lineEditup->insert(ui->lineEditdown->text());
            main_calculator.getop(3);
            preop = 3;
            preoprint = btn->text();
            ui->lineEditup->insert(btn->text());
            downnum.clear();
            iscalculated = false;
        }
        if (downnum.empty()) { //覆盖前一个运算符
            ui->lineEditup->setCursorPosition(ui->lineEditup->cursorPosition() - 1);
            ui->lineEditup->del();
            main_calculator.deletenum();
            main_calculator.getop(3);
            preop = 3;
            preoprint = btn->text();
        }
        if (preop == 1 || preop == 2) operatelater = true; //处理加减与乘除运算顺序的问题
        if (!willcalculate || operatelater || unpairednum != 0) { //只有一个数时按下运算符不运算
            willcalculate = true;
            bool flag = false; //标志括号
            if (!ui->lineEditup->text().isEmpty()) {
                QChar c = *(ui->lineEditup->text().end() - 1);
                if (c.toLatin1() == ')')flag = true;
            }
            if (!flag)main_calculator.getcnum(downnum);
            if (!flag)ui->lineEditup->insert(QString::fromStdString(downnum));
            if (!flag)main_calculator.getop(3);
            if (!flag)preop = 3;
            if (!flag)preoprint = btn->text();
            downnum.clear();
            ui->lineEditup->insert(btn->text());
        }
        else if (willcalculate && (!downnum.empty())) { //运算数多时按下运算符直接运算
            main_calculator.getcnum(downnum);
            calculate_number temp = main_calculator.Cal_operate();
            string stemp = temp.printcnum(haderror);
            ui->lineEditdown->clear();
            ui->lineEditdown->insert(QString::fromStdString(stemp));
            ui->lineEditup->insert(QString::fromStdString(downnum));
            main_calculator.getop(3);
            preop = 3;
            preoprint = btn->text();
            downnum.clear();
            ui->lineEditup->insert(btn->text());
        }
        else ui->lineEditup->insert(btn->text());

    }else if (btn->text() == "÷") {
        if (iscalculated) { //按过等号了就把结果参加运算
            ui->lineEditup->clear();
            ui->lineEditup->insert(ui->lineEditdown->text());
            main_calculator.getop(4);
            preop = 4;
            preoprint = btn->text();
            ui->lineEditup->insert(btn->text());
            downnum.clear();
            iscalculated = false;
        }
        if (downnum.empty()) { //覆盖前一个运算符
            ui->lineEditup->setCursorPosition(ui->lineEditup->cursorPosition() - 1);
            ui->lineEditup->del();
            main_calculator.deletenum();
            main_calculator.getop(4);
            preop = 4;
            preoprint = btn->text();
        }
        if (preop == 1 || preop == 2) operatelater = true; //处理加减与乘除运算顺序的问题
        if (!willcalculate || operatelater || unpairednum != 0) { //只有一个数时按下运算符不运算
            willcalculate = true;
            bool flag = false; //标志括号
            if (!ui->lineEditup->text().isEmpty()) {
                QChar c = *(ui->lineEditup->text().end() - 1);
                if (c.toLatin1() == ')')flag = true;
            }
            if (!flag)main_calculator.getcnum(downnum);
            if (!flag)ui->lineEditup->insert(QString::fromStdString(downnum));
            if (!flag)main_calculator.getop(4);
            if (!flag)preop = 4;
            if (!flag)preoprint = btn->text();
            downnum.clear();
            ui->lineEditup->insert(btn->text());
        }
        else if (willcalculate && (!downnum.empty())) { //运算数多时按下运算符直接运算
            main_calculator.getcnum(downnum);
            calculate_number temp = main_calculator.Cal_operate();
            string stemp = temp.printcnum(haderror);
            ui->lineEditdown->clear();
            ui->lineEditdown->insert(QString::fromStdString(stemp));
            ui->lineEditup->insert(QString::fromStdString(downnum));
            main_calculator.getop(4);
            preop = 4;
            preoprint = btn->text();
            downnum.clear();
            ui->lineEditup->insert(btn->text());
        }
        else ui->lineEditup->insert(btn->text());

    }else if (btn->text() == "mod") {
        if (iscalculated) { //按过等号了就把结果参加运算
            ui->lineEditup->clear();
            ui->lineEditup->insert(ui->lineEditdown->text());
            main_calculator.getop(5);
            preop = 5;
            preoprint = btn->text();
            ui->lineEditup->insert(btn->text());
            downnum.clear();
            iscalculated = false;
        }
        if (downnum.empty()) { //覆盖前一个运算符
            ui->lineEditup->setCursorPosition(ui->lineEditup->cursorPosition() - 3);
            ui->lineEditup->del();
            ui->lineEditup->del();
            ui->lineEditup->del();
            main_calculator.deletenum();
            main_calculator.getop(5);
            preop = 5;
            preoprint = btn->text();
        }
        if (preop == 1 || preop == 2) operatelater = true; //处理加减与乘除运算顺序的问题
        if (!willcalculate || operatelater || unpairednum != 0) { //只有一个数时按下运算符不运算
            willcalculate = true;
            bool flag = false; //标志括号
            if (!ui->lineEditup->text().isEmpty()) {
                QChar c = *(ui->lineEditup->text().end() - 1);
                if (c.toLatin1() == ')')flag = true;
            }
            if (!flag)main_calculator.getcnum(downnum);
            if (!flag)ui->lineEditup->insert(QString::fromStdString(downnum));
            if (!flag)main_calculator.getop(5);
            if (!flag)preop = 5;
            if (!flag)preoprint = btn->text();
            downnum.clear();
            ui->lineEditup->insert(btn->text());
        }
        else if (willcalculate && (!downnum.empty())) { //运算数多时按下运算符直接运算
            main_calculator.getcnum(downnum);
            calculate_number temp = main_calculator.Cal_operate();
            string stemp = temp.printcnum(haderror);
            ui->lineEditdown->clear();
            ui->lineEditdown->insert(QString::fromStdString(stemp));
            ui->lineEditup->insert(QString::fromStdString(downnum));
            main_calculator.getop(5);
            preop = 5;
            preoprint = btn->text();
            downnum.clear();
            ui->lineEditup->insert(btn->text());
        }
        else ui->lineEditup->insert(btn->text());

    }else if (btn->text() == "√x") { //实现运算结果和单个数字的开方
        if (iscalculated) {
            ui->lineEditup->clear();
            downnum.clear();
            ui->lineEditup->insert("sqrt(");
            ui->lineEditup->insert(ui->lineEditdown->text());
            ui->lineEditup->insert(")");
            main_calculator.clearnum();
            main_calculator.getop(32);
            calculate_number temp = main_calculator.Cal_operate();
            string stemp = temp.printcnum(haderror);
            ui->lineEditdown->clear();
            ui->lineEditdown->insert(QString::fromStdString(stemp));
            main_calculator.clearnum();
        }else if (!willcalculate) {
            ui->lineEditup->clear();
            ui->lineEditup->insert("sqrt(");
            ui->lineEditup->insert(ui->lineEditdown->text());
            ui->lineEditup->insert(")");
            main_calculator.getop(32);
            main_calculator.getcnum(downnum);
            calculate_number temp = main_calculator.Cal_operate();
            string stemp = temp.printcnum(haderror);
            ui->lineEditdown->clear();
            ui->lineEditdown->insert(QString::fromStdString(stemp));
            main_calculator.clearnum();
            iscalculated = true;
        }
        else return;
    }else if (btn->text() == "+/-") { //实现切换运算数正负和按等号后结果的正负
        if (downnum.empty())return;
        else {
            if (iscalculated) {
                main_calculator.getop(3);
                main_calculator.getcnum(double(-1));
                string temp = main_calculator.Cal_operate().cnumtos();
                ui->lineEditdown->clear();
                ui->lineEditdown->insert(QString::fromStdString(temp));
            }
            else {
                if (downnum[0] == '-')downnum.erase(downnum.begin());
                else downnum.insert(downnum.begin(), '-');
                ui->lineEditdown->clear();
                ui->lineEditdown->insert(QString::fromStdString(downnum));
            }
        }
    }else if (btn->objectName() == "toolButton_left") {
        if (!downnum.empty()&&downnum!="0") {
            willcalculate = true;
            main_calculator.getcnum(downnum);
            ui->lineEditup->insert(QString::fromStdString(downnum));
            main_calculator.getop(3);
            preop = 3;
            preoprint = btn->text();
            downnum.clear();
            ui->lineEditup->insert("×");
        }
        ui->lineEditup->insert("(");
        main_calculator.getop(98);
        unpairednum += 1;
        QString temp = "(";
        temp += QString::number(unpairednum);
        ui->toolButton_left->setText(temp);
    }else if (btn->objectName() == "toolButton_right") {
        if (!downnum.empty()) {
            main_calculator.getcnum(downnum);
            downnum.clear();
            ui->lineEditup->insert(ui->lineEditdown->text());
            ui->lineEditdown->clear();
        }
        else return;
        if (unpairednum == 0) { ui->toolButton_left->setText("("); return; }
        ui->lineEditup->insert(") ");
        main_calculator.getop(99);
        main_calculator.getop(-1);
        unpairednum -= 1;
        if (unpairednum == 0) { ui->toolButton_left->setText("("); return; }
        QString temp = "(";
        temp += QString::number(unpairednum);
        ui->toolButton_left->setText(temp);
    }
}

void QtCalculator::Clearbutton_move()
{
    QToolButton* btn = qobject_cast<QToolButton*> (sender());
    if (haderror||iscalculated) {
        ui->lineEditup->clear();
        ui->lineEditdown->clear();
        main_calculator.clearnum();
        main_calculator.clearans();
        pointflag = false;
        willcalculate = false;
        iscalculated = false;
        haderror = false;
        operatelater = false;
        preop = 0;
        preoprint.clear();
        unpairednum = 0;
        ui->toolButton_left->setText("(");
        ui->lineEditdown->insert("0");
        downnum = "0";
        return;
    }
    if (btn->text() == "C") {
        downnum.clear();
        ui->lineEditup->clear();
        ui->lineEditdown->clear();
        main_calculator.clearnum();
        main_calculator.clearans();
        pointflag = false;
        willcalculate = false;
        iscalculated = false;
        haderror = false;
        operatelater = false;
        preop = 0;
        preoprint.clear();
        unpairednum = 0;
        ui->toolButton_left->setText("(");
        ui->lineEditdown->insert("0");
        downnum = "0";
    }
    else if (btn->text() == "CE") {
        downnum.clear();
        ui->lineEditdown->clear();
        pointflag = false;
        ui->lineEditdown->insert("0");
        downnum = "0";
    }
    else if (btn->text() == "del") {
        if (ui->lineEditdown->text() == "0")return;
        ui->lineEditdown->setCursorPosition(ui->lineEditdown->cursorPosition() - 1);
        ui->lineEditdown->del();
        if (!downnum.empty())downnum.pop_back();
        if (downnum.empty()) {
            downnum += '0';
            ui->lineEditdown->insert("0");
        }
    }
}