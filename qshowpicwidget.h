#ifndef QSHOWPICWIDGET_H
#define QSHOWPICWIDGET_H

#include <QObject>
#include <QWidget>
#include<QPoint>
#include<QEyeDefine.h>
class QShowpicWidget : public QWidget
{
    Q_OBJECT

public:
    enum drawType{
        notype = 0,
        onePoint = 1,
        pointList = 2,
        eyeTrack = 3,

                      //等待添加其他

    };
    explicit QShowpicWidget(QWidget *parent = nullptr);
    void PaintCirle(QPainter & painter,QPoint pointer,int cx,int cy);

    void DrawLines(QPainter &painter, QPoint leftpoint,QPoint ringhtpoint,int size,QColor leftcolor,QColor rightcolor);

    void drawTarget( QPainter &painter,QPoint point,int radius,QColor color=QColor(229,131,8));

    void drawTargetandCalibration(QPainter &painter,int radius,QColor Circlecolor=QColor(229,131,8),QColor leftColor=QColor(255,0,0),QColor rightColor=QColor(255,255,255));

    void drawLeftEyePosition(QPainter & painter,QList<QPoint> pointlist,int radius=5,QColor color=QColor(255,0,0));
    void drawRightEyePosition(QPainter & painter,QList<QPoint> pointlist,int radius=5,QColor color = QColor(0,255,0));

    void setTargetList(QList<QPoint> pointlist){targetPointList = pointlist;}
    void setLeftList(QList<QPoint> pointlist){leftPointList = pointlist;}
    void setRigthList(QList<QPoint> pointlist){rightPointList = pointlist;}

    void setLeftPoint(QPoint point){leftPoint=point;}
    void setRightPoint(QPoint point){rightPoint = point;}
    void setNowPoint(QPoint point){NowPoint = point;}

    void SetBgColor(QColor color =QColor(3,38,58));
    void setBgPicture(SignalType picType);

    void SetDrawType(drawType  type){ DrawPictype = type;  }   //需要画一个点还是  校准完成的所有点
    QColor getBgColor(){return bgColor;}
    void SetPicType(SignalType type);
    void setEyeTrackLeftPoinList(QList<QPoint> pointlist){EyeTrackleftPointList.clear(),EyeTrackleftPointList = pointlist;}
    void setEyeTrackRightPoinList(QList<QPoint> pointlist){EyeTrackrightPointList.clear() ,EyeTrackrightPointList = pointlist;}
    void clearPointList(){
        EyeTrackleftPointList.clear();
        EyeTrackrightPointList.clear();
     }
protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject * watched, QEvent * event);

private:
    SignalType picType;
    drawType DrawPictype;
    QList<QPoint> leftPointList;
    QList<QPoint> rightPointList;
    QList<QPoint> targetPointList;
    QList<QPoint> EyeTrackleftPointList;
    QList<QPoint> EyeTrackrightPointList;


    QPoint leftPoint;   //右眼坐标
    QPoint rightPoint;  //左眼坐标
    QPoint NowPoint;  //当前坐标
    QColor bgColor;
signals:

};

#endif // QSHOWPICWIDGET_H
