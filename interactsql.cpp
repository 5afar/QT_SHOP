#include "interactsql.h"
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>

interactsql::interactsql()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("0712");
    db.setDatabaseName("shop");
    if(db.open())
    {
        isConnected=true;
        qDebug()<<isConnected;
    }
    else
    {
        isConnected=false;
        qDebug()<<isConnected;
    }
}
interactsql::~interactsql()
{
}
bool interactsql::get_isConnected()
{
    return isConnected ;
}
bool interactsql::get_Auth(bool isAuth,QString l,QString p)
{
    db.open();
    QSqlQuery q(QSqlDatabase::database("shop"));

    if (q.exec("SELECT iduser, login, password FROM user WHERE login='"+l+"' AND password='"+p+"'"))
    {
        QString login;
        QString password;
        while (q.next())
        {
            userID=q.value(0).toInt();
            login = q.value(1).toString();
            password = q.value(2).toString();
            qDebug()<<login<<password;
        }
        if (login.isEmpty() or password.isEmpty())
        {
            isAuth=false;
        }
        else if(login==l and password==p)
        {
            isAuth=true;
        }
    }
    else
    {
        isAuth=false;
    }
    return isAuth;
}

int interactsql::get_id()
{
    return userID;
}


