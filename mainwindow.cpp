#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "auth.h"
#include "qlabel.h"
#include "qsqlquery.h"
#include <QDialog>
#include <QMessageBox>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    a.exec();
    if(a.get_isAuth())
    {
        this->setWindowFlag(Qt::FramelessWindowHint);
        this->show();
    }
    else
    {
        this->close();
    }
    User u (a.get_id());
    user=u;
    on_Shop_Button_clicked();
}
MainWindow::~MainWindow()
{
    isWorked = false;
    delete ui;
}
bool MainWindow::get_isWorked()
{
    return (isWorked);
}
void MainWindow::on_Exit_Button_clicked()
{
    QCoreApplication::quit();
    this->close();
}
void MainWindow::on_Shop_Button_clicked()
{

    onRemoveWidget();

    db.open();
    QSqlQuery q1(QSqlDatabase::database("shop"));
    QSqlQuery q2(QSqlDatabase::database("shop"));
    q1.exec("SELECT idcontent, name, price FROM content");

    QWidget *wid=new QWidget;
    QVBoxLayout* lay=new QVBoxLayout(wid);
    QScrollArea *sc = new QScrollArea;
    sc->setWidget(wid);
    sc->setWidgetResizable(true);
    while(q1.next())
    {
        QString idcontent=q1.value(0).toString();
        q2.exec("SELECT link FROM content_img WHERE idcontent='"+idcontent+"'");
        q2.next();
        isFull=true;

        QWidget *element= new QWidget ();
        QHBoxLayout* layout = new QHBoxLayout(element);

        QLabel* labelimg = new QLabel();
        labelimg->setObjectName("image");
        labelimg->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
        QPixmap pic = QPixmap(q2.value(0).toString());
        QPixmap scaled = pic.scaled(720,405,Qt::KeepAspectRatio);
        labelimg->setFixedWidth(720);
        labelimg->setPixmap(scaled);
        layout->addWidget(labelimg);

        QLabel* labelname = new QLabel();
        labelname->setText(q1.value(1).toString());
        labelname->setObjectName("game");
        labelname->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
        layout->addWidget(labelname);

        QLabel* labelprice = new QLabel();
        labelprice->setText(q1.value(2).toString());
        labelprice->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
        layout->addWidget(labelprice);

        QString buttonText ="Купить";
        QPushButton* button = new QPushButton(buttonText,this);
        button->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
        QObject::connect(
                    button, &QPushButton::clicked,
                    this, &MainWindow::buy_Button);
        layout->addWidget(button);
        lay->insertWidget(0,element);
        mButtonToLayoutMap.insert(button,layout);
    }
    ui->widgets_frame1->addWidget(sc);
    lay->addStretch();
    db.close();
}

void MainWindow::onRemoveWidget()
{
///////// SSTEP 1
    QList<QWidget*> children;
    do
    {
        children=ui->widgets_frame1->findChildren<QWidget*>();
        if(children.count()==0)
            break;
        delete children.at(0);
    }
    while(true);
///////////// SSTEP 2
    if(ui->widgets_frame1->layout())
    {
        QLayoutItem* item;
        while((item= ui->widgets_frame1->layout()->takeAt(0))!=nullptr)
            delete item;
    }
}

void MainWindow::on_Library_Button_clicked()
{
    onRemoveWidget();


    db.open();
    QString id=QString::number(a.get_id());
    QSqlQuery q1(QSqlDatabase::database("shop"));
    q1.exec("SELECT name FROM library JOIN content ON library.idcontent=content.idcontent WHERE iduser='"+id+"'");

    QWidget *wid=new QWidget;
    QVBoxLayout* lay=new QVBoxLayout(wid);
    QScrollArea *sc = new QScrollArea;
    sc->setWidget(wid);
    sc->setWidgetResizable(true);
    while(q1.next())
    {
        QWidget *element= new QWidget ();
        QHBoxLayout* layout = new QHBoxLayout(element);

        QLabel* labelname = new QLabel();
        labelname->setText(q1.value(0).toString());
        labelname->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
        layout->addWidget(labelname);

        QString buttonText ="Скачать";
        QPushButton* button = new QPushButton(buttonText,this);
        button->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
        layout->addWidget(button);
        QObject::connect(
                    button, &QPushButton::clicked,
                    this, &MainWindow::download_Button);

        lay->insertWidget(0,element);
        mButtonToLayoutMap2.insert(button,layout);
    }
    ui->widgets_frame1->addWidget(sc);
    lay->addStretch();
    db.close();
}

