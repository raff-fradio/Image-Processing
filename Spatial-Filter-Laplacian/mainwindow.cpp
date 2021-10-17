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

    Mat laplacianInput;
    capture.copyTo(laplacianInput);
    laplacianInput.convertTo(laplacianInput, CV_64FC1);

    Mat laplacianOrthogonalMask = (Mat_<int>(3, 3) <<
        -1, -1, -1,
        -1,  8, -1,
        -1, -1, -1);

    auto laplacianOrthogonalApplied = iterateMask(laplacianInput, laplacianOrthogonalMask);

    auto orthogonalMin = .0;
    auto orthogonalMax = .0;

    minMaxLoc(laplacianOrthogonalApplied, &orthogonalMin, &orthogonalMax);

    laplacianOrthogonalApplied = (laplacianOrthogonalApplied - orthogonalMin);
    minMaxLoc(laplacianOrthogonalApplied, &orthogonalMin, &orthogonalMax);
    laplacianOrthogonalApplied = laplacianOrthogonalApplied * (255.0 / orthogonalMax);

    Mat sharpenedOrthogonal = laplacianInput + laplacianOrthogonalApplied;

    minMaxLoc(sharpenedOrthogonal, &orthogonalMin, &orthogonalMax);

    sharpenedOrthogonal = (sharpenedOrthogonal - orthogonalMin);
    minMaxLoc(sharpenedOrthogonal, &orthogonalMin, &orthogonalMax);
    sharpenedOrthogonal = sharpenedOrthogonal * (255.0 / orthogonalMax);

    sharpenedOrthogonal.convertTo(sharpenedOrthogonal, CV_8U);
    laplacianOrthogonalApplied.convertTo(laplacianOrthogonalApplied, CV_8U);

    //Apply gradient filter
    auto gradientApplied = iterateMaskForGradient(laplacianInput);

    gradientApplied.convertTo(gradientApplied, CV_8U);

    QImage img1 = MatToQImage(capture);
    QImage img2 = MatToQImage(laplacianOrthogonalApplied);
    QImage img3 = MatToQImage(sharpenedOrthogonal);
    QImage img4 = MatToQImage(gradientApplied);

    ui->display1->setPixmap(QPixmap::fromImage(img1));
    ui->display2->setPixmap(QPixmap::fromImage(img2));
    ui->display3->setPixmap(QPixmap::fromImage(img3));
    ui->display4->setPixmap(QPixmap::fromImage(img4));
}
