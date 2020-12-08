#include "qeyetrackwidget.h"
#include "ui_qeyetrackwidget.h"
#include<qeyecontrol.h>
#include<QDesktopWidget>
#include<QScreen>
QEyeTrackWidget::QEyeTrackWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QEyeTrackWidget)
{
    ui->setupUi(this);
    EyeTrackStatus= false;
    FrameCount=0;
    grazePointNums = 0;
    showTimer = new QTimer(this);
    stopEyeTrackTimer = new QTimer(this);
    EyeTrackTimer = new QTimer(this);
    grazeTimer = new QTimer(this);
    connect(showTimer,SIGNAL(timeout()),this,SLOT(Slot_GetFrame()));
    connect(stopEyeTrackTimer,SIGNAL(timeout()),this,SLOT(slotStopEyeTrack()));

    connect(EyeTrackTimer,SIGNAL(timeout()),this,SLOT(slotGetGazePoint()));
    connect(grazeTimer,SIGNAL(timeout()),this,SLOT(slotCreateGazePoint()));
    InitShowWidget();
    InitCcdConnect();

}

QEyeTrackWidget::~QEyeTrackWidget()
{
    delete showTimer;
    delete stopEyeTrackTimer;
    delete ui;
}
void QEyeTrackWidget::InitShowWidget()
{
    ui->lineEdit_time->setText("30");
    ui->pushButtonStartTrack->setEnabled(true);
    ui->pushButton_StopTrack->setEnabled(false);
}
void QEyeTrackWidget::InitCcdConnect()
{
    if(QEyeControl::Instance()->GetCDDControl()->isInited())
    {
         showTimer->start(3);
         QEyeControl::Instance()->GetCDDControl()->GetFrameSize();
     }
     else
    {
         if(QEyeControl::Instance()->GetCDDControl()->InitCCD())
         {
             if(QEyeControl::Instance()->GetCDDControl()->isInited())
             {
                 showTimer->start(3);
                 QEyeControl::Instance()->GetCDDControl()->GetFrameSize();

             }
         }

    }


}
QRect QEyeTrackWidget::GetScreenSize()
{
    QList<QScreen *> list_screen = QGuiApplication::screens();  //多显示器
    QRect screenRect = list_screen.at(0)->geometry();

    if(list_screen.size()>1)
    {
           screenRect = list_screen.at(1)->geometry();
           return screenRect;
    }
    else
        return screenRect;



}
void QEyeTrackWidget::DrawLines(QPainter &painter, QPoint leftpoint,QPoint ringhtpoint,int size,QColor leftcolor,QColor rightcolor)
{

    QPen leftpen(leftcolor);
    painter.setPen(leftpen);
    painter.drawLine(leftpoint.x()-size,leftpoint.y()-size,leftpoint.x()+size,leftpoint.y()+size);
    painter.drawLine(leftpoint.x()-size,leftpoint.y()+size,leftpoint.x()+size,leftpoint.y()-size);

    QPen rightpen(rightcolor);
    painter.setPen(rightpen);
    painter.drawLine(ringhtpoint.x()-size,ringhtpoint.y()-size,ringhtpoint.x()+size,ringhtpoint.y()+size);
    painter.drawLine(ringhtpoint.x()-size,ringhtpoint.y()+size,ringhtpoint.x()+size,ringhtpoint.y()-size);

}
void QEyeTrackWidget::DrawFrameInfo()
{
  //  qDebug()<<"DrawFrameInfo"<<"EyeTrackStatus"<<EyeTrackStatus;
    QLFrameData framedata= QEyeControl::Instance()->GetCDDControl()->GetNowFrame();
    QString tmp;
    tmp = QString("%1").arg(framedata.Distance);
    ui->lineEdit_distance->setText(tmp);
    tmp = QString("%1").arg(framedata.Focus);
    ui->lineEdit_focus->setText(tmp);

    tmp = QString::asprintf("%.1f", framedata.LeftEye.Pupil.x);
    ui->lineEdit_LeftX->setText(tmp);
    tmp = QString::asprintf("%.1f", framedata.LeftEye.Pupil.y);
    ui->lineEdit_LeftY->setText(tmp);
    tmp = QString::asprintf("%.1f", framedata.RightEye.Pupil.x);
    ui->lineEdit_RightX->setText(tmp);
    tmp =QString::asprintf("%.1f", framedata.RightEye.Pupil.y);
    ui->lineEdit_RightY->setText(tmp);

    //qDebug()<<"valid"<<framedata.WeightedGazePoint.Valid<<"gaze x"<<framedata.LeftEye.GazePoint.x<<"gaze y"<<framedata.LeftEye.GazePoint.y;

 //   qDebug()<<"Glint0"<<framedata.LeftEye.Glint0.x<<"GazePoint"<<framedata.LeftEye.GazePoint.x<<"Calibrated"<<framedata.LeftEye.Calibrated;
   // if(EyeTrackStatus)      //如果开始了采集从采集到的数据得到 凝视点;
     //   getGazePoint(framedata);


}
float QEyeTrackWidget::CalPointDistance(QPointF nowPoint, QPointF lastPoint)
{
    double dis;//两点间距离
    double x,y;
    x = nowPoint.x()-lastPoint.x();
    y = nowPoint.y()-lastPoint.y();
    dis = sqrt(x*x+y*y);
    //qDebug()<<"dis:"<<dis;
    return dis;
}
void QEyeTrackWidget::getGazePoint(QLFrameData framedata)
{

    QPoint leftpoint,rightpoint;
    QPointF leftpointNow,RightpointNow;
    int width = ui->widget_picture->size().width();
    int height = ui->widget_picture->size().height();
    if(framedata.LeftEye.Found&&framedata.RightEye.Found)
    {
       // qDebug()<<"fameCount"<<FrameCount<<"width"<<width<<"heigth"<<height;
        //if(FrameCount>20)           //大概100ms 获取一次  获取后取到
        //{

            int leftx = (int)(framedata.LeftEye.GazePoint.x*width/100);
            int lefty = (int)(framedata.LeftEye.GazePoint.y*height/100);
            int rightx = (int)(framedata.RightEye.GazePoint.x*width/100);
            int righty = (int)(framedata.RightEye.GazePoint.y*height/100);
            //qDebug()<<"width"<<width<<"height"<<height;
            qDebug()<<"x" <<framedata.LeftEye.GazePoint.x<<"y"<<framedata.LeftEye.GazePoint.y;
            leftpointNow.setX(framedata.LeftEye.GazePoint.x);
            leftpointNow.setY(framedata.LeftEye.GazePoint.y);
            RightpointNow.setX(framedata.RightEye.GazePoint.x);
            RightpointNow.setY(framedata.RightEye.GazePoint.y);
            float leftdis = CalPointDistance(leftpointNow,Leftpoint_last);
            float rightdis = CalPointDistance(leftpointNow,Leftpoint_last);
          //  qDebug()<<"leftdis"<<leftdis<<"rightds"<<rightdis;
            if(leftx>width||lefty>height||leftx<0||lefty<0||rightx>width||righty>height||rightx<0||righty<0)
                return;
            leftpoint.setX(leftx);
            leftpoint.setY(lefty);
            rightpoint.setX(rightx);
            rightpoint.setY(righty);
            Leftpoint_last.setX(framedata.LeftEye.GazePoint.x);
            Leftpoint_last.setY(framedata.LeftEye.GazePoint.y);
            RightPoint_last.setX(framedata.RightEye.GazePoint.x);
            RightPoint_last.setY(framedata.RightEye.GazePoint.y);
            FrameCount=0;
            if(leftdis<=1&&rightdis<=1)
            {
                    leftpointlist.append(leftpoint);
                    rightpointlist.append(rightpoint);
                    ui->widget_picture->SetDrawType(QShowpicWidget::eyeTrack);
                    ui->widget_picture->setEyeTrackLeftPoinList(leftpointlist);
                   // ui->widget_picture->setEyeTrackRightPoinList(rightpointlist);
                    ui->widget_picture->update();


            }
      //  }
        //else
         //   FrameCount++;


    }
}
void QEyeTrackWidget::slotPicType(SignalType picType)
{
    qDebug()<<"picType"<<picType;
    EyeTrackPic = picType;
    if(picType == SportsLines||picType == SPicture||picType == RandomPic||picType==Graze)
     {
        ui->widget_picture->SetDrawType(QShowpicWidget::eyeTrack);
        ui->widget_picture->SetPicType(picType);

    }
    else {   //不是当前测试页面 关闭当前页面中的定时器
        if(EyeTrackTimer->isActive())
            EyeTrackTimer->stop();
        ui->widget_picture->clearPointList();  //清空显示用的数组
        ui->widget_picture->update();           //刷新显示的界面
        ui->widget_picture->SetDrawType(QShowpicWidget::notype);
    }
}
void QEyeTrackWidget::slotCreateGazePoint()
{

    createPointAnddraw();
}
void QEyeTrackWidget::stopGraze()
{
    if(grazeTimer->isActive())
        grazeTimer->stop();
    grazePointNums=0;
    ui->pushButtonStartTrack->setEnabled(true);
    ui->pushButton_StopTrack->setEnabled(false);


}
void QEyeTrackWidget::createPointAnddraw()
{
    grazePointNums++;
    if(grazePointNums>=10)
    {

        stopGraze();
        return ;
    }
    QTime time;
    time= QTime::currentTime();
    int width = GetScreenSize().width();
    int height = GetScreenSize().height();
    qDebug()<<"width "<<width<<"height"<<height<<"grazepoint num" <<grazePointNums;
    qsrand(time.msec()+time.second()*1000);
    int x =  qrand()%95;
    int y =  qrand()%95;
    qDebug()<<"x"<<x<<"y"<<y<<"grazePointNums"<<grazePointNums;
    int pointx = GetScreenSize().width()*x/100;
    int pointy = GetScreenSize().height()*y/100;
    emit signaleSendGazePoint(QPoint(pointx,pointy));



    //int n = qrand() % 1024;    //产生5以内的随机数
}
void QEyeTrackWidget::slotGetGazePoint()
{
//    QLFrameData framedata = QEyeControl::Instance()->GetCDDControl()->GetNowFrame();
//    QPoint leftpoint,rightpoint;
//    QPointF leftpointNow,RightpointNow;
//    int width = ui->widget_picture->width();
//    int height = ui->widget_picture->height();
//    int tvwidth = GetScreenSize().width();
//    int tvheight = GetScreenSize().height();
//    if(framedata.LeftEye.Found&&framedata.RightEye.Found)
//    {
//        int leftx = (int)(framedata.LeftEye.GazePoint.x*width/100);
//        int lefty = (int)(framedata.LeftEye.GazePoint.y*height/100);
//        int rightx = (int)(framedata.RightEye.GazePoint.x*width/100);
//        int righty = (int)(framedata.RightEye.GazePoint.y*height/100);
//         qDebug()<<"x" <<framedata.LeftEye.GazePoint.x<<"y"<<framedata.LeftEye.GazePoint.y;
//        leftpointNow.setX(framedata.LeftEye.GazePoint.x);
//        leftpointNow.setY(framedata.LeftEye.GazePoint.y);
//        RightpointNow.setX(framedata.RightEye.GazePoint.x);
//        RightpointNow.setY(framedata.RightEye.GazePoint.y);
//        float leftdis = CalPointDistance(leftpointNow,Leftpoint_last);
//        float rightdis = CalPointDistance(leftpointNow,Leftpoint_last);
//        qDebug()<<"leftdis"<<leftdis<<"rightds"<<rightdis;
//        leftpoint.setX(leftx);
//        leftpoint.setY(lefty);
//        rightpoint.setX(rightx);
//        rightpoint.setY(righty);
//        Leftpoint_last.setX(framedata.LeftEye.GazePoint.x);
//        Leftpoint_last.setY(framedata.LeftEye.GazePoint.y);
//        RightPoint_last.setX(framedata.RightEye.GazePoint.x);
//        RightPoint_last.setY(framedata.RightEye.GazePoint.y);

//      //  if(leftdis<=1&&rightdis<=1)
//        //{
//            leftpointlist.clear();
//                leftpointlist.append(leftpoint);
//                rightpointlist.append(rightpoint);

//                int tvleftx = (int)(framedata.LeftEye.GazePoint.x*tvwidth/100);
//                int tvlefty = (int)(framedata.LeftEye.GazePoint.y*tvheight/100);
//                emit signalSendPoint(QPoint(tvleftx,tvlefty));
//                ui->widget_picture->SetDrawType(QShowpicWidget::eyeTrack);
//                ui->widget_picture->setEyeTrackLeftPoinList(leftpointlist);
//               // ui->widget_picture->setEyeTrackRightPoinList(rightpointlist);
//                ui->widget_picture->update();


//        //}

//    }



                    QLFrameData framedata = QEyeControl::Instance()->GetCDDControl()->GetNowFrame();
                    QPoint leftpoint,rightpoint;
                    QPointF leftpointNow,RightpointNow;
                    int width = ui->widget_picture->width();
                    int height = ui->widget_picture->height();
                    int tvwidth = GetScreenSize().width();
                    int tvheight = GetScreenSize().height();
                    if(framedata.LeftEye.Found&&framedata.RightEye.Found)
                    {
                        int leftx = (int)(framedata.LeftEye.GazePoint.x*width/100);
                        int lefty = (int)(framedata.LeftEye.GazePoint.y*height/100);
                        int rightx = (int)(framedata.RightEye.GazePoint.x*width/100);
                        int righty = (int)(framedata.RightEye.GazePoint.y*height/100);
                     //    qDebug()<<"x" <<framedata.LeftEye.GazePoint.x<<"y"<<framedata.LeftEye.GazePoint.y;

                       // qDebug()<<"leftdis"<<leftdis<<"rightds"<<rightdis;
                        leftpoint.setX(leftx);
                        leftpoint.setY(lefty);
                        rightpoint.setX(rightx);
                        rightpoint.setY(righty);

                        int tvleftx = (int)(framedata.LeftEye.GazePoint.x*tvwidth/100);
                        int tvlefty = (int)(framedata.LeftEye.GazePoint.y*tvheight/100);
                        qDebug()<<"tvwidget"<<tvwidth<<"tvheight"<<tvheight<<"tvx"<<tvleftx<<"tv y"<<tvlefty<<"x"<<framedata.LeftEye.GazePoint.x<<"y"<<framedata.LeftEye.GazePoint.y;
                        emit signalSendPoint(QPoint(tvleftx,tvlefty));

                        FrameCount++;
                        if((FrameCount+1)%10==0)  //15副图有 15*33 ms 大概500ms的时间取点
                        {

                            leftpointNow.setX(framedata.LeftEye.GazePoint.x);
                            leftpointNow.setY(framedata.LeftEye.GazePoint.y);
                            RightpointNow.setX(framedata.RightEye.GazePoint.x);
                            RightpointNow.setY(framedata.RightEye.GazePoint.y);
                            float leftdis = CalPointDistance(leftpointNow,Leftpoint_last);
                            float rightdis = CalPointDistance(leftpointNow,Leftpoint_last);
                            Leftpoint_last.setX(framedata.LeftEye.GazePoint.x);
                            Leftpoint_last.setY(framedata.LeftEye.GazePoint.y);
                            RightPoint_last.setX(framedata.RightEye.GazePoint.x);
                            RightPoint_last.setY(framedata.RightEye.GazePoint.y);
                            if(leftdis<=1&&rightdis<=1)
                            {

                                    leftpointlist.append(leftpoint);
                                   rightpointlist.append(rightpoint);


                                    ui->widget_picture->SetDrawType(QShowpicWidget::eyeTrack);
                                    ui->widget_picture->setEyeTrackLeftPoinList(leftpointlist);
                                   // ui->widget_picture->setEyeTrackRightPoinList(rightpointlist);
                                    ui->widget_picture->update();


                            }
                            FrameCount = 0;
                        }

                    }


















}
void QEyeTrackWidget::slotStopEyeTrack()
{
    stopEyeTrackTimer->stop();
    EyeTrackStatus = false;

}

