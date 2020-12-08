#ifndef QPATIENTWIDGET_H
#define QPATIENTWIDGET_H

#include <QWidget>
#include<QString>
#include<QStringList>
#include"mainwindow.h"
namespace Ui {
class QPatientWidget;
}

class QPatientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QPatientWidget(QWidget *parent = nullptr);
    ~QPatientWidget();
    Ui::QPatientWidget *ui;
    void InitWidget();
    void GetDocList(QStringList &doclist);
    void GetallEduType(QStringList & eduTypeList);
    void GetallControlValue(PatientInfo & patient);
    void SavePatient(PatientInfo patient);
private slots:
    void on_pushButton_save_clicked();

private:
};

#endif // QPATIENTWIDGET_H
