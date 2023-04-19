/**
 * @file replay.h
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Declaration of Replay class.
 */

#ifndef REPLAY_H
#define REPLAY_H

#include "log.h"
#include <vector>
#include <QString>
#include <QPushButton>
#include <QWidget>
#include <QTimer>

class Map; // forward declaration
class MainWindow; // forward declaration

using namespace std;

/**
 * @brief Class with methods and attributes needed for replaying game.
 */
class Replay : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param srcPath path to src folder
     * @param mainwindow pointer to main window
     */
    Replay(QString srcPath, MainWindow *mainwindow);

    /**
     * @brief Custom destructor.
    */
    ~Replay();

    /**
     * @brief Method which handles key press -> changing modes etc..
     *
     * @param event key event
     */
    void handleKey(QKeyEvent* event);
private:
    vector<Instruction*> instructions; /// loaded instructions
    unsigned long instructionIndex; /// index of actual instruction in instructions vector
    Map *map; /// pointer to map
    string mapname; /// map name (txt)
    ifstream file; /// log file in read mode
    QString srcPath; /// path to src folder
    MainWindow *mainwindow; /// pointer to main window
    QPushButton* exitButton; /// pointer to exit button

    /** modes */
    bool run = false, runback = false, prev = false;
    bool stop = true;

    QTimer *runTimer; /// timer used in run mode

    /**
     * @brief Method which manages run mode.
     */
    void runForward();

    /**
     * @brief Method which manages run backward mode.
     */
    void runBackward();

    /**
     * @brief Method which is called after clicking exit button.
     */
    void handleExit();

    /**
     * @brief Method which creates exit button.
     */
    void createExitButton();

    /**
     * @brief Method which gets all instruction from log file to instructions vector.
     */
    void getAllInstructions();

    /**
     * @brief Method which performs all loaded instructions.
     */
    void performInstruction();

    /**
     * @brief Method which clears instructions vector.
     */
    void deleteAllInstructions();

    /**
     * @brief Method which handles previous instructions (if going back in replay)
     */
    void handlePrevInstruction();

    /**
     * @brief Method which handles next instruction.
     */
    void handleNextInstruction();
private slots:
    /**
     * @brief Method which connects runTimer with methods.
     */
    void handleConnect();
};

#endif // REPLAY_H

/*** End of replay.h ***/
