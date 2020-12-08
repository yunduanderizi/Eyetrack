#include "SSToolBox.h"
#include "SSToolBoxItem.h"

#include <QEvent>
#include <QScrollBar>

/********************************************************
 * 函数名称: SSToolBox
 * 函数功能: 构造函数 初始化各成员变量值|初始化界面相关信息
 * 输入参数: parent    当前窗口的父（窗口）对象的指针
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
SSToolBox::SSToolBox(QWidget *parent) : QWidget(parent)
{
    //初始化
    initVar();

    this->installEventFilter(this);
}

/********************************************************
 * 函数名称: addBar
 * 函数功能: 设置Bar栏高度
 * 输入参数: boxItem  新添加的Item
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
void SSToolBox::addBar(SSToolBoxItem *boxItem)
{
    if (boxItem == NULL) return;
    m_listBar << boxItem;
}

/********************************************************
 * 函数名称: setBarHeight
 * 函数功能: 设置Bar栏高度
 * 输入参数: index  Bar的索引
 *          height 要设置Bar的高度
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
void SSToolBox::setBarHeight(int index, int height)
{
    int iCount = m_listBar.count();
    if (index < 0 || index >= iCount) return;

    m_listBar[index]->setBarHeight(height);
}

/********************************************************
 * 函数名称: setContentLayout
 * 函数功能: 设置Content布局
 * 输入参数: index  Bar的索引
 *          layout 要设置Bar的布局
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
void SSToolBox::setContentLayout(int index, QLayout *layout)
{
    int iCount = m_listBar.count();
    if (index < 0 || index >= iCount) return;

    m_listBar[index]->setContentLayout(layout);
}

/********************************************************
 * 函数名称: initVar
 * 函数功能: 初始化变量
 * 输入参数:
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
void SSToolBox::initVar()
{
    m_pScrollArea = NULL;
    m_pScrollAreaWidget = NULL;
}

/********************************************************
 * 函数名称: initLayout
 * 函数功能: 初始化布局
 * 输入参数:
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
void SSToolBox::initLayout()
{
    //建立布局
    QVBoxLayout *pMainLayout = new QVBoxLayout;
    pMainLayout->setSpacing(SPACE);
    pMainLayout->setContentsMargins(SPACEL, SPACET, SPACER, SPACEB);
    foreach (SSToolBoxItem *pItem, m_listBar)
    {
        pMainLayout->addWidget(pItem);
    }    
    pMainLayout->addStretch();
    qDebug()<<"6666666";
    m_pScrollAreaWidget->setLayout(pMainLayout);
    adjustScrollAreaWidgetSize();
}

/********************************************************
 * 函数名称: createScrollArea
 * 函数功能: 创建滚动视窗
 * 输入参数:
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
void SSToolBox::createScrollArea()
{
    //创建
    m_pScrollAreaWidget = new QWidget;
    m_pScrollArea = new QScrollArea(this);
    m_pScrollArea->setWidget(m_pScrollAreaWidget);
    m_pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    //不开启横向滚动
    m_pScrollArea->verticalScrollBar()->installEventFilter(this);           //给竖向滚动安装过滤器，因为在滚动条出现或者消失的时候需要调节m_pScrollAreaWidget大小
}

/********************************************************
 * 函数名称: eventFilter
 * 函数功能: 事件过滤器
 * 输入参数:
 * 输出参数:
 * 日   期: 2018.12.24
 * 作   者: PangShun    QQ: 872082177    Tel:
********************************************************/
bool SSToolBox::eventFilter(QObject *watched, QEvent *event)
{
    //重新改变控件的显示大小
    switch ((int)event->type())
    {
    case QEvent::Resize:
        if (watched->inherits("SSToolBox"))
        {
            //根据当前是否有滚动条出现，如果有需要减去滚动条的宽度以免挡住Bar的图标
            bool b = m_pScrollArea->verticalScrollBar()->isVisible();
            int iScrollBarWidth = m_pScrollArea->verticalScrollBar()->width();

            if (m_pScrollArea) m_pScrollArea->setFixedSize(size());
            if (m_pScrollAreaWidget) m_pScrollAreaWidget->setFixedWidth(width() - (b ?iScrollBarWidth : 0));
        }
        break;

    case QEvent::Show:
    case QEvent::Hide:
        if (watched->inherits("QScrollBar"))
        {
            //在点击Bar显示/隐藏Contents 根据当前是否有滚动条出现，如果有需要减去滚动条的宽度以免挡住Bar的图标
            int iScrollBarWidth = m_pScrollArea->verticalScrollBar()->width();
            int iWidth = width() - ((event->type() == QEvent::Show) ? iScrollBarWidth : 0);
            if (m_pScrollAreaWidget) m_pScrollAreaWidget->setFixedWidth(iWidth);
        }
        break;
    }

    return QWidget::eventFilter(watched, event);
}
