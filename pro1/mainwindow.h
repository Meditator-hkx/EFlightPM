#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "benchmark1.h"
#include "benchmark2.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btngoben1_clicked();

    void on_btngoben2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    BenchMark1 bmw1;
    BenchMark2 bmw2;
};

#endif // MAINWINDOW_H
