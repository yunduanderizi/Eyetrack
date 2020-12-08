#ifndef QINDOCKWIDGET_H
#define QINDOCKWIDGET_H

#include<QWidget>
#include<QSize>

class QInDockWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QInDockWidget(QWidget *parent = nullptr);
    QSize sizeHint() const;
    void SetframeSize(QSize size);
signals:
private:
    QSize FrameSize;
};

#endif // QINDOCKWIDGET_H
