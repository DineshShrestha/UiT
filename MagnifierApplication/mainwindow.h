#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include<QMediaPlayer>
#include<QVideoWidget>
#include<QProgressBar>
#include<QDialog>
#include<QSlider>
#include<QLabel>
#include <QCoreApplication>
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <opencv2\highgui.hpp>
#include "opencv2\imgproc.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/videoio.hpp"
#include"opencv2/cvconfig.h"
#include "player.h"
#include <QTime>
#include <cv.h>
#include <highgui.h>
#include <math.h>
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int getFrames();
    void VideoMaker();
private slots:
    //Display video frame in player UI
    void updatePlayerUI(QImage img);
    void updatePlayerUI_2(QImage img);
    void updatePlayerUI_3(QImage img);
    //Slot for the load video push button.
    void on_pushButton_clicked();
    // Slot for the play push button.
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    QString getFormattedTime(int timeInSeconds);
    void on_horizontalSlider_sliderPressed();
    void on_horizontalSlider_sliderReleased();
    void on_horizontalSlider_sliderMoved(int position);
    void on_pushButton_5_clicked();
    void on_horizontalSlider_2_sliderPressed();
    void on_horizontalSlider_2_sliderMoved(int position);
    void on_horizontalSlider_2_sliderReleased();
    void on_horizontalSlider_3_sliderMoved(int position);
    void on_horizontalSlider_3_sliderPressed();
    void on_horizontalSlider_3_sliderReleased();
    void on_pushButton_7_clicked();
    void on_pushButton_3_clicked();
    void video_splitter();

private:
    VideoWriter writer;
    Ui::MainWindow *ui;
    Player* myPlayer;
    Player* myPlayer_2;
    Player* myPlayer_3;
};

#endif // MAINWINDOW_H
