#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.10.3");
    db.setDatabaseName("mydb");
    db.setUserName("root");
    //db.setPort(22);
    //db.setPort(3306);
    db.setPassword("СЮДА ПАРОЛЬ!!!!");
    if (!db.open()){
        qDebug() << db.lastError().text(); //дебажим в консоли
        ui->label->setText(db.lastError().text()); //вывод ошибки в лейбл
        return;
    }
    else{
        qDebug() << "Connect";
        ui->label->setText("Соединение установлено!");
    }

    model = new QSqlRelationalTableModel(this, db);
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setTable("Certificate");
    //model->setRelation(model->fieldIndex("Pasport_woman_Номер"),QSqlRelation("Pasport_woman","Номер","Номер"));
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    model->submitAll();
}

void MainWindow::on_pushButton_2_clicked()
{
    model->revertAll();
}

void MainWindow::on_pushButton_3_clicked()
{
    model->select();
}

void MainWindow::on_pushButton_4_clicked()
{
    qDebug() << "Добавили строку" << model->insertRow(model->rowCount());
}

void MainWindow::on_pushButton_5_clicked()
{
    int selectedRow = ui->tableView->currentIndex().row();
    if (selectedRow >= 0){
        qDebug() << "Удаление строки:" << model->removeRow(selectedRow);
    }
    else
    {
        qDebug() << "Не могу удалить!";
    }
}
