
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

class MainWindow : public QMainWindow  /// Класс главного окна
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool get_isWorked();  ///Функция получения статуса приложения
    void onRemoveWidget(); /// Функция удаления виджетов

private slots:

    void on_Exit_Button_clicked();  /// Слот обработки кнопки выхода

    void on_Shop_Button_clicked(); /// Слот обработки кнопки магазина

    void on_Library_Button_clicked();   /// Слот обработки кнопки библиотеки

    void buy_Button();   /// Слот обработки нажатия динамической кнопки покупки товара
    void payment_Button();  /// Слот обработки динамической кнопки оплаты товара
    void download_Button();   /// Слот обработки динамической кнопки скачивания из библиотеки

    void on_Profile_Button_clicked(); /// Обработка нажатия кнопки профиля

private:
    QHash<QPushButton*,QHBoxLayout*> mButtonToLayoutMap;  /// хеш карта для запоминания указателей на виджеты страницы покупки
    QHash<QPushButton*,QHBoxLayout*> mButtonToLayoutMap2;   /// хеш карта для запоминания указателей на виджеты страницы библиотеки
    interactsql sql;   /// Экземпляр класса interactsql
    bool isConnected=false;   /// статус подключения к бд
    QSqlDatabase db;
    Ui::MainWindow *ui;
    bool isWorked = true;  /// статус работы программы
    Auth a;   /// Объект класса Auth
    User *user; /// Объект класса User
    QString temp;   /// Строковая переменная для запоминания промежуточных строк


};
#endif // MAINWINDOW_H
