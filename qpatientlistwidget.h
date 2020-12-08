#ifndef QPATIENTLISTWIDGET_H
#define QPATIENTLISTWIDGET_H

#include <QWidget>

namespace Ui {
class QPatientListWidget;
}

class QPatientListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QPatientListWidget(QWidget *parent = nullptr);
    ~QPatientListWidget();

private:
    Ui::QPatientListWidget *ui;
};

#endif // QPATIENTLISTWIDGET_H
