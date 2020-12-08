#include "qdisplayontv.h"
#include "ui_qdisplayontv.h"
#include<QDesktopWidget>
#include<QScreen>
#include<QApplication>
#include<QPainter>
#include"QDesktopWidget"
#include<QDebug>
QDisPlayOnTV::QDisPlayOnTV(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QDisPlayOnTV)
{
    ui->setupUi(this);
    initParameter();
    initWidget();

}

QDisPlayOnTV::~QDisPlayOnTV()
{
    delete ui;
}
void QDisPlayOnTV::paintEvent(QPaintEvent *event)
{

    Q_UNUSED(event);
    QPainter  painter(this);
 //   drawPicture(painter,screenType);    //画背景图
             //  qDebug()<<"screenType------------------"<<screenType;                          //如果是校准界面 显示目标点
    if(screenType == Calibrate)                                  //如果校准完成显示所有的校准点和目标点
    {
         if(!calibreateStatus)  // 校准成功
         {
             if(!targetPoint.isNull())
                drawTarget(painter,targetPoint,20);
         }

    }



   if(screenType == Graze)
    {
         drawTarget(painter,gazePoint,20);
    }
    drawTarget(painter,eyeTrackPoint,5,QColor(255,0,0));  //画眼睛位置

}
int QDisPlayOnTV::GetScreenCount()
{
    QList<QScreen *> list_screen =  QGuiApplication::screens();  //多显示器
    return list_screen.size();
}
QRect QDisPlayOnTV::GetTVSize()
{
    QList<QScreen *> list_screen = QGuiApplication::screens();  //多显示器
    QRect screenRect;
    if(list_screen.size()>1)
    {
        screenRect = list_screen.at(1)->geometry();
    }
    else
    {
        screenRect= list_screen.at(0)->geometry();
    }
    return screenRect;
}
void QDisPlayOnTV::initParameter()
{
    screenType = noSignale;
    calibreateStatus= false;
}
void QDisPlayOnTV::initWidget()
{

    this->setWindowFlag(Qt::FramelessWindowHint);
    this->showMaximized();
    this->setAttribute(Qt::WA_StyledBackground,true);
    QDesktopWidget* desktop = QApplication::desktop();
    if(GetScreenCount()<=1)
         setGeometry(desktop->screenGeometry(0));
    else
    {
        setGeometry(desktop->screenGeometry(1));

    }
    QPalette pal(this->palette());
    drawPicture(pal,screenType);
}
/*
//接收到信号后刷新主屏幕 如果和之前相同 不刷新屏幕 相同不刷新屏幕
*/
void QDisPlayOnTV::slotbigScreenType(SignalType ScreenType)
{
    qDebug()<<"screenType:"<<screenType<<"ScreenType:"<<ScreenType;
    if(screenType == ScreenType)
        return;
    else
        screenType = ScreenType;
    QPalette palette;
    palette = this->palette();
    drawPicture(palette,screenType);    //画背景图

}
void QDisPlayOnTV::slotGrazePoint(QPoint point)
{
    gazePoint=point;
    qDebug()<<"grazepoint"<<point;
    update();
}
void QDisPlayOnTV::slotEyetrackPoint(QPoint point)
{

   eyeTrackPoint = point;
   update();
}
//校准中每个校准点的位置
void QDisPlayOnTV::slotCalibrateTargetPoint(QPoint  point)
{
    Q_UNUSED(point)
    qDebug()<<"targetpoint"<<targetPoint;
    targetPoint=point;  //接收到当前的target 目标  刷新界面
    update();
}
//校准完成所有的校准点
void QDisPlayOnTV::calibratePoints(QList<QPoint> pointlist)
{
        Q_UNUSED(pointlist)
     //   update();
}
void QDisPlayOnTV::drawTarget(QPainter &painter, QPoint point, int radius, QColor color)
{
    QPen pen(color);
    QBrush brush(color);
    painter.setPen(pen);
    painter.setBrush(brush);
    PaintCirle(painter,point,radius,radius);

}
void QDisPlayOnTV::PaintCirle(QPainter & painter,QPoint pointer, int cx, int cy)
{
    painter.drawEllipse(pointer,cx,cy);
}

