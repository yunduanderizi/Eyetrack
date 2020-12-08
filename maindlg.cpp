#include "maindlg.h"
#include "ui_maindlg.h"

MainDlg::MainDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDlg)
{
    ui->setupUi(this);
    initControlWidget();
    initForm();
}

MainDlg::~MainDlg()
{
    qDebug()<<"Maindlg ~";

    delete patienWidget;
    delete calibrateWidget;
    delete eyetrackWidget;
    delete measureWidget;

    delete ui;
}

void MainDlg::initControlWidget()
{

    patienWidget = new QPatientWidget;
    calibrateWidget = new QCalibrationWidget;
    eyetrackWidget = new QEyeTrackWidget;
    measureWidget = new QMeasureAnalyWidget;
    displayOnTVWidget = new QDisPlayOnTV;
    displayOnTVWidget->show();


    ui->stackedWidget->insertWidget(0,patienWidget);
    ui->stackedWidget->insertWidget(2,calibrateWidget);
    ui->stackedWidget->insertWidget(3,eyetrackWidget);
    ui->stackedWidget->insertWidget(4,measureWidget);
    initSignals();
}
void MainDlg::initSignals()
{
      connect(calibrateWidget,&QCalibrationWidget::signalSendStartCalibrate,displayOnTVWidget,&QDisPlayOnTV::slotstartEyeTrack);//校准信号开始
      connect(calibrateWidget,&QCalibrationWidget::signalSendStopCalibrate,displayOnTVWidget,&QDisPlayOnTV::slotStopCalibrate);  // 停止校准
      connect(eyetrackWidget,&QEyeTrackWidget::signaleSendStartEyeTrack,displayOnTVWidget,&QDisPlayOnTV::slotstartEyeTrack); //开始眼睛追踪
      connect(eyetrackWidget,&QEyeTrackWidget::signalSendStopEyeTrack,displayOnTVWidget,&QDisPlayOnTV::slotstopEyeTrack);    //停止眼睛追踪

      void(MainDlg::*signalSendBigScreenType)(SignalType) = &MainDlg::signalSendBigScreenType;
      connect(this,signalSendBigScreenType,displayOnTVWidget,&QDisPlayOnTV::slotbigScreenType);             //主界面点击了左侧菜单 发送属性到大屏幕
      connect(this,signalSendBigScreenType,calibrateWidget,&QCalibrationWidget::slotPicType);             //主界面点击了左侧菜单 发送属性到大屏幕
      connect(this,signalSendBigScreenType,eyetrackWidget,&QEyeTrackWidget::slotPicType);             //主界面点击了左侧菜单 发送属性到大屏幕
      connect(calibrateWidget,SIGNAL(signaleSendTargetlist(QList<QPoint>)),displayOnTVWidget,SLOT(slotReceivetargetlist(QList<QPoint>)));
      connect(calibrateWidget,SIGNAL(singnalSendLeftlist(QList<QPoint>)),displayOnTVWidget,SLOT(slotRecevileftlist(QList<QPoint>)));
      connect(calibrateWidget,SIGNAL(singnalSendRightlist(QList<QPoint>)),displayOnTVWidget,SLOT(slotReceviRightlist(QList<QPoint>)));
      connect(calibrateWidget,SIGNAL(signaleCalibrateFinished()),displayOnTVWidget,SLOT(slotFinishedCalibrete()));   //校准完成发给大屏幕信号
      connect(calibrateWidget,SIGNAL(signaleSendOnePoint(QPoint)),displayOnTVWidget,SLOT(slotCalibrateTargetPoint(QPoint)));   //校准完成发给大屏幕信号
      connect(eyetrackWidget,SIGNAL(signalSendPoint(QPoint)),displayOnTVWidget,SLOT(slotEyetrackPoint(QPoint)));
        connect(eyetrackWidget,SIGNAL(signaleSendGazePoint(QPoint)),displayOnTVWidget,SLOT(slotGrazePoint(QPoint)));


}
void MainDlg::initForm()
{
    this->max = false;
    this->location = this->geometry();
    this->setProperty("form", true);
    this->setProperty("canMove", false);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    this->on_btnMenu_Max_clicked();

    this->installEventFilter(this);

   // IconHelper::Instance()->setIcon(ui->labTitle, QChar(0xf072), 35);
    IconHelper::Instance()->setIcon(ui->btnMenu_Min, QChar(0xF068));
    IconHelper::Instance()->setIcon(ui->btnMenu_Max, QChar(0xF067));
    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xF00d));

    QStringList qss;
    qss.append("QLabel#labTitle{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #2AA2DA, stop:1 #12B5C9);color:#F0F0F0;}");
    qss.append("QWidget#widgetTop{background:#FFFFFF;}");
    qss.append("QWidget#widgetMain{background:#F1F3F6;}");
    qss.append("QLabel#label{color:#202020;font:50pt;}");
    qss.append("QListView#listView{background:rgb(52,73,94);border-width:0px;}");
    this->setStyleSheet(qss.join(""));

    QStringList listItem;
    listItem.append("主界面||0|");

    listItem.append("病例||0|");
    listItem.append("添加病例|病例||");
    listItem.append("病例列表|病例||");


    listItem.append("定标||1|");
