#ifndef QCCDCONTROL_H
#define QCCDCONTROL_H

#include"QEyeCommon.h"
#include <QImage>
#include<QSize>
typedef enum
{
    DEC_OK,
    DEC_EXIT,
    DEC_ERROR
} DisplayExitCode;

class QCCDControl
{
public:
    QCCDControl();
    ~QCCDControl();
//    static QCCDControl *Instance() {
//        static QMutex mutex;
//        if (!self) {
//            QMutexLocker locker(&mutex);
//            if (!self) {
//                self = new QCCDControl;
//            }
//        }
//        return self;
//    }
    bool InitCCD();
    bool isInited();
    bool isStoped();
    QLDeviceId  QL2Initialize(const char* path);
    bool QlDevicestart();


    void QlStopDevice();
    IplImage * GetShowVideoSrc();
    IplImage * GetShowVideoDraw();

     QImage IplImage2QImageGray(IplImage * Image);
     QImage IplImage2QImageColor(IplImage * Image);

    QLError GetFrame(QLFrameData* frame);

    bool GetFramebool(QLFrameData* frame);
    void DrawCross(IplImage* image, CvPoint center, int size, CvScalar color, int thickness);
    void SetImage(IplImage *Image);
    void GetFrameSize();
    IplImage * GetSrcImage(){return SrcImage; }
    IplImage * GetdisplayImage(){return displayImage; }
    QLDeviceId GetDeviceId(){return  DeviceId;}
    bool GetCCDStatus(QLDeviceStatus *status);
    bool SettingsLoad();
    bool SettingsRemove();
    bool SettingsSave();

    bool GetGazeCollectStatus(){return GazeFlag;}
    bool GetCcdFrameScale(int * scale);
    bool SetCcdFrameScale(int  scale);
    void SetGazeCollect(bool flag){GazeFlag = flag;}

    void GetGazeNums(QLFrameData frame);//获取凝视点数量
    /*
L_SETTING_TYPE_INT
A c/c++ int type.

QL_SETTING_TYPE_INT8
An 8-bit wide integer type.

QL_SETTING_TYPE_INT16
A 16-bit wide integer type.

QL_SETTING_TYPE_INT32
A 32-bit wide integer type.

QL_SETTING_TYPE_INT64
A 64-bit wide integer type.

QL_SETTING_TYPE_UINT
A c/c++ unsigned int type.

QL_SETTING_TYPE_UINT8
An 8-bit wide unsigned integer type.

QL_SETTING_TYPE_UINT16
An 16-bit wide unsigned integer type.

QL_SETTING_TYPE_UINT32
An 32-bit wide unsigned integer type.

QL_SETTING_TYPE_UINT64
An 64-bit wide unsigned integer type.

QL_SETTING_TYPE_FLOAT
A c/c++ float type.

QL_SETTING_TYPE_DOUBLE
A c/c++ double type.

QL_SETTING_TYPE_BOOL
A c/c++ bool type.

QL_SETTING_TYPE_STRING
A c/c++ char* type.

QL_SETTING_TYPE_VOID_POINTER
A c/c++ void* type.


*/
    bool SettingCreate(QLSettingsId source,QLSettingsId * settings);
    bool SettingsSetValue(const char * settingName,QLSettingType type,const void *value);
    bool SettingGetValue(const char * 	settingName, QLSettingType 	settingType, int size,void *value);

    bool GetExposure(int *exposuretime);
        bool SetExposure(int exposuretime);
    QSize GetframeSize();
    QSize Getsize(){return FrameSize;}
    QLFrameData GetNowFrame(){return frame;}
private:

    QLDeviceId DeviceId;
    QLFrameData frame;
    IplImage* SrcImage;
    IplImage* displayImage;

    QLDeviceStatus DeviceStatus;

    QLSettingsId sourceId;
    QLSettingsId SettingsId;
    QSize FrameSize;
    bool  GazeFlag;//是否获取凝视点数量
//    static QCCDControl * self;

};































#endif // QCCDCONTROL_H
