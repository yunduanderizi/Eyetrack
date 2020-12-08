#include "mainwindow.h"

#include <QApplication>
#include"QSplashScreen"
#include "QPixmap"
#include<QCoreApplication>
#include<userlogindialog.h>
#include<QDialog>
#include<QTextCodec>
#include <QMutex>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include"maindlg.h"
#include"quiwidget.h"
#include"appinit.h"
#include"qeyecontrol.h"
void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text = QString("Debug:");
        break;

    case QtWarningMsg:
        text = QString("Warning:");
        break;

    case QtCriticalMsg:
        text = QString("Critical:");
        break;

    case QtFatalMsg:
        text = QString("Fatal:");
    }

    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);

    QFile file("log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //qInstallMessageHandler(outputMessage);
    //CommonHelper::setStyle(":/Res/qss/style.qss");
    // UserLoginDialog * dlg = new UserLoginDialog;
    QUIWidget::setCode();
    QUIWidget::setTranslator(":/Image/Res/Image/qt_zh_CN.qm");

//        QIcon icon(":/Image/Res/Image/EyeTrack.jpg");
//        QSplashScreen * splash = new QSplashScreen();
//        splash->setPixmap(QPixmap(":/Image/Res/Image/IsenSplansh.png"));
//        splash->show();
//        Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
//        splash->showMessage(QObject::tr("Setting up the main window..."), topRight, Qt::white);//显示信息

//        splash->showMessage(QObject::tr("Loading modules..."),topRight, Qt::black); //显示信息

//        splash->showMessage(QObject::tr("Establishing connections..."),topRight, Qt::white); //显示信息
//        gpSys->InitControl();
//        gpSys->GetCDDControl()->InitCCD();
//        MainWindow w;
//        w.setWindowIcon(icon);
//        splash->finish(&w);//图片一直显示到mainWin加载完成
//        delete splash;//释放空间，节省内存
//        w.show();
//
//    a.connect( &a,SIGNAL(lastWindowClosed()),&a,SLOT(quit()));
    CommonHelper::setStyle(":/Res/qss/style.qss");
    a.setFont(QFont("Microsoft Yahei", 9));
    QUIWidget::setCode();
    QEyeControl::Instance()->InitControl();
    QEyeControl::Instance()->ccdControl->InitCCD();
    AppInit::Instance()->start();

    MainDlg dlg;

    dlg.show();
    return a.exec();





}