void QEyeTrackWidget::Slot_GetFrame()
{

        IplImage  * dstImage;
        IplImage  * srcImage;

        CvSize dstsize;
        dstsize.width = ui->label_showvideo->width();
        dstsize.height = ui->label_showvideo->height();
        //图片cvSize设置长宽
        srcImage = QEyeControl::Instance()->GetCDDControl()->GetShowVideoDraw();
        DrawFrameInfo();

        dstImage=cvCreateImage(dstsize,srcImage->depth,srcImage->nChannels);
        cvResize(srcImage,dstImage);
        imageshow= QEyeControl::Instance()->GetCDDControl()->IplImage2QImageColor(dstImage);
        ui->label_showvideo->setPixmap(QPixmap::fromImage(imageshow));
        ui->label_showvideo->show();
        cvReleaseImage(&dstImage);

}
void QEyeTrackWidget::stopGather()
{
        if(showTimer->isActive())
            showTimer->stop();
        if(stopEyeTrackTimer->isActive())
            stopEyeTrackTimer->stop();
        if(EyeTrackTimer->isActive())
            EyeTrackTimer->stop();

}

void QEyeTrackWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}
void QEyeTrackWidget::timerEvent(QTimerEvent *e)
{

    Q_UNUSED(e);
}
void QEyeTrackWidget::closeEvent(QCloseEvent *event)
{

    Q_UNUSED(event);

}
void QEyeTrackWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

}
bool QEyeTrackWidget::eventFilter(QObject *watched, QEvent *event)
{

    return QWidget::eventFilter(watched,event);

}


