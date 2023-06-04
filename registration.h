#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "qdialog.h"
#include <QWidget>

namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT

public:
    explicit Registration(QDialog *parent = nullptr);
    ~Registration();

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_regist_clicked();

private:
    Ui::Registration *ui;
};

#endif // REGISTRATION_H
