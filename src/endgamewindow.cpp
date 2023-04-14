#include "endgamewindow.h"
#include "mainwindow.h"

void EndGameWindow::deleteAll(MainWindow *mainwindow) {
    foreach (QObject* child, mainwindow->children()) {
        QWidget* childWidget = qobject_cast<QWidget*>(child);
        if (childWidget) {
            childWidget->deleteLater();
        }
    }
}

void EndGameWindow::backToMenu(MainWindow *mainwindow) {
    this->deleteAll(mainwindow);
    mainwindow->createUi();
}

void EndGameWindow::playAgain(MainWindow *mainwindow) {
    this->deleteAll(mainwindow);
    mainwindow->start();
}

EndGameWindow::EndGameWindow(MainWindow *mainwindow, endGameType type)
{
    // you win label
    QLabel *label;
    if (type == WIN) {
        QString backgroundPath = "background-image:url(%1%2)";
        mainwindow->setStyleSheet(backgroundPath.arg(mainwindow->srcPath, "/images/win.png"));
        label = new QLabel("You win!", mainwindow);
        label->setGeometry(250, 100, 250, 50);
    } else {
        QString backgroundPath = "background-image:url(%1%2)";
        mainwindow->setStyleSheet(backgroundPath.arg(mainwindow->srcPath, "/images/gameover.png"));
        label = new QLabel("Game over!", mainwindow);
        label->setGeometry(230, 100, 250, 50);
    }

    QFont labelFont("Arial Black", 40);
    label->setFont(labelFont);
    label->setStyleSheet("color:white;");
    label->show();

    // play again button
    QPushButton *playAgainButton = new QPushButton("Play again", mainwindow);
    playAgainButton->setGeometry(290, 530, 120, 30);
    playAgainButton->setStyleSheet("QPushButton{color:white; border: 1px solid white; border-radius: 3px; padding-bottom: 3px;}  QPushButton:pressed{border: 1px solid gray;}");

    QFont playAgainFont("Arial Black", 16);
    playAgainButton->setFont(playAgainFont);

    playAgainButton->show();

    QObject::connect(playAgainButton, &QPushButton::clicked, [=]() {
        this->playAgain(mainwindow);
    });

    // back to menu button
    QPushButton *backToMenuButton = new QPushButton("Back to menu", mainwindow);
    backToMenuButton->setGeometry(280, 580, 140, 30);
    backToMenuButton->setStyleSheet("QPushButton{color:white; border: 1px solid white; border-radius: 3px; padding-bottom: 3px;}  QPushButton:pressed{border: 1px solid gray;}");

    backToMenuButton->setFont(playAgainFont);

    backToMenuButton->show();

    QObject::connect(backToMenuButton, &QPushButton::clicked, [=]() {
        this->backToMenu(mainwindow);
    });

    // replay game button
    QPushButton *replayButton = new QPushButton("Replay game", mainwindow);
    replayButton->setGeometry(280, 620, 140, 30);
    replayButton->setStyleSheet("QPushButton{color:white; border: 1px solid white; border-radius: 3px; padding-bottom: 3px;}  QPushButton:pressed{border: 1px solid gray;}");

    replayButton->setFont(playAgainFont);

    replayButton->show();

    QObject::connect(replayButton, &QPushButton::clicked, [=]() {
        mainwindow->replay();
    });
}
