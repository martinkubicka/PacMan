/**
 * @file mainwindow.cpp
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Definitions of functions declared in MainWindow class.
 */

#include "mainwindow.h"

void MainWindow::createUi() {
    // set background image
    QString backgroundPath = "background-image:url(%1%2)";
    this->setStyleSheet(backgroundPath.arg(this->srcPath, "/images/background.jpg"));

    // create objects
    this->createChooseMapLabel();
    this->createComboBox();
    this->createStartButton();
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setFixedSize(HEIGHT, WIDTH); // set size + cannot resize
    this->findImageDirPath();

    this->map = this->srcPath.toStdString() + "/maps/map01.txt"; // selected map by default

    this->createUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::findImageDirPath() {
    QString searchDir = "/images/";
    QString currentPath = QDir::currentPath();
    QDir dir(currentPath);

    while (!dir.isRoot()) {
        QString absolutePath = dir.absolutePath() + searchDir;
        if (QDir(absolutePath).exists()) {
            this->srcPath = dir.absolutePath();
            break;
        }
        dir.cdUp();
    }
}

void MainWindow::createChooseMapLabel() {
    QLabel *label = new QLabel("Choose map", this);
    label->setGeometry(280, 250, 135, 20);

    QFont labelFont("Arial Black", 20);
    label->setFont(labelFont);

    label->setStyleSheet("color:white;");

    label->show();
}

void MainWindow::createComboBox() {
    QComboBox *comboBox = new QComboBox(this);

    comboBox->addItem("PacMan's Playground");
    comboBox->addItem("Ghostly Maze");
    comboBox->addItem("Endless Journey");

    QFont comboBoxFont("Arial Black", 13);
    comboBox->setFont(comboBoxFont);

    QIcon icon(this->srcPath + "/images/drop_down_icon.png");

    comboBox->setStyleSheet("QComboBox{background-color: rgb(27,27,27); border: 1px solid white; border-radius: 3px; color: white;} QComboBox::drop-down {border:none; image: url(/Users/martinkubicka/Documents/ICP/PacMan/images/drop_down_icon.png); padding-top: 3px; padding-right: 5px;}");
    comboBox->setGeometry(250, 290, 200, 30);

    comboBox->show();

    // combobox dropdown menu
    QListView* dropdownMenu = qobject_cast<QListView*>(comboBox->view());
    dropdownMenu->setStyleSheet("QListView { background-color: black; padding-left: 5px;}");
    dropdownMenu->setMinimumWidth(212);

    connect(comboBox, SIGNAL(activated(const QString &)), this, SLOT(setMap(const QString &)));
}

void MainWindow::createStartButton() {
    QPushButton *startButton = new QPushButton("Start", this);
    startButton->setGeometry(290, 340, 120, 30);
    startButton->setStyleSheet("QPushButton{color:white; border: 1px solid white; border-radius: 3px; padding-bottom: 3px;}  QPushButton:pressed{border: 1px solid gray;}");
    
    QFont startButtonFont("Arial Black", 16);
    startButton->setFont(startButtonFont);

    startButton->show();

    connect(startButton, &QPushButton::clicked, this, &MainWindow::start);
}

void MainWindow::setMap(const QString &mapName) {
    if (mapName == "PacMan's Playground") {
        this->map = this->srcPath.toStdString() + "/maps/map01.txt";
    } else if (mapName == "Ghostly Maze") {
        this->map = this->srcPath.toStdString() + "/maps/map02.txt";
    } else if (mapName == "Endless Journey") {
        this->map = this->srcPath.toStdString() + "/maps/map03.txt";
    }
}

void MainWindow::start() {
    // remove all object from UI
    foreach (QObject* child, this->children()) {
        QWidget* childWidget = qobject_cast<QWidget*>(child);
        if (childWidget) {
            childWidget->deleteLater();
        }
    }

    // create map UI
    this->mapObject = new Map(this, this->map, this->srcPath);
    setCentralWidget(this->mapObject);

    this->mapObject->Start();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
        qDebug() << "Key pressed!"; // TODO na vsetky ostatne keys to reaguje po vykliknuti
    // Handle the key press event
    switch (event->key()) {
    case Qt::Key_W:
        this->mapObject->pacman->setNextDirection(Direction::UP);
        break;
    case Qt::Key_S:
        this->mapObject->pacman->setNextDirection(Direction::DOWN);
        break;
    case Qt::Key_A:
        this->mapObject->pacman->setNextDirection(Direction::LEFT);
        break;
    case Qt::Key_D:
        this->mapObject->pacman->setNextDirection (Direction::RIGHT);
        break;
    default:
        break;
    }
}

/*** End of mainwidow.cpp ***/
