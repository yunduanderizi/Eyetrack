#include "SSToolBoxItem.h"
#include "SSToolBox.h"

#include <QMouseEvent>


/********************************************************
 * 函数名称: SSToolBoxItem
 * 函数功能: 构造函数 初始化各成员变量值|初始化界面相关信息
 * 输入参数: parent    当前窗口的父（窗口）对象的指针
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
SSToolBoxItem::SSToolBoxItem(QWidget *parent, QString name) : QWidget(parent)
{
    //初始化变量
    m_pToolBox = (SSToolBox *)parent;

    m_bExpand = true;
    m_sName = name;

    //创建标题栏、内容区、名称、图标
    createCtrl();

    //初始化布局
    initLayout();
}

/********************************************************
 * 函数名称: createCtrl
 * 函数功能: 创建标题栏、内容区、名称、图标
 * 输入参数:
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
void SSToolBoxItem::createCtrl()
{
    //标题栏
    m_pBar = new QWidget(this);
    m_pBar->setFixedHeight(BAR_HEIGHT);
    m_pBar->setStyleSheet("background: rgb(170, 170, 170)");

    //标题名称
    m_pName = new QLabel(m_sName, m_pBar);
    m_pName->adjustSize();

    //图标
    m_pIcon = new QLabel(m_pBar);
    setIcon();
    m_pIcon->adjustSize();

    //内容
    m_pContent = new QWidget(this);
    m_pContent->setStyleSheet("background: rgb(218, 222, 225)");
 //   m_pContent->hide();
}

/********************************************************
 * 函数名称: initLayout
 * 函数功能: 初始化布局
 * 输入参数:
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
void SSToolBoxItem::initLayout()
{
    //标题栏布局
    QHBoxLayout *pBarLayout = new QHBoxLayout;
    pBarLayout->addWidget(m_pName);
    pBarLayout->addStretch();
    pBarLayout->addWidget(m_pIcon);
    pBarLayout->setSpacing(0);
    pBarLayout->setContentsMargins(10, 0, 4, 0);
    m_pBar->setLayout(pBarLayout);

    //整体布局
    QVBoxLayout *pMainLayout = new QVBoxLayout;
    pMainLayout->addWidget(m_pBar);
    pMainLayout->addWidget(m_pContent);
    pMainLayout->addStretch();
    pMainLayout->setSpacing(0);
    pMainLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(pMainLayout);
}

/********************************************************
 * 函数名称: setIcon
 * 函数功能: 设置标题栏图标
 * 输入参数:
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
void SSToolBoxItem::setIcon()
{
    //图标
    QPixmap pixmap(m_bExpand ? ":/Image/Res/Image/bottom.png" : ":/Image/Res/Image/top.png");
    m_pIcon->setPixmap(pixmap);
}

/********************************************************
 * 函数名称: stateSwitch
 * 函数功能: 展开/闭合状态切换
 * 输入参数:
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
void SSToolBoxItem::stateSwitch()
{
    m_bExpand = !m_bExpand;

    //图标
    setIcon();

    //状态
    m_pContent->setVisible(m_bExpand);

    //自适应高度
    this->adjustSize();
    m_pToolBox->adjustScrollAreaWidgetSize();
}

/********************************************************
 * 函数名称: mousePressEvent
 * 函数功能: 鼠标点击标题栏区 显示/隐藏内容区
 * 输入参数:
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
void SSToolBoxItem::mousePressEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    if (m_pBar->geometry().contains(point))
    {
        stateSwitch();
    }

    QWidget::mousePressEvent(event);
}
