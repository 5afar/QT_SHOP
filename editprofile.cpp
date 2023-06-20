#include "editprofile.h"
#include "ui_editprofile.h"

EditProfile::EditProfile(QDialog *parent) :
    QDialog(parent) ,
    ui(new Ui::EditProfile)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
}

EditProfile::~EditProfile()
{
    delete ui;
}

void EditProfile::on_buttonBox_accepted()
{
//    if(ui->lineName->text()!="")
//        MainWindow::user->SetName(ui->lineName->text());
//    if(ui->lineSecondName->text()!="")
//        MainWindow::user->SetSecondName(ui->lineSecondName->text());
//    if(ui->lineEmail->text()!="")
//        MainWindow::user->SetEmail(ui->lineEmail->text());
//    if(ui->lineCA->text()!="")
//        MainWindow::user->SetControlAnswer(ui->lineCA->text());
//    if(ui->lineCQ->text()!="")
//        MainWindow::user->SetControlQuestion(ui->lineCQ->text());

}