//    listItem.append("定标|定标||");
//    listItem.append("标定校验|定标||");


    listItem.append("视线追踪||0|");
    listItem.append("凝视|视线追踪|0|");
    listItem.append("运动曲线|视线追踪|0|");
    listItem.append("S曲线|视线追踪|0|");
    listItem.append("随机图片|视线追踪|0|");

    listItem.append("测量分析||1|");

    listItem.append("报告||1|");



    listItem.append("帮助||1|");
    listItem.append("退出软件||1|");

    ui->listView->setData(listItem);
    ui->listView->setColorLine(QColor(32, 53, 74));
    ui->listView->setColorBgNormal(QColor(52, 73, 94));
    ui->listView->setColorBgHover(QColor(24, 189, 155));
    ui->listView->setColorBgSelected(QColor(24, 189, 155));
    ui->listView->setColorTextNormal(QColor(250, 250, 250));
    ui->listView->setColorTextHover(QColor(0, 0, 0));
    ui->listView->setColorTextSelected(QColor(252, 252, 252));

//    QString items = "会员积分;积分;等级";
//    ui->widgetNavTop->setItems(items);
//    ui->widgetNavTop->setHorizontal(true);
//    ui->widgetNavTop->setLineWidth(5);
//    ui->widgetNavTop->setSpace(100);
//    ui->widgetNavTop->setLineColor(QColor(255, 107, 107));
//    ui->widgetNavTop->setBgColorStart(QColor(255, 255, 255));
//    ui->widgetNavTop->setBgColorEnd(QColor(255, 255, 255));
//    ui->widgetNavTop->setBarColorStart(QColor(24, 189, 155));
//    ui->widgetNavTop->setBarColorEnd(QColor(24, 189, 155));
//    ui->widgetNavTop->setTextNormalColor(QColor(80, 80, 80));
//    ui->widgetNavTop->setTextSelectColor(QColor(250, 250, 250));




}

void MainDlg::initIndex()
{
  //  ui->widgetNavTop->setCurrentIndex(0);
}

void MainDlg::on_btnMenu_Min_clicked()
{
    showMinimized();
}

void MainDlg::on_btnMenu_Max_clicked()
{
    if (max) {
        this->setGeometry(location);
        this->setProperty("canMove", true);
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
        this->setProperty("canMove", false);

    }

    max = !max;
}

void MainDlg::on_btnMenu_Close_clicked()
{
    close();
}
SignalType MainDlg::changeWidgetByString(QString indexName)
{
    if(indexName.compare(MAINDLGSTR)==0)
        return noSignale;
    else if(indexName.compare(ADDPETIENTSTR)==0)
        return addPatient;
    else if(indexName.compare(PATIENTLISTSTR)==0)
        return Patientlist;
    else if(indexName.compare(CALIBRATIONSTR)==0)
        return Calibrate;
    else if(indexName.compare(GAZESTR)==0)
        return Graze;
    else if(indexName.compare(SPORTLINESTR)==0)
        return SportsLines;
    else if(indexName.compare(SLINESSTR)==0)
        return SPicture;
    else if(indexName.compare(RANDOMPICSTR)==0)
        return RandomPic;
    else if(indexName.compare(MEASUREANALYSTR)==0)
        return MeasureAnaly;
    else if(indexName.compare(REPORTSTR)==0)
        return ReportForm;
    else if(indexName.compare(HELPSTR)==0)
        return Help;
    else if(indexName.compare(EXITSOFTSTR)==0)
        return Exit;
    else {
        return noSignale;
    }

}
void MainDlg::switchStack(int index)
{
    emit  signalSendBigScreenType((SignalType)index);
    switch (index) {

//    ui->stackedWidget->insertWidget(0,patienWidget);
//    ui->stackedWidget->insertWidget(2,calibrateWidget);
//    ui->stackedWidget->insertWidget(3,eyetrackWidget);
//    ui->stackedWidget->insertWidget(4,measureWidget);
    case addPatient:
    {
        ui->stackedWidget->setCurrentIndex(0);
        break;
    }
    case Patientlist:
    {
        ui->stackedWidget->setCurrentIndex(0);
        break;
    }
    case Calibrate:
    {
        ui->stackedWidget->setCurrentIndex(2);
        break;
    }
    case Graze:
    {
        ui->stackedWidget->setCurrentIndex(3);
        break;
    }
    case SportsLines:
    {
        ui->stackedWidget->setCurrentIndex(3);
        break;
    }
    case SPicture:
    {
        ui->stackedWidget->setCurrentIndex(3);
        break;
    }
    case RandomPic:
    {
        ui->stackedWidget->setCurrentIndex(3);
        break;
    }
    case MeasureAnaly:
    {
        ui->stackedWidget->setCurrentIndex(4);
        break;
    }
    case ReportForm:
    {
        ui->stackedWidget->setCurrentIndex(index);
        break;
    }
    case Help:
    {
        break;
    }
    case Exit:
    {
        close();
        break;
    }

    }
}
SignalType MainDlg::changeWidgetByIndex(int index)
{
Q_UNUSED(index)
    return noSignale;
}
void MainDlg::on_listView_pressed(const QModelIndex &index)
{

    int stackIndex = changeWidgetByString(index.data().toString());
    qDebug()<<"stackIndex"<<stackIndex;
    switchStack(stackIndex);


}
bool MainDlg::eventFilter(QObject * obj,QEvent * event)
{
        QDialog *pDialog = qobject_cast<QDialog *>(obj);
        if (pDialog != NULL)
        {
            if(event->type()==QEvent::KeyPress)
            {
                QKeyEvent *pKeyEvent = static_cast<QKeyEvent*>(event);
                if (pKeyEvent->key() == Qt::Key_Escape)
                {
                    return true;
                }
            }

        }

    return QDialog::eventFilter(obj,event);
}
void MainDlg::closeEvent(QCloseEvent *)
{


    calibrateWidget->stopGather();
 //   eyetrackWidget->stopGather();
    displayOnTVWidget->close();
    qDebug()<<"this is the test";
    QEyeControl::Instance()->GetCDDControl()->QlStopDevice();
}
