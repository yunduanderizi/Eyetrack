#ifndef EYECALIBRATETHREAD_H
#define EYECALIBRATETHREAD_H

#include<QThread>
#include<QObject>
#include"QPoint"
#include<QLTypes.h>
class QCalibrationWidget;

class EyeCalibrateThread : public QThread
{
    Q_OBJECT
public:
    explicit EyeCalibrateThread(QObject *parent = nullptr);

    EyeCalibrateThread();
    void run();
    bool CalibrateTarget(QLCalibrationTarget target);
    void SetPoint(QPoint point){CiclePoint = point;}
    void SetwidgetSize(int width,int height){ widgetWidth=width,widgetHeight=height;}
    void stopThread(){quitThread=true;}
    void startThread(){quitThread=false;}
private:
    QCalibrationWidget * calibrateWidget;
    QPoint CiclePoint;
    int widgetWidth;
    int widgetHeight;
    bool quitThread;
signals:
    void SendUpdate();
    void signalSendPoint(QPoint point);
    void signalSendtarget(QPointF pointf);  //发送的是 target.x target.y
};

#endif // EYECALIBRATETHREAD_H
