#include "auth.h"
#include "registration.h"
#include "ui_auth.h"
#include <QMessageBox>

Auth::Auth(QDialog *parent) :   /// ����������� ���� �����������
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
bool Auth::get_isAuth()  /// ������� ��� ��������� ������� �����������
{
    return (isAuth);
}
void Auth::on_pushButton_clicked()   /// ����, ������� ������������ ��� ������� ������ �����������
{

    isAuth=sql.get_Auth(isAuth,ui->loginLine->text(),ui->passwordLine->text()); /// ������ ������� �� ������ interactsql ��� ��������� ������ �����������
    id=sql.get_id();   /// ��������� id ������������ �� ������ interactsql
    if (isAuth)  /// �������� ������� �����������
    {
        this->close();
    }
    else
    {
        ui->pushButton->setText("Try again!");
    }
}

void Auth::on_pushButton_2_clicked() /// ����, ������� ������������ ��� ������� ������ �����
{
    QCoreApplication::quit();
    this->close();
}
int Auth::get_id()  /// �������, ������� ���������� id ������������
{
    return id;
}
void Auth::on_pushButton_3_clicked()
{
    Registration r;
    r.exec();
    reg=true;
}
bool Auth::get_reg()
{
    return reg;
}

