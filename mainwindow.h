
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "auth.h"
#include "interactsql.h"
#include "qboxlayout.h"
#include "user.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow  /// ����� �������� ����
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool get_isWorked();  ///������� ��������� ������� ����������
    void onRemoveWidget(); /// ������� �������� ��������

private slots:

    void on_Exit_Button_clicked();  /// ���� ��������� ������ ������

    void on_Shop_Button_clicked(); /// ���� ��������� ������ ��������

    void on_Library_Button_clicked();   /// ���� ��������� ������ ����������

    void buy_Button();   /// ���� ��������� ������� ������������ ������ ������� ������
    void payment_Button();  /// ���� ��������� ������������ ������ ������ ������
    void download_Button();   /// ���� ��������� ������������ ������ ���������� �� ����������

    void on_Profile_Button_clicked(); /// ��������� ������� ������ �������

private:
    QHash<QPushButton*,QHBoxLayout*> mButtonToLayoutMap;  /// ��� ����� ��� ����������� ���������� �� ������� �������� �������
    QHash<QPushButton*,QHBoxLayout*> mButtonToLayoutMap2;   /// ��� ����� ��� ����������� ���������� �� ������� �������� ����������
    interactsql sql;   /// ��������� ������ interactsql
    bool isConnected=false;   /// ������ ����������� � ��
    QSqlDatabase db;
    Ui::MainWindow *ui;
    bool isWorked = true;  /// ������ ������ ���������
    Auth a;   /// ������ ������ Auth
    User *user; /// ������ ������ User
    QString temp;   /// ��������� ���������� ��� ����������� ������������� �����


};
#endif // MAINWINDOW_H
