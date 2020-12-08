#ifndef QEYECONTROL_H
#define QEYECONTROL_H


#include"qccdcontrol.h"
#include"qcalibration.h"
#include"QEyeCommon.h"
#include<QRect>
#include<QDesktopWidget>
#include"qeyeconfigcontrol.h"
#include"QEyeDefine.h"
#include"patientcongrol.h"
#include"qplayaudio.h"
#include"QMutex"
class QEyeControl
{
public:
    QEyeControl();
    ~QEyeControl();
    static QEyeControl *Instance() {
        static QMutex mutex;
        if (!self) {
            QMutexLocker locker(&mutex);
            if (!self) {
                self = new QEyeControl;
            }
        }
        return self;
    }
    void InitControl();
    void InitConfigIni();
    void LoadConfig();
    void SaveConfig();
    QCCDControl * GetCDDControl(){return ccdControl;}
    QCalibration * GetCaliControl(){return calibrationControl;}
    QEyeConfigControl * GetconfigControl(){return configControl;}
    QPlayAudio * GetPlayAudioControl(){return playAudio;}
    PatientCongrol * GetsqlPatientControl(){return sqlPatient;}

    QRect  GetScreenSize(int screen);
    QString GetApplicationPath();
    QString GetImageFilePath();

public:
    QCCDControl * ccdControl;               //ccd控制类指针
    QCalibration * calibrationControl;      //校准类指针
    QEyeConfigControl * configControl;      // 配置文件类指针
    QLCalibrationType CalibrateType;        //校准点数
    QPlayAudio * playAudio;
    PatientCongrol * sqlPatient;
private:

    bool        CalibrateStatus;            //是否校准  不校准无法进行其他测试
    static QEyeControl *self;

};

#endif // QEYECONTROL_H
