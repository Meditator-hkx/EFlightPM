#ifndef BENCHMARK2_H
#define BENCHMARK2_H

#include <QDialog>
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE
namespace Ui {
class BenchMark2;
}

class BenchMark2 : public QDialog
{
    Q_OBJECT

public:
    explicit BenchMark2(QWidget *parent = 0);
    ~BenchMark2();
    void Result_Draw(double[]);
signals:
    void click_btn_test();


private slots:
    void on_pushButton_clicked();
    void on_btntest_clicked();
    void doWork();


private:
    Ui::BenchMark2 *ui;
    QChart *chart = new QChart();
    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
};

#endif // BENCHMARK2_H
