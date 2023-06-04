#ifndef USER_H
#define USER_H

#include "interactsql.h"
#include "qsqldatabase.h"
#include<QDate>
class User: private interactsql ///  ласс, который держит всю информацию об авторизованном пользователе
{
public:
    User(); ///  онструктор класса
    User(int id);  /// ѕерегрузка конструктора дл€ того чтобы можно было заполнить данные пользовател€ заранее
    int GetIdUser();  /// ‘ункци€ получени€ id пользовател€
    int GetIdProfile();   /// ‘ункци€ получени€ id профил€
    QString GetName();   /// ѕолучение имени пользовател€
    QString GetSecondName();   /// ѕолучение фамилии пользовател€
    QDate GetBirthday();   /// получение даты рождени€
    QString GetEmail();   /// получение почты
    QString GetControlQuestion();   /// получение контрольного вопроса
    QString GetControlAnswer();   /// получение ответа на контрольный вопрос
    double GetWallet();   /// получение баланса кошелька
    void SyncData();  /// выгрузка данных из класса в бд
    void SetWallet(double d);   /// изменение баланса
private:
    int id_user;  /// id пользовател€
    int id_profile; /// id профил€
    QString name; /// »м€
    QString second_name;   /// ‘амили€
    QDate birthday;   /// дата рождени€
    QString email; /// почта
    QString control_question;  /// контрольный вопрос
    QString control_answer; /// ответ на контрольный вопрос
    double wallet;  /// баланс кошелька
};

#endif // USER_H
