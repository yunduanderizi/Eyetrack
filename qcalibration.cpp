#include "qcalibration.h"

QCalibration::QCalibration()
{
    nScreenCount=0;
    nowTargetNum =0;
    calibrationType = QL_CALIBRATION_TYPE_9;
    calibrateNums = 9;
    calibrateStatus = false;
    GetScreenSize();
    numTargets = CalibufferSize;

}
QCalibration::~QCalibration()
{
    qDebug()<<"Qcalibration 析构函数";

}

QCalibration::QCalibration(int CalibrationNums)
{
    nScreenCount=0;

    GetScreenSize();
    calibrateNums = CalibrationNums;
    if(CalibrationNums==5)
        calibrationType = QL_CALIBRATION_TYPE_5;
    else if(CalibrationNums==9)
    {
        calibrationType = QL_CALIBRATION_TYPE_9;
    }
    else if(CalibrationNums==16)
    {
        calibrationType = QL_CALIBRATION_TYPE_16;
    }
    else
    {
        calibrationType = QL_CALIBRATION_TYPE_9;
    }

}
void QCalibration::GetScreenSize()
{
    QList<QScreen *> list_screen =  QGuiApplication::screens();  //多显示器
    qDebug()<<list_screen.size();
    screenComputerRect = list_screen.at(0)->geometry();
    if(list_screen.size()>1)
    {
           screenTVRect = list_screen.at(1)->geometry();
    }


}
void QCalibration::SetDeviceId(QLDeviceId id)
{
    DeviceId = id;
}
bool QCalibration::CalibrateCancle()
{
    QLError error =QLCalibration_Cancel(calibrationId);
    if(error==QL_ERROR_OK)
        return  true;
    else
        return false;
}
bool QCalibration::CalibrateInitialize()
{
    QLError error =  QLCalibration_Initialize(DeviceId,calibrationId, calibrationType);
    qDebug()<<"CalibrateInitialize::calibrationType"<<calibrationType;
   if(error==QL_ERROR_OK)
       return  true;
   else if (error == QL_ERROR_INVALID_CALIBRATION_ID)
   {
       QLCalibration_Create(0, &calibrationId);
       error = QLCalibration_Initialize(DeviceId, calibrationId, calibrationType);
       if(error==QL_ERROR_OK)
           return  true;
       else
           return false;
   }
   else
       return false;



}
bool QCalibration::CalibrateCreate()
{
    QLError error = QLCalibration_Create(0, &calibrationId);
   if(error==QL_ERROR_OK)
       return  true;
   else
       return false;
}
bool QCalibration::CalibrateGetTargets()
{
     QLError error =  QLCalibration_GetTargets(calibrationId, &numTargets, targets);
    if(error==QL_ERROR_OK)
        return  true;
    else
        return false;
}
bool QCalibration::CalibrateTarget(QLCalibrationTarget target,bool block)
{
    QLError error= QLCalibration_Calibrate(calibrationId, target.targetId, 1500, block);
    if(error == QL_ERROR_OK)
        return true;
    else
        return false;
}

