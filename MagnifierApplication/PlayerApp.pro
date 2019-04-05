#-------------------------------------------------
#
# Project created by QtCreator 2017-04-20T10:40:22
#
#-------------------------------------------------

QT += widgets
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x000000
QT       += core gui multimedia multimediawidgets

CONFIG +=c++11


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlayerApp
TEMPLATE = app

INCLUDEPATH +=C:\opencv\Release\install\include

 INCLUDEPATH += "C:\\opencv\\build\\include" \
                   "C:\\opencv\\build\\include\\opencv" \
                   "C:\\opencv\\build\\include\\opencv2"

#LIBS +=-L<opencv_library_path>
#    CONFIG(debug, debug | release) {
#        LIBS += -L"C:\\opencv\\build\\x86\\vc10\\lib" \
#            -lopencv_core248d \
#            -lopencv_highgui248d \
#            -lopencv_imgproc248d
#    }

#    CONFIG(release, debug | release) {
#        LIBS += -L"C:\\opencv\\build\\x86\\vc10\\lib" \
#            -lopencv_core248 \
#            -lopencv_highgui248 \
#            -lopencv_imgproc248
#    }
LIBS +=C:\opencv\Release\bin\libopencv_ml320.dll
LIBS +=C:\opencv\Release\bin\libopencv_highgui320.dll
LIBS +=C:\opencv\Release\bin\libopencv_imgproc320.dll
LIBS +=C:\opencv\Release\bin\libopencv_imgcodecs320.dll
LIBS +=C:\opencv\Release\bin\libopencv_calib3d320.dll
LIBS +=C:\opencv\Release\bin\libopencv_videoio320.dll
LIBS +=C:\opencv\Release\bin\libopencv_video320.dll
LIBS +=C:\opencv\Release\bin\libopencv_core320.dll
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    player.cpp

HEADERS  += mainwindow.h \
    player.h

FORMS    += mainwindow.ui
