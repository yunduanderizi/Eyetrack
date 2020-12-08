#ifndef EYETRACKERTOOLBOX_H
#define EYETRACKERTOOLBOX_H
#include"SSToolBox.h"
#include"SSToolBoxItem.h"
#include"QEyeDefine.h"
#include<QWidget>
#include<QObject>
class EyeTrackerToolBox : public SSToolBox
{
    Q_OBJECT
public:
    explicit EyeTrackerToolBox(QWidget *parent = nullptr);
    QSize sizeHint() const;
public slots:
      void buttonClick();
//    void buttonPatientclick();
//    void buttonCalibateClick();
//    void buttonEyetrackerClick();
//    void buttonMeasureAnalyClick();
//    void buttonDataMangerClick();
//    void buttonReportForClick();
//    void buttonHelpClick();
//    void buttonExitbar();

signals:
      void SendMsg(SIGNALSYPE signal);
private:
    ANALYTYPE  analytype;// 分析疾病的类型
    void createPatientBar();
    void createCalibrateBar();
    void createEyeTrackerBar();
    void createMeasureAnalyBar();
    void createDateMangerBar();
    void createReportFormBar();
    void createHelpBar();
    void createExitBar();
private:

private:
    //病例管理
    SSToolBoxItem *m_pPatientBar;

    //校准
    SSToolBoxItem *m_pCalibrateBar;

    //测试
    SSToolBoxItem *m_pEyetrackerBar;

    //分析
    SSToolBoxItem *m_pMeasureAnalyBar;

    //数据管理
    SSToolBoxItem *m_pDataManagerBar;
    //报告
    SSToolBoxItem *m_pReportFormBar;
//帮助
    SSToolBoxItem *m_pHelpBar;
    //退出
    SSToolBoxItem *m_pExitBar;
private slots:

};

#endif // EYETRACKERTOOLBOX_H
