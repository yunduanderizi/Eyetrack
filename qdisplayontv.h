#ifndef QDISPLAYONTV_H
#define QDISPLAYONTV_H

#include <QWidget>
#include"QEyeDefine.h"
#include<QSize>
#include<QRect>

namespace Ui {
class QDisPlayOnTV;
}

class QDisPlayOnTV : public QWidget
{
    Q_OBJECT

public:
    explicit QDisPlayOnTV(QWidget *parent = nullptr);

    ~QDisPlayOnTV();
    int GetScreenCount();
    QRect GetTVSize();
    void GetComputerSize();
    void drawPicture(QPainter &painter,SignalType pictureType);
    void drawPicture(QPalette &palette,SignalType pictureType);
    void drawPoint(QPainter &painter,QPoint point);
    void drawPoint(QPainter &painter,QList<QPoint> pointList);
    void drawTargetPoints(QPainter &painter,QList<QPoint> pointlist);
    void PaintCirle(QPainter & painter,QPoint pointer, int cx, int cy);
     void drawTarget( QPainter &painter,QPoint point,int radius,QColor color=QColor(229,131,8));
    void setBgColor(QColor color = QColor(3,38,58));
protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::QDisPlayOnTV *ui;
    SignalType screenType;  //当前的屏幕显示的是什么图
    bool calibreateStatus;   //校准完成状态
    QPoint targetPoint;     //当前的目标的位置
    QPoint eyeTrackPoint;       //
    QPoint gazePoint;     //凝视点 的坐标
public slots:
    void initWidget();                         //初始化界面
    void initParameter();
    void slotbigScreenType(SignalType ScreenType);//屏幕需要显示的图片类型
    void slotCalibrateTargetPoint(QPoint  point);  //校准点的位置
    void slotEyetrackPoint(QPoint point);
    void slotGrazePoint(QPoint point);  //收到 graze 的目标点
    void calibratePoints(QList<QPoint> pointlist);//获取收到的所有的点
    void slotStartCalibrate();
    void slotStopCalibrate();
    void slotstartEyeTrack();
    void slotstopEyeTrack();

    void  slotReceivetargetlist(QList<QPoint> targetlist);
    void  slotRecevileftlist(QList<QPoint> leftlist);
    void  slotReceviRightlist(QList<QPoint> Rightlist);
    void  slotFinishedCalibrete();
    void  slotReCalibrate();

};

#endif // QDISPLAYONTV_H
