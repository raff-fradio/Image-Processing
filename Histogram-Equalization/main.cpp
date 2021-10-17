#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QString("OpenCV Histogram Equalization V %1:%2").arg(CV_MAJOR_VERSION).arg(CV_MINOR_VERSION));
    w.show();

    return a.exec();
}
