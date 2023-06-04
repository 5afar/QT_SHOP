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
    a.exec(); /// Запуск окна авторизации
    if(a.get_isAuth()) /// проверка авторизации
    {
        this->setWindowFlag(Qt::FramelessWindowHint);
        this->show(); /// Запуск главного окна
    }
    else
    {
        this->close();
        QCoreApplication::quit();
        isWorked=false;
    }


//    User u (a.get_id()); /// Запрос данных пользователя с определенным id
    user= new User(a.get_id());
    on_Shop_Button_clicked();  /// Прогрузка страницы магазина в главном окне
}
MainWindow::~MainWindow()
{
    isWorked = false;
    delete ui;
}
bool MainWindow::get_isWorked()   /// Статус работы программы
{
    return (isWorked);
}
void MainWindow::on_Exit_Button_clicked()  /// Обработка кнопки выхода из программы
{
    QCoreApplication::quit();   /// Завершение программы
    this->close();
}
void MainWindow::on_Shop_Button_clicked()   /// Обработка кнопки магазин
{
    onRemoveWidget();  /// Чистка виджетов
    db.open();  /// Открытие подключения (ВОзможно не нужно уже)!!!
    QSqlQuery q1(QSqlDatabase::database("shop"));  /// Создание двух переменных для разных запросов
    QSqlQuery q2(QSqlDatabase::database("shop"));
    q1.exec("SELECT idcontent, name, price FROM content"); /// Первый запрос в базу данных

    QWidget *wid=new QWidget;   /// Создание динамического виджета
    QVBoxLayout* lay=new QVBoxLayout(wid);  /// Динамический слой наследующийся от виджета
    QScrollArea *sc = new QScrollArea;  /// Создание области прокрутки
    sc->setWidget(wid); /// Установка зоны прокрутки внутри виджета
    sc->setWidgetResizable(true);
    while(q1.next()) /// Обработка строк первого запроса бд
    {
        QString idcontent=q1.value(0).toString(); 
        q2.exec("SELECT link FROM content_img WHERE idcontent='"+idcontent+"'"); /// Второй запрос в бд
        q2.next();

        QWidget *element= new QWidget (); /// Динамический виджет, который содержит в себе информацию об одном товаре
        QHBoxLayout* layout = new QHBoxLayout(element);  /// слой с горизонтальным выравниванием внутри виджета

        QLabel* labelimg = new QLabel();  /// Метка с встроенной картинкой
        labelimg->setObjectName("image");
        labelimg->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
        QPixmap pic = QPixmap(q2.value(0).toString()); /// Загрузка картинки по адресу на компьютере, который записан в бд
        QPixmap scaled = pic.scaled(720,405,Qt::KeepAspectRatio); /// Установлене размеров изображения
        labelimg->setFixedWidth(720);
        labelimg->setPixmap(scaled); 
        layout->addWidget(labelimg); /// Добавления виджета в слой

        QLabel* labelname = new QLabel(); /// Текстовая метка
        labelname->setText(q1.value(1).toString());
        labelname->setObjectName("game");
        labelname->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
        layout->addWidget(labelname);

        QLabel* labelprice = new QLabel();   /// Текстовая метка
        labelprice->setText(q1.value(2).toString());
        labelprice->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
        layout->addWidget(labelprice);

        QString buttonText ="Купить";
        QPushButton* button = new QPushButton(buttonText,this);
        button->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
        QObject::connect(                               /// Обработка нажатий динамической кнопки
                    button, &QPushButton::clicked,
                    this, &MainWindow::buy_Button);
        layout->addWidget(button);
        lay->insertWidget(0,element);
        mButtonToLayoutMap.insert(button,layout);   /// Добавление записи в карту
    }
    ui->widgets_frame1->addWidget(sc); /// Добавление общего виджета на экран
    lay->addStretch();
    db.close(); /// Закрытие бд ВОЗМОЖНО НЕ НУЖНО !!!!
}

void MainWindow::onRemoveWidget()   /// Функция удаления виджетов 
{
///////// SSTEP 1
    QList<QWidget*> children;  /// лист указателей на дочерние виджеты
    do
    {
        children=ui->widgets_frame1->findChildren<QWidget*>(); /// поиск дочерних виджетов
        if(children.count()==0) /// проверка наличия виджетов
            break;
        delete children.at(0);  /// удаления дочернего виджета
    }
    while(true);
///////////// SSTEP 2
    if(ui->widgets_frame1->layout()) /// Проверка наличия слоев
    {
        QLayoutItem* item;  /// Экземляр объекта слоя
        while((item= ui->widgets_frame1->layout()->takeAt(0))!=nullptr) /// Пока присутствуют объекты происходит их удаление
            delete item;
    }
}

