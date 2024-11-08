#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Client  client;
    //client.sendHouseRequest();
}

MainWindow::~MainWindow()
{
    delete ui;
}
