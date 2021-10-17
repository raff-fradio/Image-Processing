#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cap.open(1);

    // Call update every 100ms
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(333);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    cap >> capture;
    cvtColor(capture, capture, COLOR_BGR2GRAY);

    Mat boxMask = applyBoxMask(capture);
    Mat weightedAverage = applyWeightedAverageMask(capture);
    Mat medianMask = applyMedian(capture, 5);

    QImage img1 = MatToQImage(capture);
    QImage img2 = MatToQImage(boxMask);
    QImage img3 = MatToQImage(weightedAverage);
    QImage img4 = MatToQImage(medianMask);

    ui->display1->setPixmap(QPixmap::fromImage(img1));
    ui->display2->setPixmap(QPixmap::fromImage(img2));
    ui->display3->setPixmap(QPixmap::fromImage(img3));
    ui->display4->setPixmap(QPixmap::fromImage(img4));
}
