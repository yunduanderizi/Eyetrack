#include "qindockwidget.h"

QInDockWidget::QInDockWidget(QWidget *parent) : QWidget(parent)
{
    frameSize().setWidth(800);
    frameSize().setHeight(800);
     setAttribute(Qt::WA_DeleteOnClose);
}
QSize QInDockWidget::sizeHint() const
{
   return QSize(270, 900); /* 在这里定义dock的初始大小 */
}
void QInDockWidget::SetframeSize(QSize size)
{
    frameSize()=size;
}
