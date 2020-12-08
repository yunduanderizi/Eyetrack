#include "qcalibrationwidget.h"
#include "ui_qcalibrationwidget.h"
#include<QPixmap>
#include"qeyecontrol.h"
#include<QColorDialog>
QCalibrationWidget::QCalibrationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QCalibrationWidget)
{

    ui->setupUi(this);
    showTimer = new QTimer(this);
    CalibrateTimer = new QTimer(this);

    ui->label_showvideo->installEventFilter(this); //这行不能省

    thread = new EyeCalibrateThread(this);  //创建用于校准的线程
    connect(thread,SIGNAL(SendUpdate()),this,SLOT(slotFinishUpdate())); //  线程校准完成一个目标后 返回信号
    //void(EyeCalibrateThread(::*signalSendPoint)(QPoint) = &EyeCalibrateThread::signalSendPoint;
    connect(thread,SIGNAL(signalSendPoint(QPoint)),this,SLOT(slot_CalibratePoint(QPoint)));   //接收到校准目标坐标
    connect(showTimer,SIGNAL(timeout()),this,SLOT(Slot_GetFrame()));        //用于显示视频的定时器
    connect(CalibrateTimer,SIGNAL(timeout()),this,SLOT(Slot_DrawLabel()));   //用于校准的定时器 暂时不用


    connect(thread,SIGNAL(signalSendtarget(QPointF)),this,SLOT(slotGetTarget(QPointF)));
    InitCcdConnect();  //初始化ccd
    InitShowWidget();  //初始化按钮
    ui->widget_picture->SetBgColor();

}


QCalibrationWidget::~QCalibrationWidget()
{
    qDebug()<<QStringLiteral("QCalibrationWidget  析构函数");
    if(showTimer->isActive())
        showTimer->stop();
    if(CalibrateTimer->isActive())
        CalibrateTimer->stop();

    showTimer = NULL;
    CalibrateTimer = NULL;
    delete showTimer;
    delete  CalibrateTimer;
    delete ui;
}
void QCalibrationWidget::slotFinishUpdate()
{

    //校准完成后设置 状态设置各个pointlist 然后刷新界面
    ui->widget_picture->SetDrawType(QShowpicWidget::pointList);
    QList<QPoint> targetlist,leftlist,rightlist,TVtargetlist;
    QPoint drawpoint;
    QEyeControl::Instance()->GetCaliControl()->CalibrateGetScores();  //获取所有分数
    int tx=0,ty=0;
    for(int i =0;i<QEyeControl::Instance()->GetCaliControl()->GetCalibrateNums();i++)
    {
        tx = (int)QEyeControl::Instance()->GetCaliControl()->targets[i].x * ui->widget_picture->size().width()/100;
        ty = (int)QEyeControl::Instance()->GetCaliControl()->targets[i].y * ui->widget_picture->size().height()/100;
        drawpoint.setX(tx);
        drawpoint.setY(ty);
        targetlist.append(drawpoint);
        tx = (int)QEyeControl::Instance()->GetCaliControl()->targets[i].x * GetScreenSize().width()/100;
        ty = (int)QEyeControl::Instance()->GetCaliControl()->targets[i].y * GetScreenSize().height()/100;
        drawpoint.setX(tx);
        drawpoint.setY(ty);

        TVtargetlist.append(drawpoint);
        tx = (int)(QEyeControl::Instance()->GetCaliControl()->targets[i].x  + QEyeControl::Instance()->GetCaliControl()->leftscores[i].x) * ui->widget_picture->size().width()/100;
        ty = (int)(QEyeControl::Instance()->GetCaliControl()->targets[i].y + QEyeControl::Instance()->GetCaliControl()->leftscores[i].y) * ui->widget_picture->size().height()/100;
        drawpoint.setX(tx);
        drawpoint.setY(ty);
        leftlist.append(drawpoint);
        tx = (int)(QEyeControl::Instance()->GetCaliControl()->targets[i].x  + QEyeControl::Instance()->GetCaliControl()->rightsocres[i].x )* ui->widget_picture->size().width()/100;
        ty = (int)(QEyeControl::Instance()->GetCaliControl()->targets[i].y + QEyeControl::Instance()->GetCaliControl()->rightsocres[i].y )* ui->widget_picture->size().height()/100;
        drawpoint.setX(tx);
        drawpoint.setY(ty);
        rightlist.append(drawpoint);
    }

    QEyeControl::Instance()->GetCaliControl()->SetCalibrateStatus(true);
    QEyeControl::Instance()->GetCaliControl()->CalibrateFinalized();
    QEyeControl::Instance()->GetCaliControl()->Applycalibration();

    ui->widget_picture->setRigthList(rightlist);
    ui->widget_picture->setLeftList(leftlist);
    ui->widget_picture->setTargetList(targetlist);
    ui->widget_picture->update();

    emit signaleCalibrateFinished();
    //emit signaleSendTargetlist(targetlist);  //发送所有的目标到大屏幕 没必要应该  但是保留功能
}

