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
         const char * fxFunctionName = ui->fxName->text().toStdString().c_str();
         const char * dfxFunctionName = ui->dfxName->text().toStdString().c_str();
         if(ui->intervalArithRadioBtn->isChecked()) {
             this->ifx = (ifxFunctionCall)library.resolve(fxFunctionName);
             this->idfx = (ifxFunctionCall)library.resolve(dfxFunctionName);
         }
         else {
             this->fx = (fxFunctionCall)library.resolve(fxFunctionName);
             this->dfx = (fxFunctionCall)library.resolve(dfxFunctionName);
         }
}

void MainWindow::count()
{
    long double result;
    const long double epsConstValue = 1e-16;
    Interval <long double> intervalResult;
    Newton newton;
    QMessageBox Msgbox;
    int maxIterations = ui->maxIterSpinBox->value();
    int iterations = 0;
    int state = 0;
    long double functionValue = 0;
    Interval<long double> intervalFunctionValue(ui->leftXSpinBox->value(),ui->rightXSpinBox->value());
    long double eps = 0;
    if(ui->smallRangeCheckBox->isChecked()) {
        eps = epsConstValue;
    }
    else {
        eps = ui->epsSpinBox->value();
    }
    Interval<long double> ix(0,0);
    if(ui->intervalArithRadioBtn->isChecked()){
        intervalResult = newton.intervalArithmetic(ix, (ifxFunctionCall) this->ifx,
                                             (ifxFunctionCall) this->idfx, maxIterations, eps,
                                             &intervalFunctionValue, &iterations, &state);

        Msgbox.setText("Result is x_: " + QString::number(intervalResult.a, 'g', 16) +
                       "and x: " + QString::number(intervalResult.b, 'g', 16) +
                       "\n state: " + QString::number(state) +
                       " Function Value: " + QString::number(functionValue, 'g', 16) +
                       "Iterations: " + QString::number(iterations));
    }
    else {
        result = newton.normalArithmetic(ui->xValueSpinBox->value(), (fxFunctionCall) this->fx,
                                         (fxFunctionCall) this->dfx, maxIterations, eps,
                                         &functionValue, &iterations, &state);

        Msgbox.setText("Result is x: " + QString::number(result, 'g', 16) +
                       "\n state: " + QString::number(state) +
                       " Function Value: " + QString::number(functionValue, 'g', 16) +
                       "Iterations: " + QString::number(iterations));
    }
    Msgbox.exec();
}
