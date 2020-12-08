#ifndef SSTOOLBOXITEM_H
#define SSTOOLBOXITEM_H

#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

class SSToolBox;
class SSToolBoxItem : public QWidget
{
    Q_OBJECT
    enum { BAR_HEIGHT = 28 };
public:
    explicit SSToolBoxItem(QWidget *parent = nullptr, QString name = tr(""));

    inline void setBarHeight(int height) { m_pBar->setFixedHeight(height); }
    inline void setContentLayout(QLayout *pLayout = NULL) { m_pContent->setLayout(pLayout); }

private:
    void createCtrl();
    void initLayout();
    void setIcon();
    void stateSwitch();

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    bool m_bExpand;
    QString m_sName;        //名称

    QLabel  *m_pName;       //标题名称
    QLabel  *m_pIcon;       //图标
    QWidget *m_pBar;        //标题栏
    QWidget *m_pContent;    //内容区

    SSToolBox *m_pToolBox;  //父窗口
};

#endif // SSTOOLBOXITEM_H
