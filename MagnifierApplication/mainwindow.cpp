#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include <QByteArray>
#include<iostream>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    myPlayer = new Player();
    myPlayer_2 = new Player();
    myPlayer_3 = new Player();
    QObject::connect(myPlayer, SIGNAL(processedImage(QImage)),
                     this, SLOT(updatePlayerUI(QImage)));
    QObject::connect(myPlayer_2, SIGNAL(processedImage(QImage)),
                     this, SLOT(updatePlayerUI_2(QImage)));
    QObject::connect(myPlayer_3, SIGNAL(processedImage(QImage)),
                     this, SLOT(updatePlayerUI_3(QImage)));
    ui->setupUi(this);

    ui->horizontalSlider->setEnabled(false);
    ui->horizontalSlider_2->setEnabled(false);
    ui->horizontalSlider_3->setEnabled(false);

    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->label_4->setText("00:00");
    ui->label_5->setText("00:00");
    ui->label_6->setText("00:00");
    ui->label_7->setText("00:00");
    ui->label_8->setText("00:00");
    ui->label_9->setText("00:00");
}

void MainWindow::updatePlayerUI(QImage img)
{

    if (!img.isNull())
    {
        ui->label->setAlignment(Qt::AlignCenter);
        ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
        ui->horizontalSlider->setValue(myPlayer->getCurrentFrame());
        ui->label_4->setText( getFormattedTime( (int)myPlayer->getCurrentFrame()/(int)myPlayer->getFrameRate()) );

    }

}

