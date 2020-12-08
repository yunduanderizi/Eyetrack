#ifndef QEYETRACKINGWIDGET_H
#define QEYETRACKINGWIDGET_H

#include <QWidget>
#include<QTimer>
#include"qccdcontrol.h"
#include"mainwindow.h"
#include"qcalibratewidgetontv.h"
#include"eyetrackertoolbox.h"
namespace Ui {
class QEyeTrackingWidget;
}

class QEyeTrackingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QEyeTrackingWidget(QWidget *parent = nullptr);
    ~QEyeTrackingWidget();
    void InitShowWidget();
    void InitCcdConnect();
    void DrawFrameInfo();
    void DrawGazePoint();
    void ShowGrazePic(QPainter& painter);
    void ShowSportsLines(QPainter& painter);
    void ShowSpicture(QPainter& painter);
    void ShowRandomPic(QPainter& painter);
    void ShowPicture();
    void PaintCirle(QPainter & painter,QPoint pointer, int cx, int cy);
    void drawPoint(QPainter &painter,QList<QPoint> leftPointlist,QList<QPoint> RightPointlist, int radius=10, QColor leftcolor=QColor(255,0,0),QColor RightColor=QColor(0,255,0));
    void stopGather();
protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent * e);
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
private:
    void * parents;
    QLFrameData frame;
    QImage imageshow;
    QCalibrateWidgetOnTv * TvWidget;
    QList<QPoint> leftpointlist;
    QList<QPoint>rightpointlist;
private slots:
    void Slot_GetFrame();
    void Slot_ShowGazePoint();
    void on_toolButton_Start_clicked(bool checked);

    void on_toolButton_Start_clicked();

    void on_toolButton_Stop_clicked();
signals:
    void EyeTrackType(SIGNALSYPE signal);
    void signaleSendStartEyeTrack();
    void signalSendStopEyeTrack();
public slots:
    void SlotGetSignalType(SIGNALSYPE signal);
    void SlotChangeCurrentstackWidget(int index);
    void slotPicType(SignalType picType);

private:
    QTimer * showTimer;
    QTimer * ShowPointTimer;
    SignalType ReceivedSignal;
    Ui::QEyeTrackingWidget *ui;
    bool EyeTrackflag;
    int FrameNum;
};

#endif // QEYETRACKINGWIDGET_H
