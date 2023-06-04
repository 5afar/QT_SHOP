#ifndef USER_H
#define USER_H

#include "interactsql.h"
#include "qsqldatabase.h"
#include<QDate>
class User: private interactsql /// �����, ������� ������ ��� ���������� �� �������������� ������������
{
public:
    User(); /// ����������� ������
    User(int id);  /// ���������� ������������ ��� ���� ����� ����� ���� ��������� ������ ������������ �������
    int GetIdUser();  /// ������� ��������� id ������������
    int GetIdProfile();   /// ������� ��������� id �������
    QString GetName();   /// ��������� ����� ������������
    QString GetSecondName();   /// ��������� ������� ������������
    QDate GetBirthday();   /// ��������� ���� ��������
    QString GetEmail();   /// ��������� �����
    QString GetControlQuestion();   /// ��������� ������������ �������
    QString GetControlAnswer();   /// ��������� ������ �� ����������� ������
    double GetWallet();   /// ��������� ������� ��������
    void SyncData();  /// �������� ������ �� ������ � ��
    void SetWallet(double d);   /// ��������� �������
private:
    int id_user;  /// id ������������
    int id_profile; /// id �������
    QString name; /// ���
    QString second_name;   /// �������
    QDate birthday;   /// ���� ��������
    QString email; /// �����
    QString control_question;  /// ����������� ������
    QString control_answer; /// ����� �� ����������� ������
    double wallet;  /// ������ ��������
};

#endif // USER_H
