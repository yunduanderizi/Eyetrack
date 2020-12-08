#ifndef ADDPATIENTDIALOG_H
#define ADDPATIENTDIALOG_H

#include <QDialog>

namespace Ui {
class AddPatientDialog;
}

class AddPatientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPatientDialog(QWidget *parent = nullptr);
    ~AddPatientDialog();
    void InitDialog();
    void GetallText();
    void SaveAllInfomation();


private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_ok_clicked();

private:
    Ui::AddPatientDialog *ui;
};

#endif // ADDPATIENTDIALOG_H
