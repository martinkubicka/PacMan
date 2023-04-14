#ifndef REPLAY_H
#define REPLAY_H

#include "log.h"
#include <vector>
#include <QString>
#include <QPushButton>
#include <QWidget>
#include <QTimer>

class Map;
class MainWindow;

using namespace std;

class Replay : public QObject {
    Q_OBJECT
public:
    Replay(QString srcPath, MainWindow *mainwindow);
    ~Replay();
    void handleKey(QKeyEvent* event);
private:
    vector<Instruction*> instructions;
    unsigned long instructionIndex;
    Map *map;
    string mapname;
    ifstream file;
    QString srcPath;
    MainWindow *mainwindow;
    QPushButton* exitButton;

    bool run = false, runback = false, prev = false;
    bool stop = true;

    QTimer *runTimer;


    void runForward();

    void runBackward();

    void handleExit();

    void createExitButton();

    void getAllInstructions();

    void performInstruction();

    void deleteAllInstructions();

    void handlePrevInstruction();

    void handleNextInstruction();
private slots:
    void handleConnect();
};

#endif // REPLAY_H
