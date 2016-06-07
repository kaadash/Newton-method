#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QLibrary>
#include <QDebug>
#include "newton.h"
#include <string>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->countBtn, SIGNAL(clicked()), this, SLOT(count()));
    connect(ui->loadDLLBtn, SIGNAL(clicked()), this, SLOT(loadDLL()));
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

QString MainWindow::getDllFileName() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open DLL File"),
                                                    "/home/kadash/Prace/EAN",
                                                    tr("DLL Files (*.so)"));
    return fileName;
}


void MainWindow::loadDLL() {
    QString fileName = this->getDllFileName();
    qDebug() << fileName;
    QLibrary library(fileName);
    if (!library.load())
     qDebug() << library.errorString();
         if (library.load())
            qDebug() << "library loaded";
     fxFunctionCall function = (fxFunctionCall)library.resolve("fx");
     if (function) {
        qDebug() << (double)function(100) << " << wynik";
     } else {
      qDebug() << "Could not show widget from the loaded library";
     }
}

void MainWindow::count()
{
    long double result;
    Newton newton;
//    result = newton.test(2, (fxFunctionCall) fx, (fxFunctionCall) dfx);
    int iterations = 0;
    int state = 0;
    long double functionValue = 0;
    Interval<long double> intervalFunctionValue(0,0);
    const long double eps = 1e-16;
    Interval<long double> ix(1,1);
    /*
    result = newton.normalArithmetic(1, (fxFunctionCall) fx,
                                     (fxFunctionCall) dfx, 100, eps,
                                     &functionValue, &iterations, &state);*/

    result = newton.intervalArithmetic(ix, (ifxFunctionCall) ifx,
                                         (ifxFunctionCall) idfx, 100, eps,
                                         &intervalFunctionValue, &iterations, &state).a;
    QMessageBox Msgbox;
    Msgbox.setText("Result is x: " + QString::number(result, 'g', 16)
                   + "\n state: " + QString::number(state) +
                   " Function Value: " + QString::number(intervalFunctionValue.a, 'g', 16)
                   + "Iterations: " + QString::number(iterations));
    Msgbox.exec();
}
