QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MatToQImage.cpp \
    histogram.cpp \
    main.cpp \
    mainwindow.cpp \
    utility.cpp

HEADERS += \
    MatToQImage.h \
    NamedType.h \
    histogram.h \
    mainwindow.h \
    utility.h

FORMS += \
    mainwindow.ui \
    mainwindow_copy.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Change these paths to the opencv build directory
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
