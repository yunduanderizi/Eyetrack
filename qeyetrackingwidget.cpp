#include "qeyetrackingwidget.h"
#include "ui_qeyetrackingwidget.h"
#include<QMessageBox>
#include"QEyeDefine.h"
#include<QTime>
QEyeTrackingWidget::QEyeTrackingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QEyeTrackingWidget)
{
    ui->setupUi(this);
    ReceivedSignal = noSignale;
    TvWidget = NULL;
    FrameNum =0;
    EyeTrackflag=false;
    showTimer = new QTimer(this);
    parents = (void * )parent;
    ShowPointTimer = new QTimer(this);
    setAttribute(Qt::WA_DeleteOnClose);
    connect(showTimer,SIGNAL(timeout()),this,SLOT(Slot_GetFrame()));
    connect(ShowPointTimer,SIGNAL(timeout()),this,SLOT(Slot_ShowGazePoint()));


    InitShowWidget();
    InitCcdConnect();
    ui->showPicLabel_2->setStyleSheet("QLabel{background-color:rgb(3,38,58);}");  //设置样式表
    ui->showPicLabel_2->installEventFilter(this);
}

QEyeTrackingWidget::~QEyeTrackingWidget()
{
    showTimer->stop();
    qDebug()<<QStringLiteral("QEyeTrackingWidget  析构函数");
    ShowPointTimer->stop();
    delete ShowPointTimer;
    delete showTimer;
    delete ui;
}
void QEyeTrackingWidget::ShowGrazePic(QPainter &painter)
{
    Q_UNUSED(painter)
    Q_UNUSED(painter);
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    //int n = qrand() % 1024;    //产生5以内的随机数


}
void QEyeTrackingWidget::ShowSpicture(QPainter &painter)
{
    Q_UNUSED(painter);
    ui->showPicLabel_2->setPixmap(QPixmap(":/Image/Res/Image/S_002.png"));
    ui->showPicLabel_2->setScaledContents(true);


}
void QEyeTrackingWidget::ShowSportsLines(QPainter& painter)
{
    Q_UNUSED(painter);
    ui->showPicLabel_2->setPixmap(QPixmap(":/Image/Res/Image/S_001.png"));
    ui->showPicLabel_2->setScaledContents(true);
}
void QEyeTrackingWidget::ShowRandomPic(QPainter &painter)
{
    Q_UNUSED(painter);
    ui->showPicLabel_2->setPixmap(QPixmap(":/Image/Res/Image/bg.jpg"));
    ui->showPicLabel_2->setScaledContents(true);
}
void QEyeTrackingWidget::SlotChangeCurrentstackWidget(int index)
{
    qDebug()<<"index"<<index;
    if(index==2)
    {

    }
    else
    {
       if(TvWidget)
       {
            TvWidget->close();
            TvWidget=NULL;
       }
    }
}
void QEyeTrackingWidget::slotPicType(SignalType picType)
{
    ReceivedSignal = picType;
}
void QEyeTrackingWidget::SlotGetSignalType(SIGNALSYPE signal)
{
    qDebug()<<"QEyeTrackingWidget signale"<<signal;
    ReceivedSignal = signal;
    QPainter painter(ui->showPicLabel_2);
    if((ReceivedSignal>=Graze)&&(ReceivedSignal<=RandomPic))
    {
        if(TvWidget==NULL){
            TvWidget = new QCalibrateWidgetOnTv;
            TvWidget->SetScreenProperty(EYETRACKINGPROPERTY);
        }
    }
    switch (ReceivedSignal){

        case Graze:
        {
            ShowGrazePic(painter);
            TvWidget->SetPicType(ReceivedSignal);
            break;
        }
        case SPicture:
        {
            ShowSpicture(painter);
            TvWidget->SetPicType(ReceivedSignal);
            break;
        }
        case SportsLines:
        {
            ShowSportsLines(painter);
            TvWidget->SetPicType(ReceivedSignal);
             break;
        }
        case RandomPic:
        {
            ShowRandomPic(painter);
            TvWidget->SetPicType(ReceivedSignal);
            break;
        }
        default:
            break;

        }




}
void QEyeTrackingWidget::InitCcdConnect()
{
    if(QEyeControl::Instance()->GetCDDControl()->isInited())
    {
         showTimer->start(33);
         QEyeControl::Instance()->GetCDDControl()->GetFrameSize();
     }
     else
    {
         if(QEyeControl::Instance()->GetCDDControl()->InitCCD())
         {
             if(QEyeControl::Instance()->GetCDDControl()->isInited())
             {
                 showTimer->start(33);
                 QEyeControl::Instance()->GetCDDControl()->GetFrameSize();
             }
         }

    }

}
void QEyeTrackingWidget::paintEvent(QPaintEvent *event)
{

    Q_UNUSED(event)

}
void QEyeTrackingWidget::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e)
}
bool QEyeTrackingWidget::eventFilter(QObject *watched, QEvent *event)
{

    if(watched == ui->showPicLabel_2 && event->type()==QEvent::Paint)
    {


//           drawPoint(painter,leftpointlist,rightpointlist);
    }
    return QWidget::eventFilter(watched, event);

}
void QEyeTrackingWidget::PaintCirle(QPainter & painter,QPoint pointer, int cx, int cy)
{
    painter.drawEllipse(pointer,cx,cy);
}
void QEyeTrackingWidget::drawPoint(QPainter &painter, QList<QPoint> leftPointlist, QList<QPoint> RightPointlist, int radius, QColor leftcolor, QColor RightColor)
{
    Q_UNUSED(leftcolor)
    Q_UNUSED(leftcolor)
    Q_UNUSED(RightColor)
    QPen leftpen(QColor(255,0,0));
    QBrush leftbrush(QColor(255,0,0));
    painter.setPen(leftpen);
    painter.setBrush(leftbrush);
    for(int i =0;i<leftPointlist.size();i++)
    {
        PaintCirle(painter,leftPointlist[i],radius,radius);
    }
//    QPen rightpen(leftcolor);
//    QBrush rightbrush(RightColor);
//    painter.setPen(rightpen);
//    painter.setBrush(rightbrush);
//    for(int i =0;i<RightPointlist.size();i++)
//    {
//        PaintCirle(painter,RightPointlist[i],radius,radius);

//    }

}
void QEyeTrackingWidget::InitShowWidget()
{
    ui->toolButton_Stop->setEnabled(false);
    ui->toolButton_Start->setEnabled(true);
 //   ui->toolButton_Start->setCheckable(true);
  //  qDebug()<<"ui->toolButton_Start->setCheckable"<<ui->toolButton_Start->isCheckable();
    ui->showPicLabel_2->move(ui->groupBox_pic_2->geometry().x(),ui->groupBox_pic_2->geometry().y());
    ui->labelShowVideo_3->move(ui->groupBox_video_2->geometry().x(),ui->groupBox_video_2->geometry().y());

}
void QEyeTrackingWidget::Slot_ShowGazePoint()
{
    ShowPointTimer->stop();

}
void QEyeTrackingWidget::Slot_GetFrame()
{
    IplImage  * dstImage;
    IplImage  * srcImage;
    ui->labelShowVideo_3->resize(ui->groupBox_video_2->size());
    CvSize dstsize;
    dstsize.width = ui->labelShowVideo_3->width();
    dstsize.height = ui->labelShowVideo_3->height();
    //图片cvSize设置长宽
    srcImage = QEyeControl::Instance()->GetCDDControl()->GetShowVideoDraw();
    DrawFrameInfo();
    if(EyeTrackflag)
        DrawGazePoint();
    dstImage=cvCreateImage(dstsize,srcImage->depth,srcImage->nChannels);
    cvResize(srcImage,dstImage);
    imageshow= QEyeControl::Instance()->GetCDDControl()->IplImage2QImageColor(dstImage);
    ui->labelShowVideo_3->setPixmap(QPixmap::fromImage(imageshow));
    ui->labelShowVideo_3->show();
    cvReleaseImage(&dstImage);
}
void QEyeTrackingWidget::ShowPicture()
{

     QPixmap pix;
    if(ReceivedSignal==SPicture)
    {
        pix.load(":/Image/Res/Image/S_001.png");
    }
    else if(ReceivedSignal == SportsLines)
    {
        pix.load(":/Image/Res/Image/S_002.png");
    }
    else if(ReceivedSignal == RandomPic)
    {
        pix.load(":/Image/Res/Image/bg.png");
    }
    else if(ReceivedSignal == Graze)
    {

    }
    QPainter painterpix(&pix);
    drawPoint(painterpix,leftpointlist,rightpointlist);
    ui->showPicLabel_2->setPixmap(pix);
    ui->showPicLabel_2->setScaledContents(true);
    //qDebug()<<"testt";

}
void QEyeTrackingWidget::DrawGazePoint()
{
        QLFrameData framedata= QEyeControl::Instance()->GetCDDControl()->GetNowFrame();
        QPoint leftpoint,rightpoint;
        int leftx = (int)(framedata.LeftEye.GazePoint.x*ui->showPicLabel_2->width()/100);
        int lefty = (int)(framedata.LeftEye.GazePoint.y*ui->showPicLabel_2->height()/100);
        int rightx = (int)(framedata.RightEye.GazePoint.x*ui->showPicLabel_2->width()/100);
        int righty = (int)(framedata.RightEye.GazePoint.y*ui->showPicLabel_2->height()/100);
        leftpoint.setX(leftx);
        leftpoint.setY(lefty);
        rightpoint.setX(rightx);
        rightpoint.setY(righty);
//        qDebug()<<"label width "<<ui->showPicLabel_2->width()<<"heigt"<<ui->showPicLabel_2->height();
//        qDebug()<<"leftx"<<leftx<<"left y"<<lefty;
//        qDebug()<<"rightx"<<rightx<<"Righty"<<rightx;
//       // qDebug()<<"leftpointx"<<leftpoint.x()<<"leftpointy"<<leftpoint.y();
        leftpointlist.append(leftpoint);
        rightpointlist.append(rightpoint);
        FrameNum++;

        if((FrameNum+1)%(MAXFRAMECOUNT)==0)
         {

            leftpointlist.append(leftpoint);
            rightpointlist.append(rightpoint);
            ShowPicture();
           // qDebug()<<"update";
          }
}
/*
     显示眼睛信息
*/
void QEyeTrackingWidget::DrawFrameInfo()
{
    QLFrameData framedata= QEyeControl::Instance()->GetCDDControl()->GetNowFrame();
    QString tmp;
    tmp = QString("%1").arg(framedata.Distance);
    ui->lineEdit_distance_3->setText(tmp);
    tmp = QString("%1").arg(framedata.Focus);
    ui->lineEdit_focus_3->setText(tmp);

    tmp = QString::asprintf("%.1f", framedata.LeftEye.Pupil.x);
    ui->lineEdit_LeftX_3->setText(tmp);
    tmp = QString::asprintf("%.1f", framedata.LeftEye.Pupil.y);
    ui->lineEdit_LeftY_3->setText(tmp);
    tmp = QString::asprintf("%.1f", framedata.RightEye.Pupil.x);
    ui->lineEdit_RightX_3->setText(tmp);
    tmp =QString::asprintf("%.1f", framedata.RightEye.Pupil.y);
    ui->lineEdit_RightY_3->setText(tmp);

}
void QEyeTrackingWidget::resizeEvent(QResizeEvent *event)
{
     Q_UNUSED(event)

     ui->showPicLabel_2->resize(ui->groupBox_pic_2->size());
}
void QEyeTrackingWidget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    if(showTimer->isActive())
    {
        showTimer->stop();
    }
    if(ShowPointTimer->isActive())
    {
        ShowPointTimer->stop();
    }

}



