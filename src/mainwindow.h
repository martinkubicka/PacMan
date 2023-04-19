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
#include <QDebug>
#include "ui_mainwindow.h"
#include "map.h"
#include "pacman.h"
#include "replay.h"

namespace Ui {
    class MainWindow; // forward declaration
}

/**
 * @brief Declaration of methods and attributes of MainWindow class which represents
          MainWindow (menu).
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /** path of src folder set by findImageDirPath method. */
    QString srcPath;
    /** pointer to Map object */
    Map *mapObject = nullptr;
    /** Pointer to Replay object if replay is active */
    Replay* replayObj = nullptr;

    /**
     * @brief Overriding closeEvent function (clicking X button).
     *
     * @param event event
     */
    void closeEvent(QCloseEvent *event) override;

    /**
     * @brief Constructor of MainWindow object.
     *
     * @param parent QWidget parent
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Overriding destructor of MainWindow object.
     */
    ~MainWindow() override;

    /**
     * @brief Method which creates UI (buttons, labels etc..).
     */
    void createUi();

    /**
     * @brief Method which handle replaying (creating Replay object etc..).
     */
    void replay();

private:
    /** selected map */
    std::string map;
    /** pointer to mainwindow ui */
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

    /**
     * @brief Method which creates replay button.
     */
    void createReplayButton();
protected:
    /**
     * @brief Overriding keyPressEvent function for handling user keys input.
     *
     * @param event event
     */
    void keyPressEvent(QKeyEvent* event) override;
private slots:
    /**
     * @brief Function for setting map attribute when map is selected from dropdown menu.
     * 
     * @param mapName map name
     */
    void setMap(const QString &mapName);
public slots:
    /**
     * @brief Function which reacts when start button is clicked.
              Function creates selected map.
     */
    void start();
};

#endif // MAINWINDOW_H

/*** End of mainwidow.h ***/
