#ifndef QCALIBRATION_H
#define QCALIBRATION_H
#include"QEyeCommon.h"
const int CalibufferSize = 20;

const int cvWaitKeyEsc = 27;
const int cvWaitKeyEnter = 13;
class QCalibration
{
public:
    QCalibration();
    QCalibration(int CalibrationNums);
    ~QCalibration();
    void GetScreenSize();
    void SetDeviceId(QLDeviceId id);
    bool CalibrateInitialize();     //初始化
    bool CalibrateCreate();
    bool CalibrateGetTargets();      //获取目标
    bool AutoCalibrate();               //自动校准

    bool Applycalibration();            //应用校准
    bool CalibrateCancle();             //取消校准
    QRect GetComputerSize(){return screenComputerRect;}
    QRect GetTVSize(){return screenTVRect;}
    bool CalibrateTarget(QLCalibrationTarget target,bool block=false);

    bool Calibration_GetStatus( QLTargetId targetid, QLCalibrationStatus *status);
    void SetCalibrationType(QLCalibrationType CalibrationNums);
    int GetCalibrateNums(){return calibrateNums;}

    bool GetCalibrateStatus(){return calibrateStatus;}
    void SetCalibrateStatus(bool status){ calibrateStatus= status;}
    void CalibrateGetScores();
    bool GetCalibrateLeftScrore(int Num);
    bool GetCalibrateRightScrore(int Num);
    bool GetCalibrateLeftScrore(int Num,QLCalibrationScore * leftscore);
    bool GetCalibrateRightScrore(int Num,QLCalibrationScore * rightscore);
    void CalibrateFinalized(){    QLCalibration_Finalize(calibrationId);}
    void CalibrateApply(){   QLDevice_ApplyCalibration(DeviceId, calibrationId);}
    QLCalibrationTarget targets[CalibufferSize];
    QLCalibrationScore leftscores[CalibufferSize];
    QLCalibrationScore  rightsocres[CalibufferSize];
    void SetNowTargetNum(int num){nowTargetNum = num;}
    int GetNowTargetNum(){return nowTargetNum;}
private:

    QRect screenComputerRect; //电脑屏幕
    QRect screenTVRect;//电视屏幕
    int nScreenCount;                    //屏幕个数
    QLDeviceId DeviceId;                 //设备id;
    QLCalibrationId calibrationId;      //校准id;
    QLCalibrationType calibrationType;  //校准类型 校准点的个数  枚举
    int             calibrateNums;//    和校准类型相对   校准点的个数
    IplImage* displayImage;               //显示用的opecv的图像
    int     nowTargetNum;                   //校准中当前的目标
    bool    calibrateStatus;            //校准状态   true 已经校准 false 未校准
    int numTargets;

};

#endif // QCALIBRATION_H
