#ifndef QEYEDEFINE_H
#define QEYEDEFINE_H

#define CALIBRATIONCONFIG "CalibrationConfig"
#define CALIBRATETYPE      "CalibrateType"
#define LONGININFOCONFIG   "LoginConfig"

#define HOSPITALNAME        "hospitaName"  //医院名
#define OFFICENAME          "officeName"   //科室名
#define USERNUMS            "usernums"     //操作人员编号
#define USERNAME            "userName"     //操作人员名字
#define INSPECTIONTYPE      "inspectiontype"  //检验类型
#define INSPECTIONTYPELIST   "inspectiontypelist"  //类型列表
//类名
#define ADDPATIENT "addPatient"
#define PATIENTLIST "patientList"
#define CALIBRATE   "calibrate"

#define GRAZE       "graze"
#define SPORTLINES  "sportLines"
#define SPICTURE    "sPicture"
#define RADDOMPIC   "randomPic"

#define MEASUREANALY     "MeasureAnaly"
#define DATAMANAGER "DataManger"

#define REPORT      "Report"
#define HELP        "help"
#define EXITAPP     "ExitApp"

#define MAXFRAMECOUNT   20







typedef  enum SignalType
{
    noSignale=-1,
    addPatient=0,
    Patientlist=1,
    Calibrate=2,
    Graze =3,
    SportsLines=4,
    SPicture=5,
    RandomPic=6,


    MeasureAnaly=10,

    DataManger = 15,


    ReportForm=20,


    Help=21,
    Exit=22

}SIGNALSYPE;

typedef  enum Screenproperties
{
    NOPROPERTIES = -1,
    CALIBRATEPROPERTY =0,
    EYETRACKINGPROPERTY=1,


}SCREENPROPERTIES;
typedef  enum analytype
{

    MENTALDISEASE=0, //精神病
    DEPRESSION=1,    //抑郁症
    BOPRESSION=2,   //强迫症
    SCHIZOPHRENIA=3  //精神分裂
}ANALYTYPE;

#include<QString>
#include<QTime>
typedef struct patientinfo
{
     int    ID;
     QString PatientID;
     QString name;
     int age;
     QString sex;
     QString   birth;
     QString   patientDate;
     QString admissionNum;//住院编号
     int     MeasureNum;
     QString education;//学历
     int     testTimes;//测量次数
     QString studyNum;
     QString Describe;
     QString docName;
     QString docNum;
     QString docOfiice;




}PatientInfo;

#endif // QEYEDEFINE_H
