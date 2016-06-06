#include "mainwindow.h"
#include <QApplication>
#include <boost/function.hpp>
#include <gmp.h>
#include <mpfr.h>
#include "Interval.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