void QCalibrationWidget::InitCcdConnect()
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
void QCalibrationWidget::InitShowWidget()
{
    ui->comboBox_CalibrateNum->addItem("5");
    ui->comboBox_CalibrateNum->addItem("9");
    ui->comboBox_CalibrateNum->addItem("16");
    ui->comboBox_CalibrateNum->setCurrentIndex(1);
    ui->pushButton_StopCalibraion->setEnabled(false);

}
void QCalibrationWidget::slotGetTarget(QPointF point)
{
    qDebug()<<"slotGettarget"<<point;
    QPoint TVpoint;
    int width = GetScreenSize().width();
    int height = GetScreenSize().height();

    TVpoint.setX(point.x()*width/100);
    TVpoint.setY(point.y()*height/100);

    emit signaleSendOnePoint(TVpoint);  //收到校准玩的point 发送到 大屏幕 进行 校准用
}
void QCalibrationWidget::slot_CalibratePoint(QPoint point)
{


    qDebug()<<"slot_CalibratePoint"<<point;
    ui->widget_picture->setNowPoint(point);
    ui->widget_picture->SetDrawType(QShowpicWidget::onePoint);
    ui->widget_picture->update();



}
void QCalibrationWidget::Slot_DrawLabel()//
{

    if(!QEyeControl::Instance()->GetCaliControl()->GetCalibrateStatus())//没校准完成
    {
          update();
    }
    else
    {
         qDebug()<<"校准已经完成";

          update();
          CalibrateTimer->stop();
    }

}
void QCalibrationWidget::DrawFrameInfo()
{
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

}
void QCalibrationWidget::slotPicType(SignalType picType)
{
    Q_UNUSED(picType)
    //接收到进入校准界面
    //设置背景颜色


}
void QCalibrationWidget::Slot_GetFrame()
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
void QCalibrationWidget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    if(showTimer->isActive())
        showTimer->stop();
    if(CalibrateTimer->isActive())
        CalibrateTimer->stop();

}
bool QCalibrationWidget::eventFilter(QObject *watched, QEvent *event)
{


//    if(watched == ui->widget_picture && event->type()==QEvent::Paint)
//    {
//        qDebug()<<"watched name"<<watched<<"event type"<<event->type();
//        QPainter painter(ui->widget_picture);

//        QPoint CirclePoint;
//        if(!QEyeControl::Instance()->GetCaliControl()->GetCalibrateStatus())//没校准完成在label上画 校准的图像
//        {
//            int num = QEyeControl::Instance()->GetCaliControl()->GetNowTargetNum();
//            int tx = (int)QEyeControl::Instance()->GetCaliControl()->targets[num].x *ui->widget_picture->size().width()/100;
//            int ty = (int)QEyeControl::Instance()->GetCaliControl()->targets[num].y *ui->widget_picture->size().height()/100;
//            qDebug()<<"eventFilter::"<<"tx:"<<tx<<"ty:"<<ty<<"QEyeControl::Instance()->GetCaliControl()->GetCalibrateNums()"<<num;
//            CirclePoint.setX(tx);
//            CirclePoint.setY(ty);
//            drawTarget(painter,CirclePoint,10);

//        }
//        else
//        {

//            drawTargetandCalibration(painter,5);
//            QEyeControl::Instance()->GetCaliControl()->CalibrateFinalized();
//           QEyeControl::Instance()->GetCaliControl()->CalibrateApply();
//           QEyeControl::Instance()->GetCaliControl()->SetCalibrateStatus(true);

//        }

//    }
    return QWidget::eventFilter(watched, event);
}
QRect QCalibrationWidget::GetScreenSize()
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
bool QCalibrationWidget::CalibrateTarget(QLCalibrationTarget target)
{

    QLCalibrationStatus status = QL_CALIBRATION_STATUS_OK;
    do
    {
        int tx = target.x * ui->widget_picture->size().width()/100;
        int ty = target.y * ui->widget_picture->size().height()/100;
        CirclePoint.setX(tx);
        CirclePoint.setY(ty);
        ui->widget_picture->SetDrawType(QShowpicWidget::onePoint);
        ui->widget_picture->setNowPoint(CirclePoint);
        ui->widget_picture->update();
        bool block = false;
        QEyeControl::Instance()->GetCaliControl()->CalibrateTarget(target,block);
        while(( QEyeControl::Instance()->GetCaliControl()->Calibration_GetStatus(target.targetId, &status) == QL_ERROR_OK) &&(status == QL_CALIBRATION_STATUS_CALIBRATING));

        QEyeControl::Instance()->GetCaliControl()->Calibration_GetStatus(target.targetId,&status);


    }while(status != QL_CALIBRATION_STATUS_OK);

    // Return true to indicate that the target has successfully been calibrated
    return true;
}

