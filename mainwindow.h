#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDockWidget>
#include"qeyecontrol.h"
#include<QPainter>
#include<QBrush>
#include<QPen>
#include<QColor>
#include<QPalette>
#include<QMdiArea>
//#include"qindockwidget.h"
#include<QStackedWidget>
#include<QMessageBox>
#include<QDockWidget>
#include"eyetrackertoolbox.h"
#include"SSCameraToolBox.h"
#include <QFile>
#include <QApplication>
class QPatientWidget;
class QCalibrationWidget;
class  QEyeTrackingWidget;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
extern QEyeControl * gpSys;



class CommonHelper
{
public:
    static void setStyle(const QString &style) {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void InitWindow();
    void SetWidgetBgColor(QWidget* widget);
    void switchWidget(int widgetNum);
protected:
    void paintEvent(QPaintEvent * event);
    void closeEvent(QCloseEvent * event);
    void resizeEvent(QResizeEvent * event);
    bool eventFilter(QObject *watched, QEvent *event);private slots:


//    void on_patientPushBtn_clicked();

//    void on_EyeTrackPushBtn_clicked();

//    void on_MeasurePushBtn_clicked();

//    void on_CalibratePushBtn_clicked();

private:
    Ui::MainWindow *ui;
    QStackedWidget * stackwidget;
    QPatientWidget * patientwidget;
    QEyeTrackingWidget * eyetrackwidget;
    QCalibrationWidget * calibratewidget;
    QDockWidget * dockwidget;
    EyeTrackerToolBox * toolbox;

public slots:
    void  SlotGetSignalType(SignalType signal);
};
#endif // MAINWINDOW_H
