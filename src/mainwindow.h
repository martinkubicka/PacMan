#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QListView>
#include <string>
#include <iostream>

#define HEIGHT 700
#define WIDTH 700

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    std::string map = "/Users/martinkubicka/Documents/ICP/PacMan/maps/map01.txt";
    Ui::MainWindow *ui;

private slots:
    void setMap(const QString &mapName);

    void start();
};

#endif // MAINWINDOW_H