void MainWindow::on_Library_Button_clicked()   /// Обработка нажатий на кнопку библиотека
{
    onRemoveWidget();
    db.open();
    QString id=QString::number(a.get_id());
    QSqlQuery q1(QSqlDatabase::database("shop"));
    q1.exec("SELECT name FROM library JOIN content ON library.idcontent=content.idcontent WHERE iduser='"+id+"'"); /// Запрос к бд

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

void MainWindow::buy_Button()   /// Обработка нажатий на кнопку покупки товара
{
    QPushButton* button=qobject_cast<QPushButton*>(sender()); /// Отлавливание указателя на кнопку, которая отправила сигнал
    QHBoxLayout* layou=mButtonToLayoutMap.value(button);   /// поиск в карте слоя, которому принадлежит эта кнопка
    QString s;
    if (layou){   /// Проверка наличия слоя
        QLabel *label=qobject_cast<QLabel*>(layou->itemAt(1)->widget()); /// Получение виджета из слоя с названием товара
        if (label){
            s=label->text(); /// Сохранение названия товара
        }
    }
    temp=s;  /// Перенос во внешнюю переменную
    onRemoveWidget(); /// Чистка виджетов
    db.open();
    QSqlQuery q1(QSqlDatabase::database("shop"));
    QSqlQuery q2(QSqlDatabase::database("shop"));
    q1.exec("SELECT * FROM content WHERE name='"+s+"'"); /// Строка запроса

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
        q2.exec("SELECT link FROM content_img WHERE idcontent='"+idcontent+"'"); /// Строка запроса картинок из бд
        while(q2.next())  /// Цикл вывода изображение на экран
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


        QLabel* labelprice = new QLabel();
        labelprice->setText("Цена: "+q1.value(2).toString()+"руб.");
        labelprice->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
        lay->addWidget(labelprice);

        QLabel* labelwallet = new QLabel();
        labelwallet->setText("Ваш баланс: "+QString::number(user->GetWallet())+"руб.");
        labelwallet->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
        lay->addWidget(labelwallet);

        QString buttonText ="Оплатить";
        QPushButton* button = new QPushButton(buttonText,this);
        button->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
        lay->addWidget(button);
        QObject::connect(button,&QPushButton::clicked, this, &MainWindow::payment_Button); /// Сигнал нажатия кнопки оплаты
    }
    lay->addWidget(element);
    ui->widgets_frame1->addWidget(sc);
    lay->addStretch();
    db.close();
}
void MainWindow::payment_Button()  /// Обработка нажатий кнопки оплаты
{
    QSqlQuery q(QSqlDatabase::database("shop"));
    q.exec("SELECT idcontent FROM content WHERE name='"+temp+"'"); /// Получение id товара из бд по названию
    q.next();
    QString idcontent=q.value(0).toString();
    QString iduser=QString::number(user->GetIdUser()); /// Получение id пользователя
    QSqlQuery q1(QSqlDatabase::database("shop"));
    q1.exec("SELECT * FROM library WHERE idcontent="+idcontent+" AND iduser="+iduser); /// Проверка наличия товара в бибилотеке пользователя
    q1.next();
    qDebug()<<q1.lastQuery();
    QString check=q1.value(0).toString(); /// Присваивание записи к строке
    if(check.isEmpty()) /// Проверка наличия
    {
        QMessageBox::information(this,check,"Вы купили это");
        QSqlQuery q2(QSqlDatabase::database("shop"));
        q2.exec("SELECT price FROM content WHERE name='"+temp+"'");
        q2.next();
        double price=q2.value(0).toDouble();
        if(price<user->GetWallet()) /// Проверка того, хватает ли пользователю средств на балансе для бриобретения
        {
            QSqlQuery q3(QSqlDatabase::database("shop"));
            user->SetWallet(user->GetWallet()-price);
            q3.exec("INSERT INTO library (iduser,idcontent)VALUES('"+QString::number(user->GetIdUser())+"','"+idcontent+"')");/// Добавление записи в базу данных
            qDebug()<<q3.lastQuery();
            q3.next();
        }
        else
        {
            QMessageBox::warning(this,"Wallet","Недостаточно средств!");
        }
    }
    else
    {
        QMessageBox::information(this,"Product","У вас уже есть это");
    }
    user->SyncData(); /// Обновление данных пользователя
}
void MainWindow::download_Button()  /// Обработка нажатий на кнопку скачать
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
void MainWindow::on_Profile_Button_clicked() /// Обработка нажатий на кнопку профиль
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
    labelname->setText(user->GetName());
    labelname->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
    layout->addWidget(labelname);

    QLabel* label_second_name = new QLabel();
    label_second_name->setText(user->GetSecondName());
    label_second_name->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
    layout->addWidget(label_second_name);

    QLabel* label_Date = new QLabel();
    label_Date->setText(user->GetBirthday().toString());
    label_Date->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
    layout->addWidget(label_Date);

    QLabel* label_email = new QLabel();
    label_email->setText(user->GetEmail());
    label_email->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
    layout->addWidget(label_email);

    QLabel* labelCQ = new QLabel();
    labelCQ->setText(user->GetControlQuestion());
    labelCQ->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
    layout->addWidget(labelCQ);

    QLabel* labelAN = new QLabel();
    labelAN->setText(user->GetControlAnswer());
    labelAN->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
    layout->addWidget(labelAN);

    QLabel* label_wallet = new QLabel();
    label_wallet->setText(QString::number(user->GetWallet()));
    label_wallet->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);
    layout->addWidget(label_wallet);

    int index = lay->count();
    lay->insertWidget(index,element);
    ui->widgets_frame1->addWidget(sc);
    lay->addStretch();
}

