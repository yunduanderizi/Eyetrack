#include "qpatientlistwidget.h"
#include "ui_qpatientlistwidget.h"

QPatientListWidget::QPatientListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QPatientListWidget)
{
    ui->setupUi(this);
     setAttribute(Qt::WA_DeleteOnClose);
}

QPatientListWidget::~QPatientListWidget()
{
    delete ui;
}
