#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);


}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_Cancel_clicked()
{

}

void LoginDialog::on_pushButtonLogin_clicked()
{

}
