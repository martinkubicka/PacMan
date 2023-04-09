#ifndef WINWINDOW_H
#define WINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QtDebug>
#include <QPushButton>
#include <QApplication>

class MainWindow;

enum endGameType {
    WIN,
    GAMEOVER
};

class EndGameWindow : public QObject {
    Q_OBJECT
public:
    EndGameWindow(MainWindow *mainwindow, endGameType type);
private:
    void deleteAll(MainWindow *mainwindow);
private slots:
    void backToMenu(MainWindow *mainwindow);
    void playAgain(MainWindow *mainwindow);
};

#endif // WINWINDOW_H