bool QCalibration::Applycalibration()
{
    QLError error = QLDevice_ApplyCalibration(DeviceId,calibrationId);
    if(error==QL_ERROR_OK)
        return  true;
    else
        return false;
}
void QCalibration::SetCalibrationType(QLCalibrationType CalibrationNums)
{

   calibrationType = CalibrationNums;
    if(calibrationType == QL_CALIBRATION_TYPE_5)
    {
        calibrateNums=5;
    }
    else if(calibrationType == QL_CALIBRATION_TYPE_9)
    {
        calibrateNums=9;
    }
    else if(QL_CALIBRATION_TYPE_16 == calibrationType)
    {
        calibrateNums=16;
    }
    else {
        calibrateNums=9;
    }
}
bool QCalibration::Calibration_GetStatus(QLTargetId targetid, QLCalibrationStatus *status)
{
    QLError error= QLCalibration_GetStatus(calibrationId,targetid,status);
    if(error==QL_ERROR_OK)
        return true;
    else
        return false;
}
bool QCalibration::AutoCalibrate()
{
//    QLError qlerror = QL_ERROR_OK;
//    int keyPress = 0;

//    // Use OpenCV to create a window for doing the calibration. The calibration
//    // will only be valid over the area of this window. If the entire screen
//    // area is to be calibrated then this window should be set to the screen
//    // size.
//    int windowWidth = 1920;
//    int windowHeight = 1080;
//    const char* windowName = "Calibration Window";
//    IplImage* displayImage = cvCreateImage(cvSize(windowWidth, windowHeight), 8, 3);
//    cvNamedWindow(windowName, CV_WINDOW_AUTOSIZE);
//    cvMoveWindow(windowName, 0, 0);
//    cvResizeWindow(windowName, windowWidth, windowHeight);

//    //Clear the calibration window
//    memset(displayImage->imageData,255 , displayImage->imageSize);

//    // Create a font for printing to the window.
//    CvFont font;
//    cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX, .5, .5, 0, 1);
///*
// * 给显示的界面显示提示
//*/


//    // Display the image to the window.
//    cvShowImage(windowName, displayImage);

//    // Wait for the user to place the window and press a key.
//    QLCalibrationType calibrationType = QL_CALIBRATION_TYPE_16;
//    keyPress = cvWaitKey();
//    if(keyPress == cvWaitKeyEsc)
//    {
//        QLCalibration_Cancel(calibrationId);
//        cvReleaseImage(&displayImage);
//        cvDestroyWindow(windowName);
//        return false;
//    }
//    if (keyPress == 'u' || keyPress == 'U')
//        calibrationType = QL_CALIBRATION_TYPE_USERDRIVEN_9;

//    // Initialize the calibration using the inputed data.
//    qlerror = QLCalibration_Initialize(DeviceId, calibrationId, calibrationType);

//    // If the calibrationId was not valid then create a new calibration
//    // container and use it.
//    if (qlerror == QL_ERROR_INVALID_CALIBRATION_ID)
//    {
//        QLCalibration_Create(0, &calibrationId);
//        qlerror = QLCalibration_Initialize(DeviceId, calibrationId, calibrationType);
//    }

//    // If the initialization failed then print an error and return false.
//    if (qlerror == QL_ERROR_INVALID_DEVICE_ID)
//    {
//        printf_s("QLCalibration_Initialize() failed with error code %d.\n", qlerror);
//        return false;
//    }

//    // Create a buffer for the targets. This just needs to be large enough to
//    // hold the targets.
//    const int bufferSize = 20;
//    int numTargets = bufferSize;
//    QLCalibrationTarget targets[bufferSize];

//    // Get the targets. After the call, numTargets will contain the number of
//    // actual targets.
//    qlerror = QLCalibration_GetTargets(calibrationId, &numTargets, targets);

//    // If the buffer was not large enough then print an error and return false.
//    if (qlerror == QL_ERROR_BUFFER_TOO_SMALL)
//    {
//        printf_s(
//            "The target buffer is too small. It should be at least %d bytes.\n",
//            numTargets * sizeof(QLCalibrationTarget));
//        return false;
//    }

//    if (calibrationType == QL_CALIBRATION_TYPE_USERDRIVEN_9)
//    {	//User driven 9 point calibration

//        // Calibrate the first target to allow for target detection on remaining
//        // targets. If the user terminates the calibration then return false.
//        if (!CalibrateTarget(calibrationId,targets[0],	displayImage,windowName))
//        {
//            QLCalibration_Cancel(calibrationId);
//            cvReleaseImage(&displayImage);
//            cvDestroyWindow(windowName);
//            return false;
//        }

//        // Calibrate the next 4 targets. If the user terminates the calibration
//        // then return false.
//        QLCalibrationTarget targetSet[4];
//        for (int i = 0; i < 4; i++)
//            targetSet[i] = targets[i + 1];
////        if (!CalibrateMultipleTargets(
////            *calibrationId,
////            targetSet,
////            4,
////            displayImage,
////            windowName))
////        {
////            QLCalibration_Cancel(*calibrationId);
////            cvReleaseImage(&displayImage);
////            cvDestroyWindow(windowName);
////            return false;
////        }

////        // Calibrate the final 4 targets. If the user terminates the calibration
////        // then return false.
////        for (int i = 0; i < 4; i++)
////            targetSet[i] = targets[i + 5];
////        if (!CalibrateMultipleTargets(
////            calibrationId,
////            targetSet,
////            4,
////            displayImage,
////            windowName))
////        {
////            QLCalibration_Cancel(*calibrationId);
////            cvReleaseImage(&displayImage);
////            cvDestroyWindow(windowName);
////            return false;
////        }
//    }
//    else {	// Standard Calibration
//        // Loop through each target and calibrate them
//        for (int i = 0; i < numTargets; i++)
//        {
//            // Calibrate each target. If the user terminates the calibration then
//            // return false.
//            if (!CalibrateTarget(
//                calibrationId,
//                targets[i],
//                displayImage,
//                windowName))
//            {
//                QLCalibration_Cancel(calibrationId);
//                cvReleaseImage(&displayImage);
//                cvDestroyWindow(windowName);
//                return false;
//            }

//        }

//    }

//    // Get the scores and display them. If the user wants to improve the
//    // calibration then recalibrate the worst target and loop through again.
//    do
//    {
//        // When all calibration targets have been successfully calibrated then get
//        // the scoring. Scores can only be calculated once all targets have been
//        // calibrated.
//        QLCalibrationScore leftScores[bufferSize];
//        QLCalibrationScore rightScores[bufferSize];
//        for (int i = 0; i < numTargets; i++)
//        {
//            QLCalibration_GetScoring(
//                calibrationId,
//                targets[i].targetId,
//                QL_EYE_TYPE_LEFT,
//                leftScores + i);

//            QLCalibration_GetScoring(
//                calibrationId,
//                targets[i].targetId,
//                QL_EYE_TYPE_RIGHT,
//                rightScores + i);
//        }

//        // Display the calibration results graphically.
//      //  DisplayCalibration(displayImage, targets, leftScores, rightScores, numTargets, windowName);

//        // Wait for user input to determine what to do.
//        keyPress = cvWaitKey();

//        // If the user wants to improve the calibration then determine which
//        // target has the largest score and recalibrate it.
//        if(keyPress == 'i')
//        {
//            float highestScore = 0;
//            int highestIndex = 0;
//            for (int i = 0; i < numTargets; i++)
//            {
//                if(leftScores[i].score > highestScore)
//                {
//                    highestScore = leftScores[i].score;
//                    highestIndex = i;
//                }

//                if(rightScores[i].score > highestScore)
//                {
//                    highestScore = rightScores[i].score;
//                    highestIndex = i;
//                }
//            }

//            // Calibrate the target. If the user terminates the calibration then
//            // return false.
//            if(!CalibrateTarget(
//                calibrationId,
//                targets[highestIndex],
//                displayImage,
//                windowName))
//            {
//                QLCalibration_Cancel(calibrationId);
//                cvReleaseImage(&displayImage);
//                cvDestroyWindow(windowName);
//                return false;
//            }
//        }

//    }while(keyPress == 'i');

//    // If the user would not like to save the calibration then cancel the
//    // calibration and return false.
//    if(keyPress == cvWaitKeyEsc)
//    {
//        QLCalibration_Cancel(calibrationId);
//        cvReleaseImage(&displayImage);
//        cvDestroyWindow(windowName);
//        return false;
//    }


//    QLCalibration_Finalize(calibrationId);
//    cvReleaseImage(&displayImage);
//    cvDestroyWindow(windowName);
    return true;
}