void MainWindow::updatePlayerUI_2(QImage img)
{
    if (!img.isNull())
    {
        ui->label_2->setAlignment(Qt::AlignCenter);
        ui->label_2->setPixmap(QPixmap::fromImage(img).scaled(ui->label_2->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
        ui->horizontalSlider_2->setValue(myPlayer_2->getCurrentFrame());
        ui->label_7->setText( getFormattedTime( (int)myPlayer_2->getCurrentFrame()/(int)myPlayer_2->getFrameRate()) );

    }

}
void MainWindow::updatePlayerUI_3(QImage img)
{
    if (!img.isNull())
    {
        ui->label_3->setAlignment(Qt::AlignCenter);
        ui->label_3->setPixmap(QPixmap::fromImage(img).scaled(ui->label_3->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
        ui->horizontalSlider_3->setValue(myPlayer_3->getCurrentFrame());
        ui->label_9->setText( getFormattedTime( (int)myPlayer_3->getCurrentFrame()/(int)myPlayer_3->getFrameRate()) );

    }
}
MainWindow::~MainWindow()
{
    delete ui;
}



//For Evm label play video
void MainWindow::on_pushButton_clicked()
{

    if(myPlayer->isStopped())
    {
        myPlayer->Play();
        ui->pushButton->setText(tr("stop"));
    }
    else
    {
        myPlayer->Play();
        ui->pushButton->setText(tr("play"));
    }

}
//For loading the Evm video
void MainWindow::on_pushButton_2_clicked()
{
    if(myPlayer_2->isStopped())
    {
        myPlayer_2->Play();
        ui->pushButton_2->setText(tr("stop"));
    }
    else
    {
        myPlayer_2->Play();
        ui->pushButton_2->setText(tr("play"));
    }

}

void MainWindow::on_pushButton_4_clicked()
{
    QString filename= QFileDialog::getOpenFileName(this,tr("open Video"),".",tr("Video Files(*.*)"));
    QFileInfo name = filename;
    if(!filename.isEmpty())
    {
        if(!myPlayer->loadVideo(filename.toAscii().data()))
        {
            QMessageBox message;
            message.setText("the selected video cannot be opened");
            message.exec();
        }

        else{
            this->setWindowTitle(name.fileName());
            ui->pushButton->setEnabled(true);
            ui->horizontalSlider->setEnabled(true);
            ui->horizontalSlider->setMaximum(myPlayer->getNumberOfFrames());
            ui->label_5->setText( getFormattedTime( (int)myPlayer->getNumberOfFrames()/(int)myPlayer->getFrameRate()) );
        }
    }
}

QString MainWindow::getFormattedTime(int timeInSeconds)
{
    int seconds = (int) (timeInSeconds) % 60 ;
    int minutes = (int) ((timeInSeconds / 60) % 60);
    int hours   = (int) ((timeInSeconds / (60*60)) % 24);
    QTime t(hours, minutes, seconds);
    if (hours == 0 )
        return t.toString("mm:ss");
    else
        return t.toString("h:mm:ss");
}

void MainWindow::on_horizontalSlider_sliderPressed()
{
    myPlayer->Stop();
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
    myPlayer->Play();
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    myPlayer->setCurrentFrame(position);
    ui->label_4->setText( getFormattedTime( position/(int)myPlayer->getFrameRate()) );
}

void MainWindow::on_pushButton_5_clicked()
{
    QString filename= QFileDialog::getOpenFileName(this,tr("open Video"),".",tr("Video Files(*.*)"));
    QFileInfo name = filename;
    if(!filename.isEmpty())
    {
        if(!myPlayer_2->loadVideo(filename.toAscii().data()))
        {
            QMessageBox message;
            message.setText("the selected video cannot be opened");
            message.exec();
        }
        else
        {
            this->setWindowTitle(name.fileName());
            ui->pushButton_2->setEnabled(true);
            ui->horizontalSlider_2->setEnabled(true);
            ui->horizontalSlider_2->setMaximum(myPlayer_2->getNumberOfFrames());
            ui->label_6->setText( getFormattedTime( (int)myPlayer_2->getNumberOfFrames()/(int)myPlayer_2->getFrameRate()) );
        }
    }
}

void MainWindow::on_horizontalSlider_2_sliderPressed()
{
    myPlayer_2->Stop();
}

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    myPlayer_2->setCurrentFrame(position);
    ui->label_7->setText( getFormattedTime( position/(int)myPlayer_2->getFrameRate()) );
}

void MainWindow::on_horizontalSlider_2_sliderReleased()
{
    myPlayer_2->Play();
}

void MainWindow::on_horizontalSlider_3_sliderMoved(int position)
{
    myPlayer_3->setCurrentFrame(position);
    ui->label_9->setText( getFormattedTime( position/(int)myPlayer_3->getFrameRate()) );
}

void MainWindow::on_horizontalSlider_3_sliderPressed()
{
    myPlayer_3->Stop();
}

void MainWindow::on_horizontalSlider_3_sliderReleased()
{
    myPlayer_3->Play();
}

void MainWindow::on_pushButton_7_clicked()
{

    VideoMaker();
    QString filename= QFileDialog::getOpenFileName(this,tr("open Video"),".",tr("Video Files(*.*)"));
    QFileInfo name = filename;
    if(!filename.isEmpty())
    {
        if(!myPlayer_3->loadVideo(filename.toAscii().data()))
        {
            QMessageBox message;
            message.setText("The selected video cannot be opened");
            message.exec();
        }

        else{
            this->setWindowTitle(name.fileName());
            ui->pushButton_3->setEnabled(true);
            ui->horizontalSlider_3->setEnabled(true);
            ui->horizontalSlider_3->setMaximum(myPlayer_3->getNumberOfFrames());
            ui->label_8->setText( getFormattedTime( (int)myPlayer_3->getNumberOfFrames()/(int)myPlayer_3->getFrameRate()) );
        }
    }

}

void MainWindow::on_pushButton_3_clicked()
{

    if(myPlayer_3->isStopped())
    {
        myPlayer_3->Play();
        ui->pushButton_3->setText(tr("stop"));
    }
    else
    {
        myPlayer_3->Play();
        ui->pushButton_3->setText(tr("play"));
    }
}

void MainWindow::VideoMaker()
{

    VideoCapture cap(myPlayer->filename_); //open the video video file
    VideoCapture cap1(myPlayer_2->filename_);
    VideoCapture cap3("c:\\result.avi");

    int framenum1=cap.get(CV_CAP_PROP_FRAME_COUNT);
    int framenum2=cap1.get(CV_CAP_PROP_FRAME_COUNT);
    auto fps1=cap.get(CV_CAP_PROP_FPS);
    auto fps2=cap1.get(CV_CAP_PROP_FPS);
    int i=0;
    double dWidth = cap3.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = cap3.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
    cv::Size frameSize(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    VideoWriter writer("C:\\result.avi", CV_FOURCC('P','I','M','1'), 20, frameSize, true); //initialize the VideoWriter object

    std::cout << "Frame Size = " << dWidth << "x" << dHeight << endl;

    if (!cap.isOpened()&&!cap1.isOpened())  // if not success, exit program
    {
        std::cout << "ERROR INITIALIZING VIDEO CAPTURE" << endl;
        //return -1;
    }

    int count=0;
    std::cout<<framenum1<<std::endl;

    //while(1)
    int framenum=0;
    auto fps=0;
    if (framenum1<=framenum2)
    {
        framenum=framenum1;
        fps=fps1;
    }
    else {
        framenum=framenum2;
        fps=fps2;
    }
    while(cap1.isOpened())
    {
        cv::Mat frame,frame1;
        Mat dst;
        double input=0.25,beta,alpha=0.5;
        std::cout<<"frames per second"<<fps<<std::endl;
        count++;
        cap.read(frame);
        cap1.read(frame1);
        Mat resized;

        // Setup a rectangle to define your region of interest
        cv::Rect myROI(20, 34, 620, 393);

        // Crop the full image to that image contained by the rectangle myROI
        // Note that this doesn't copy the data
        frame1 = frame1(myROI);

        //crop the original image to the defined ROI
        cv::resize(frame,resized,cv::Size(640,357));
        if( frame.empty()&&frame1.empty()) break;
        char filename[1000],filename1[1000];
        sprintf(filename,"C:\\res\\normal_%d.jpg",i);
        sprintf(filename1,"C:\\res\\flir_%d.jpg",i);
        imwrite(filename, frame);
        imwrite(filename1, frame1);
        String a="c:\\res\\flir_"+std::to_string(i)+".jpg";
        String b="c:\\res\\normal_"+std::to_string(i)+".jpg";
        String c="c:\\res\\result_"+std::to_string(i)+".jpg";
        cv::resize(frame1, frame1, frame.size());
        /// Create Windows
        namedWindow("Linear Blend", 1);

        beta = (1.0 - alpha);
        addWeighted( frame1, alpha, frame, beta, 0.0, dst);
        //imshow( "Linear Blend", dst );
        imwrite(c,dst);
        writer.write(dst);

        waitKey(30);

        i++;
        if ( i == framenum-1)
        {
            QMessageBox message;
            message.setText("Click ok to open the result video");
            message.exec();
            break;
        }

    }
    cap1.release();


}

