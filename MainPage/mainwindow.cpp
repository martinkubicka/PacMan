#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(700, 700);
    // TODO CHANGE PATH
    this->setStyleSheet("background-image:url(\"/Users/martinkubicka/Documents/ICP/PacMan/images/background.jpg\")");

}

MainWindow::~MainWindow()
{
    delete ui;
}
