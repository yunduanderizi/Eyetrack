#ifndef SQLITECONTROL_H
#define SQLITECONTROL_H
#include<QString>
#include<QtSql/QSql>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlError>
#include<QDebug>
#include<QStringList>
#include<QApplication>
#include<QList>
class sqliteControl
{
public:
    sqliteControl();
    bool opendb();
    bool opendb(QString sPath);
    void Closedb();
    bool insertData(const QString& table, QStringList& names, QStringList& values);
    void SetDbName(QString dbName);
    bool updateData(const QString &table, QStringList &names, QStringList &values, QString &expression);
    bool del(const QString &table, QString &expression);
    void getValues(const QString &table, QStringList &values);
    void getValues(const QString &table, QStringList namelist,QList<QStringList> &valueslist);
    void getValues(QString table,QString name,QStringList &values);
    bool GetTableInfo(QString tabName,QStringList & names);
private:
    QSqlDatabase  database;
    bool isOpen;
    QString m_dbName;

};

#endif // SQLITECONTROL_H
