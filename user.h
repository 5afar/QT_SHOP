#ifndef USER_H
#define USER_H

#include "interactsql.h"
#include "qsqldatabase.h"
#include<QDate>
class User: private interactsql
{
public:
    User();
    User(int id);
    int GetIdUser();
    int GetIdProfile();
    QString GetName();
    QString GetSecondName();
    QDate GetBirthday();
    QString GetEmail();
    QString GetControlQuestion();
    QString GetControlAnswer();
    double GetWallet();
private:
    int id_user;
    int id_profile;
    QString name;
    QString second_name;
    QDate birthday;
    QString email;
    QString control_question;
    QString control_answer;
    double wallet;
};

#endif // USER_H
