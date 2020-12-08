#include "addpatientdialog.h"
#include "ui_addpatientdialog.h"

AddPatientDialog::AddPatientDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPatientDialog)
{
    ui->setupUi(this);
    this->setStyleSheet("QWidget#widgetMain{background:qlineargradient(spread:pad,x1:1,y1:0,x2:0,y2:0,stop:0 #0973AB,stop:1 #098DCE);}");
}
AddPatientDialog::~AddPatientDialog()
{
    delete ui;
}

void AddPatientDialog::on_pushButton_cancel_clicked()
{

}

void AddPatientDialog::on_pushButton_ok_clicked()
{

}
void AddPatientDialog::InitDialog()
{

}
void AddPatientDialog::GetallText()
{

}
