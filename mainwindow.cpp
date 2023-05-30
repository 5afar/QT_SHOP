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
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("0712");
    db.setDatabaseName("shop");
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
        element->setFixedWidth(720);
        QHBoxLayout* layout = new QHBoxLayout(element);

        QLabel* labelimg = new QLabel();
        labelimg->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
        QPixmap pic = QPixmap(q2.value(0).toString());
        QPixmap scaled = pic.scaled(QSize(640,360));
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

        QString buttonText ="Buy";
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
        element->setFixedWidth(720);
        QHBoxLayout* layout = new QHBoxLayout(element);

        QLabel* labelname = new QLabel();
        labelname->setText(q1.value(0).toString());
        labelname->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
        layout->addWidget(labelname);

        QString buttonText ="Download";
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
    QHBoxLayout* layout=mButtonToLayoutMap.value(button);
    if (layout){
        QLabel *label=qobject_cast<QLabel*>(layout->itemAt(1)->widget());
        if (label){
            QString s=label->text();
            QMessageBox::question(this,"buy","Вы хотите купить "+s+"?");
        }
    }

}

void MainWindow::download_Button()
{
    QPushButton* button=qobject_cast<QPushButton*>(sender());
    QHBoxLayout* layout=mButtonToLayoutMap2.value(button);
    if (layout){
        QLabel *label=qobject_cast<QLabel*>(layout->itemAt(0)->widget());
        if (label){
            QString s=label->text();
            QMessageBox::question(this,"buy","Вы хотите скачать "+s+"?");
        }
    }
}

