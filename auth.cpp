#include "auth.h"
#include "ui_auth.h"
#include <QMessageBox>

Auth::Auth(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Auth)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);

}

Auth::~Auth()
{
    delete ui;
}
bool Auth::get_isAuth()
{
    return (isAuth);
}
void Auth::on_pushButton_clicked()
{

    isAuth=sql.get_Auth(isAuth,ui->loginLine->text(),ui->passwordLine->text());
    id=sql.get_id();
    if (isAuth)
    {
        this->close();
    }
    else
    {
        ui->pushButton->setText("Try again!");
    }
}


void Auth::on_pushButton_2_clicked()
{
    QCoreApplication::quit();
    this->close();
}
int Auth::get_id()
{
    return id;
}

