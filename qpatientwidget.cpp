#include "qpatientwidget.h"
#include "ui_qpatientwidget.h"


QPatientWidget::QPatientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QPatientWidget)
{
    ui->setupUi(this);
    InitWidget();
}

QPatientWidget::~QPatientWidget()
{
    qDebug()<<"this is~ QPainterWIdget";
    delete ui;
}
void QPatientWidget::InitWidget()
{
    QStringList docNamelist,edutypelist;
    GetDocList(docNamelist);
    ui->comboBox_docName->clear();
    ui->comboBox_docName->insertItems(0,docNamelist);
    GetallEduType(edutypelist);
    ui->comboBox_education->clear();
    ui->comboBox_education->insertItems(0,edutypelist);
   QList<PatientInfo> patinetlist;
   QList<QStringList>  valuslist;
    QEyeControl::Instance()->GetsqlPatientControl()->ReadAllPatient(patinetlist,valuslist);
    qDebug()<<"patinetlist.size:"<<patinetlist.size();


}
void QPatientWidget::GetDocList(QStringList &doclist)
{
    QEyeControl::Instance()->GetsqlPatientControl()->GetallDocNamelist(doclist);
}
void QPatientWidget::GetallEduType(QStringList &eduTypeList)
{
    QEyeControl::Instance()->GetsqlPatientControl()->GetallEduTypelist(eduTypeList);
}

void QPatientWidget::GetallControlValue(PatientInfo & patient)
{

    patient.name = ui->lineEdit_patientName->text();
   // patient.age = ui->lineEdit_patientage->text().toUInt();
    patient.sex = ui->lineEdit_patientSex->text();

    patient.docName = ui->comboBox_docName->currentText();
    patient.patientDate = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss ddd");
    patient.PatientID = ui->lineEdit_admissionNum->text();
    patient.education = ui->comboBox_education->currentText();
//    /patient.studyNum  = ui->lineEdit_studyNum->text();
    patient.Describe = ui->textEdit_describe->toPlainText();
    qDebug()<<"patientDate"<<patient.patientDate;
     qDebug()<<"Describe"<<patient.Describe;
}


void QPatientWidget::on_pushButton_save_clicked()
{
    PatientInfo patient;
    GetallControlValue(patient);
    SavePatient(patient);
}
void QPatientWidget::SavePatient(PatientInfo patient)
{
    QEyeControl::Instance()->GetsqlPatientControl()->InsertIntoDb(patient);
}
