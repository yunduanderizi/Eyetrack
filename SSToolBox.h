#ifndef SSTOOLBOX_H
#define SSTOOLBOX_H

#include <QDebug>
#include <QLabel>
#include <QWidget>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>


class SSToolBoxItem;
class SSToolBox : public QWidget
{
    Q_OBJECT
    enum { SPACE = 2, SPACEL = 2, SPACET = 2, SPACER = 4, SPACEB = 2};
public:
    explicit SSToolBox(QWidget *parent = nullptr);

    void addBar(SSToolBoxItem *boxItem = 0);
    void setBarHeight(int index = 0, int height = 0);
    void setContentLayout(int index = 0, QLayout *layout = 0);
    inline void adjustScrollAreaWidgetSize() { if (m_pScrollAreaWidget) m_pScrollAreaWidget->adjustSize(); }

protected:

    void initVar();
    void initLayout();
    void createScrollArea();

    bool eventFilter(QObject *watched, QEvent *event);

protected:
    //Bar
    QList<SSToolBoxItem *> m_listBar;

private:
    //滚动视窗
    QScrollArea *m_pScrollArea;
    QWidget *m_pScrollAreaWidget;
};

#endif // SSTOOLBOX_H
