#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "auth.h"
#include "interactsql.h"
#include "qboxlayout.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool get_isWorked();
    void onAddWidget();
    void onRemoveWidget();

private slots:

    void on_Exit_Button_clicked();

    void on_Shop_Button_clicked();

    void on_Library_Button_clicked();

    void buy_Button();

    void download_Button();

private:
    QHash<QPushButton*,QHBoxLayout*> mButtonToLayoutMap;
    interactsql sql;
    bool isConnected=false;
    QSqlDatabase db;
    Ui::MainWindow *ui;
    bool isWorked = true;
    bool isFull=false;
    Auth a;



};
#endif // MAINWINDOW_H
