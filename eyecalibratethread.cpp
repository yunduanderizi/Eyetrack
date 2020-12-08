#include "eyecalibratethread.h"
#include"qcalibrationwidget.h"

EyeCalibrateThread::EyeCalibrateThread()
{

}
EyeCalibrateThread::EyeCalibrateThread(QObject *parent)
{
    calibrateWidget = (QCalibrationWidget *)parent;
    quitThread= false;

}
bool EyeCalibrateThread::CalibrateTarget(QLCalibrationTarget target)
{
     bool Okflag = false;  //是否校准成功 标记
    QLCalibrationStatus status = QL_CALIBRATION_STATUS_CALIBRATING;
    do
    {

        Okflag =false;
        bool block = true;
        QEyeControl::Instance()->GetCaliControl()->CalibrateTarget(target,block);
        QEyeControl::Instance()->GetCaliControl()->Calibration_GetStatus(target.targetId,&status);
        qDebug()<<"status "<<status<<"targetid"<<target.targetId;
        while((QEyeControl::Instance()->GetCaliControl()->Calibration_GetStatus(target.targetId, &status) == QL_ERROR_OK) &&(status == QL_CALIBRATION_STATUS_CALIBRATING));

        if(quitThread)
            break;

        if(status == QL_CALIBRATION_STATUS_OK)
        {
            QLCalibrationScore  leftsocre,rightscore;
            if(QEyeControl::Instance()->GetCaliControl()->GetCalibrateLeftScrore((int)target.targetId,&leftsocre))
            {
                qDebug()<<"leftscore"<<leftsocre.score;
                qDebug()<<"rightscore"<<rightscore.score;
                if(leftsocre.score>3.0&&leftsocre.score<-3.0&&rightscore.score>3.0&&rightscore.score<-3.0)
                {
                    continue;
                }
                else
                    Okflag=true;

            }
        }
        //QEyeControl::Instance()->GetCaliControl()->Calibration_GetStatus(target.targetId,&status);

    }while(!Okflag);

    // Return true to indicate that the target has successfully been calibrated
    return true;
}


void EyeCalibrateThread::run()
{
    qDebug()<<"this is run";
    if(QEyeControl::Instance()->GetCDDControl()->isInited())
            QEyeControl::Instance()->GetCaliControl()->SetDeviceId(QEyeControl::Instance()->GetCDDControl()->GetDeviceId());
        qDebug()<<"QEyeControl::Instance()->GetCaliControl()->CalibrateInitialize()"<<QEyeControl::Instance()->GetCaliControl()->CalibrateInitialize();
        if(QEyeControl::Instance()->GetCaliControl()->CalibrateInitialize())
        {
            //初始化成功;
            if(QEyeControl::Instance()->GetCaliControl()->CalibrateGetTargets())  // 获取targets 成功
             {
                for (int i = 0; i < QEyeControl::Instance()->GetCaliControl()->GetCalibrateNums(); i++)
                {
                    if(quitThread)
                    {
                        qDebug()<<"quitThread"<<quitThread;
                        break;
                    }
                    qDebug()<<"this calibrate num "<<i;
                    int tx = QEyeControl::Instance()->GetCaliControl()->targets[i].x * widgetWidth/100;
                    int ty = QEyeControl::Instance()->GetCaliControl()->targets[i].y * widgetHeight/100;
                    QPoint CirclePoint;
                    QPointF point;
                    point.setX(QEyeControl::Instance()->GetCaliControl()->targets[i].x);
                    point.setY(QEyeControl::Instance()->GetCaliControl()->targets[i].y);
                    emit signalSendtarget(point);
                    CirclePoint.setX(tx);
                    CirclePoint.setY(ty);
                    emit signalSendPoint(CirclePoint);

                    qDebug()<<"1111111111111111";
                    QEyeControl::Instance()->GetCaliControl()->SetNowTargetNum(i);
                    CalibrateTarget(QEyeControl::Instance()->GetCaliControl()->targets[i]);
                    qDebug()<<"jiaozhun chenggong ";


                }
                if(!quitThread)
                {
                    QEyeControl::Instance()->GetCaliControl()->SetCalibrateStatus(true);

                    emit SendUpdate();
                }
            }

         }
        quit();
}
