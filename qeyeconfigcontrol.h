#ifndef QEYECONFIGCONTROL_H
#define QEYECONFIGCONTROL_H

#include"QEyeCommon.h"
#include<QDir>

class QEyeConfigControl
{
public:
    QEyeConfigControl();


        ~QEyeConfigControl();
        QEyeConfigControl(QString sPath);
         QEyeConfigControl(QString sPath,QString fileName);
        void ConfigCreateFile(QString filePath,QString fileName);
        bool InitIniFileSetting(QString sPath,QString fileName);
        bool InitIniFileSetting(QString sPath);
        bool WriteIntIniFile(QString Group, QString Key, int iValue);
        bool WriteLongIniFile(QString Group, QString Key, long lValue);
        bool WriteStringIniFile(QString Group, QString Key, QString SValue);
        bool WriteFloatIniFile(QString Group, QString Key, float fValue);
        bool WriteDoubleIniFile(QString Group, QString Key, double dValue);
        bool WriteBoolIniFile(QString Group, QString Key, bool bValue);


        int ReadIntIniFile(QString Group, QString Key,int Val);
        long ReadLongIniFile(QString Group, QString Key,long Val);
        QString ReadStringIniFile(QString Group, QString Key, QString Val);
        float ReadFloatIniFile(QString Group, QString Key, float Val);
        double ReadDoubleIniFile(QString Group, QString Key, double Val);
        bool ReadBoolIniFile(QString Group, QString Key, bool Val);
        QVariant ReadIniFileValue(QString Group, QString Key, QVariant Val);

    private:
        QSettings * qSetting;
};

#endif // QEYECONFIGCONTROL_H
