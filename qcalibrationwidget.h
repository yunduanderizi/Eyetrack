#ifndef QCALIBRATIONWIDGET_H
#define QCALIBRATIONWIDGET_H

#include <QWidget>
#include<QEyeCommon.h>
#include<QTimer>
#include<QImage>
#include"mainwindow.h"
#include<QSize>
#include<QComboBox>
#include<QLabel>
#include<eyecalibratethread.h>
namespace Ui {
class QCalibrationWidget;
}

class QCalibrationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QCalibrationWidget(QWidget *parent = nullptr);
    ~QCalibrationWidget();

    void InitShowWidget();
    void InitCcdConnect();
    void ShowCalibratePic();
    void PaintCirle(QPainter & painter,QPoint pointer,int cx,int cy);
    void DrawLines(QPainter &painter, QPoint leftpoint,QPoint ringhtpoint,int size,QColor leftcolor,QColor rightcolor);
    void drawTarget( QPainter &painter,QPoint point,int radius,QColor color=QColor(229,131,8));
    void drawTargetandCalibration(QPainter &painter,int radius,QColor Circlecolor=QColor(229,131,8),QColor leftColor=QColor(255,0,0),QColor rightColor=QColor(255,255,255));
    void DrawFrameInfo();
    void stopGather();
    bool CalibrateTarget(QLCalibrationTarget target);
    QRect GetScreenSize();
protected:
    void paintEvent(QPaintEvent *event);
      bool eventFilter(QObject *watched, QEvent *event);
    void timerEvent(QTimerEvent * e);
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);
private:
    int width;
    int height;
    QLFrameData frame;
    QImage imageshow;
    QSize videoSize;

    QSize labelsize;
    QSize labelpicsize;
    qint32  CalibrationNum;     //校准点数
    int testnum;
    EyeCalibrateThread * thread;
    QPoint  CirclePoint;  //校准中的每个目标点的坐标位置;

public slots:
    void slotPicType(SignalType picType);

private slots:
    void Slot_GetFrame();
    void  Slot_DrawLabel();
    void slot_CalibratePoint(QPoint point);
    void slotGetTarget(QPointF point);
    void on_pushButton_StartCalibrion_clicked();        //点击开始校准按钮
    void on_pushButton_StopCalibraion_clicked();


    void on_pushButtonBgColor_clicked();

    void slotFinishUpdate();

    void on_pushButtonTargetColor_clicked();

private:
    QTimer * showTimer;
    QTimer * CalibrateTimer;            //显示labe 上的图片定时器
    Ui::QCalibrationWidget *ui;

signals:
    void signalSendStartCalibrate();
    void signalSendStopCalibrate();
    void signaleSendOnePoint(QPoint point);

    void signaleCalibrateFinished();
    void signaleSendTargetlist(QList<QPoint> targetlist);
    void singnalSendLeftlist(QList<QPoint> leftList);
    void singnalSendRightlist(QList<QPoint> rightList);

};

#endif // QCALIBRATIONWIDGET_H
