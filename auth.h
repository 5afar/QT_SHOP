#ifndef AUTH_H
#define AUTH_H

#include "interactsql.h"
#include <QDialog>

namespace Ui {
class Auth;   /// Класс окна авторизации
}

class Auth : public QDialog
{
    Q_OBJECT

public:
    explicit Auth(QDialog *parent = nullptr);
    ~Auth();
    bool get_isAuth(); /// Функция для получения статуса авторизации
    int get_id();  /// Функция для получения id пользователя
    bool get_reg();

private slots:
    void on_pushButton_clicked();   /// Слот, который активируется при нажатии кнопки авторизации

    void on_pushButton_2_clicked();  /// Слот, который активируется при нажатии кнопки Выход

    void on_pushButton_3_clicked();

private:
    interactsql sql;  /// Объект класса interactsql
    Ui::Auth *ui;  /// Указатель на графический интерфейс окна авторизации
    bool isAuth=false; /// Статус авторизации
    int id;  /// id пользователя
    bool reg=false;
};

#endif // AUTH_H
