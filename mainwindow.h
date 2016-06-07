#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString getDllFileName();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void count();
    void loadDLL();
};

#endif // MAINWINDOW_H