bool QCalibration::GetCalibrateLeftScrore(int Num)
{

   QLError error= QLCalibration_GetScoring(calibrationId,targets[Num].targetId,QL_EYE_TYPE_LEFT,&leftscores[Num]);
   if(error==QL_ERROR_OK)
       return true;
   else
       return false;

}
bool QCalibration::GetCalibrateRightScrore(int Num)
{


   QLError error= QLCalibration_GetScoring(calibrationId,targets[Num].targetId,QL_EYE_TYPE_RIGHT,&rightsocres[Num]);
    if(error==QL_ERROR_OK)
        return true;
    else
        return false;

}

bool QCalibration::GetCalibrateLeftScrore(int Num, QLCalibrationScore *leftscore)
{

    qDebug()<<"targets[Num].targetId"<<targets[Num].targetId<<"Num"<<Num;
   QLError error= QLCalibration_GetScoring(calibrationId,targets[Num].targetId,QL_EYE_TYPE_LEFT,leftscore);
   if(error==QL_ERROR_OK)
       return true;
   else
       return false;

}
bool QCalibration::GetCalibrateRightScrore(int Num, QLCalibrationScore *rightscore)
{


   QLError error= QLCalibration_GetScoring(calibrationId,targets[Num].targetId,QL_EYE_TYPE_RIGHT,rightscore);
    if(error==QL_ERROR_OK)
        return true;
    else
        return false;

}

void QCalibration::CalibrateGetScores()
{

            if(GetCalibrateStatus())
            {
                for (int i = 0; i < calibrateNums; i++)
                {
                    QLCalibration_GetScoring(
                        calibrationId,
                        targets[i].targetId,
                        QL_EYE_TYPE_LEFT,
                        leftscores + i);

                    QLCalibration_GetScoring(
                        calibrationId,
                        targets[i].targetId,
                        QL_EYE_TYPE_RIGHT,
                        rightsocres + i);
                }
            }
            else
                qDebug()<<"Please Check calibrate stauts";

}
