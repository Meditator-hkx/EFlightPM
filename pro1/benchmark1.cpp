#include "benchmark1.h"
#include "ui_benchmark1.h"
#include "QProcess"
#include "qdebug.h"
#include <QtCore/qmath.h>

# define BENCH1_SMALL_DIR "/home/hhx008/Downloads/pseudoDEMO/bench1-small.sh"
# define BENCH1_MIDDLE_DIR "/home/hhx008/Downloads/pseudoDEMO/bench1-middle.sh"
# define BENCH1_BIG_DIR "/home/hhx008/Downloads/pseudoDEMO/bench1-big.sh"
# define BENCH2_SMALL_DIR "/home/hhx008/Downloads/pseudoDEMO/bench2-small.sh"
# define BENCH2_MIDDLE_DIR "/home/hhx008/Downloads/pseudoDEMO/bench2-middle.sh"
# define BENCH2_BIG_DIR "/home/hhx008/Downloads/pseudoDEMO/bench2-big.sh"

# define BENCH_STAGE_FAST "/home/hhx008/Downloads/pseudoDEMO/bench-stage1"
# define BENCH_STAGE_MIDDLE "/home/hhx008/Downloads/pseudoDEMO/bench-stage2"
# define BENCH_STAGE_SLOW "/home/hhx008/Downloads/pseudoDEMO/bench-stage3"

int testdataflag;
int testtypeflag;
int flag;
BenchMark1::BenchMark1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BenchMark1)
{
    testdataflag = 1;
    testtypeflag = 1;

    ui->setupUi(this);
    connect(this,SIGNAL(click_btn_test()),this,SLOT(on_btntest_clicked()));
}

BenchMark1::~BenchMark1()
{
    delete ui;
}

void BenchMark1::on_pushButton_clicked()
{
    this->close();
}

