#ifndef BENCHMARK1_H
#define BENCHMARK1_H

#include <QDialog>
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE
namespace Ui {
class BenchMark1;
}

class BenchMark1 : public QDialog
{
    Q_OBJECT

public:
    explicit BenchMark1(QWidget *parent = 0);
    ~BenchMark1();
    void TestForData();
    void TestForType();
    void Result_Draw(QString,QString,QString);
signals:
    void timeout();
    void changscmprogressbar(int);
    void changdramprogressbar(int);
    void changramdiskprogressbar(int);
    void click_btn_test();

private slots:
    void on_pushButton_clicked();

    void on_btntest_clicked();

    void doWork();

    void on_progressBar_scm_valueChanged(int value);

    void on_progressBar_dram_valueChanged(int value);

    void on_progressBar_ramdisk_valueChanged(int value);

    void processError(QProcess::ProcessError error);
    //void Result_Draw(QString,QString,QString);

private:
    Ui::BenchMark1 *ui;
};

#endif // BENCHMARK1_H
