#include "userlogindialog.h"
#include "ui_userlogindialog.h"
#include<mainwindow.h>
#include"QEyeDefine.h"

UserLoginDialog::UserLoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserLoginDialog)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    GetAllIniInfo();
    InitDialog();


//    ui->pushButtonLogin->setStyleSheet("QPushButton{background-color: rgb(225, 225, 225);border:1px groove gray;border-radius:4px;padding:1px 4px;border-style: outset;}"
//                                                          "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
//                                                          "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
}

UserLoginDialog::~UserLoginDialog()
{
    qDebug()<<"UserLoginDialog 析构函数";
    GetWidgetText();
    SaveAllIniInfo();
    delete ui;
}
void UserLoginDialog::closeEvent(QCloseEvent *event)
{
    qDebug()<<"this is the  closeevent";
}



void UserLoginDialog::on_pushButtonLogin_clicked()
{
    GetWidgetText();
    SaveAllIniInfo();
}

void UserLoginDialog::on_pushButtonCancel_clicked()
{

}
void UserLoginDialog::GetWidgetText()
{
    hospitalName = ui->lineEdit_HospitalName->text();
    officeName=ui->lineEdit_Office->text();
    userName=ui->lineEdit_UserName->text();
    userNums = ui->lineEdit_UserNum->text();
    inspectionType =ui->comboBox->currentText();
    qDebug()<<"hostpitalname"<<hospitalName<<"officename"<<officeName<<"username"<<userName<<"num"<<userNums<<"inspect"<<inspectionType;
}
void UserLoginDialog::InitDialog()
{
    ui->lineEdit_HospitalName->setText(hospitalName);
    ui->lineEdit_Office->setText(officeName);
    ui->lineEdit_UserNum->setText(userNums);
    ui->lineEdit_UserName->setText(userName);
    ui->comboBox->addItems(inspectlists);
    ui->comboBox->setCurrentText(inspectionType);
}

void UserLoginDialog::GetAllIniInfo()
{
    QString path=QEyeControl::Instance()->GetApplicationPath();
    QString configfilename("EyeTrack.ini");
    Iniinfo = new QEyeConfigControl(path,configfilename);
    hospitalName= Iniinfo->ReadStringIniFile(LONGININFOCONFIG,HOSPITALNAME,"");
    officeName=Iniinfo->ReadStringIniFile(LONGININFOCONFIG,OFFICENAME,"");
    userNums=Iniinfo->ReadStringIniFile(LONGININFOCONFIG,USERNUMS,"");
    userName=Iniinfo->ReadStringIniFile(LONGININFOCONFIG,USERNAME,"");

    inspectionType=Iniinfo->ReadStringIniFile(LONGININFOCONFIG,INSPECTIONTYPE,QStringLiteral("神经"));
    inspectionTypelist = Iniinfo->ReadStringIniFile(LONGININFOCONFIG,INSPECTIONTYPELIST,QStringLiteral("神经,抑郁症,强迫症,精神分裂症"));
    inspectlists = inspectionTypelist.split(',');
    qDebug()<<"inspectlists"<<inspectlists;

}
void UserLoginDialog::SaveAllIniInfo()
{
    Iniinfo->WriteStringIniFile(LONGININFOCONFIG,HOSPITALNAME,hospitalName);
    Iniinfo->WriteStringIniFile(LONGININFOCONFIG,OFFICENAME,officeName);
    Iniinfo->WriteStringIniFile(LONGININFOCONFIG,USERNUMS,userNums);
    Iniinfo->WriteStringIniFile(LONGININFOCONFIG,USERNAME,userName);
    Iniinfo->WriteStringIniFile(LONGININFOCONFIG,INSPECTIONTYPE,inspectionType);

}