void BenchMark1::on_btntest_clicked()
{
//    if(ui->graph_1->chart()->series().length() != 0 && ui->graph_2->chart()->series().length() != 0 && ui->graph_3->chart()->series().length() != 0){
//        qDebug()<<"test";
//        ui->graph_1->chart()->series().erase(ui->graph_1->chart()->series().at(0));
//        ui->graph_1->chart()->series().erase(ui->graph_1->chart()->series().at(1));
//        ui->graph_1->chart()->series().erase(ui->graph_1->chart()->series().at(2));
//        ui->graph_2->chart()->series().erase(ui->graph_1->chart()->series().at(0));
//        ui->graph_2->chart()->series().erase(ui->graph_1->chart()->series().at(1));
//        ui->graph_2->chart()->series().erase(ui->graph_1->chart()->series().at(2));
//        ui->graph_3->chart()->series().erase(ui->graph_1->chart()->series().at(0));
//        ui->graph_3->chart()->series().erase(ui->graph_1->chart()->series().at(1));
//        ui->graph_3->chart()->series().erase(ui->graph_1->chart()->series().at(2));
//    }
    if(ui->radioButtonData->isChecked()){
        TestForData();
    }
    else if(ui->radioButtonType->isChecked()){
        TestForType();
    }
}
void BenchMark1::TestForData(){
    flag = 1;
    QProcess *prorun = new QProcess;
    QStringList args;
    connect(prorun, SIGNAL(error(QProcess::ProcessError)), this, SLOT(processError (QProcess::ProcessError)));
    // qDebug("Aha: %d\n",testdataflag);
    switch(testdataflag){
    case 1:{
        args << BENCH1_SMALL_DIR;
        prorun->start("sh", args);
        ui->textBrowser_input->setFontPointSize(16);
        ui->textBrowser_input->setText("程序正在运行:");
        ui->textBrowser_input->append("LPMS:    向数据库中插入30万条给定的键值对记录");
        ui->textBrowser_input->append("无持久架构:向数据库中插入30万条给定的键值对记录");
        ui->textBrowser_input->append("文件系统:  向数据库中插入30万条给定的键值对记录");
        ui->progressBar_dram->setRange(0,300000);
        ui->progressBar_ramdisk->setRange(0,300000);
        ui->progressBar_scm->setRange(0,300000);
        QTimer::singleShot(1000,this, SLOT(doWork()) );
        break;
    }
    case 2:{
        args << BENCH1_MIDDLE_DIR;
        prorun->start("sh", args);
        ui->textBrowser_input->setText("程序正在运行:");
        ui->textBrowser_input->append("LPMS    :向数据库中插入60万条给定的键值对记录");
        ui->textBrowser_input->append("无持久架构:向数据库中插入60万条给定的键值对记录");
        ui->textBrowser_input->append("文件系统  :向数据库中插入60万条给定的键值对记录");
        ui->progressBar_dram->setRange(0,600000);
        ui->progressBar_ramdisk->setRange(0,600000);
        ui->progressBar_scm->setRange(0,600000);
        QTimer::singleShot(1000,this, SLOT(doWork()));
        break;
    }
    case 3:{
        args << BENCH1_BIG_DIR;
        prorun->start("sh", args);
        ui->textBrowser_input->setText("程序正在运行:");
        ui->textBrowser_input->append("LPMS    :向数据库中插入100万条给定的键值对记录");
        ui->textBrowser_input->append("无持久架构:向数据库中插入100万条给定的键值对记录");
        ui->textBrowser_input->append("文件系统  :向数据库中插入100万条给定的键值对记录");
        ui->progressBar_dram->setRange(0,1000000);
        ui->progressBar_ramdisk->setRange(0,1000000);
        ui->progressBar_scm->setRange(0,1000000);
        QTimer::singleShot(1000,this, SLOT(doWork()) );
        break;
    }
    }
    //    QTimer *timer = new QTimer(this);
    //    connect(timer, SIGNAL (timeout()), this, SLOT (doWork()));
    //    timer->start(100,true);

}
void BenchMark1::TestForType(){
    flag = 2;
    QProcess *prorun = new QProcess;
    QStringList args;
    //qDebug("%d\n",testdataflag);
    switch(testtypeflag){
    case 1:{
        args << BENCH2_SMALL_DIR;
        prorun->start("sh", args);
        ui->textBrowser_input->setFontPointSize(16);
        ui->textBrowser_input->setText("程序正在运行:");
        ui->textBrowser_input->append("LPMS    :向数据库中插入35万条，删除35万条键值对");
        ui->textBrowser_input->append("无持久架构:向数据库中插入35万条，删除35万条键值对");
        ui->textBrowser_input->append("文件系统  :向数据库中插入35万条，删除35万条键值对");
        ui->progressBar_dram->setRange(0,700000);
        ui->progressBar_ramdisk->setRange(0,700000);
        ui->progressBar_scm->setRange(0,700000);
        QTimer::singleShot(1000,this, SLOT(doWork()) );
        break;
    }
    case 2:{
        args << BENCH2_MIDDLE_DIR;
        prorun->start("sh", args);
        ui->textBrowser_input->setText("程序正在运行:");
        ui->textBrowser_input->append("LPMS    :向数据库中插入50万条，删除20万条键值对");
        ui->textBrowser_input->append("无持久架构:向数据库中插50万条，删除20万条键值对");
        ui->textBrowser_input->append("文件系统  :向数据库中插入50万条，删除20万条键值对");
        ui->progressBar_dram->setRange(0,700000);
        ui->progressBar_ramdisk->setRange(0,700000);
        ui->progressBar_scm->setRange(0,700000);
        QTimer::singleShot(1000,this, SLOT(doWork()) );
        break;
    }
    case 3:{
        args << BENCH2_BIG_DIR;
        prorun->start("sh", args);
        ui->textBrowser_input->setText("程序正在运行:");
        ui->textBrowser_input->append("LPMS:    向数据库中插入70万条键值对，无删除操作");
        ui->textBrowser_input->append("无持久架构:向数据库中插入70万条键值对，无删除操作");
        ui->textBrowser_input->append("文件系统:  向数据库中插入70万条键值对，无删除操作");
        ui->progressBar_dram->setRange(0,700000);
        ui->progressBar_ramdisk->setRange(0,700000);
        ui->progressBar_scm->setRange(0,700000);
        QTimer::singleShot(1000,this, SLOT(doWork()) );
        break;
    }
    }
    //    QTimer *timer = new QTimer(this);
    //    connect(timer, SIGNAL (timeout()), this, SLOT (doWork()));
    //    timer->start(100,true);

}
void BenchMark1::doWork(){
    connect(this,SIGNAL(changscmprogressbar(int)),this,SLOT(on_progressBar_scm_valueChanged(int)));
    connect(this,SIGNAL(changdramprogressbar(int)),this,SLOT(on_progressBar_dram_valueChanged(int)));
    connect(this,SIGNAL(changramdiskprogressbar(int)),this,SLOT(on_progressBar_ramdisk_valueChanged(int)));
    QFile filescm(BENCH_STAGE_MIDDLE);
    QFile filedram(BENCH_STAGE_FAST);
    QFile fileramdisk(BENCH_STAGE_SLOW);
    int endscm = 1,enddram = 1,endramdisk = 1;
    QString resscm = "",resdram = "",resramdisk = "";
    while(endscm || enddram || endramdisk){
        //qDebug("%d %d %d\n",endscm,enddram,endramdisk);
        int scmnumber = 0,dramnumber = 0,ramdisknumber = 0;
        if(!filescm.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug()<<"Can't open filescm!"<<endl;
        }
        if(!filedram.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug()<<"Can't open filedram!"<<endl;
        }
        if(!fileramdisk.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug()<<"Can't open fileramdisk!"<<endl;
        }
        QTextStream inscm(&filescm),indram(&filedram),inramdisk(&fileramdisk);
        while(!inscm.atEnd() && endscm){
            QString line = inscm.readLine();
            //qDebug("######");qDebug()<<(line[0]);
            if(line[0] == '$') {
                //qDebug("################");
                resscm = line;
                endscm = 0;
            }
            else{
                scmnumber = scmnumber < line.toInt() ? line.toInt():scmnumber;
                if(scmnumber != 0 ) changscmprogressbar(scmnumber);
            }
        }
        while(!indram.atEnd() && enddram){
            QString line = indram.readLine();
            //qDebug("&&&&&&");qDebug()<<(line[0]);
            if(line[0] == '$') {
                //qDebug("&&&&&&&&&&&&&");
                resdram = line;
                enddram = 0;
            }
            else{
                dramnumber = dramnumber < line.toInt()?line.toInt():dramnumber;
                if(dramnumber != 0) changdramprogressbar(dramnumber);
            }
        }
        while(!inramdisk.atEnd() && endramdisk){
            QString line = inramdisk.readLine();
            // qDebug("^^^^^^");qDebug()<<(line[0]);
            if(line[0] == '$') {
                //qDebug("^^^^^^^^^^^^^^^^^^^");
                resramdisk = line;
                endramdisk = 0;
            }
            else{
                ramdisknumber = ramdisknumber < line.toInt()?line.toInt():ramdisknumber;
                if(ramdisknumber != 0) changramdiskprogressbar(ramdisknumber);
            }
        }
        filescm.close();
        filedram.close();
        fileramdisk.close();
    }
    //ui->textBrowser_input->append("scm:"+resscm); //ui->textBrowser_input->append(resscm);
    //ui->textBrowser_input->append("dram:"+resdram);//ui->textBrowser_input->append(resdram);
    //ui->textBrowser_input->append("ramdisk:"+resramdisk);//ui->textBrowser_input->append(resramdisk);
    //ui->textBrowser_input->append("下图所示中，速度代表每秒插入的数据（对数表示）");
    //QTimer::singleShot(100,this, SLOT(Result_Draw(resscm,resdram,resramdisk)));
    Result_Draw(resscm,resdram,resramdisk);
    // QProcess *prodelete = new QProcess;
    // prodelete->start("/home/cx/demo/insert-benchmark/delete.sh");
    if(flag == 1){
        if(testdataflag == 1 || testdataflag == 2){
            testdataflag += 1;
            click_btn_test();
        }
        else if(testdataflag == 3){
            testdataflag = 1;
        }
    }
    else if(flag == 2){
        if(testtypeflag == 1 || testtypeflag == 2){
            testtypeflag += 1;
            click_btn_test();
        }
        else if(testtypeflag == 3){
            testtypeflag = 1;
        }
    }
}
void BenchMark1::Result_Draw(QString resscm, QString resdram, QString resramdisk){
    QStringList sectionscm = resscm.split(" ");
    QStringList sectiondram = resdram.split(" ");
    QStringList sectionramdisk = resramdisk.split(" ");
    //    qDebug()<<sectionscm.
    QBarSet *set0 = new QBarSet("LPMS");
    QBarSet *set1 = new QBarSet("无持久化架构");
    QBarSet *set2 = new QBarSet("文件系统");
    //
    *set0 << sectionscm.at(4).toFloat();
    *set1 << sectiondram.at(4).toFloat();
    *set2 << sectionramdisk.at(4).toFloat();

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);

    QChart *chart = new QChart();
    //chart->de
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "时间";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    //qDebug("%d\b",testdataflag);
    if(flag == 1){
        switch (testdataflag){
        case 1:{
            chart->setTitle("30万数据集下的测试结果");
            ui->graph_1->setChart(chart);
            ui->graph_1->setRenderHint(QPainter::Antialiasing);
            break;
        }
        case 2:{
            chart->setTitle("50万数据集下的测试结果");
            ui->graph_2->setChart(chart);
            ui->graph_2->setRenderHint(QPainter::Antialiasing);
            break;
        }
        case 3:{
            chart->setTitle("100万数据集下的测试结果");
            ui->graph_3->setChart(chart);
            ui->graph_3->setRenderHint(QPainter::Antialiasing);
            break;
        }
        }
    }
    else if(flag == 2){
        switch (testtypeflag){
        case 1:{
            chart->setTitle("50%:50%数据集下的测试结果");
            ui->graph_1->setChart(chart);
            ui->graph_1->setRenderHint(QPainter::Antialiasing);
            break;
        }
        case 2:{
            chart->setTitle("80%:20%数据集下的测试结果");
            ui->graph_2->setChart(chart);
            ui->graph_2->setRenderHint(QPainter::Antialiasing);
            break;
        }
        case 3:{
            chart->setTitle("100%:0%大数据集下的测试结果");
            ui->graph_3->setChart(chart);
            ui->graph_3->setRenderHint(QPainter::Antialiasing);
            break;
        }
        }
    }
}

