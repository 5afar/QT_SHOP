#ifndef USER_H
#define USER_H

#include "interactsql.h"
#include "qsqldatabase.h"
#include<QDate>
class User: private interactsql /// Класс, который держит всю информацию об авторизованном пользователе
{
public:
    User(); /// Конструктор класса
    User(int id);  /// Перегрузка конструктора для того чтобы можно было заполнить данные пользователя заранее
    int GetIdUser();  /// Функция получения id пользователя
    int GetIdProfile();   /// Функция получения id профиля
    QString GetName();   /// Получение имени пользователя
    QString GetSecondName();   /// Получение фамилии пользователя
    QDate GetBirthday();   /// получение даты рождения
    QString GetEmail();   /// получение почты
    QString GetControlQuestion();   /// получение контрольного вопроса
    QString GetControlAnswer();   /// получение ответа на контрольный вопрос
    void SetName(QString str);   /// Запись имени пользователя
    void SetSecondName(QString str);   /// Запись фамилии пользователя
    void SetBirthday(QDate str);   /// Запись даты рождения
    void SetEmail(QString str);   /// Запись почты
    void SetControlQuestion(QString str);   /// Запись контрольного вопроса
    void SetControlAnswer(QString str);   /// Запись ответа на контрольный вопрос
    double GetWallet();   /// получение баланса кошелька
    void SyncData();  /// выгрузка данных из класса в бд
    void SetWallet(double d);   /// изменение баланса
private:
    int id_user;  /// id пользователя
    int id_profile; /// id профиля
    QString name; /// Имя
    QString second_name;   /// Фамилия
    QDate birthday;   /// дата рождения
    QString email; /// почта
    QString control_question;  /// контрольный вопрос
    QString control_answer; /// ответ на контрольный вопрос
    double wallet;  /// баланс кошелька
};

#endif // USER_H
