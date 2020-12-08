#include "qeyecontrol.h"
#include <qccdcontrol.h>
#include<qcalibration.h>
#include<QEyeDefine.h>

const char * ImageFileName="TestPic";
const char *  configfile="EyeTrack.ini";
QEyeControl *QEyeControl::self = 0;
QEyeControl::QEyeControl()
{
    CalibrateStatus=false;
}
QEyeControl::~QEyeControl()
{
    qDebug()<<"QEyeControl 析构函数";

    SaveConfig();

    delete self;
    delete ccdControl;
    delete  calibrationControl;

//  delete configControl;
}
void QEyeControl::InitControl()
{
    QString path=GetApplicationPath();
    QString configfilename(configfile);
    configControl = new QEyeConfigControl(path,configfilename);
    ccdControl = new QCCDControl;
    calibrationControl = new QCalibration;
    sqlPatient  = new PatientCongrol;
    playAudio = new QPlayAudio;
}
void QEyeControl::InitConfigIni()
{

}
void QEyeControl::LoadConfig()
{
     CalibrateType=(QLCalibrationType)configControl->ReadIntIniFile(CALIBRATIONCONFIG,CALIBRATETYPE,QL_CALIBRATION_TYPE_9);

}
void QEyeControl::SaveConfig()
{
    configControl->WriteIntIniFile(CALIBRATIONCONFIG,CALIBRATETYPE,(int)CalibrateType);

}
/************************
获取屏幕大小
参数 screenNum  屏幕编号
返回值为 0  获取失败
***************************/
QRect QEyeControl::GetScreenSize(int screenNum)
{
    QDesktopWidget * desktop = QApplication::desktop();
    int screenCount = desktop->screenCount();
    QRect screen;
    if(screenNum>screenCount)
    {
        screen.setY(0);
        screen.setX(0);
    }
    else
        screen=desktop->screenGeometry(screenNum);
    qDebug("screen %d, width %d, height %d", screenNum, screen.width(), screen.height());
    return  screen;
}
QString QEyeControl::GetApplicationPath()
{
//获取程序当前运行目录
    QString fileName = QCoreApplication::applicationDirPath();
    qDebug()<<"filename:"<<fileName;
    return fileName;

}
QString QEyeControl::GetImageFilePath()
{
    QString QImageFileName(ImageFileName);
    QString ImageFilePath;
    ImageFilePath = GetApplicationPath()+"/"+QImageFileName+"/";
    qDebug()<<"ImageFilePath:"<<ImageFilePath;

    return ImageFilePath;
}
