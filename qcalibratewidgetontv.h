#ifndef QCALIBRATEWIDGETONTV_H
#define QCALIBRATEWIDGETONTV_H

#include <QWidget>
#include<QEyeCommon.h>
#include<QPoint>
#include<QPainter>
#include<QPen>
#include<QBrush>
#include<QPixmap>
#include<QBitmap>
#include<QPicture>
#include<QFont>
#include<QRect>
#include<QTimer>
#include<qcalibration.h>
#include"mainwindow.h"
#include"eyecalibratethread.h"
namespace Ui {
class QCalibrateWidgetOnTv;
}

class QCalibrateWidgetOnTv : public QWidget
{
    Q_OBJECT

public:
    explicit QCalibrateWidgetOnTv(QWidget *parent = nullptr);
    ~QCalibrateWidgetOnTv();
    bool InitWidgetFace();
    QRect GetScreenSize();
    int GetScreenCount();//获取屏幕个数
    void ShowEyeTrackVerification();//校准验证
    void ShowGrazePic(QPalette& pal);
    void ShowSportsLines(QPalette& pal);
    void ShowSpicture(QPalette& pal);
    void ShowRandomPic(QPalette& pal);
    void PaintCirle(QPainter & painter,QPoint pointer,int cx,int cy);
    void PaintPoint(QPainter & painter,int x,int y);
    void PaintRect(QPainter & painter,QRect rect);
    void DrawLines(QPainter &painter, QPoint leftpoint,QPoint ringhtpoint,int size,QColor leftcolor,QColor rightcolor);
    void drawTarget(QPainter & painter, QPoint point,int radius,QColor color=QColor(229,131,8));
    void drawTargetandCalibration(QPainter & painter,int radius,QColor Circlecolor=QColor(229,131,8),QColor leftColor=QColor(255,0,0),QColor rightColor=QColor(255,255,255));
    bool AutoCalibrate();
    int GetNowCalibrationNum();
    void SetCalibrationType(int CalibrationNum);
    bool StartCalibrate();
    SCREENPROPERTIES GetScreenProperty(){return screenProtity;}
    void SetScreenProperty(SCREENPROPERTIES property){screenProtity = property;}
    void SetPicType(SIGNALSYPE Picturetype);
    void StartEytTracking();
    void StopEyeTracking();
    QRect GetScreenRect(){ if(!screenTVRect.isEmpty()) return screenTVRect;}
    void autoCalibrate();
    void drawPoint(QPainter &painter,QList<QPoint> leftPointlist,QList<QPoint> RightPointlist, int radius=10, QColor leftcolor=QColor(255,0,0),QColor RightColor=QColor(0,255,0));
    bool CalibrateTarget(QLCalibrationTarget target);
    void SetCalibrateNum(int num){CalibratetargetNum = num;}
    int GetCalibrateNum(){return CalibratetargetNum;}
    float CalPointDistance(QPointF nowPoint,QPointF lastPoint);
private:
    Ui::QCalibrateWidgetOnTv *ui;
    QRect screenComputerRect; //电脑屏幕
    QRect screenTVRect;//电视屏幕
    int nScreenCount;
    SCREENPROPERTIES screenProtity;
  //  QPainter *  painter;
    QPen     *  pen;
    QColor   *  penColor;
    QColor  *   bgColor;
    QBrush  *   brush;
    QFont   *   font;
    QTimer  *   CalibrateTimer;
    QTimer  *    EyeTrackTimer;
    QPoint  CirclePoint;
    int CalibratetargetNum;// 校准的目标标记
    SIGNALSYPE pictureType;
    QPointF Leftpoint_last;
    QPointF RightPoint_last;
    QList<QPoint> leftpointlist;
    QList<QPoint>rightpointlist;
    EyeCalibrateThread *thread;
    QEyeControl * control;
protected:
    void paintEvent(QPaintEvent * event);
    void closeEvent(QCloseEvent *event);
private slots:
    void  Slot_CalibrateJudge();
    void SlotEyeTrackingTimer();
    void SlotUpdate();
};

#endif // QCALIBRATEWIDGETONTV_H
