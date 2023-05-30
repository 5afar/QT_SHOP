#include "user.h"
#include "qsqlquery.h"

User::User()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("0712");
    db.setDatabaseName("shop");
}
User::User(int id)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("0712");
    db.setDatabaseName("shop");
    if (db.open())
    {
        QString q="SELECT * FROM profile WHERE iduser="+QString::number(id);
        QSqlQuery query(QSqlDatabase::database("shop"));
        if (query.exec(q))
        {
            while (query.next())
            {
                id_profile=query.value(0).toInt();
                id_user=query.value(1).toInt();
                name=query.value(2).toString();
                second_name=query.value(3).toString();
                birthday=query.value(4).toDate();
                email=query.value(5).toString();
                control_question=query.value(6).toString();
                control_answer=query.value(7).toString();
                wallet=query.value(8).toDouble();
            }
        }
        db.close();
    }

}

int User::GetIdUser()
{
    return id_user;
}
int User::GetIdProfile()
{
    return id_profile;
}
QString User::GetName()
{
    return name;
}
QString User::GetSecondName()
{
    return second_name;
}
QDate User::GetBirthday()
{
    return birthday;
}
QString User::GetEmail()
{
    return email;
}
QString User::GetControlQuestion()
{
    return control_question;
}
QString User::GetControlAnswer()
{
    return control_answer;
}
double User::GetWallet()
{
    return wallet;
}