void MainWindow::buy_Button()
{
    QPushButton* button=qobject_cast<QPushButton*>(sender());
    QHBoxLayout* layou=mButtonToLayoutMap.value(button);
    QMessageBox::StandardButton reply;
    QString s;
    if (layou){
        QLabel *label=qobject_cast<QLabel*>(layou->itemAt(1)->widget());
        if (label){
            s=label->text();
//            reply = QMessageBox::question(this,"buy","Вы хотите купить "+s+"?", QMessageBox::Yes|QMessageBox::No);
        }
    }

    onRemoveWidget();
    db.open();
    QSqlQuery q1(QSqlDatabase::database("shop"));
    QSqlQuery q2(QSqlDatabase::database("shop"));
    q1.exec("SELECT * FROM content WHERE name='"+s+"'");

    QWidget *wid=new QWidget;
    QVBoxLayout* lay=new QVBoxLayout(wid);
    QScrollArea *sc = new QScrollArea;
    sc->setWidget(wid);
    sc->setWidgetResizable(true);
    QString idcontent;
    QWidget *element= new QWidget ();
    QHBoxLayout* layout = new QHBoxLayout(element);
    while(q1.next())
    {
        idcontent=q1.value(0).toString();
        q2.exec("SELECT link FROM content_img WHERE idcontent='"+idcontent+"'");
        while(q2.next())
        {
            QLabel* labelimg = new QLabel();
            labelimg->setObjectName("image");
            labelimg->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
            QPixmap pic = QPixmap(q2.value(0).toString());
            QPixmap scaled = pic.scaled(720,405,Qt::KeepAspectRatio);
            labelimg->setFixedWidth(720);
            labelimg->setPixmap(scaled);
            layout->addWidget(labelimg);
        }
        QLabel* labelname = new QLabel();
        labelname->setText("Название: "+q1.value(1).toString());
        labelname->setObjectName("game");
        labelname->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
        lay->addWidget(labelname);
        temp=(labelname->text());

        QLabel* labelprice = new QLabel();
        labelprice->setText("Цена: "+q1.value(2).toString()+"руб.");
        labelprice->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
        lay->addWidget(labelprice);

        QLabel* labelwallet = new QLabel();
        labelwallet->setText("Ваш баланс: "+QString::number(user.GetWallet())+"руб.");
        labelwallet->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
        lay->addWidget(labelwallet);

        QString buttonText ="Оплатить";
        QPushButton* button = new QPushButton(buttonText,this);
        button->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
        lay->addWidget(button);
        QObject::connect(button,&QPushButton::clicked, this, &MainWindow::payment_Button);
    }

    lay->addWidget(element);
    ui->widgets_frame1->addWidget(sc);
    lay->addStretch();
    db.close();

}

void MainWindow::payment_Button()
{

        QMessageBox::information(this,"q",temp);
//    db.open();
//    QSqlQuery q1(QSqlDatabase::database("shop"));
//    q1.exec("SELECT price FROM content WHERE name='"+s+"'");
//    q1.next();
//    double price=q1.value(0).toDouble();
//    user.SetWallet(user.GetWallet()-price);

}
void MainWindow::download_Button()
{
    onRemoveWidget();
//    QPushButton* button=qobject_cast<QPushButton*>(sender());
//    QHBoxLayout* layout=mButtonToLayoutMap2.value(button);
//    if (layout){
//        QLabel *label=qobject_cast<QLabel*>(layout->itemAt(0)->widget());
//        if (label){
//            QString s=label->text();
//            QMessageBox::question(this,"buy","Вы хотите скачать "+s+"?");
//        }
//    }
}


void MainWindow::on_Profile_Button_clicked()
{

    onRemoveWidget();
    QWidget *wid=new QWidget;
    QVBoxLayout* lay=new QVBoxLayout(wid);
    QScrollArea *sc = new QScrollArea;
    sc->setWidget(wid);
    sc->setWidgetResizable(true);

    QWidget *element= new QWidget ();
    QVBoxLayout* layout = new QVBoxLayout(element);

    QLabel* labelname = new QLabel();
    labelname->setText(user.GetName());
    labelname->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
    layout->addWidget(labelname);

    QLabel* label_second_name = new QLabel();
    label_second_name->setText(user.GetSecondName());
    label_second_name->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
    layout->addWidget(label_second_name);

    QLabel* label_Date = new QLabel();
    label_Date->setText(user.GetBirthday().toString());
    label_Date->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
    layout->addWidget(label_Date);

    QLabel* label_email = new QLabel();
    label_email->setText(user.GetEmail());
    label_email->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
    layout->addWidget(label_email);

    QLabel* labelCQ = new QLabel();
    labelCQ->setText(user.GetControlQuestion());
    labelCQ->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
    layout->addWidget(labelCQ);

    QLabel* labelAN = new QLabel();
    labelAN->setText(user.GetControlAnswer());
    labelAN->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
    layout->addWidget(labelAN);

    QLabel* label_wallet = new QLabel();
    label_wallet->setText(QString::number(user.GetWallet()));
    label_wallet->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
    layout->addWidget(label_wallet);

    int index = lay->count();
    lay->insertWidget(index,element);
    ui->widgets_frame1->addWidget(sc);
    lay->addStretch();


}

