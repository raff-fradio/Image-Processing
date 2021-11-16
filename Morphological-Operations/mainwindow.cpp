#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <iostream>

#define L 256

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->display1->setScaledContents(true);
    ui->display2->setScaledContents(true);
    ui->display3->setScaledContents(true);
    ui->display4->setScaledContents(true);

    ui->display1->setFixedSize( QLWidth, QLHeight );
    ui->display2->setFixedSize( QLWidth, QLHeight );
    ui->display3->setFixedSize( QLWidth, QLHeight );
    ui->display4->setFixedSize( QLWidth, QLHeight );

//    cap.open(1);

//    // Call update every 100ms
//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
//    timer->start(333);

    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    Mat original = imread("");
    QImage img1 = MatToQImage(original);


    ui->display1->setPixmap(QPixmap::fromImage(img1));
    ui->display2->setPixmap(QPixmap::fromImage(img2));
    ui->display3->setPixmap(QPixmap::fromImage(img3));
    ui->display4->setPixmap(QPixmap::fromImage(img4));
}
