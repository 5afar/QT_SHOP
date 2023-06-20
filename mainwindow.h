
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "auth.h"
#include "interactsql.h"
#include "qboxlayout.h"
#include "user.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QDialog>
#include <QMessageBox>
#include <QScrollArea>
#include <QFileInfo>
#include <QTcpSocket>

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
    User *user; /// ������ ������ User

private slots:

    void on_Exit_Button_clicked();  /// ���� ��������� ������ ������

    void on_Shop_Button_clicked(); /// ���� ��������� ������ ��������

    void on_Library_Button_clicked();   /// ���� ��������� ������ ����������

    void buy_Button();   /// ���� ��������� ������� ������������ ������ ������� ������
    void payment_Button();  /// ���� ��������� ������������ ������ ������ ������
    void download_Button();   /// ���� ��������� ������������ ������ ���������� �� ����������
    void edit_Button();

    void on_Profile_Button_clicked(); /// ��������� ������� ������ �������

public slots:
    void slotReadyRead();

private:
    QHash<QPushButton*,QHBoxLayout*> mButtonToLayoutMap;  /// ��� ����� ��� ����������� ���������� �� ������� �������� �������
    QHash<QPushButton*,QHBoxLayout*> mButtonToLayoutMap2;   /// ��� ����� ��� ����������� ���������� �� ������� �������� ����������
    interactsql sql;   /// ��������� ������ interactsql
    bool isConnected=false;   /// ������ ����������� � ��
    QSqlDatabase db;
    Ui::MainWindow *ui;
    bool isWorked = true;  /// ������ ������ ���������
    Auth a;   /// ������ ������ Auth
    QTcpSocket *socket;
    QByteArray Data;
    quint32 nextBlockSize;
    void SendToServer(QString str);
    QString temp;   /// ��������� ���������� ��� ����������� ������������� �����
    void loadimg(QString str);
    bool loading;


};
#endif // MAINWINDOW_H
