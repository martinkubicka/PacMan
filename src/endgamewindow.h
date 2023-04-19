/**
 * @file endgamewindow.h
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Declaration of EndGameWindow class used for creating window after end of the game.
 */

#ifndef ENDGAMEWINDOW_H
#define ENDGAMEWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QtDebug>
#include <QPushButton>
#include <QApplication>
#include "replay.h"

class MainWindow; // forward declaration

/** Enum which is used as param to know if function will create win or game over window */
enum endGameType {
    WIN,
    GAMEOVER
};

/**
 * @brief Class used for creating UI after end of the game.
 */
class EndGameWindow : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructor of EndGameWindow object.
     *
     * @param mainwindow pointer to mainwindow
     * @param type type of window which will be created
     */
    EndGameWindow(MainWindow *mainwindow, endGameType type);
private:
    /**
     * @brief Method for deleting all graphical objects from UI.
     *
     * @param mainwindow pointer to mainwindow
     */
    void deleteAll(MainWindow *mainwindow);
private slots:
    /**
     * @brief Method used for handling clicking to back to menu button.
     *
     * @param mainwindow pointer to mainwindow
     */
    void backToMenu(MainWindow *mainwindow);

    /**
     * @brief Method used for handling clicking to play again button.
     *
     * @param mainwindow pointer to mainwindow
     */
    void playAgain(MainWindow *mainwindow);
};

#endif // ENDGAMEWINDOW_H

/*** End of endgamewindow.h ***/
