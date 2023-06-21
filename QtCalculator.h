#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtCalculator.h"

class QtCalculator : public QWidget
{
    Q_OBJECT

public:
    QtCalculator(QWidget *parent = nullptr);
    ~QtCalculator();

private:
    Ui::QtCalculatorClass ui;
};
