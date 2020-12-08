#include "qcalibratewidgetontv.h"
#include "ui_qcalibratewidgetontv.h"

QCalibrateWidgetOnTv::QCalibrateWidgetOnTv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QCalibrateWidgetOnTv)
{
    ui->setupUi(this);
    InitWidgetFace();
    CalibratetargetNum=0;
    screenProtity = NOPROPERTIES;
    pictureType = noSignale;
    control = QEyeControl::Instance();
    setAttribute(Qt::WA_QuitOnClose,false);
    CalibrateTimer = new QTimer;
    EyeTrackTimer = new QTimer;
    thread = new EyeCalibrateThread(this);
    connect(CalibrateTimer,SIGNAL(timeout()),this,SLOT(Slot_CalibrateJudge()));
    connect(EyeTrackTimer,SIGNAL(timeout()),this,SLOT(SlotEyeTrackingTimer()));
    connect(thread,SIGNAL(SendUpdate()),this,SLOT(SlotUpdate()));
}


QCalibrateWidgetOnTv::~QCalibrateWidgetOnTv()
{
    //delete  painter;
    qDebug()<<"QCalibrateWidgetOnTv 析构函数";
    CalibrateTimer->stop();
    delete CalibrateTimer;
    delete  pen;
    delete  penColor;
    delete  bgColor;
    delete  brush;
    delete  font;

    delete ui;
}
void QCalibrateWidgetOnTv::SlotUpdate()
{
    update();
}

