#include"sqlitecontrol.h"
#include<QCoreApplication>
sqliteControl::sqliteControl()
{


}
void sqliteControl::SetDbName(QString dbName)
{
    if(!dbName.contains(".db",Qt::CaseInsensitive))
          m_dbName = dbName + ".db";
      else
          m_dbName = dbName;
}
bool sqliteControl::opendb()
{
    if(m_dbName.isEmpty())
    {
        qDebug()<<"m_dbName is Empty";
        return false;
    }
    QString filepath = QCoreApplication::applicationDirPath();
     database=QSqlDatabase::addDatabase("QSQLITE"); //添加 SQL LITE数据库驱动
    QString sPath =filepath+"/"+m_dbName;
    qDebug()<<"sPath:"<<sPath;
    database.setDatabaseName(sPath);
    isOpen = database.open();
    qDebug()<<"DataBase is Open:"<<isOpen;

    return isOpen;

}
bool sqliteControl::opendb(QString sPath)
{
    database = QSqlDatabase::addDatabase( "QSQLITE" );//第二个参数可以设置连接名字，这里为default
    database.setDatabaseName(sPath);
    isOpen = database.open();
    qDebug()<<"DataBase is Open:"<<isOpen;
    return isOpen;


}
void sqliteControl::Closedb()
{
    if(database.isOpen())
    {
        database.close();
        isOpen = false;
    }
}
bool sqliteControl::insertData(const QString& table, QStringList& names, QStringList& values)
{
    if (names.size() != values.size())
    {
        return false;
    }
    if(!isOpen)
    {
        qDebug()<<m_dbName<<"no open";
        SetDbName(m_dbName);
        if(!opendb())
            return false;
    }
    QSqlQuery query(database);
    QString sql = QString("insert into %1 (").arg(table);
    int i;
    for (i=0; i < names.size(); i++)
    {
        sql = sql + names.value(i);
        if (i != names.size() - 1)
        {
            sql += QString(",");
        }
        else
        {
            sql += QString(") ");
        }
    }
    sql +=  QString("values (");
    for (i = 0; i < values.size(); i++)
    {
        sql +=  QString("'%1'").arg(values.value(i));
        if (i != values.size()-1)
        {
            sql += QString(",");
        }
    }
    sql += QString(")");
    qDebug()<<sql;
    bool ok=query.exec(sql);
    qDebug()<<"Insert data:"<<ok;
    Closedb();
    if (ok)
    {
        return true;
    }
    else
    {
        database.close();
        return false;
    }
}
bool sqliteControl::updateData(const QString &table, QStringList &names, QStringList &values, QString &expression)
{
    if (names.size() != values.size())
    {
        return false;
    }
    //UPDATE 表名称 SET 列名称 = 新值 WHERE 列名称 = 某值
    QSqlQuery query(QSqlDatabase::database());
    QString sql = QString("update ")+table+QString(" set ");
    for (int i = 0; i < names.size(); i++)
    {
        sql +=  names.value(i);
        sql +=  QString(" = '");
        sql +=  values.value(i);
        sql +=  QString("'");
        if (i != names.size()-1)
        {
            sql += QString(" ,");
        }
    }
    sql +=  QString(" where %1").arg(expression);
    if (query.exec(sql))
    {
        return true;
    }
    else
    {
        return false;
    }
}
/*
    删除函数.
    构造SQL删除语句.
*/
bool sqliteControl::del(const QString &table, QString &expression)
{
    //DELETE FROM 表名称 WHERE 列名称 = 值
    QSqlQuery query(QSqlDatabase::database());
    QString sql = QString("delete from %1 ").arg(table) + QString(" where %1").arg(expression);
    if (query.exec(sql))
    {
        return true;
    }
    else
    {
        return false;
    }
}
void sqliteControl::getValues(const QString &table, QStringList &values)
{
    QSqlQuery query(QSqlDatabase::database());
    if(!isOpen)
    {
        qDebug()<<m_dbName<<"no open";
        SetDbName(m_dbName);
        if(!opendb())
            return;
    }  //打开数据库;
    QString sql = QString("select * from %1 ;").arg(table);
    qDebug()<<sql;
   bool ok=query.exec(sql);
    qDebug()<<ok;
   while (query.next())
    {
        values << query.value(1).toString();
    }
    qDebug()<<values;
    database.close();

}
void sqliteControl::getValues(const QString &table, QStringList namelist, QList<QStringList> &valueslist)
{
    QStringList values;
    QSqlQuery query(QSqlDatabase::database());
    if(!isOpen)
    {
        qDebug()<<m_dbName<<"no open";
        SetDbName(m_dbName);
        if(!opendb())
            return;
    }  //打开数据库;
    QString sql = QString("select * from %1 ;").arg(table);
    qDebug()<<sql;
    bool ok=query.exec(sql);
    qDebug()<<ok;
    while (query.next())
    {
        for(int i=0;i<namelist.size();i++)
        {
            values<< query.value(namelist[i]).toString();
        }
        valueslist.append(values);
    }
    qDebug()<<valueslist;
    database.close();


}
void sqliteControl::getValues(QString table, QString name, QStringList &values)
{
    QSqlQuery query(QSqlDatabase::database());
    if(!isOpen)
    {
        qDebug()<<m_dbName<<"no open";
        SetDbName(m_dbName);
        if(!opendb())
            return;
    }  //打开数据库;
    QString sql = QString("select * from %1 ;").arg(table);
    qDebug()<<sql;
    bool ok=query.exec(sql);
    qDebug()<<ok;
    while (query.next())
    {
        values << query.value(name).toString();
    }
    qDebug()<<values;
    database.close();

}
bool sqliteControl::GetTableInfo(QString tabName,QStringList & names)
{
    QSqlQuery query(QSqlDatabase::database());
    if(!isOpen)
    {
        qDebug()<<m_dbName<<"no open";
        SetDbName(m_dbName);
        if(!opendb())
            return false;
    }  //打开数据库;
    QString strTableNmae = tabName;
    QString str = "PRAGMA table_info(" + strTableNmae + ")";

    query.prepare(str);
    if (query.exec())
    {
        while (query.next())
        {
             names<<query.value(1).toString();

            //qDebug() << QString(QString::fromLocal8Bit("字段数:%1     字段名:%2     字段类型:%3")).arg(query.value(0).toString()).arg(query.value(1).toString()).arg(query.value(2).toString());
        }

    }
    else
    {
        qDebug() << query.lastError();
        return false;
    }
    qDebug()<<"names:"<<names;
    return true;
}
