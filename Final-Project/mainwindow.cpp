#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    util = Utility();

    cap.set(CAP_PROP_FRAME_HEIGHT, Utility::FRAME_HEIGHT);
    cap.set(CAP_PROP_FRAME_WIDTH, Utility::FRAME_WIDTH);

    cap.open(0);

    if (!cap.isOpened()) {
        cerr << "[ERROR] Unable to open camera";
        return;
    }

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(33);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update() {
    Mat frame;

    cap.read(frame);

    Mat frame2 = util.getForeground(frame);

    QImage img1 = MatToQImage(frame);
    QImage img2 = MatToQImage(frame2);

    ui->display1->setPixmap(QPixmap::fromImage(img1));
    ui->display2->setPixmap(QPixmap::fromImage(img2));

}

