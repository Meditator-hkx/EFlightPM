#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap("image1.jpg")));
    this->setPalette(palette);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btngoben1_clicked()
{
    this->close();
    bmw1.show();
    bmw1.exec();
    this->show();
}

void MainWindow::on_btngoben2_clicked()
{
    this->close();
    bmw2.show();
    bmw2.exec();
    this->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    this->close();
}