void QCalibrationWidget::DrawLines(QPainter &painter, QPoint leftpoint,QPoint ringhtpoint,int size,QColor leftcolor,QColor rightcolor)
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
void QCalibrationWidget::drawTargetandCalibration(QPainter &painter,int radius, QColor Circlecolor, QColor leftColor, QColor rightColor)
{
    Q_UNUSED(radius)
    Q_UNUSED(leftColor)
    Q_UNUSED(rightColor)
    QPen pen(Circlecolor);
    QBrush brush(Circlecolor);
    painter.setPen(pen);
    painter.setBrush(brush);

    QPoint drawpoint,leftpoint,rightpoint;
    int tx=0,ty=0;
    Q_UNUSED(tx)
    Q_UNUSED(ty)
    QEyeControl::Instance()->GetCaliControl()->CalibrateGetScores();  //获取所有分数
    for(int i =0;i<QEyeControl::Instance()->GetCaliControl()->GetCalibrateNums();i++)
    {
//        tx = (int)QEyeControl::Instance()->GetCaliControl()->targets[i].x * ui->showPicLabel->width()/100;
//        ty = (int)QEyeControl::Instance()->GetCaliControl()->targets[i].y * ui->showPicLabel->height()/100;
//        drawpoint.setX(tx);
//        drawpoint.setY(ty);
//        drawTarget(painter,drawpoint,radius,Circlecolor);
//        // Draw the left
//        tx = (int)(QEyeControl::Instance()->GetCaliControl()->targets[i].x  + QEyeControl::Instance()->GetCaliControl()->leftscores[i].x) * ui->showPicLabel->width()/100;
//        ty = (int)(QEyeControl::Instance()->GetCaliControl()->targets[i].y + QEyeControl::Instance()->GetCaliControl()->leftscores[i].y) * ui->showPicLabel->height()/100;
//        leftpoint.setX(tx);
//        leftpoint.setY(ty);
//        tx = (int)(QEyeControl::Instance()->GetCaliControl()->targets[i].x  + QEyeControl::Instance()->GetCaliControl()->rightsocres[i].x )* ui->showPicLabel->width()/100;
//        ty = (int)(QEyeControl::Instance()->GetCaliControl()->targets[i].y + QEyeControl::Instance()->GetCaliControl()->rightsocres[i].y )* ui->showPicLabel->height()/100;
//        rightpoint.setX(tx);
//        rightpoint.setY(ty);
//        DrawLines(painter,leftpoint,rightpoint,5,leftColor,rightColor);

    }
}
void QCalibrationWidget::drawTarget(QPainter &painter,QPoint point, int radius, QColor color)
{


    QPen pen(color);
    QBrush brush(color);
    painter.setPen(pen);
    painter.setBrush(brush);
    PaintCirle(painter,point,radius,radius);

}
void QCalibrationWidget::PaintCirle(QPainter & painter,QPoint pointer, int cx, int cy)
{
    painter.drawEllipse(pointer,cx,cy);
}

void QCalibrationWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)





//    QPainter painter(ui->widget_picture);

//        setAutoFillBackground(true);

//        if(QEyeControl::Instance()->GetCaliControl()->GetCalibrateStatus())
//        {
//            qDebug()<<"GetCalibrateStatus111"<<QEyeControl::Instance()->GetCaliControl()->GetCalibrateStatus();
//            drawTargetandCalibration(painter,20);
//            QEyeControl::Instance()->GetCaliControl()->CalibrateFinalized();
//            QEyeControl::Instance()->GetCaliControl()->CalibrateApply();
//            QEyeControl::Instance()->GetCaliControl()->SetCalibrateStatus(true);

//        }
//        else
//        {
//            qDebug()<<"GetCalibrateStatus2222"<<QEyeControl::Instance()->GetCaliControl()->GetCalibrateStatus();
//            drawTarget(painter,CirclePoint,20);

//        }



}
void QCalibrationWidget::timerEvent(QTimerEvent *e)
{

    Q_UNUSED(e)
}
void QCalibrationWidget::resizeEvent(QResizeEvent *event)
{

    Q_UNUSED(event)
  //  ShowCalibratePic();

}
void QCalibrationWidget::ShowCalibratePic()
{

//  qDebug()<<"labelsize"<<labelsize<<"labelpicsize"<<labelpicsize;
        //ui->showPicLabel->resize(ui->groupBox_pic->size());

//    QString ImageFilePath = QEyeControl::Instance()->GetImageFilePath();
//    QString filename("S_001.png");
//    QString filepath= ImageFilePath+"/"+filename;
//    QPixmap pixmap(filepath);
//    QPixmap scalePixmap=pixmap.scaled(ui->showPicLabel->size());

//    ui->showPicLabel->setPixmap(scalePixmap); //将图片放入label，使用setPixmap,注意指针*img

//    ui->showPicLabel->show();


}



void QCalibrationWidget::on_pushButton_StartCalibrion_clicked()
{

        ui->pushButton_StartCalibrion->setEnabled(false);
        ui->pushButton_StopCalibraion->setEnabled(true);
        ui->lineEdit_exposuretime->setReadOnly(true);
        QEyeControl::Instance()->GetCaliControl()->SetCalibrateStatus(false);
        thread->SetwidgetSize(ui->widget_picture->size().width(),ui->widget_picture->size().height());
        thread->startThread();
        thread->start();
      //  CalibrateTimer->start(500);

}

void QCalibrationWidget::on_pushButton_StopCalibraion_clicked()
{
        ui->pushButton_StartCalibrion->setEnabled(true);
        ui->pushButton_StopCalibraion->setEnabled(false);
        ui->widget_picture->SetDrawType(QShowpicWidget::notype);

        if(thread->isRunning())
        {
           thread->stopThread();
           thread->wait();
        }
        qDebug()<<"isruning"<<thread->isRunning();

}
void QCalibrationWidget::stopGather()
{
        if(showTimer->isActive())
            showTimer->stop();
        if(CalibrateTimer->isActive())
            CalibrateTimer->stop();
}

void QCalibrationWidget::on_pushButtonBgColor_clicked()
{

    QColor color = QColorDialog::getColor();

    if (!color.isValid()) {
        return;
    }

}


void QCalibrationWidget::on_pushButtonTargetColor_clicked()
{

    QColor color = QColorDialog::getColor();

    if (!color.isValid()) {
        return;
    }
}
