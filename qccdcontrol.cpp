#include "qccdcontrol.h"
#include<QByteArray>

//QCCDControl *QCCDControl::self = 0;
QCCDControl::QCCDControl()
{
    sourceId=0;
    SettingsId=0;
    GazeFlag= false;
    SrcImage=NULL;
    displayImage = NULL;
}
QCCDControl::~QCCDControl()
{


        qDebug()<<"QccdControl xigou析构函数";
        QlStopDevice();
        if(!SrcImage)
            cvReleaseImage(&SrcImage);
        if(!displayImage)
            cvReleaseImage(&displayImage);


}
bool QCCDControl::InitCCD()
{
    const int bufferSize = 32;
    char versionBuffer[bufferSize];
    versionBuffer[0] = 0;
    DeviceId = 0;
    QLAPI_GetVersion(bufferSize, versionBuffer);
    //qDebug("Quick Link 2 loaded. Version: %s\n", versionBuffer);
    DeviceId = QL2Initialize("C:\\temp\\QL2Settings.txt");
    //qDebug("InitCCD DeviceId %d \n",DeviceId);
    QlDevicestart();
    int exposure=0;
    SetExposure(5);
    if(GetExposure(&exposure))
        qDebug()<<"expusure"<<exposure;
    int scale=0;
//    if(SetCcdFrameScale(2))
//    {
//        qDebug()<<"scale "<<scale;
//    }
//    else
//    {
//        qDebug()<<"获取比例失败";
//    }
//    if(GetCcdFrameScale(&scale))
//        qDebug()<<"scale "<<scale;


    return true;
}
bool QCCDControl::isInited()
{
    if(DeviceId)
        return true;
    else
        return false;

}
bool QCCDControl::QlDevicestart()
{
     if(QLDevice_Start(DeviceId) != QL_ERROR_OK)
         return true;
     else
         return false;
}

