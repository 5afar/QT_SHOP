#ifndef EDITPROFILE_H
#define EDITPROFILE_H

#include <QDialog>
#include "mainwindow.h"


namespace Ui {
class EditProfile;
}

class EditProfile : public QDialog
{
    Q_OBJECT

public:
    explicit EditProfile(QDialog *parent = nullptr);
    ~EditProfile();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditProfile *ui;
};

#endif // EDITPROFILE_H
