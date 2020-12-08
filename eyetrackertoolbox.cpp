#include "eyetrackertoolbox.h"
#include "SSToolBoxItem.h"

#include <QToolButton>

/********************************************************
 * 函数名称: SSCameraToolBox
 * 函数功能: 构造函数 初始化各成员变量值|初始化界面相关信息
 * 输入参数: parent    当前窗口的父（窗口）对象的指针
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
EyeTrackerToolBox::EyeTrackerToolBox(QWidget *parent) : SSToolBox(parent)
{
    //创建控件

    createPatientBar();
    createCalibrateBar();
    createEyeTrackerBar();
    createMeasureAnalyBar();
   // createDateMangerBar();
    createReportFormBar();
    createHelpBar();
    createExitBar();
    createScrollArea();

    //初始化
    initLayout();
}

QSize EyeTrackerToolBox::sizeHint() const
{
   return QSize(270, 900); /* 在这里定义dock的初始大小 */
}
/********************************************************
 * 函数名称: buttonClicked
 * 函数功能: 响应按钮点击事件
 * 输入参数:
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
void EyeTrackerToolBox::buttonClick()
{
    
    QToolButton *pButton = qobject_cast<QToolButton *>(sender());
    if (pButton == NULL) return;
    SIGNALSYPE signal=noSignale;
    QString buttonObjectName = pButton->objectName();
    if(buttonObjectName.compare(CALIBRATE)==0)
        signal = Calibrate;
    else if(buttonObjectName.compare(ADDPATIENT)==0)
        signal = addPatient;
    else if(buttonObjectName.compare(PATIENTLIST)==0)
        signal =Patientlist;
    else if(buttonObjectName.compare(GRAZE)==0)
        signal= Graze;
    else if(buttonObjectName.compare(SPORTLINES)==0)
        signal = SportsLines;
    else if(buttonObjectName.compare(SPICTURE)==0)
        signal = SPicture;
    else if(buttonObjectName.compare(RADDOMPIC)==0)
        signal = RandomPic;
    else if(buttonObjectName.compare(MEASUREANALY)==0)
        signal = MeasureAnaly;
    else if(buttonObjectName.compare(DATAMANAGER)==0)
        signal = DataManger;
    else if(buttonObjectName.compare(REPORT)==0)
        signal = ReportForm;
    else if(buttonObjectName.compare(HELP)==0)
        signal = Help;
    else if(buttonObjectName.compare(EXITAPP)==0)
        signal = Exit;

    emit SendMsg(signal);

}


/********************************************************
 * 函数名称: createResolutionBar
 * 函数功能: 创建分辨率栏
 * 输入参数:
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
void EyeTrackerToolBox::createPatientBar()
{
    //分辨率
    m_pPatientBar = new SSToolBoxItem(this, QStringLiteral("病例"));
    m_listBar << m_pPatientBar;
    QStringList buttontextlist,objectNamelist;
    buttontextlist<<QStringLiteral("添加病例")<<QStringLiteral("病例列表");
    objectNamelist<<ADDPATIENT<<PATIENTLIST;
    objectNamelist<<"addPatient"<<"patientList";
    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->addStretch();
    for (int i = 0; i < buttontextlist.size(); i++)
    {
        QToolButton *pButton = new QToolButton;
        pButton->setText(buttontextlist[i]);
        pButton->setObjectName(objectNamelist[i]);
        connect(pButton, SIGNAL(clicked()), this, SLOT(buttonClick()));
        pLayout->addWidget(pButton);
    }
    pLayout->addStretch();
    pLayout->setSpacing(4);

    m_pPatientBar->setContentLayout(pLayout);
}
void EyeTrackerToolBox::createCalibrateBar()
{
     m_pCalibrateBar = new SSToolBoxItem(this, QStringLiteral("标定"));
    m_listBar << m_pCalibrateBar;
    QStringList buttontextlist,objectNamelist;
    objectNamelist<<CALIBRATE;
    buttontextlist<<QStringLiteral("  标定  ");
    QVBoxLayout *pLayout = new QVBoxLayout;

    pLayout->addStretch();
    for (int i = 0; i < buttontextlist.size(); i++)
    {
        QToolButton *pButton = new QToolButton;
        pButton->setObjectName(objectNamelist[i]);
        pButton->setText(buttontextlist[i]);
        connect(pButton, SIGNAL(clicked()), this, SLOT(buttonClick()));
        pLayout->addWidget(pButton);
    }
    pLayout->addStretch();
    pLayout->setSpacing(4);

    m_pCalibrateBar->setContentLayout(pLayout);
}
void EyeTrackerToolBox::createEyeTrackerBar()
{
    m_pEyetrackerBar = new SSToolBoxItem(this, QStringLiteral("视线追踪"));
   m_listBar << m_pEyetrackerBar;
   QStringList buttontextlist,objectNamelist;
   objectNamelist<<GRAZE<<SPORTLINES<<SPICTURE<<RADDOMPIC;
   buttontextlist<<QStringLiteral("  凝视  ")<<QStringLiteral("运动曲线")<<QStringLiteral("  S图片 ")<<QStringLiteral("随机图片");
   QVBoxLayout *pLayout = new QVBoxLayout;
   pLayout->addStretch();
   for (int i = 0; i < buttontextlist.size(); i++)
   {
       QToolButton *pButton = new QToolButton;
       pButton->setText(buttontextlist[i]);
       pButton->setObjectName(objectNamelist[i]);
       connect(pButton, SIGNAL(clicked()), this, SLOT(buttonClick()));
       pLayout->addWidget(pButton);
   }
   pLayout->addStretch();
   pLayout->setSpacing(4);

   m_pEyetrackerBar->setContentLayout(pLayout);
}
void EyeTrackerToolBox::createMeasureAnalyBar()
{
    m_pMeasureAnalyBar = new SSToolBoxItem(this, QStringLiteral("测量分析"));
   m_listBar << m_pMeasureAnalyBar;
   QStringList buttontextlist,objectNamelist;
   objectNamelist<<MEASUREANALY;
   buttontextlist<<QStringLiteral("测量分析");
   QVBoxLayout *pLayout = new QVBoxLayout;
   pLayout->addStretch();
   for (int i = 0; i < buttontextlist.size(); i++)
   {
       QToolButton *pButton = new QToolButton;
       pButton->setText(buttontextlist[i]);
       pButton->setObjectName(objectNamelist[i]);
       connect(pButton, SIGNAL(clicked()), this, SLOT(buttonClick()));
       pLayout->addWidget(pButton);
   }
   pLayout->addStretch();
   pLayout->setSpacing(4);

   m_pMeasureAnalyBar->setContentLayout(pLayout);
}
void EyeTrackerToolBox::createDateMangerBar()
{
    m_pDataManagerBar = new SSToolBoxItem(this, QStringLiteral("数据分析"));
   m_listBar << m_pDataManagerBar;
   QStringList buttontextlist,objectNamelist;
   objectNamelist<<DATAMANAGER;
   buttontextlist<<QStringLiteral("数据分析");
   QVBoxLayout *pLayout = new QVBoxLayout;
   pLayout->addStretch();
   for (int i = 0; i < buttontextlist.size(); i++)
   {
       QToolButton *pButton = new QToolButton;
       pButton->setText(buttontextlist[i]);
       pButton->setObjectName(objectNamelist[i]);
       connect(pButton, SIGNAL(clicked()), this, SLOT(buttonClick()));
       pLayout->addWidget(pButton);
   }
   pLayout->addStretch();
   pLayout->setSpacing(4);

   m_pDataManagerBar->setContentLayout(pLayout);

}
void EyeTrackerToolBox::createReportFormBar()
{
    m_pReportFormBar = new SSToolBoxItem(this, QStringLiteral("报告"));
   m_listBar << m_pReportFormBar;

   QStringList buttontextlist,objectNamelist;
   objectNamelist<<REPORT;

   buttontextlist<<QStringLiteral("  报告  ");
   QVBoxLayout *pLayout = new QVBoxLayout;
   pLayout->addStretch();
   for (int i = 0; i < buttontextlist.size(); i++)
   {
       QToolButton *pButton = new QToolButton;
       pButton->setText(buttontextlist[i]);
       pButton->setObjectName(objectNamelist[i]);
       connect(pButton, SIGNAL(clicked()), this, SLOT(buttonClick()));
       pLayout->addWidget(pButton);
   }
   pLayout->addStretch();
   pLayout->setSpacing(4);

   m_pReportFormBar->setContentLayout(pLayout);
}
void EyeTrackerToolBox::createHelpBar()
{
    m_pHelpBar = new SSToolBoxItem(this, QStringLiteral("帮助"));
   m_listBar << m_pHelpBar;
   QStringList buttontextlist,objectNamelist;
   objectNamelist<<HELP;

   buttontextlist<<QStringLiteral("  帮助  ");
   QVBoxLayout *pLayout = new QVBoxLayout;
   pLayout->addStretch();
   for (int i = 0; i < buttontextlist.size(); i++)
   {
       QToolButton *pButton = new QToolButton;
       pButton->setText(buttontextlist[i]);
       pButton->setObjectName(objectNamelist[i]);
       connect(pButton, SIGNAL(clicked()), this, SLOT(buttonClick()));
       pLayout->addWidget(pButton);
   }
   pLayout->addStretch();
   pLayout->setSpacing(4);

   m_pHelpBar->setContentLayout(pLayout);
}
void EyeTrackerToolBox::createExitBar()
{
    m_pExitBar = new SSToolBoxItem(this, QStringLiteral("退出应用"));
   m_listBar << m_pExitBar;
   QStringList buttontextlist,objectNamelist;
   objectNamelist<<EXITAPP;
   buttontextlist<<QStringLiteral("退出应用");
   QVBoxLayout *pLayout = new QVBoxLayout;
   pLayout->addStretch();
   for (int i = 0; i < buttontextlist.size(); i++)
   {
       QToolButton *pButton = new QToolButton;
       pButton->setText(buttontextlist[i]);
       pButton->setObjectName(objectNamelist[i]);
       connect(pButton, SIGNAL(clicked()), this, SLOT(buttonClick()));
       pLayout->addWidget(pButton);
   }
   pLayout->addStretch();
   pLayout->setSpacing(4);

   m_pExitBar->setContentLayout(pLayout);
}