QLDeviceId QCCDControl::QL2Initialize(const char * path)
{
       QLError qlerror = QL_ERROR_OK;
       QLDeviceId deviceId = 0;
       QLDeviceInfo deviceInfo;
               const int bufferSize = 100;
       QLDeviceId deviceIds[bufferSize];
       int numDevices = bufferSize;
       qlerror = QLDevice_Enumerate(&numDevices, deviceIds);

       // If the enumeration failed then return 0
       if(qlerror != QL_ERROR_OK)
       {
           qDebug("QLDevice_Enumerate() failed with error code %d\n", qlerror);
           return 0;
       }

       // If no devices were found then return 0;
       else if(numDevices == 0)
       {
           qDebug("No devices present.\n");
           return 0;
       }

       // If there was only one device connected then use it without prompting the
       // user.
       else if(numDevices == 1)
       {
           deviceId = deviceIds[0];
           QLDevice_GetInfo(deviceIds[0], &deviceInfo);
           qDebug("Device %d\n", 0);
           qDebug("\tdeviceInfo.modelName = %s\n", deviceInfo.modelName);
           qDebug("\tdeviceInfo.serialNumber = %s\n\n", deviceInfo.serialNumber);
           qDebug("\tdeviceInfo.sensorWidth = %d\n\n", deviceInfo.sensorWidth);
           qDebug("\tdeviceInfo.sensorHeight = %d\n\n", deviceInfo.sensorHeight);
       }

       // If there is more than one device then ask which one to use.
       else if(numDevices > 1)
       {
           qDebug("QLDevice_Enumerate() found %d devices\n\n", numDevices);

           // Get the information for each eye tracker and print it to the screen.
           for(int i = 0; i < numDevices; i++)
           {
               QLDevice_GetInfo(deviceIds[i], &deviceInfo);
               qDebug("Device %d\n", i);
               qDebug("\tdeviceInfo.modelName = %s\n", deviceInfo.modelName);
               qDebug("\tdeviceInfo.serialNumber = %s\n\n", deviceInfo.serialNumber);
           }

           // Ask which device to use
           int deviceToUse = -1;

           qDebug("Which device would you like to use? ");
           deviceToUse = getchar() - (int)'0';
           _flushall();

           // Check to make sure the user input is valid. If it is not valid then
           // return 0.
           if((deviceToUse < 0) || (deviceToUse >= numDevices))
           {
               qDebug("Invalid device.\n\n", deviceToUse);
               return 0;
           }

           // If the device is valid then select it as the device to use.
           else
               deviceId = deviceIds[deviceToUse];
       }

       // Create a blank settings container. QLSettings_Load() can create a
       // settings container but it won't if the file fails to load. By calling
       // QLSettings_Create() we ensure that a container is created regardless.
       qlerror = QLSettings_Create(0, &SettingsId);
        qDebug()<<"SettingsId"<<SettingsId;
       // Load the file with the stored password.
       qlerror = QLSettings_Load(path, &SettingsId);

       // Get the device info so we can access the serial number.
       QLDevice_GetInfo(deviceId, &deviceInfo);

       // Create an application defined setting name using the serial number. The
       // settings containers can be used to hold settings other than the
       // QuickLink2 defined setting. Using it to store the password for future
       // use as we are doing here is a good example.
       std::string serialNumberName = "SN_";
       serialNumberName += deviceInfo.serialNumber;

       // Create a buffer for getting the stored password.
       const int passwordBufferSize = 128;
       char password[passwordBufferSize];
       password[0] = 0;

       // Check for the password in the settings file.
       int stringSize = passwordBufferSize;
       QLSettings_GetValue(
           SettingsId,
           serialNumberName.c_str(),
           QL_SETTING_TYPE_STRING,
           stringSize,
           password);

       // Try setting the password for the device.
       qlerror = QLDevice_SetPassword(deviceId, password);

       // If setting the password failed then get the password from the user and
       // try again.
       if(qlerror == QL_ERROR_INVALID_PASSWORD)
       {
           qDebug("What is the password for the device? ");
           gets_s(password, bufferSize);

           // Set the password for the device.
           qlerror = QLDevice_SetPassword(deviceId, password);

           // If the password is not correct then print an error and return 0.
           if(qlerror != QL_ERROR_OK)
           {
               qDebug("Invalid password. Error = %d\n", qlerror);
               return 0;
           }

           // Set the password for the device in the settings container.
           QLSettings_SetValue(
               SettingsId,
               serialNumberName.c_str(),
               QL_SETTING_TYPE_STRING,
               password);

           // Save the settings container to file.
           QLSettings_Save(path, SettingsId);
       }
       else if(qlerror != QL_ERROR_OK)
       {
           qDebug("Error setting the password for the device. Error = %d\n", qlerror);
           return 0;
       }

       // The application defined password setting that is stored in the settings
       // container will have no effect if imported to the device, but there may
       // have been other settings in the file that was loaded which are Quick
       // Link 2 settings. Try and import them to the device.
       QLDevice_ImportSettings(deviceId, SettingsId);

       QLAPI_ImportSettings(SettingsId);


       return deviceId;

}
IplImage * QCCDControl::GetShowVideoSrc()
{
    GetFrame(&frame);
    SrcImage->imageData = (char*)frame.ImageData.PixelData;
    if(SrcImage->imageData != 0)
           cvCvtColor(SrcImage, displayImage, CV_GRAY2RGB);
//    if(frame.LeftEye.Found)
//      {
//          DrawCross(displayImage,
//          cvPoint((int)frame.LeftEye.Pupil.x, (int)frame.LeftEye.Pupil.y),
//          10, CV_RGB(0,255,0), 1);

//          DrawCross(displayImage,
//          cvPoint((int)frame.LeftEye.Glint0.x, (int)frame.LeftEye.Glint0.y),
//          5, CV_RGB(0,255,0), 1);

//          DrawCross(displayImage,
//          cvPoint((int)frame.LeftEye.Glint1.x, (int)frame.LeftEye.Glint1.y),
//          5, CV_RGB(0,255,0), 1);
//      }

//      // If the right was was found then mark the pupil and the glints;
//      if(frame.RightEye.Found)
//      {
//          DrawCross(displayImage,
//          cvPoint((int)frame.RightEye.Pupil.x, (int)frame.RightEye.Pupil.y),
//          10, CV_RGB(0,0,255), 1);

//          DrawCross(displayImage,
//          cvPoint((int)frame.RightEye.Glint0.x, (int)frame.RightEye.Glint0.y),
//          5, CV_RGB(0,0,255), 1);

//          DrawCross(displayImage,
//          cvPoint((int)frame.RightEye.Glint1.x, (int)frame.RightEye.Glint1.y),
//          5, CV_RGB(0,0,255), 1);
//      }
        return SrcImage;
}

