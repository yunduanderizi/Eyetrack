#ifndef PATIENTCONGROL_H
#define PATIENTCONGROL_H

#include"sqlitecontrol.h"
#include"QEyeDefine.h"
class PatientCongrol : public sqliteControl
{

public:
    PatientCongrol();
    void ReadAllPatient(QList<PatientInfo> &patinetlist,QList<QStringList> & valuslist);
    void GetallDocNamelist(QStringList & docNameList);
    void GetallEduTypelist(QStringList & eduTypelist);
    void InsertIntoDb(PatientInfo patient);
    void GetPatientValues(QString tableName,QStringList name,QStringList &value);
private:
    QStringList sqlNames;
};

#endif // PATIENTCONGROL_H
