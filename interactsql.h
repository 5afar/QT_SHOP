#ifndef INTERACTSQL_H
#define INTERACTSQL_H


#include "qsqldatabase.h"

class interactsql   /// Класс подключения к базе данных
{
private:
    bool isConnected=false;   /// Статус подключения
    QSqlDatabase db;  /// Экземпляр базы данных


public:
    interactsql(); /// Конструктор класса
    int userID;  /// id пользователя
    bool get_isConnected(); /// Функция проверки статуса подключения
    bool get_Auth(bool isAuth,QString l,QString p);  /// Функция запроса данных авторизации из бд
    int get_id(); /// Функция, которая возвращает id пользователя
};

#endif // INTERACTSQL_H
