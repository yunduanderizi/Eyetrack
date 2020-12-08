#include "qeyeconfigcontrol.h"
#include<QTextCodec>

QEyeConfigControl::QEyeConfigControl()
{

}
QEyeConfigControl::QEyeConfigControl(QString sPath)
{
    if (InitIniFileSetting(sPath))
        qDebug() << "创建目录" << sPath;
}
QEyeConfigControl::QEyeConfigControl(QString sPath,QString fileName)
{
    if (InitIniFileSetting(sPath,fileName))
        qDebug() << "创建目录--" << sPath+"/"+fileName;

}
void QEyeConfigControl::ConfigCreateFile(QString filePath,QString fileName)
{

        QDir tempDir;
        //临时保存程序当前路径
        QString currentDir = tempDir.currentPath();
        //如果filePath路径不存在，创建它
        if(!tempDir.exists(filePath))
        {
            qDebug()<<"不存在该路径"<<endl;
            tempDir.mkpath(filePath);
        }
        QFile *tempFile = new QFile;
        //将程序的执行路径设置到filePath下
        tempDir.setCurrent(filePath);
        qDebug()<<tempDir.currentPath();
        //检查filePath路径下是否存在文件fileName,如果停止操作。
        if(tempFile->exists(fileName))
        {
            qDebug()<<"文件存在";
            return ;
        }
        //此时，路径下没有fileName文件，使用下面代码在当前路径下创建文件
        tempFile->setFileName(fileName);
        if(!tempFile->open(QIODevice::WriteOnly|QIODevice::Text))
        {
            qDebug()<<"打开失败";
        }
        tempFile->close();
        //将程序当前路径设置为原来的路径
        tempDir.setCurrent(currentDir);
        qDebug()<<tempDir.currentPath();

}
bool QEyeConfigControl::InitIniFileSetting(QString sPath, QString fileName)
{
    ConfigCreateFile(sPath,fileName);
    QString path= sPath+"/"+fileName;
    qDebug()<<"Initfilesetting "<<path;
    qSetting = new QSettings(path, QSettings::IniFormat);
     qSetting->setIniCodec(QTextCodec::codecForName("GBK"));
    if (qSetting)
        return true;
    else
        return false;
}

bool QEyeConfigControl::InitIniFileSetting(QString sPath)
{
    if (sPath.isEmpty())
        return false;
    qSetting = new QSettings(sPath, QSettings::IniFormat);

    qSetting->setIniCodec(QTextCodec::codecForName("GBK"));
    if (qSetting)
        return true;
    else
        return false;
}
bool QEyeConfigControl::WriteBoolIniFile(QString Group, QString Key, bool bValue)
{
    qSetting->beginGroup(Group);
    qSetting->setValue(Key, bValue);
    qSetting->endGroup();
    return true;
}
bool QEyeConfigControl::WriteDoubleIniFile(QString Group, QString Key, double dValue)
{
    qSetting->beginGroup(Group);
    qSetting->setValue(Key, dValue);
    qSetting->endGroup();

    return true;
}
bool QEyeConfigControl::WriteFloatIniFile(QString Group, QString Key, float fValue)
{
    qSetting->beginGroup(Group);
    qSetting->setValue(Key, fValue);
    qSetting->endGroup();
    return true;
}
bool QEyeConfigControl::WriteIntIniFile(QString Group, QString Key, int iValue)
{
    qSetting->beginGroup(Group);
    qSetting->setValue(Key, iValue);
    qSetting->endGroup();
    return true;
}
bool QEyeConfigControl::WriteLongIniFile(QString Group, QString Key, long lValue)
{
//    qSetting->beginGroup(Group);
//    qSetting->setValue(Key, lValue);
//    qSetting->endGroup();

    return true;
}
bool QEyeConfigControl::WriteStringIniFile(QString Group, QString Key, QString qValue)
{
    qSetting->beginGroup(Group);
    qSetting->setValue(Key,qValue);
    qSetting->endGroup();
    return true;
}
double  QEyeConfigControl::ReadDoubleIniFile(QString Group, QString Key,double Val)
{

    qSetting->beginGroup(Group);
    Val = qSetting->value(Key).toDouble();
    qSetting->endGroup();
    return Val;
}
float QEyeConfigControl::ReadFloatIniFile(QString Group, QString Key,float Val)
{
    float NewVal;
    qSetting->beginGroup(Group);
    NewVal = qSetting->value(Key).toFloat();
    qSetting->endGroup();
    return Val;

}
QString QEyeConfigControl::ReadStringIniFile(QString Group, QString Key,QString Val)
{
    QString NewVal;
    qSetting->beginGroup(Group);
    NewVal = qSetting->value(Key).toString();
    qSetting->endGroup();
    if(NewVal.length()!=0)
    {
        return NewVal;
    }
    else
        return Val;

}
int QEyeConfigControl::ReadIntIniFile(QString Group, QString Key,int Val)
{


    qSetting->beginGroup(Group);
    Val = qSetting->value(Key).toInt();
    qSetting->endGroup();
    return Val;
}
long QEyeConfigControl::ReadLongIniFile(QString Group, QString Key,long Val)
{

    qSetting->beginGroup(Group);
    Val = qSetting->value(Key).toLongLong();
    qSetting->endGroup();

    return Val;;

}
QVariant QEyeConfigControl::ReadIniFileValue(QString Group, QString Key,QVariant Val)
{

    qSetting->beginGroup(Group);
    Val = qSetting->value(Key);
    qSetting->endGroup();
    return Val;
}

bool QEyeConfigControl::ReadBoolIniFile(QString Group, QString Key,bool Val)
{

    qSetting->beginGroup(Group);
    Val = qSetting->value(Key).toBool();
    qSetting->endGroup();
    return Val;

}


