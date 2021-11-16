QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    image.cpp \
    main.cpp \
    mainwindow.cpp \
    MatToQImage.cpp \
    morphological-operations.cpp

HEADERS += \
    image.h \
    mainwindow.h \
    MatToQImage.h \
    morphological-operations.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += "C:\Utilities\opencv-4.5.1\build\include"
LIBS += C:\Utilities\opencv-build\bin\libopencv_core451.dll
LIBS += C:\Utilities\opencv-build\bin\libopencv_highgui451.dll
LIBS += C:\Utilities\opencv-build\bin\libopencv_imgcodecs451.dll
LIBS += C:\Utilities\opencv-build\bin\libopencv_imgproc451.dll
LIBS += C:\Utilities\opencv-build\bin\libopencv_features2d451.dll
LIBS += C:\Utilities\opencv-build\bin\libopencv_calib3d451.dll
LIBS += C:\Utilities\opencv-build\bin\libopencv_calib3d451.dll
LIBS += C:\Utilities\opencv-build\bin\libopencv_video451.dll
LIBS += C:\Utilities\opencv-build\bin\libopencv_videoio451.dll