void QEyeTrackWidget::on_pushButtonStartTrack_clicked()
{
    ui->pushButtonStartTrack->setEnabled(false);
    ui->pushButton_StopTrack->setEnabled(true);
    EyeTrackStatus=true;
    timeTimerCount=ui->lineEdit_time->text().toUInt();

    if(EyeTrackPic==Graze)  //如果选择凝视点 则随机生成 目标点  同时显示在大屏幕和 小屏幕
    {
        grazeTimer->start(5000);
    }
    ui->widget_picture->SetDrawType(QShowpicWidget::eyeTrack);
    ui->widget_picture->clearPointList();
    EyeTrackTimer->start(33);




}
void QEyeTrackWidget::stopEyeTrack()
{
    ui->pushButtonStartTrack->setEnabled(true);
    ui->pushButton_StopTrack->setEnabled(false);
    ui->widget_picture->clearPointList();
    ui->widget_picture->setBgPicture(EyeTrackPic);
    ui->widget_picture->update();
    EyeTrackStatus=false;
    stopEyeTrackTimer->stop();
    if(EyeTrackTimer->isActive())
        EyeTrackTimer->stop();

}
void QEyeTrackWidget::on_pushButton_StopTrack_clicked()
{
    if(Graze==EyeTrackPic)
    {
        stopGraze();
    }

    stopEyeTrack();


}
