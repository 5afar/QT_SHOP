#ifndef INTERACTSQL_H
#define INTERACTSQL_H


#include "qsqldatabase.h"

class interactsql
{
private:
    bool isConnected=false;
    QSqlDatabase db;


public:
    interactsql();
    int userID;
    bool get_isConnected();
    bool get_Auth(bool isAuth,QString l,QString p);
    int get_id();
    QSqlQuery que(QString s);
};

#endif // INTERACTSQL_H
