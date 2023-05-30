#ifndef AUTH_H
#define AUTH_H

#include "interactsql.h"
#include <QDialog>

namespace Ui {
class Auth;
}

class Auth : public QDialog
{
    Q_OBJECT

public:
    explicit Auth(QDialog *parent = nullptr);
    ~Auth();
    bool get_isAuth();
    int get_id();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    interactsql sql;
    Ui::Auth *ui;
    bool isAuth=false;
    int id;
};

#endif // AUTH_H
