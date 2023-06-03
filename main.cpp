#include "mainwindow.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(":/style.css");   /// Указание пути к файлу стилей
    file.open(QFile::ReadOnly);  /// Открытие файла стилей
    a.setStyleSheet(file.readAll()); /// Установка стилей скопированных из файла стилей
    MainWindow w;  /// Запуск главного окна
    return a.exec();
}
