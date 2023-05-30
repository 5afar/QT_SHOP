#ifndef USER_H
#define USER_H


#include "interactsql.h"
class user
{
public:
    user();
private:
    interactsql sql;
    QSqlDatabase db;
};

#endif // USER_H
