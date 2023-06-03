#include "interactsql.h"
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>


interactsql::interactsql()
{ /*
  Строки подключения к базе данных
  1. Выбор драйвера
  2. Установки имени хоста
  3. Установка имени пользователя бд
  4. Установка пароля
  5. Выбор бд, к которой происходит подключение
  */
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("0712");
    db.setDatabaseName("shop");
    if(db.open())  /// Проверка подключение к бд
    {
        isConnected=true;
    }
    else
    {
        isConnected=false;
    }
}

bool interactsql::get_isConnected()  /// Функция проверки статуса подключения
{
    return isConnected ;
}
bool interactsql::get_Auth(bool isAuth,QString l,QString p) /// Функция запроса данных авторизации из бд
{
    QSqlQuery q(QSqlDatabase::database("shop"));  /// Переменная запросов

    if (q.exec("SELECT iduser, login, password FROM user WHERE login='"+l+"' AND password='"+p+"'")) /// Создание и выполнение запроса к бд
    {
        QString login;
        QString password;
        while (q.next())  /// Ставит указатель на следующую строку возвращаемую из бд
        {
            userID=q.value(0).toInt(); /// Получение id пользователя
            login = q.value(1).toString();  /// Получение логина
            password = q.value(2).toString(); /// Получение пароля
            qDebug()<<login<<password; /// Вывод в консоль полученных данных
        }
        if(login==l and password==p and !l.isEmpty()) /// Условие проверяющее соответствие введенных данных и полученных из бд, а также проверка пустого поля
        {
            isAuth=true;
        }
        else
        {
            isAuth=false;
        }
    }
    else
    {
        isAuth=false;
    }
    return isAuth;
}

int interactsql::get_id()  /// Функция, которая возвращает id пользователя
{
    return userID;
}


