#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_pushButton_cancel_clicked()
{
    this->close();
}