void BenchMark1::on_progressBar_scm_valueChanged(int value)
{
    // qDebug("scm:%d\n",value);
    ui->progressBar_scm->setValue(value);
}

void BenchMark1::on_progressBar_dram_valueChanged(int value)
{
    // qDebug("dram:%d\n",value);
    ui->progressBar_dram->setValue(value);
}

void BenchMark1::on_progressBar_ramdisk_valueChanged(int value)
{
    // qDebug("ramdisk:%d\n",value);
    ui->progressBar_ramdisk->setValue(value);
}

void BenchMark1::processError(QProcess::ProcessError error)
{
 switch(error)
 {
  case QProcess::FailedToStart:
    QMessageBox::information(0,"FailedToStart","FailedToStart");
    break;
  case QProcess::Crashed:
    QMessageBox::information(0,"Crashed","Crashed");
    break;
  case QProcess::Timedout:
    QMessageBox::information(0,"FailedToStart","FailedToStart");
    break;
  case QProcess::WriteError:
    QMessageBox::information(0,"Timedout","Timedout");
    break;
  case QProcess::ReadError:
    QMessageBox::information(0,"ReadError","ReadError");
    break;
  case QProcess::UnknownError:
    QMessageBox::information(0,"UnknownError","UnknownError");
    break;
  default:
    QMessageBox::information(0,"default","default");
    break;
 }
}
