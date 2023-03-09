/**
 * @file mainwidow.h
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Declaration of MainWidow class especially generated automatically with few own functions for creating main page UI.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QListView>
#include <QDir>
#include <iostream>
#include <string>
#include "ui_mainwindow.h"
#include "map.h"

#define HEIGHT 700 // height of window
#define WIDTH 700 // width of window

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    QString srcPath; // path of src folder set by findImageDirPath method.

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    std::string map; // selected map
    Ui::MainWindow *ui;

    /**
     * @brief Functions which creates a Choose Map Label;
     */
    void createChooseMapLabel();
    
    /**
     * @brief Functions which creates a Combobox (dropdown);
     */
    void createComboBox();

    /**
     * @brief Functions which creates a start button;
     */
    void createStartButton();

    /**
     * @brief Function for finding images parent directory absolute path.
              Result saved to srcPath attribute.
     */
    void findImageDirPath();

private slots:
    /**
     * @brief Function for setting map attribute when map is selected from dropdown menu.
     * 
     * @param mapName map name
     */
    void setMap(const QString &mapName);

    /**
     * @brief Function which reacts when start button is clicked. 
              Function creates selected map.
     */
    void start();
};

#endif // MAINWINDOW_H

/*** End of mainwidow.h ***/
