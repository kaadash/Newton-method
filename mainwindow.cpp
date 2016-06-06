#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include "newton.h"
#include <string>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->countBtn, SIGNAL(clicked()), this, SLOT(count()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

long double fx(long double x) {
    return x*x - 2;
}

long double dfx(long double x) {
    return 2*x;
}

Interval <long double> ifx(Interval <long double> x) {
    Interval <long double> twoInterval(2, 2);
    return x*x - twoInterval;
}

Interval <long double> idfx(Interval <long double> x) {
    Interval <long double> twoInterval(2, 2);
    return twoInterval*x;
}

void MainWindow::count()
{
    long double result;
    Newton newton;
//    result = newton.test(2, (fxFunctionCall) fx, (fxFunctionCall) dfx);
    int iterations = 0;
    int state = 0;
    long double functionValue = 0;

    result = newton.normalArithmetic(1, (fxFunctionCall) fx,
                                     (fxFunctionCall) dfx, 100, 0.0000001,
                                     &functionValue, &iterations, &state);
    QMessageBox Msgbox;
    float test = 0.012334;
    Msgbox.setText("Result is: " + QString::number(result, 'g', 12));
    Msgbox.exec();
}
