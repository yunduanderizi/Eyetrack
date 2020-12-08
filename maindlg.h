#ifndef MAINDLG_H
#define MAINDLG_H
#pragma execution_character_set("utf-8")
#include <QDialog>
#include"ControlWidget/navlistview.h"
#include"quiwidget.h"
#include"QEyeDefine.h"
#include "addpatientdialog.h"
#include"qcalibrationwidget.h"
#include"qeyetrackingwidget.h"
#include"qmeasureanalywidget.h"

#include"qpatientwidget.h"
#include"qdisplayontv.h"
#include<qeyetrackwidget.h>

#define MAINDLGSTR      "主界面"
#define PATIENTSTR      "病例"
#define ADDPETIENTSTR   "添加病例"
#define PATIENTLISTSTR  "病例列表"
#define CALIBRATIONSTR  "定标"
#define EYTRAKINGSTR    "视线追踪"

#define GAZESTR         "凝视"
#define SPORTLINESTR  "运动曲线"
#define SLINESSTR       "S曲线"
#define RANDOMPICSTR    "随机图片"
#define MEASUREANALYSTR "测量分析"
#define REPORTSTR       "报告"
#define HELPSTR         "帮助"
#define EXITSOFTSTR     "退出软件"
namespace Ui {
class MainDlg;
}

class MainDlg : public QDialog
{
    Q_OBJECT

public:

    explicit MainDlg(QWidget *parent = nullptr);
    ~MainDlg();
    SignalType changeWidgetByString(QString indexName);
    SignalType changeWidgetByIndex(int index);
    void switchStack(int index);
    void initControlWidget();
    void initSignals();
private:
    Ui::MainDlg *ui;
    bool max;
    QRect location;
    QPatientWidget * patienWidget;
    QMeasureAnalyWidget * measureWidget;
    QCalibrationWidget * calibrateWidget;
    QEyeTrackWidget * eyetrackWidget;
    AddPatientDialog * addPatientDialog;
    QDisPlayOnTV *      displayOnTVWidget;

protected:
    bool eventFilter(QObject *obj, QEvent * event);
    void closeEvent(QCloseEvent *);

signals:
    void signalSendBigScreenType(SignalType  screenType);


private slots:
    void initForm();
    void initIndex();

    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();
    void on_listView_pressed(const QModelIndex &index);



};

#endif // MAINDLG_H