void QDisPlayOnTV::drawPoint(QPainter &painter, QPoint point)
{

}
void QDisPlayOnTV::drawPoint(QPainter &painter, QList<QPoint> pointList)
{
    Q_UNUSED(painter)
    Q_UNUSED(pointList)
}
void QDisPlayOnTV::drawPicture(QPalette &palette, SignalType pictureType)
{
    Q_UNUSED(palette)
    Q_UNUSED(pictureType)

    this->setAutoFillBackground(true);
    if(pictureType==noSignale)
    {
        QPixmap pixmap(":/Image/Res/Image/bg.jpg");
        qDebug()<<pixmap.height();
        palette.setBrush(QPalette::Background,QBrush(pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// 使用平滑的缩放方式
        this->setPalette(palette);// 给widget加上背景图
    }
    else if(pictureType == Calibrate)
    {
        //画背景色
        setBgColor();

    }
    else if(pictureType == Graze)
    {
        //画背景色
        setBgColor();

    }
    else if(pictureType == SPicture)
    {

        QPixmap pixmap(":/Image/Res/Image/S_001.png");
        qDebug()<<pixmap.height();
        palette.setBrush(QPalette::Background,QBrush(pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// 使用平滑的缩放方式
        this->setPalette(palette);// 给widget加上背景图
    }
    else if(pictureType == SportsLines)
    {
        QPixmap pixmap(":/Image/Res/Image/S_002.png");
        qDebug()<<pixmap.height();
        palette.setBrush(QPalette::Background,QBrush(pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// 使用平滑的缩放方式
        this->setPalette(palette);// 给widget加上背景图
    }
    else if(pictureType == RandomPic)
    {
        QPixmap pixmap(":/Image/Res/Image/bg.jpg");
        qDebug()<<pixmap.height();
        palette.setBrush(QPalette::Background,QBrush(pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// 使用平滑的缩放方式
        this->setPalette(palette);// 给widget加上背景图
    }

}
void QDisPlayOnTV::drawPicture(QPainter &painter,SignalType pictureType)
{
    Q_UNUSED(painter)
    Q_UNUSED(pictureType)
    qDebug()<<"piactureType"<<pictureType;
    QPalette palette = this->palette();
    this->setAutoFillBackground(true);
    if(pictureType==noSignale)
    {
        QPixmap pixmap(":/Image/Res/Image/bg.jpg");
        qDebug()<<pixmap.height();
        palette.setBrush(QPalette::Background,QBrush(pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// 使用平滑的缩放方式
        this->setPalette(palette);// 给widget加上背景图
    }
    else if(pictureType == Calibrate)
    {
        //画背景色
        setBgColor();

    }
    else if(pictureType == SPicture)
    {

        QPixmap pixmap(":/Image/Res/Image/S_001.png");
        qDebug()<<pixmap.height();
        palette.setBrush(QPalette::Background,QBrush(pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// 使用平滑的缩放方式
        this->setPalette(palette);// 给widget加上背景图
    }
    else if(pictureType == SportsLines)
    {
        QPixmap pixmap(":/Image/Res/Image/S_002.png");
        qDebug()<<pixmap.height();
        palette.setBrush(QPalette::Background,QBrush(pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// 使用平滑的缩放方式
        this->setPalette(palette);// 给widget加上背景图
    }
    else if(pictureType == RandomPic)
    {
        QPixmap pixmap(":/Image/Res/Image/bg.jpg");
        qDebug()<<pixmap.height();
        palette.setBrush(QPalette::Background,QBrush(pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// 使用平滑的缩放方式
        this->setPalette(palette);// 给widget加上背景图
    }

}
void QDisPlayOnTV::drawTargetPoints(QPainter &painter, QList<QPoint> pointlist)
{
    Q_UNUSED(painter)
    Q_UNUSED(pointlist)
    for(int i =0;i< pointlist.size();i++)
    {
        drawPoint(painter,pointlist.at(i));
    }



}
void QDisPlayOnTV::setBgColor(QColor color)
{
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, color);
    setPalette(pal);
    setAutoFillBackground(true);
}
void QDisPlayOnTV::slotStartCalibrate()

{
     calibreateStatus=false;
}
void QDisPlayOnTV::slotStopCalibrate()
{

}
void QDisPlayOnTV::slotstartEyeTrack()
{

}
void QDisPlayOnTV::slotstopEyeTrack()
{

}
void QDisPlayOnTV::slotReceivetargetlist(QList<QPoint> targetlist)
{

    update();
}
void QDisPlayOnTV::slotRecevileftlist(QList<QPoint> leftlist)
{
    update();
}
void QDisPlayOnTV::slotReceviRightlist(QList<QPoint> Rightlist)
{
    update();
}
void QDisPlayOnTV::slotFinishedCalibrete()   //校准完成  大屏幕 进行一部分显示
{
    calibreateStatus=true;
    update();
}
void QDisPlayOnTV::slotReCalibrate()
{
    calibreateStatus=false;
}