float QCalibrateWidgetOnTv::CalPointDistance(QPointF nowPoint, QPointF lastPoint)
{
    double dis;//两点间距离
    double x,y;
    x = nowPoint.x()-lastPoint.x();
    y = nowPoint.y()-lastPoint.y();
    dis = sqrt(x*x+y*y);
    //qDebug()<<"dis:"<<dis;
    return dis;
}
void QCalibrateWidgetOnTv::SlotEyeTrackingTimer()
{
    QLFrameData framedata = QEyeControl::Instance()->GetCDDControl()->GetNowFrame();
    QPoint leftpoint,rightpoint;
    QPointF leftpointNow,RightpointNow;
    if(framedata.LeftEye.Found&&framedata.RightEye.Found)
    {
        int leftx = (int)(framedata.LeftEye.GazePoint.x*this->width()/100);
        int lefty = (int)(framedata.LeftEye.GazePoint.y*this->height()/100);
        int rightx = (int)(framedata.RightEye.GazePoint.x*this->width()/100);
        int righty = (int)(framedata.RightEye.GazePoint.y*this->height()/100);
        leftpointNow.setX(framedata.LeftEye.GazePoint.x);
        leftpointNow.setY(framedata.LeftEye.GazePoint.y);
        RightpointNow.setX(framedata.RightEye.GazePoint.x);
        RightpointNow.setY(framedata.RightEye.GazePoint.y);
        float leftdis = CalPointDistance(leftpointNow,Leftpoint_last);
        float rightdis = CalPointDistance(leftpointNow,Leftpoint_last);
        qDebug()<<"leftdis"<<leftdis<<"rightds"<<rightdis;
        leftpoint.setX(leftx);
        leftpoint.setY(lefty);
        rightpoint.setX(rightx);
        rightpoint.setY(righty);
        Leftpoint_last.setX(framedata.LeftEye.GazePoint.x);
        Leftpoint_last.setY(framedata.LeftEye.GazePoint.y);
        RightPoint_last.setX(framedata.RightEye.GazePoint.x);
        RightPoint_last.setY(framedata.RightEye.GazePoint.y);
        //leftpointlist.clear();
        //rightpointlist.clear();
        if(leftdis<=1&&rightdis<=1)
        {
                leftpointlist.append(leftpoint);
                rightpointlist.append(rightpoint);
                update();
        }

    }

//    qDebug()<<"label width "<<this->width()<<"heigt"<<this->height();
//    qDebug()<<"leftx"<<leftx<<"left y"<<lefty;
//    qDebug()<<"rightx"<<rightx<<"Righty"<<rightx;
   // qDebug()<<"leftpointx"<<leftpoint.x()<<"leftpointy"<<leftpoint.y();


}
void QCalibrateWidgetOnTv::Slot_CalibrateJudge()
{

    QEyeControl::Instance()->GetCaliControl()->CalibrateTarget(QEyeControl::Instance()->GetCaliControl()->targets[CalibratetargetNum]);
    QLCalibrationStatus status;
    if(QEyeControl::Instance()->GetCaliControl()->Calibration_GetStatus(QEyeControl::Instance()->GetCaliControl()->targets[CalibratetargetNum].targetId,&status))
    {
        qDebug()<<"Calibratestatus"<<status;
        if(status == QL_CALIBRATION_STATUS_OK)
        {
            QLCalibrationScore leftscore,rightscore;
            qDebug()<<"Slot_CalibrateJudge CalibratetargetNum"<<CalibratetargetNum;
            if((QEyeControl::Instance()->GetCaliControl()->GetCalibrateLeftScrore(CalibratetargetNum,&leftscore))&&(QEyeControl::Instance()->GetCaliControl()->GetCalibrateLeftScrore(CalibratetargetNum,&rightscore)))
            {
                qDebug()<<"leftscore:x"<<leftscore.x<<"leftscore.y"<<leftscore.y<<"leftscore.score"<<leftscore.score;
                qDebug()<<"rightscore:x"<<rightscore.x<<"rightscore.y"<<rightscore.y<<"rightscore.score"<<rightscore.score;
                CalibratetargetNum++;
                if(CalibratetargetNum>=QEyeControl::Instance()->GetCaliControl()->GetCalibrateNums())  //所有校准完成
                {
                    CalibratetargetNum=0;
                    CalibrateTimer->stop();         //关闭校准定时器
                    QEyeControl::Instance()->GetCaliControl()->SetCalibrateStatus(true);//校准完成
                    update();
                                                     //显示校准和目标的位置
                }
                int tx = (int)QEyeControl::Instance()->GetCaliControl()->targets[CalibratetargetNum].x * GetScreenSize().width()/100;
                int ty = (int)QEyeControl::Instance()->GetCaliControl()->targets[CalibratetargetNum].y * GetScreenSize().height()/100;
              //  qDebug()<<"tx:"<<tx<<"ty:"<<ty;
                CirclePoint.setX(tx);
                CirclePoint.setY(ty);
                update();
            }
        }
    }
    else
    {

    }

}
void QCalibrateWidgetOnTv::PaintCirle(QPainter & painter,QPoint pointer, int cx, int cy)
{
    painter.drawEllipse(pointer,cx,cy);
}
void QCalibrateWidgetOnTv::PaintPoint(QPainter & painter,int x,int y)
{
    painter.drawPoint(x,y);
}
void QCalibrateWidgetOnTv::PaintRect(QPainter & painter,QRect rect)
{
    painter.drawRect(rect);
}
bool QCalibrateWidgetOnTv::InitWidgetFace()
{

    // 将本窗口显示在tv
    //获取tv屏幕大小
    setWindowFlag(Qt::FramelessWindowHint);
    showMaximized();
    this->setAttribute(Qt::WA_StyledBackground,true);
  // this->setStyleSheet("background-color: rgb(3,38,58)");
    QDesktopWidget* desktop = QApplication::desktop();
    if(GetScreenCount()<=1)
         setGeometry(desktop->screenGeometry(0));
    else
    {
        setGeometry(desktop->screenGeometry(1));

    }

    return true;
}
void QCalibrateWidgetOnTv::ShowGrazePic(QPalette& pal)
{

}
void QCalibrateWidgetOnTv::ShowSpicture(QPalette &pal)
{
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/Image/Res/Image/S_001.png").scaled(this->size())));
    this->setPalette(pal);
}
void QCalibrateWidgetOnTv::ShowSportsLines(QPalette& pal)
{
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/Image/Res/Image/S_002.png").scaled(this->size())));
    this->setPalette(pal);

}
void QCalibrateWidgetOnTv::ShowRandomPic(QPalette& pal)
{
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/Image/Res/Image/bg.jpg").scaled(this->size())));
    this->setPalette(pal);
}
void QCalibrateWidgetOnTv::drawPoint(QPainter &painter, QList<QPoint> leftPointlist, QList<QPoint> RightPointlist, int radius, QColor leftcolor, QColor RightColor)
{


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
void QCalibrateWidgetOnTv::paintEvent(QPaintEvent *event)//用于修改图片位置
{
    QPainter painter(this);
    QPalette pal(this->palette());

    //设置背景黑色

    if(screenProtity==CALIBRATEPROPERTY)  //如果是校准界面
    {
        qDebug()<<"CALIBRATEPROPERTY"<<CALIBRATEPROPERTY;
        pal.setColor(QPalette::Background, QColor(3,38,58));
        setAutoFillBackground(true);
        setPalette(pal);
        if(QEyeControl::Instance()->GetCaliControl()->GetCalibrateStatus())
        {
            qDebug()<<"GetCalibrateStatus111"<<QEyeControl::Instance()->GetCaliControl()->GetCalibrateStatus();
            drawTargetandCalibration(painter,20);
            QEyeControl::Instance()->GetCaliControl()->CalibrateFinalized();
            QEyeControl::Instance()->GetCaliControl()->CalibrateApply();
            QEyeControl::Instance()->GetCaliControl()->SetCalibrateStatus(true);
            CalibratetargetNum=0;
        }
        else
        {
            qDebug()<<"GetCalibrateStatus2222"<<QEyeControl::Instance()->GetCaliControl()->GetCalibrateStatus();
            drawTarget(painter,CirclePoint,20);

        }
    }
    else if(screenProtity == EYETRACKINGPROPERTY) //如果是眼动追踪界面
    {
        //如果是凝视
      //qDebug()<<"pictureType"<<pictureType;
        switch(pictureType){
        case SPicture:
        {
            ShowSpicture(pal);
            break;
        }
        case SportsLines:
        {
           ShowSportsLines(pal);
            break;
        }
        case RandomPic:
        {
            ShowRandomPic(pal);
            break;
        }

        }
        drawPoint(painter,leftpointlist,rightpointlist);

    }
}
void QCalibrateWidgetOnTv::closeEvent(QCloseEvent *event)
{
    QEyeControl::Instance()->GetCaliControl()->SetCalibrateStatus(false);
}
int QCalibrateWidgetOnTv::GetScreenCount()
{
  QList<QScreen *> list_screen =  QGuiApplication::screens();  //多显示器
  return list_screen.size();

}
QRect QCalibrateWidgetOnTv::GetScreenSize()
{
    QList<QScreen *> list_screen = QGuiApplication::screens();  //多显示器
    screenComputerRect = list_screen.at(0)->geometry();

    if(list_screen.size()>1)
    {
           screenTVRect = list_screen.at(1)->geometry();
           return screenTVRect;
    }
    else
        return screenComputerRect;



}
void QCalibrateWidgetOnTv::DrawLines(QPainter &painter, QPoint leftpoint,QPoint ringhtpoint,int size,QColor leftcolor,QColor rightcolor)
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
void QCalibrateWidgetOnTv::drawTarget(QPainter &painter, QPoint point, int radius, QColor color)
{
    QPen pen(color);
    QBrush brush(color);
    painter.setPen(pen);
    painter.setBrush(brush);
    PaintCirle(painter,point,radius,radius);

}

void QCalibrateWidgetOnTv::drawTargetandCalibration(QPainter &painter, int radius, QColor Circlecolor, QColor leftColor, QColor rightColor)
{
    QPen pen(Circlecolor);
    QBrush brush(Circlecolor);
    painter.setPen(pen);
    painter.setBrush(brush);

    QPoint drawpoint,leftpoint,rightpoint;
    int tx=0,ty=0;
    QEyeControl::Instance()->GetCaliControl()->CalibrateGetScores();  //获取所有分数
    for(int i =0;i<QEyeControl::Instance()->GetCaliControl()->GetCalibrateNums();i++)
    {
        tx = (int)QEyeControl::Instance()->GetCaliControl()->targets[i].x * GetScreenSize().width()/100;
        ty = (int)QEyeControl::Instance()->GetCaliControl()->targets[i].y * GetScreenSize().height()/100;
        drawpoint.setX(tx);
        drawpoint.setY(ty);
        drawTarget(painter,drawpoint,radius,Circlecolor);
        // Draw the left
        tx = (int)(QEyeControl::Instance()->GetCaliControl()->targets[i].x  + QEyeControl::Instance()->GetCaliControl()->leftscores[i].x) * GetScreenSize().width()/100;
        ty = (int)(QEyeControl::Instance()->GetCaliControl()->targets[i].y + QEyeControl::Instance()->GetCaliControl()->leftscores[i].y) * GetScreenSize().height()/100;
        leftpoint.setX(tx);
        leftpoint.setY(ty);
        tx = (int)(QEyeControl::Instance()->GetCaliControl()->targets[i].x  + QEyeControl::Instance()->GetCaliControl()->rightsocres[i].x )* GetScreenSize().width()/100;
        ty = (int)(QEyeControl::Instance()->GetCaliControl()->targets[i].y + QEyeControl::Instance()->GetCaliControl()->rightsocres[i].y )* GetScreenSize().height()/100;
        rightpoint.setX(tx);
        rightpoint.setY(ty);
        DrawLines(painter,leftpoint,rightpoint,10,leftColor,rightColor);

    }
}

bool QCalibrateWidgetOnTv::AutoCalibrate()
{

    return true;
}
void QCalibrateWidgetOnTv::SetCalibrationType(int CalibrationNum)
{
    qDebug()<<"CalibrationNum"<<CalibrationNum;
    QLCalibrationType type;
    if(CalibrationNum==5)
    {
        type = QL_CALIBRATION_TYPE_5;
    }
    else if(CalibrationNum==9)
    {
        type = QL_CALIBRATION_TYPE_9;
    }
    else if(CalibrationNum==16)
    {
        type = QL_CALIBRATION_TYPE_16;
    }
    else
    {
           type = QL_CALIBRATION_TYPE_9;
    }
    QEyeControl::Instance()->GetCaliControl()->SetCalibrationType(type);
}
void QCalibrateWidgetOnTv::StartEytTracking()
{
    EyeTrackTimer->start(10);
}
void QCalibrateWidgetOnTv::StopEyeTracking()
{
    EyeTrackTimer->stop();
}
bool QCalibrateWidgetOnTv::CalibrateTarget(QLCalibrationTarget target)
{

    QLCalibrationStatus status = QL_CALIBRATION_STATUS_OK;
    do
    {
        int tx = target.x * GetScreenSize().width()/100;
        int ty = target.y * GetScreenSize().height()/100;
        qDebug()<<"CalibrateTarget tx:"<<tx<<"ty:"<<ty<<"CalibratetargetNum"<<CalibratetargetNum;
        CirclePoint.setX(tx);
        CirclePoint.setY(ty);
        update();

        bool block = false;

        QEyeControl::Instance()->GetCaliControl()->CalibrateTarget(target,block);
        qDebug()<<"calibrate  fanhui";
        while(( QEyeControl::Instance()->GetCaliControl()->Calibration_GetStatus(target.targetId, &status) == QL_ERROR_OK) &&(status == QL_CALIBRATION_STATUS_CALIBRATING));
        qDebug()<<"target:"<<target.targetId<<" status::--------"<<status;
        QEyeControl::Instance()->GetCaliControl()->Calibration_GetStatus(target.targetId,&status);


    }while(status != QL_CALIBRATION_STATUS_OK);

    // Return true to indicate that the target has successfully been calibrated
    return true;
}
void QCalibrateWidgetOnTv::autoCalibrate()
{
    thread->start();
//    if(QEyeControl::Instance()->GetCDDControl()->isInited())
//            QEyeControl::Instance()->GetCaliControl()->SetDeviceId(QEyeControl::Instance()->GetCDDControl()->GetDeviceId());
//        qDebug()<<"QEyeControl::Instance()->GetCaliControl()->CalibrateInitialize()"<<QEyeControl::Instance()->GetCaliControl()->CalibrateInitialize();
//        if(QEyeControl::Instance()->GetCaliControl()->CalibrateInitialize())
//        {
//            //初始化成功;
//            if(QEyeControl::Instance()->GetCaliControl()->CalibrateGetTargets())  // 获取targets 成功
//             {
//                for (int i = 0; i < QEyeControl::Instance()->GetCaliControl()->GetCalibrateNums(); i++)
//                {
//                    CalibratetargetNum=i;
//                    qDebug()<<"CalibratetargetNum"<<CalibratetargetNum;
//                    if (!CalibrateTarget(QEyeControl::Instance()->GetCaliControl()->targets[i]))
//                        return;

//                }
//            }

//         }
//    CalibratetargetNum=0;
//    CalibrateTimer->stop();         //关闭校准定时器
//    QEyeControl::Instance()->GetCaliControl()->SetCalibrateStatus(true);//校准完成
//    update();
}
bool QCalibrateWidgetOnTv::StartCalibrate()
{
autoCalibrate();
//    if(QEyeControl::Instance()->GetCDDControl()->isInited())
//        QEyeControl::Instance()->GetCaliControl()->SetDeviceId(QEyeControl::Instance()->GetCDDControl()->GetDeviceId());
//    qDebug()<<"QEyeControl::Instance()->GetCaliControl()->CalibrateInitialize()"<<QEyeControl::Instance()->GetCaliControl()->CalibrateInitialize();
//    if(QEyeControl::Instance()->GetCaliControl()->CalibrateInitialize())
//    {
//        //初始化成功;
//        if(QEyeControl::Instance()->GetCaliControl()->CalibrateGetTargets())  // 获取targets 成功
//        {
//            int tx = (int)QEyeControl::Instance()->GetCaliControl()->targets[CalibratetargetNum].x * GetScreenSize().width()/100;
//            int ty = (int)QEyeControl::Instance()->GetCaliControl()->targets[CalibratetargetNum].y * GetScreenSize().height()/100;
//            CirclePoint.setX(tx);
//            CirclePoint.setY(ty);
//            this->update();
//            CalibrateTimer->start(50);

//        }
//        else
//        {
//                qDebug()<<"CalibrateGetTargets error";
//        }



//    }
//    else
//    {
//        qDebug()<<"CalibrateInialize error";
//    }

    return true;
}
int QCalibrateWidgetOnTv::GetNowCalibrationNum()
{
    return CalibratetargetNum;
}
void QCalibrateWidgetOnTv::SetPicType(SIGNALSYPE Picturetype)
{
    qDebug()<<"setpictype"<<"------------";
    pictureType = Picturetype;
    update();
}
