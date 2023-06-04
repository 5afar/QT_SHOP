#include "registration.h"
#include "qsqlquery.h"
#include "ui_registration.h"
#include "interactsql.h"
#include <QMessageBox>
#include <regex>

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


void Registration::on_pushButton_regist_clicked()
{
    QSqlQuery q(QSqlDatabase::database("shop"));
    if(ui->lineEdit_login->text().isEmpty()
            || ui->lineEdit_password->text().isEmpty()
            || ui->lineEdit_email->text().isEmpty()
            || ui->lineEdit_confirm->text().isEmpty()
            || ui->lineEdit_name->text().isEmpty()
            || ui->lineEdit_secondName->text().isEmpty()
            ||ui->lineEdit_CA->text().isEmpty()
            ||ui->lineEdit_CQ->text().isEmpty())
    {
        QMessageBox::warning(this,"Ошибка","Заполните пустые поля!");
    }
    else
    {
        if(q.exec("INSERT INTO user (Login, Password) VALUES ('"+ui->lineEdit_login->text()+"','"+ui->lineEdit_password->text()+"')"))
        {
          q.exec("SELECT iduser FROM user WHERE Login = '"+ui->lineEdit_login->text()+"'");
          q.first();
          QString id_user=q.value(0).toString();
          const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
          std::string s=ui->lineEdit_email->text().toStdString();
          bool valid=std::regex_match(s,pattern);
          if(valid)
          {
            if(q.exec("INSERT INTO profile (iduser,Name, Second_name, birthday, `E-mail`, Control_question, Control_answer) "
                   "VALUES "
                   "("+id_user+",'"+ui->lineEdit_name->text()+"','"+ui->lineEdit_secondName->text()+"','"+ui->dateEdit->text()+"','"+ui->lineEdit_email->text()+"','"+ui->lineEdit_CQ->text()+"','"+ui->lineEdit_CA->text()+"')"))
            {
                QMessageBox::information(this,"Успех","Вы успешно прошли регистрацию!");
            }
            else
            {
                QMessageBox::warning(this,"Ошибка","Такой E-mail уже существует!");
                q.exec("DELETE FROM user WHERE Login='"+ui->lineEdit_login->text()+"'");
            }
          }
          else
          {
              QMessageBox::warning(this,"Ошибка","E-mail введен с ошибкой!");
              q.exec("DELETE FROM user WHERE Login='"+ui->lineEdit_login->text()+"'");
          }
        }
        else
        {
            QMessageBox::warning(this,"Ошибка", "Такой Login уже существует");
        }
    }
    this->close();
}