IplImage * QCCDControl::GetShowVideoDraw()
{

    GetFrame(&frame);
//    qDebug("timestap %lf",frame.ImageData.Timestamp);

//    qDebug()<<"frame.ImageData.Gain:"<<frame.ImageData.Gain;
//    qDebug()<<"frame.ImageData.FrameNumber:"<<frame.ImageData.FrameNumber;
    SrcImage->imageData = (char*)frame.ImageData.PixelData;
    if(SrcImage->imageData != 0)
               cvCvtColor(SrcImage, displayImage, CV_GRAY2RGB);
    if(frame.LeftEye.Found)
      {
          DrawCross(displayImage,
          cvPoint((int)frame.LeftEye.Pupil.x, (int)frame.LeftEye.Pupil.y),
          10, CV_RGB(0,255,0), 1);

          DrawCross(displayImage,
          cvPoint((int)frame.LeftEye.Glint0.x, (int)frame.LeftEye.Glint0.y),
          5, CV_RGB(0,255,0), 1);

          DrawCross(displayImage,
          cvPoint((int)frame.LeftEye.Glint1.x, (int)frame.LeftEye.Glint1.y),
          5, CV_RGB(0,255,0), 1);
      }

      // If the right was was found then mark the pupil and the glints;
      if(frame.RightEye.Found)
      {
          DrawCross(displayImage,
          cvPoint((int)frame.RightEye.Pupil.x, (int)frame.RightEye.Pupil.y),
          10, CV_RGB(0,0,255), 1);

          DrawCross(displayImage,
          cvPoint((int)frame.RightEye.Glint0.x, (int)frame.RightEye.Glint0.y),
          5, CV_RGB(0,0,255), 1);

          DrawCross(displayImage,
          cvPoint((int)frame.RightEye.Glint1.x, (int)frame.RightEye.Glint1.y),
          5, CV_RGB(0,0,255), 1);
      }

      return displayImage;

}
void QCCDControl::DrawCross(IplImage* image, CvPoint center, int size, CvScalar color, int thickness)
{
        cvLine(
            image,
            cvPoint( center.x - size, center.y - size ),
            cvPoint( center.x + size, center.y + size ),
            color,
            thickness,
            0);

        cvLine(
            image,
            cvPoint( center.x + size, center.y - size ),
            cvPoint( center.x - size, center.y + size ),
            color,
            thickness,
            0 );
};

void QCCDControl::SetImage(IplImage *Image)
{
        Image->imageData = (char*)frame.ImageData.PixelData;

        // Copy the grey scale image to the color image buffer so it can be displayed.
//         if(Image->imageData != 0)
//             cvCvtColor(Image, displayImage, CV_GRAY2RGB);
            if(frame.LeftEye.Found)
            {
                DrawCross(Image,
                cvPoint((int)frame.LeftEye.Pupil.x, (int)frame.LeftEye.Pupil.y),
                10, CV_RGB(0,255,0), 1);

                DrawCross(Image,
                cvPoint((int)frame.LeftEye.Glint0.x, (int)frame.LeftEye.Glint0.y),
                5, CV_RGB(0,255,0), 1);

                DrawCross(Image,
                cvPoint((int)frame.LeftEye.Glint1.x, (int)frame.LeftEye.Glint1.y),
                5, CV_RGB(0,255,0), 1);
            }

            // If the right was was found then mark the pupil and the glints;
            if(frame.RightEye.Found)
            {
                DrawCross(Image,
                cvPoint((int)frame.RightEye.Pupil.x, (int)frame.RightEye.Pupil.y),
                10, CV_RGB(255,0,0), 1);

                DrawCross(Image,
                cvPoint((int)frame.RightEye.Glint0.x, (int)frame.RightEye.Glint0.y),
                5, CV_RGB(255,0,0), 1);

                DrawCross(Image,
                cvPoint((int)frame.RightEye.Glint1.x, (int)frame.RightEye.Glint1.y),
                5, CV_RGB(255,0,0), 1);
            }

}
QLError QCCDControl::GetFrame(QLFrameData* frame)
{

     QLError qlerror = QL_ERROR_OK;
    if(isInited())
    {
        if((qlerror = QLDevice_GetFrame(DeviceId, 5000, frame)) != QL_ERROR_OK)
        {
             qDebug("Error getting frame from device. Error = %d\n", qlerror);
             return qlerror;
        }
    }
    return qlerror;

}
bool QCCDControl::GetFramebool(QLFrameData* frame)
{

     QLError qlerror = QL_ERROR_OK;
     if(isInited())
    {
         if((qlerror = QLDevice_GetFrame(DeviceId, 5000, frame)) != QL_ERROR_OK)
         {
              qDebug("Error getting frame from device. Error = %d\n", qlerror);
              return false;
         }
     }
    return true;

}
bool QCCDControl::isStoped()
{
    qDebug("istoped DeviceId %d ",DeviceId);
    if(DeviceId)
        return  false;
    else
        return  true;

}
void QCCDControl::QlStopDevice()
{
        qDebug()<<"QltopDevice";
        QLError error;
        QLDeviceStatus status;
        if(!isStoped())
         {
            error=QLDevice_Stop_All();
            qDebug()<<"QlStopDevice error "<<error;
            if(error == QL_ERROR_OK)
             {
              if(GetCCDStatus(&status))
              {
                    qDebug()<<"QlStopDevice status "<<status;
                    if(status==QL_DEVICE_STATUS_STOPPED)
                    {
                        DeviceId=0;
                    }
                    else
                    {
                        error=QLDevice_Stop_All();
                        qDebug()<<"QlStopDevice2 error "<<error;
                        qDebug()<<"QlStopDevice2 status "<<status;
                        if(status==QL_DEVICE_STATUS_STOPPED)
                        {
                            DeviceId=0;
                        }
                    }
              }
            }
        }

}
QSize QCCDControl::GetframeSize()
{
    GetFrame(&frame);
    FrameSize.setWidth(frame.ImageData.Width);
    FrameSize.setHeight(frame.ImageData.Height);
    return FrameSize;
}
void QCCDControl::GetFrameSize()
{
    GetFrame(&frame);
    SrcImage = cvCreateImageHeader(cvSize(frame.ImageData.Width, frame.ImageData.Height), 8, 1);
    displayImage = cvCreateImage(cvSize(frame.ImageData.Width, frame.ImageData.Height), 8, 3);
    FrameSize.setWidth(frame.ImageData.Width);
    FrameSize.setHeight(frame.ImageData.Height);
}
QImage QCCDControl::IplImage2QImageGray(IplImage * Image){
     QImage resimg(( uchar*)Image->imageData, Image->width, Image->height, QImage::Format_Indexed8);
     return resimg;
}
QImage QCCDControl::IplImage2QImageColor(IplImage * Image){
     QImage resimg(( uchar*)Image->imageData, Image->width, Image->height, QImage::Format_RGB888);
     return resimg;
}
bool QCCDControl::GetCCDStatus(QLDeviceStatus *status)
{

    QLError error= QLDevice_GetStatus(DeviceId,status);
    if(error == QL_ERROR_OK)
    {
        qDebug()<<"GetCCDStatus status"<<status;
        DeviceStatus = *status;
        return  true;
    }
    else
        return false;


}

