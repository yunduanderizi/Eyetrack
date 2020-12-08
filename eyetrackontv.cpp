#include "ui_eyetrackontv.h"
#include "EyeTrackOnTv.h"
#include "ui_EyeTrackOnTv.h"
#include<QDesktopWidget>
EyeTrackOnTv::EyeTrackOnTv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EyeTrackOnTv)
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

EyeTrackOnTv::~EyeTrackOnTv()
{
    //delete  painter;
    qDebug()<<"EyeTrackOnTv 析构函数";
    CalibrateTimer->stop();
    delete CalibrateTimer;
    delete  pen;
    delete  penColor;
    delete  bgColor;
    delete  brush;
    delete  font;

    delete ui;
}
void EyeTrackOnTv::SlotUpdate()
{
    update();
}
void EyeTrackOnTv::SlotEyeTrackingTimer()
{
    QLFrameData framedata = QEyeControl::Instance()->GetCDDControl()->GetNowFrame();
    QPoint leftpoint,rightpoint;
    int leftx = (int)(framedata.LeftEye.GazePoint.x*this->width()/100);
    int lefty = (int)(framedata.LeftEye.GazePoint.y*this->height()/100);
    int rightx = (int)(framedata.RightEye.GazePoint.x*this->width()/100);
    int righty = (int)(framedata.RightEye.GazePoint.y*this->height()/100);
    leftpoint.setX(leftx);
    leftpoint.setY(lefty);
    rightpoint.setX(rightx);
    rightpoint.setY(righty);
    qDebug()<<"label width "<<this->width()<<"heigt"<<this->height();
    qDebug()<<"leftx"<<leftx<<"left y"<<lefty;
    qDebug()<<"rightx"<<rightx<<"Righty"<<rightx;
   // qDebug()<<"leftpointx"<<leftpoint.x()<<"leftpointy"<<leftpoint.y();
    leftpointlist.append(leftpoint);
    rightpointlist.append(rightpoint);
    update();

}
void EyeTrackOnTv::Slot_CalibrateJudge()
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
void EyeTrackOnTv::PaintCirle(QPainter & painter,QPoint pointer, int cx, int cy)
{
    painter.drawEllipse(pointer,cx,cy);
}
void EyeTrackOnTv::PaintPoint(QPainter & painter,int x,int y)
{
    painter.drawPoint(x,y);
}
void EyeTrackOnTv::PaintRect(QPainter & painter,QRect rect)
{
    painter.drawRect(rect);
}
bool EyeTrackOnTv::InitWidgetFace()
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
void EyeTrackOnTv::ShowGrazePic(QPalette& pal)
{

}
void EyeTrackOnTv::ShowSpicture(QPalette &pal)
{
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/Image/Res/Image/S_001.png").scaled(this->size())));
    this->setPalette(pal);
}
void EyeTrackOnTv::ShowSportsLines(QPalette& pal)
{
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/Image/Res/Image/S_002.png").scaled(this->size())));
    this->setPalette(pal);

}
void EyeTrackOnTv::ShowRandomPic(QPalette& pal)
{
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/Image/Res/Image/bg.jpg").scaled(this->size())));
    this->setPalette(pal);
}
void EyeTrackOnTv::drawPoint(QPainter &painter, QList<QPoint> leftPointlist, QList<QPoint> RightPointlist, int radius, QColor leftcolor, QColor RightColor)
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
void EyeTrackOnTv::paintEvent(QPaintEvent *event)//用于修改图片位置
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
     // qDebug()<<"pictureType"<<pictureType;
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
     //   drawPoint(painter,leftpointlist,rightpointlist);

    }
}
void EyeTrackOnTv::closeEvent(QCloseEvent *event)
{
    QEyeControl::Instance()->GetCaliControl()->SetCalibrateStatus(false);
}
int EyeTrackOnTv::GetScreenCount()
{
  QList<QScreen *> list_screen =  QGuiApplication::screens();  //多显示器
  return list_screen.size();

}
QRect EyeTrackOnTv::GetScreenSize()
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
void EyeTrackOnTv::DrawLines(QPainter &painter, QPoint leftpoint,QPoint ringhtpoint,int size,QColor leftcolor,QColor rightcolor)
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
void EyeTrackOnTv::drawTarget(QPainter &painter, QPoint point, int radius, QColor color)
{
    QPen pen(color);
    QBrush brush(color);
    painter.setPen(pen);
    painter.setBrush(brush);
    PaintCirle(painter,point,radius,radius);

}

void EyeTrackOnTv::drawTargetandCalibration(QPainter &painter, int radius, QColor Circlecolor, QColor leftColor, QColor rightColor)
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

bool EyeTrackOnTv::AutoCalibrate()
{

    return true;
}
void EyeTrackOnTv::SetCalibrationType(int CalibrationNum)
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
void EyeTrackOnTv::StartEytTracking()
{
    EyeTrackTimer->start(300);

}
bool EyeTrackOnTv::CalibrateTarget(QLCalibrationTarget target)
{

    QLCalibrationStatus status = QL_CALIBRATION_STATUS_OK;
    do
    {
        int tx = target.x * GetScreenSize().width()/100;
        int ty = target.y * GetScreenSize().height()/100;
        qDebug()<<"tx:"<<tx<<"ty:"<<ty<<"CalibratetargetNum"<<CalibratetargetNum;
        CirclePoint.setX(tx);
        CirclePoint.setY(ty);
        update();

        bool block = false;

        QEyeControl::Instance()->GetCaliControl()->CalibrateTarget(target,block);

        while(( QEyeControl::Instance()->GetCaliControl()->Calibration_GetStatus(target.targetId, &status) == QL_ERROR_OK) &&(status == QL_CALIBRATION_STATUS_CALIBRATING));
        qDebug()<<"status::--------"<<status;
        QEyeControl::Instance()->GetCaliControl()->Calibration_GetStatus(target.targetId,&status);


    }while(status != QL_CALIBRATION_STATUS_OK);

    // Return true to indicate that the target has successfully been calibrated
    return true;
}
void EyeTrackOnTv::autoCalibrate()
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
bool EyeTrackOnTv::StartCalibrate()
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
int EyeTrackOnTv::GetNowCalibrationNum()
{
    return CalibratetargetNum;
}
void EyeTrackOnTv::SetPicType(SIGNALSYPE Picturetype)
{
    qDebug()<<"setpictype"<<"------------";
    pictureType = Picturetype;
    update();
}
