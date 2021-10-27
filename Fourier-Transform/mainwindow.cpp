#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openImageButton_clicked()
{
    // choose the image to open
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));

    // read the image
    image = imread(filename.toLocal8Bit().constData(), IMREAD_GRAYSCALE);

    // update the UI
    ui->transformButton->setEnabled(true);
    ui->filterButton->setEnabled(true);

    // we are using OpenCV windows, since QImage has some visualization problems with this type of grayscale images
    // create a named image window
    namedWindow("Original Image");
    // show the image
    imshow("Original Image", image);

}

void MainWindow::on_transformButton_clicked()
{
    Mat padded = optimizeImgDimension(image);

    // convert values in float and add another channel to complexImage
    // for storing the additional information given by the transformation
    planes[0] = Mat_<float> (padded);
    planes[1] = Mat::zeros(padded.size(), CV_32F);
    merge(planes, 2, complexImage);

    // DFT
    dft(complexImage, complexImage);

    // optimization
    Mat magnitude = createOptimizeMagnitudeSpectrum(complexImage, true);

    // show only the real part
    namedWindow("Magnitude");
    imshow("Magnitude", magnitude);

    // update the UI
    ui->antiTransformButton->setEnabled(true);
}

void MainWindow::on_antiTransformButton_clicked()
{
    // anti-transform
    idft(complexImage,complexImage);

    Mat final;
    split(complexImage, planes);
    normalize(planes[0],final,0,1, NORM_MINMAX);

    // show the image
    namedWindow("Anti-transform");
    imshow("Anti-transform", final);
}

void MainWindow::on_filterButton_clicked()
{
    // apply a median filter
    Mat filteredImage;
    int filterDim = QInputDialog::getInt(this, tr("Median Filter"), tr("Filter dimension"), 0, 3, 15, 2);
    medianBlur(image,filteredImage,filterDim);

    // show the result
    namedWindow("Filter");
    imshow("Filter", filteredImage);
}

// add some pixels to the image borders, in order to optimize its dimension for DFT
Mat MainWindow::optimizeImgDimension(Mat &image)
{
    Mat padded;
    int addPixelRows = getOptimalDFTSize(image.rows); // # pixels to horizontally add to the padded image
    int addPixelCols = getOptimalDFTSize(image.cols); // # pixels to vertically add to the padded image
    copyMakeBorder(image,
                   padded,
                   0,
                   addPixelRows - image.rows,
                   0,
                   addPixelCols - image.cols,
                   BORDER_CONSTANT,
                   Scalar::all(0)
                   );
    return padded;
}

// image crop (to return to original dimension) and quadrants swap to properly show the magnitude
void MainWindow::shiftDFT(Mat &image)
{
    //crop
    image = image(Rect(0, 0, image.cols & -2, image.rows & -2));


    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = image.cols/2;
    int cy = image.rows/2;

    Mat q0(image, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(image, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(image, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(image, Rect(cx, cy, cx, cy)); // Bottom-Right

    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

}

// split the complex image in the real and imaginary part
// return the magnitude and normalize its value according to the log scale
Mat MainWindow::createOptimizeMagnitudeSpectrum(Mat &complexImage, bool flipQuadrants)
{
    // split the transformed image in two planes, for real and imaginary part
    split(complexImage, planes);
    // magnitude: M = sqrt(planes[0]^2 + planes[1]^2);
    magnitude(planes[0], planes[1], planes[0]);
    // log scale: log(1 + M)
    Mat mag = planes[0].clone();
    mag += Scalar::all(1);
    log(mag, mag);

    if (flipQuadrants)
        shiftDFT(mag);
    // transform the matrix with float values into a
    // viewable image form (float between values 0 and 1).
    normalize(mag, mag, 0, 1, NORM_MINMAX);

    return mag;
}
