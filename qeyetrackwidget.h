#ifndef QEYETRACKWIDGET_H
#define QEYETRACKWIDGET_H

#include<QPoint>
#include<QPainter>
#include<qpalette.h>
#include<QTimer>
#include <QWidget>
#include<QLTypes.h>
#include<QEyeDefine.h>
#include<QList>
#include<QString>
namespace Ui {
class QEyeTrackWidget;
}

class QEyeTrackWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QEyeTrackWidget(QWidget *parent = nullptr);
    ~QEyeTrackWidget();

    void InitShowWidget();
    void InitCcdConnect();

    void PaintCirle(QPainter & painter,QPoint pointer,int cx,int cy);
    void DrawLines(QPainter &painter, QPoint leftpoint,QPoint ringhtpoint,int size,QColor leftcolor,QColor rightcolor);


    void DrawFrameInfo();
    void stopGather();

    QRect GetScreenSize();
    void SetTimeTimer(int Sec){timeTimerCount = Sec*1000;}  //设置测量时间  单位 s
    int GetTimemsTimer(){return timeTimerCount;}   //测量时间获取 单位ms
    void createPointAnddraw();         //生成凝视点并且划到屏幕上
    void stopGraze();       //停止凝视
    void stopEyeTrack();
private:
    Ui::QEyeTrackWidget *ui;
    QTimer * showTimer;
    QTimer * stopEyeTrackTimer;
     QTimer * EyeTrackTimer;
     QTimer * grazeTimer;       //控制凝视点生成的间隔的定时器


protected:
    void paintEvent(QPaintEvent *event);
      bool eventFilter(QObject *watched, QEvent *event);
    void timerEvent(QTimerEvent * e);
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);
private:

    int timeTimerCount;  //追踪的时间
    QLFrameData frame;
    QImage imageshow;
    bool EyeTrackStatus;  //是否采集凝视点 暂时不用


    QPoint  CirclePoint;  //校准中的每个目标点的坐标位置;
    SignalType EyeTrackPic;

    QPointF Leftpoint_last;
    QPointF RightPoint_last;
    QList<QPoint> leftpointlist;
    QList<QPoint>rightpointlist;
    int FrameCount;
    int grazePointNums;  //凝视点一共多少个 初始化为10
private:
    float CalPointDistance(QPointF nowPoint, QPointF lastPoint);
    void  getGazePoint(QLFrameData framedata);
public slots:
    void slotPicType(SignalType picType);

private slots:
    void Slot_GetFrame();
    void slotStopEyeTrack();
    void slotGetGazePoint();
    void slotCreateGazePoint();// 生成成凝视点


//    void  Slot_DrawLabel();
//    void slot_CalibratePoint(QPoint point);
//    void slotGetTarget(QPointF point);
//    void on_pushButton_StartCalibrion_clicked();        //点击开始校准按钮
//    void on_pushButton_StopCalibraion_clicked();


//    void on_pushButtonBgColor_clicked();

//    void slotFinishUpdate();

//    void on_pushButtonTargetColor_clicked();



    void on_pushButtonStartTrack_clicked();

    void on_pushButton_StopTrack_clicked();

signals:
    void signaleSendStartEyeTrack();
    void signalSendStopEyeTrack();
    void signalSendPoint(QPoint point);
    void signaleSendGazePoint(QPoint point);
};

#endif // QEYETRACKWIDGET_H
