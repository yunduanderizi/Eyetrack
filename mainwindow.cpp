#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QEyeCommon.h>
#include<QMdiArea>
#include"qcalibrationwidget.h"
#include"qeyetrackingwidget.h"
#include"qpatientwidget.h"
QEyeControl * gpSys = new QEyeControl;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitWindow();
    void(EyeTrackerToolBox::*SendMsg)(SignalType) = &EyeTrackerToolBox::SendMsg;

    connect(toolbox,SendMsg,eyetrackwidget,&QEyeTrackingWidget::SlotGetSignalType);
    connect(toolbox,SendMsg,this,&MainWindow::SlotGetSignalType);
  //  void(QStackedWidget::*currentChanged)(int) = &QStackedWidget::currentChanged;
    connect(stackwidget,&QStackedWidget::currentChanged,eyetrackwidget,&QEyeTrackingWidget::SlotChangeCurrentstackWidget);
   // toolbox->installEventFilter(this);
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);

}
void MainWindow::InitWindow()
{
   stackwidget = new QStackedWidget;


    this->showMaximized();
    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_QuitOnClose,true);
    this->setCentralWidget(stackwidget);
    calibratewidget = new QCalibrationWidget;
    eyetrackwidget = new QEyeTrackingWidget(this);
    patientwidget = new QPatientWidget;
    stackwidget->addWidget(patientwidget);
    stackwidget->addWidget(calibratewidget);
    stackwidget->addWidget(eyetrackwidget);
    dockwidget   =  new QDockWidget;
    toolbox = new EyeTrackerToolBox(this);
    dockwidget->setWidget(toolbox);
//    cameratoolbox = new SSCameraToolBox(this);
  //  dockwidget->setWidget(cameratoolbox);
    this->addDockWidget(Qt::LeftDockWidgetArea,dockwidget);






}
MainWindow::~MainWindow()
{
    qDebug()<<"MainWindow 析构函数";
    delete dockwidget;

    delete calibratewidget;
    delete eyetrackwidget;
    delete stackwidget;
    delete gpSys;
    delete ui;
}


//void MainWindow::on_patientPushBtn_clicked()
//{
//    qDebug()<<"on_patientPushBtn_clicked";
//    switchWidget(0);

//}
//void MainWindow::on_CalibratePushBtn_clicked()
//{
//    qDebug()<<"on_CalibratePushBtn_clicked";
//  switchWidget(1);

//}

//void MainWindow::on_EyeTrackPushBtn_clicked()
//{
//    //if(gpSys->GetCaliControl()->GetCalibrateStatus())
//        switchWidget(2);
//    //else
//   // {
////        QMessageBox::warning(this,QStringLiteral("警告"),QStringLiteral("请先进行校准"));
////        return;
//    //}
//}

//void MainWindow::on_MeasurePushBtn_clicked()
//{
//    qDebug()<<"on_MeasurePushBtn_clicked";
//}
void MainWindow::SetWidgetBgColor(QWidget * widget)
{

Q_UNUSED(widget)

}
void MainWindow::paintEvent(QPaintEvent *event)
{
//    SetWidgetBgColor(ui->widget);

Q_UNUSED(event)
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    qDebug()<<"mainwidows closeevent";
   // gpSys->GetCDDControl()->QlStopDevice();
}
void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
  //  qDebug()<<"resizeEvent";
}
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched)
    Q_UNUSED(event)

  //  qDebug()<<"watched:"<<watched<<"event"<<event->type();
//        switch ((int)event->type())
//        {
//            case QEvent::Resize:
//                if (toolbox) toolbox->setFixedSize(dockwidget->size());
//                break;
//        }


    return QWidget::eventFilter(watched, event);

}
void MainWindow::switchWidget(int widgetNum)
{
    stackwidget->setCurrentIndex(widgetNum);
}
void MainWindow::SlotGetSignalType(SIGNALSYPE signal)
{
    qDebug()<<"mainwindow signal"<<signal;
    switch (signal) {
    case addPatient:
    {
        switchWidget(0);
        break;
    }
    case Calibrate:
    {
        switchWidget(1);
        break;
    }
    case Graze:
    case SportsLines:
    case SPicture:
    case RandomPic:
    {
      // if(gpSys->GetCaliControl()->GetCalibrateStatus())
            switchWidget(2);
        break;
    }
    case ReportForm:
    {


        break;
    }
    case Exit:
    {
        close();
        break;
    }
    case Help:
    {
        break;
    }
    default:
        break;

    }
}
