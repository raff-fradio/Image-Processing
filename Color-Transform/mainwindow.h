#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <MatToQImage.h>
#include "colorcorrect.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    VideoCapture cap;
    Mat capture;
    colorcorrect myColor;
    Mat bgr, hsv;
    void change();

private slots:
    void update();
    void on_hmin_valueChanged(int value);
    void on_hmax_valueChanged(int value);
    void on_vmax_valueChanged(int value);
    void on_smin_valueChanged(int value);
    void on_smax_valueChanged(int value);
    void on_vmin_valueChanged(int value);
};
#endif // MAINWINDOW_H
