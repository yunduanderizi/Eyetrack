#include "SSCameraToolBox.h"
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
SSCameraToolBox::SSCameraToolBox(QWidget *parent) : SSToolBox(parent)
{
    //创建控件
    createResolutionBar();
    createExposureBar();
    createWhiteBalanceBar();
    createImageAdjustmentBar();
    createHistogramBar();
    createScrollArea();

    //初始化
    initLayout();
}

/********************************************************
 * 函数名称: buttonClicked
 * 函数功能: 响应按钮点击事件
 * 输入参数:
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
void SSCameraToolBox::buttonClicked()
{

    QToolButton *pButton = qobject_cast<QToolButton *>(sender());
    if (pButton == NULL) return;


}

/********************************************************
 * 函数名称: createResolutionBar
 * 函数功能: 创建分辨率栏
 * 输入参数:
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
void SSCameraToolBox::createResolutionBar()
{
    //分辨率    
    m_pPatientBar = new SSToolBoxItem(this, QStringLiteral("病例"));
    m_listBar << m_pPatientBar;
    QStringList buttontextlist;
    buttontextlist<<QStringLiteral("添加病例")<<QStringLiteral("病例列表");
    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->addStretch();
    for (int i = 0; i < 2; i++)
    {
        QToolButton *pButton = new QToolButton;
        pButton->setText(buttontextlist[i]);
        connect(pButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));
        pLayout->addWidget(pButton);
    }
    pLayout->addStretch();
    pLayout->setSpacing(4);

    m_pPatientBar->setContentLayout(pLayout);
}

/********************************************************
 * 函数名称: createExposureBar
 * 函数功能: 创建曝光栏
 * 输入参数:
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
void SSCameraToolBox::createExposureBar()
{
    //曝光控制
    m_pExposureBar = new SSToolBoxItem(this, tr("Exposure Control"));
    m_listBar << m_pExposureBar;

    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->addStretch();
    for (int i = 0; i < 4; i++)
    {
        QToolButton *pButton = new QToolButton;
        pLayout->addWidget(pButton);
    }
    pLayout->addStretch();
    pLayout->setSpacing(4);

    m_pExposureBar->setContentLayout(pLayout);
}

/********************************************************
 * 函数名称: createWhiteBalanceBar
 * 函数功能: 创建白平衡栏
 * 输入参数:
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
void SSCameraToolBox::createWhiteBalanceBar()
{
    //曝光控制
    m_pWhiteBalanceBar = new SSToolBoxItem(this, tr("White Balance"));
    m_listBar << m_pWhiteBalanceBar;

    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->addStretch();
    for (int i = 0; i < 4; i++)
    {
        QToolButton *pButton = new QToolButton;
        pLayout->addWidget(pButton);
    }
    pLayout->addStretch();
    pLayout->setSpacing(4);

    m_pWhiteBalanceBar->setContentLayout(pLayout);
}

/********************************************************
 * 函数名称: createImageAdjustmentBar
 * 函数功能: 创建图像调整栏
 * 输入参数:
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
void SSCameraToolBox::createImageAdjustmentBar()
{
    //图像调整
    m_pImageAdjustment = new SSToolBoxItem(this, tr("Image Adjustment"));
    m_listBar << m_pImageAdjustment;

    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->addStretch();
    for (int i = 0; i < 4; i++)
    {
        QToolButton *pButton = new QToolButton;
        pLayout->addWidget(pButton);
    }
    pLayout->addStretch();
    pLayout->setSpacing(4);

    m_pImageAdjustment->setContentLayout(pLayout);
}

/********************************************************
 * 函数名称: createHistogramBar
 * 函数功能: 创建直方图栏
 * 输入参数:
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
void SSCameraToolBox::createHistogramBar()
{
    //直方图
    m_pHistogram = new SSToolBoxItem(this, tr("Histogram"));
    m_listBar << m_pHistogram;

    QHBoxLayout *pLayout = new QHBoxLayout;
    pLayout->addStretch();
    for (int i = 0; i < 4; i++)
    {
        QToolButton *pButton = new QToolButton;
        pLayout->addWidget(pButton);
    }
    pLayout->addStretch();
    pLayout->setSpacing(4);

    m_pHistogram->setContentLayout(pLayout);
}
