#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QFileDialog>
#include <QInputDialog>

using namespace cv;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openImageButton_clicked();

    void on_transformButton_clicked();

    void on_antiTransformButton_clicked();

    void on_filterButton_clicked();

    //custom methods
    Mat optimizeImgDimension(Mat &image);
    void shiftDFT(Mat &image);
    Mat createOptimizeMagnitudeSpectrum(Mat &complexImage, bool flipQuadrants);


private:
    Ui::MainWindow *ui;
    Mat image; //the original image
    Mat complexImage; //complex image
    Mat planes[2]; //planes for real and not-real parts
};

#endif // MAINWINDOW_H
