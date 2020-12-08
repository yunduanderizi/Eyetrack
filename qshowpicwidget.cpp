#include "qshowpicwidget.h"
#include<QDebug>
#include<QEvent>
#include<QPalette>
#include<QPen>
#include<QBrush>
#include<QPainter>
QShowpicWidget::QShowpicWidget(QWidget *parent) : QWidget(parent)
{
    this->installEventFilter(this);
    picType = noSignale;
}

void QShowpicWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    if(DrawPictype == onePoint)  //校准时画点一个一个的目标
    {
        SetBgColor();
        drawTarget(painter,NowPoint,10);

    }
    else if(DrawPictype==notype)
    {
        SetBgColor();
    }
    else if(DrawPictype == pointList)  //校准完成后 画所有的目标和眼睛的位置
    {
        drawTargetandCalibration(painter,10);
    }
    else if(DrawPictype == eyeTrack)  //眼睛追踪时 画背景图 和眼睛的位置
    {
        qDebug()<<"EyetrackleftpOinstlist size"<<EyeTrackleftPointList.size();
        drawLeftEyePosition(painter,EyeTrackleftPointList);
        drawRightEyePosition(painter,EyeTrackrightPointList);
    }


}
void QShowpicWidget::drawLeftEyePosition(QPainter &painter, QList<QPoint> pointlist, int radius, QColor color)
{

    for(int i =0;i<pointlist.size();i++)
    {
        drawTarget(painter,pointlist.at(i),radius,color);
    }
}
void QShowpicWidget::drawRightEyePosition(QPainter &painter, QList<QPoint> pointlist, int radius, QColor color)
{

    for(int i =0;i<pointlist.size();i++)
    {
        drawTarget(painter,pointlist.at(i),radius,color);
    }
}
void QShowpicWidget::SetPicType(SignalType type)
{
    picType = type;
    setBgPicture(picType);
}

void QShowpicWidget::setBgPicture(SignalType picType)
{
    QPalette palette = this->palette();

    if(picType==noSignale)
    {
        QPixmap pixmap(":/Image/Res/Image/bg.jpg");
        qDebug()<<pixmap.height();
        palette.setBrush(QPalette::Background,QBrush(pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// 使用平滑的缩放方式

    }
    else if(picType==Graze)
    {
        SetBgColor();
    }

    else if(picType == SPicture)
    {

        QPixmap pixmap(":/Image/Res/Image/S_001.png");
        qDebug()<<pixmap.height();
        palette.setBrush(QPalette::Background,QBrush(pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// 使用平滑的缩放方式

    }
    else if(picType == SportsLines)
    {
        QPixmap pixmap(":/Image/Res/Image/S_002.png");
        qDebug()<<pixmap.height();
        palette.setBrush(QPalette::Background,QBrush(pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// 使用平滑的缩放方式

    }
    else if(picType == RandomPic)
    {
        QPixmap pixmap(":/Image/Res/Image/bg.jpg");
        qDebug()<<pixmap.height();
        palette.setBrush(QPalette::Background,QBrush(pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// 使用平滑的缩放方式

    }
      this->setAutoFillBackground(true);
     this->setPalette(palette);// 给widget加上背景图
}
bool QShowpicWidget::eventFilter(QObject * watched,QEvent *event)
{
  //  qDebug()<<"watched2222222"<<watched<<"event"<<event->type();
    QPainter painter(this);


    return QWidget::eventFilter(watched,event);


}
void QShowpicWidget::DrawLines(QPainter &painter, QPoint leftpoint,QPoint ringhtpoint,int size,QColor leftcolor,QColor rightcolor)
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
void QShowpicWidget::SetBgColor(QColor color)
{
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, color);
    setPalette(pal);
    setAutoFillBackground(true);

}
void QShowpicWidget::drawTarget(QPainter &painter, QPoint point, int radius, QColor color)
{
    QPen pen(color);
    QBrush brush(color);
    painter.setPen(pen);
    painter.setBrush(brush);
    PaintCirle(painter,point,radius,radius);

}
void QShowpicWidget::drawTargetandCalibration(QPainter &painter, int radius, QColor Circlecolor, QColor leftColor, QColor rightColor)
{
    QPen pen(Circlecolor);
    QBrush brush(Circlecolor);
    painter.setPen(pen);
    painter.setBrush(brush);

    for(int i=0;i<targetPointList.size();i++)
    {
        drawTarget(painter,targetPointList[i],radius,Circlecolor);
        DrawLines(painter,leftPointList[i],rightPointList[i],10,leftColor,rightColor);
    }
}
void QShowpicWidget::PaintCirle(QPainter & painter,QPoint pointer, int cx, int cy)
{
    painter.drawEllipse(pointer,cx,cy);
}
