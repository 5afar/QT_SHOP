#include "auth.h"
#include "registration.h"
#include "ui_auth.h"
#include <QMessageBox>

Auth::Auth(QDialog *parent) :   /// Конструктор окна авторизации
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
bool Auth::get_isAuth()  /// Функция для получения статуса авторизации
{
    return (isAuth);
}
void Auth::on_pushButton_clicked()   /// Слот, который активируется при нажатии кнопки авторизации
{

    isAuth=sql.get_Auth(isAuth,ui->loginLine->text(),ui->passwordLine->text()); /// Запуск функции из класса interactsql для получения данных авторизации
    id=sql.get_id();   /// Получение id пользователя из класса interactsql
    if (isAuth)  /// Проверка статуса авторизации
    {
        this->close();
    }
    else
    {
        ui->pushButton->setText("Try again!");
    }
}

void Auth::on_pushButton_2_clicked() /// Слот, который активируется при нажатии кнопки Выход
{
    QCoreApplication::quit();
    this->close();
}
int Auth::get_id()  /// Функция, которая возвращает id пользователя
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

