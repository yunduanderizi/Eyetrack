#include "patientcongrol.h"

PatientCongrol::PatientCongrol()
{
    QString path = QCoreApplication::applicationDirPath();
    QString dbname("EyeTrackerSql.db");
    QString sPath= path+"/"+dbname;
    opendb(sPath);

}
void PatientCongrol::ReadAllPatient(QList<PatientInfo> &patinetlist,QList<QStringList> & valuslist)
{

    QStringList namelist;
    QStringList tmp;
    GetTableInfo("u_patientsInfo",namelist);
    getValues("u_patientsInfo",namelist,valuslist);
    for(int i =0;i<valuslist.size();i++)
    {
        PatientInfo patient;
        tmp = valuslist[i];
        patient.ID = tmp[0].toInt();
        patient.name = tmp[1];
        patient.age = tmp[2].toInt();
        patient.sex = tmp[3];
        patient.birth = tmp[4];
        patient.patientDate = tmp[5];
        patient.admissionNum = tmp[6];
        patient.MeasureNum = tmp[7].toInt();
        patient.education = tmp[8];
        patient.testTimes = tmp[9].toInt();
        patient.studyNum = tmp[10];
        patient.Describe =tmp[11];
        patient.docName =tmp[12];
        patient.docNum = tmp[13];
        patient.docOfiice=tmp[14];
        patinetlist.append(patient);
;    }
}
void PatientCongrol::GetallDocNamelist(QStringList & docNameList)
{
    getValues("DocNamelist",docNameList);
}
void PatientCongrol::GetallEduTypelist(QStringList &eduTypelist)
{
    getValues("EducationType",eduTypelist);
}
void PatientCongrol::InsertIntoDb(PatientInfo patient)
{

}
void PatientCongrol::GetPatientValues(QString tableName, QStringList name, QStringList &value)
{


}