bool QCCDControl::SettingsSetValue(const char * SettingName,QLSettingType type,  const void *value)
{

   QLError error= QLDevice_IsSettingSupported(DeviceId,SettingName);
    if(error != QL_ERROR_OK)
    {
        qDebug()<<"SettingName:"<<SettingName<<"not support";
        return false;
    }
    else
    {
         qDebug("QLDevice_IsSettingSupported %s support",SettingName);
    }
    error=QLSettings_SetValue(SettingsId,SettingName,type,value);
    qDebug()<<"error"<<error<<"SettingsId"<<SettingsId<<"value"<<value;
    if(QL_ERROR_OK==error)
        return true;
    else
        return false;
}
bool QCCDControl::SettingGetValue(const char * 	settingName, QLSettingType 	settingType, int size,void *value)
{
    qDebug()<<"SettingsId:"<<SettingsId;
    QLError error= QLDevice_IsSettingSupported(DeviceId,settingName);
     if(error != QL_ERROR_OK)
     {
         qDebug()<<"error:"<<error;
         return false;
     }
     else
     {
          qDebug("QLDevice_IsSettingSupported %s support",settingName);
     }
     error = QLSettings_GetValue(SettingsId,settingName,settingType,size,value);
         qDebug()<<"QLSettings_GetValue error------"<<error;
    if(error==QL_ERROR_OK)
    {
        qDebug()<<"value------"<<*(int*)value;
        return true;
    }
    else
   {
        qDebug()<<"error"<<error<<"SettingId"<<SettingsId<<"settingname"<<settingName<<"Settingtype"<<settingType<<"size"<<size;
        return false;
    }
}
bool QCCDControl::GetCcdFrameScale(int *scale)
{
    if(SettingGetValue(QL_SETTING_DEVICE_DOWNSAMPLE_SCALE_FACTOR,QL_SETTING_TYPE_INT16,QL_SETTING_TYPE_INT16,scale))
        return true;
    else
        return false;

}
bool QCCDControl::SetCcdFrameScale(int scale)
{
    if(SettingsSetValue(QL_SETTING_DEVICE_DOWNSAMPLE_SCALE_FACTOR,QL_SETTING_TYPE_INT16,&scale))
        return true;
    else
        return false;
}
bool QCCDControl::SettingCreate(QLSettingsId source, QLSettingsId *settings)
{
    QLError error = QLSettings_Create(source,settings);
    if(error == QL_ERROR_OK)
        return  true;
    else
    {
        return false;
    }
}
bool QCCDControl::GetExposure(int *exposuretime)
{
    return SettingGetValue(QL_SETTING_DEVICE_EXPOSURE,QL_SETTING_TYPE_INT16,sizeof(QL_SETTING_TYPE_INT16),exposuretime);
}
bool QCCDControl::SetExposure(int exposuretime)
{
    return SettingsSetValue(QL_SETTING_DEVICE_EXPOSURE,QL_SETTING_TYPE_INT16,&exposuretime);
}
void QCCDControl::GetGazeNums(QLFrameData frame)
{

}
