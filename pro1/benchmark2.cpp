#include "benchmark2.h"
#include "ui_benchmark2.h"
#include "QProcess"
#include "qdebug.h"
int flag2;
//QChart *chart = new QChart();
BenchMark2::BenchMark2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BenchMark2)
{
    flag2 = 1;
    ui->setupUi(this);
    connect(this,SIGNAL(click_btn_test()),this,SLOT(on_btntest_clicked()));
}

BenchMark2::~BenchMark2()
{
    delete ui;
}

void BenchMark2::on_pushButton_clicked()
{
    this->close();
}

void BenchMark2::on_btntest_clicked()
{    
    QProcess* pro = new QProcess;
    switch(flag2){
    case 1:{
        pro->start("/home/cx/demo/BDBFirewall/BDBFirewallExampleSCM/RunFirewallExample.sh");
        QTimer::singleShot(1000,this, SLOT(doWork()) );
        break;
    }
    case 2:{
        pro->start("/home/cx/demo/BDBFirewall/BDBFirewallExample/RunFirewallExample.sh");
        QTimer::singleShot(1000,this, SLOT(doWork()) );
        break;
    }
    case 3:{
        pro->start("/home/cx/demo/BDBFirewall/BDBFirewallExampleRAMDISK/RunFirewallExample.sh");
        QTimer::singleShot(1000,this, SLOT(doWork()) );
        break;
    }
    }
}

void BenchMark2::doWork(){
    QFile fileout("firewallout-stage");
    double num[7];

    int lines;
    while(true){
        lines = 0;
        if(!fileout.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug("file open erro");
        }
        QTextStream infile(&fileout);
        while(!infile.atEnd()){
            QString str = infile.readLine();
            lines++;
            //qDebug("%d ",lines);
        }
        fileout.close();
        if(lines == 5)  break;
    }
    lines = 0;
    if(!fileout.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug("file open erro");
    }
    QTextStream infile(&fileout);
    while(!infile.atEnd()){
        QString str = infile.readLine();
        qDebug()<<str;
        QStringList sectionout = str.split(" ");
        qDebug()<<sectionout.at(4);
        num[lines] = sectionout.at(4).toFloat();
        lines++;
    }
    fileout.close();
    qDebug("%f\n",num[1]);
    Result_Draw(num);
    if(flag2 == 1 || flag2 == 2){
        flag2 += 1;
        click_btn_test();
    }
    else if(flag2 == 3){
        flag2 = 1;
    }
}
void BenchMark2::Result_Draw(double num[]){
    QLineSeries *series = new QLineSeries();
    switch(flag2){
    case 1:{
        series->setName("SCM");
        break;
    }
    case 2:{
        series->setName("Dram");
        break;
    }
    case 3:{
        series->setName("RamDisk");
        break;
    }
    }
    *series << QPointF(1, num[0]) << QPointF(2, num[1]) << QPointF(3, num[2]) << QPointF(4, num[3]) << QPointF(5, num[4]);

    chart->addSeries(series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setTitle("每次处理2万数据的时间折线图");
    if(flag2 == 1){
        axisX->setTitleText("数据变化");
        axisX->setTickCount(5);
        //axisX->setLabelFormat("%f");
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        //axisY->setLabelFormat("%g");
        axisY->setTitleText("所用时间");
        //axisY->setBase(8);
        chart->addAxis(axisY, Qt::AlignLeft);
        axisY->setLinePenColor(series->pen().color());
        series->attachAxis(axisY);
    }

    ui->Show->setChart(chart);
    ui->Show->setRenderHint(QPainter::Antialiasing);
    //QChartView *chartView = new QChartView(chart);
    //chartView->setRenderHint(QPainter::Antialiasing);
}
