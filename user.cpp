#include "user.h"
#include "qsqlquery.h"

User::User()   /// Конструктор класса
{
}
User::User(int id)   /// Перегрузка конструктора для того чтобы можно было заполнить данные пользователя заранее
{
    QString q="SELECT * FROM profile WHERE iduser="+QString::number(id); /// строка запроса
    QSqlQuery query(QSqlDatabase::database("shop"));
    if (query.exec(q))  /// проверка выполнения запроса
    {
        while (query.next())   /// цикл заполнения данных пользователей
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
            qDebug()<<id_profile<<id_user<<name<<second_name<<birthday<<email<<control_question<<control_answer<<wallet;
        }
    }
}
void User::SyncData()    /// выгрузка данных из класса в бд
{
    QString q="UPDATE profile SET wallet="+QString::number(wallet)+" WHERE idprofile="+QString::number(id_profile); /// строка обновления данных
    QSqlQuery query(QSqlDatabase::database("shop"));
    if (!query.exec(q))  /// проверка запроса
    {
        qDebug()<<"Синхронизация не выполнена";
    }
}

void User::SetWallet(double d)   /// изменение баланса
{
    wallet=d;
}
int User::GetIdUser()   /// Функция получения id пользователя
{
    return id_user;
}
int User::GetIdProfile()   /// Функция получения id профиля
{
    return id_profile;
}
QString User::GetName()   /// Получение имени пользователя
{
    return name;
}
QString User::GetSecondName()   /// Получение фамилии пользователя
{
    return second_name;
}
QDate User::GetBirthday()  /// получение даты рождения
{
    return birthday;
}
QString User::GetEmail()   /// получение почты
{
    return email;
}
QString User::GetControlQuestion()  /// получение контрольного вопроса
{
    return control_question;
}
QString User::GetControlAnswer()   /// получение ответа на контрольный вопрос
{
    return control_answer;
}

void User::SetName(QString str)
{
    name=str;
}

void User::SetSecondName(QString str)
{
    second_name=str;
}

void User::SetBirthday(QDate str)
{
    birthday=str;
}

void User::SetEmail(QString str)
{
    email=str;
}

void User::SetControlQuestion(QString str)
{
    control_question=str;
}

void User::SetControlAnswer(QString str)
{
    control_answer=str;
}
double User::GetWallet()   /// получение баланса кошелька
{
    return wallet;
}
