#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setFixedSize(700, 700);

    // background
    this->setStyleSheet("background-image:url(/Users/martinkubicka/Documents/ICP/PacMan/images/background.jpg)");

    // choose map label
    QLabel *label = new QLabel("Choose map", this);
    label->setGeometry(280, 250, 135, 20);

    QFont labelFont("Arial Black", 20);
    label->setFont(labelFont);

    label->setStyleSheet("color:white;");

    // combobox
    QComboBox *comboBox = new QComboBox(this);

    comboBox->addItem("PacMan's Playground");
    comboBox->addItem("Ghostly Maze");
    comboBox->addItem("Endless Journey");

    QFont comboBoxFont("Arial Black", 13);
    comboBox->setFont(comboBoxFont);

    QIcon icon("/Users/martinkubicka/Documents/ICP/PacMan/images/drop_down_icon.png");

    comboBox->setStyleSheet("QComboBox{background-color: rgb(27,27,27); border: 1px solid white; border-radius: 3px; color: white;} QComboBox::drop-down {border:none; image: url(/Users/martinkubicka/Documents/ICP/PacMan/images/drop_down_icon.png); padding-top: 3px; padding-right: 5px;}");
    comboBox->setGeometry(250, 290, 200, 30);

    // combobox dropdown menu
    QListView* dropdownMenu = qobject_cast<QListView*>(comboBox->view());
    dropdownMenu->setStyleSheet("QListView { background-color: black; padding-left: 5px;}");
    dropdownMenu->setMinimumWidth(212);

    connect(comboBox, SIGNAL(activated(const QString &)), this, SLOT(setMap(const QString &)));

    // start button
    QPushButton *startButton = new QPushButton("Start", this);
    startButton->setGeometry(290, 340, 120, 30);
    startButton->setStyleSheet("QPushButton{color:white; border: 1px solid white; border-radius: 3px; padding-bottom: 3px;}  QPushButton:pressed{border: 1px solid gray;}");
    QFont startButtonFont("Arial Black", 16);
    startButton->setFont(startButtonFont);

    connect(startButton, &QPushButton::clicked, this, &MainWindow::start);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setMap(const QString &mapName) {
    if (mapName == "PacMan's Playground") {
        this->map = "map01.txt";
    } else if (mapName == "Ghostly Maze") {
        this->map = "map02.txt";
    } else if (mapName == "Endless Journey") {
        this->map = "map03.txt";
    }
}

void MainWindow::start() {
    std::cout << this->map << std::endl; //todo
}


// TODO CHANGE PATHS
//  todo comments
