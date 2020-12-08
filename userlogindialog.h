#ifndef USERLOGINDIALOG_H
#define USERLOGINDIALOG_H

#include <QDialog>
#include"qeyeconfigcontrol.h"
#include<QString>
#include<QStringList>
namespace Ui {
class UserLoginDialog;
}

class UserLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserLoginDialog(QWidget *parent = nullptr);
    ~UserLoginDialog();
    void GetAllIniInfo();
    void InitDialog();
    void SaveAllIniInfo();
    void GetWidgetText();
private slots:


    void on_pushButtonLogin_clicked();

    void on_pushButtonCancel_clicked();
protected:
    void closeEvent(QCloseEvent * event);
private:
    QEyeConfigControl *Iniinfo;
    Ui::UserLoginDialog *ui;
    QString hospitalName;     //医院名称
    QString officeName;      // 科室名字
    QString userNums;         //检验者编号
    QString userName;          //检验者名字
    QString inspectionType;  // 检验类型
    QString inspectionTypelist;  // 检验类型
    QStringList inspectlists;//  检验类型列表
};

#endif // USERLOGINDIALOG_H
