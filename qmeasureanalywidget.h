#ifndef QMEASUREANALYWIDGET_H
#define QMEASUREANALYWIDGET_H

#include <QWidget>

namespace Ui {
class QMeasureAnalyWidget;
}

class QMeasureAnalyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QMeasureAnalyWidget(QWidget *parent = nullptr);
    ~QMeasureAnalyWidget();

private:
    Ui::QMeasureAnalyWidget *ui;
};

#endif // QMEASUREANALYWIDGET_H