void QEyeTrackingWidget::on_toolButton_Start_clicked(bool checked)
{
Q_UNUSED(checked)
}

void QEyeTrackingWidget::on_toolButton_Start_clicked()
{
    if(TvWidget==NULL)
    {
        ui->toolButton_Stop->setEnabled(true);
        ui->toolButton_Start->setEnabled(false);
        TvWidget = new QCalibrateWidgetOnTv;
        TvWidget->SetScreenProperty(EYETRACKINGPROPERTY);
        TvWidget->StartEytTracking();
        ShowPointTimer->start(60000);
        EyeTrackflag=true;
    }
    else
    {
        TvWidget->SetScreenProperty(EYETRACKINGPROPERTY);
        TvWidget->StartEytTracking();
        ShowPointTimer->start(60000);
        EyeTrackflag=true;
    }
}

void QEyeTrackingWidget::on_toolButton_Stop_clicked()
{
    ui->toolButton_Stop->setEnabled(false);
    ui->toolButton_Start->setEnabled(true);
    TvWidget->close();
    TvWidget = NULL;
}
void QEyeTrackingWidget::stopGather()
{
    if(showTimer->isActive())
    {
        showTimer->stop();
    }
    if(ShowPointTimer->isActive())
    {
        ShowPointTimer->stop();
    }
}
