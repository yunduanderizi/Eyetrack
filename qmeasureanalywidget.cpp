#include "qmeasureanalywidget.h"
#include "ui_qmeasureanalywidget.h"

QMeasureAnalyWidget::QMeasureAnalyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMeasureAnalyWidget)
{
    ui->setupUi(this);
}

QMeasureAnalyWidget::~QMeasureAnalyWidget()
{
    delete ui;
}
