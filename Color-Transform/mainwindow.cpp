#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myColor = colorcorrect();

    ui->hmin->setMaximum(myColor.hmin_Max);
    ui->hmax->setMaximum(myColor.hmax_Max);
    ui->smin->setMaximum(myColor.smin_Max);
    ui->smax->setMaximum(myColor.smax_Max);
    ui->vmin->setMaximum(myColor.vmin_Max);
    ui->vmax->setMaximum(myColor.vmax_Max);

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
    capture = imread("D:\\Uni\\Semester 7\\Image Processing\\Github\\Color-Transform\\Road.jpg");

    Mat source;
    capture.copyTo(source);

    Mat sharpened = myColor.colorCorrect(source);
    Mat concat = myColor.concat(source, sharpened);

    QImage img1 = MatToQImage(source);
    QImage img2 = MatToQImage(concat);

    ui->display1->setPixmap(QPixmap::fromImage(img1));
    ui->display2->setPixmap(QPixmap::fromImage(img2));

    capture.convertTo(bgr, CV_32FC3, 1.0 / 255, 0);
    cvtColor(bgr, hsv, COLOR_BGR2HSV);
    change();
}

void MainWindow::change() {
    Mat dst = myColor.callBack(capture, bgr, hsv);

    QImage img3 = MatToQImage(capture);
    QImage img4 = MatToQImage(dst);

    ui->display3->setPixmap(QPixmap::fromImage(img3));
    ui->display4->setPixmap(QPixmap::fromImage(img4));
}

void MainWindow::on_hmin_valueChanged(int value)
{
    myColor.hmin = value;
    change();
}


void MainWindow::on_hmax_valueChanged(int value)
{
    myColor.hmax = value;
    change();
}


void MainWindow::on_smin_valueChanged(int value)
{
    myColor.smin = value;
    change();
}


void MainWindow::on_smax_valueChanged(int value)
{
    myColor.smax = value;
    change();
}



void MainWindow::on_vmin_valueChanged(int value)
{
    myColor.vmin = value;
    change();
}


void MainWindow::on_vmax_valueChanged(int value)
{
    myColor.vmax = value;
    change();
}
