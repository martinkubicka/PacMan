#include "replay.h"
#include "map.h"
#include "mainwindow.h"

Replay::Replay(QString srcPath, MainWindow *mainwindow) : srcPath(srcPath), mainwindow(mainwindow)
{

    this->runTimer = new QTimer(this);

    this->getAllInstructions();

    qDebug() << this->instructions.size();

    if (this->instructions.size() == 0) {
        cout << "Last game not found." << endl;
        return;
    }

    this->instructionIndex = 0;

    // get map name
    string path = this->instructions[this->instructionIndex]->arg1;
    size_t pos = path.rfind("/");
    this->mapname = path.substr(pos + 1);

    this->map = new Map(this->mainwindow, path, this->srcPath, true);
    this->instructionIndex++;

    this->createExitButton();

    connect(runTimer, SIGNAL(timeout()), this , SLOT(handleConnect()));
}

Replay::~Replay() {
    this->deleteAllInstructions();
    delete this->map;
}

void Replay::handleExit() {
    foreach (QObject* child, mainwindow->children()) {
        QWidget* childWidget = qobject_cast<QWidget*>(child);
        if (childWidget) {
            childWidget->deleteLater();
        }
    }

    this->stop = true;
    this->run = false;
    this->runback = false;
    this->runTimer->stop();
    this->mainwindow->replayObj = nullptr;
    this->mainwindow->createUi();
}

void Replay::createExitButton() {
    this->exitButton = new QPushButton("Exit");
    exitButton->setGeometry(260, 380, 80, 30);
    exitButton->setStyleSheet("QPushButton{color:white; border: 1px solid white; border-radius: 3px; padding-bottom: 3px; background-color: black;}  QPushButton:pressed{border: 1px solid gray;}");

    QFont exitButtonFont("Arial Black", 16);
    exitButton->setFont(exitButtonFont);

    connect(exitButton, &QPushButton::clicked, this, &Replay::handleExit);

    QGraphicsProxyWidget *proxy = this->map->scene->addWidget(exitButton);
    proxy->setPos(570, 0);
    proxy->setZValue(1);
}

void Replay::handleConnect() {
    if (this->run) {
        handleNextInstruction();
    } else {
        handlePrevInstruction();
    }
}

void Replay::runForward() {
    runTimer->start(4);
}

void Replay::runBackward() {
    runTimer->start(4);
}

void Replay::handleKey(QKeyEvent* event)
{
    if (event->key() == Qt::Key_R)
    {
        if (this->runback) {
            this->runTimer->stop();
            this->runback = false;
        }

        this->stop = false;
        if (this->run != true) {
            this->runTimer->stop();
            this->run = true;
            this->runForward();
        }
    } else if (event->key() == Qt::Key_E) {
        this->runTimer->stop();
        this->stop = true;
        this->run = false;
        this->runback = false;
    } else if (event->key() == Qt::Key_B) {
        if (this->run) {
            this->runTimer->stop();
            this->run = false;
        }

        this->stop = false;

        if (this->runback != true) {
            this->runTimer->stop();
            this->runback = true;
            this->runBackward();
        }
    } else if (event->key() == Qt::Key_N) {
        if (this->stop) {
            this->handleNextInstruction();
        }
    } else if (event->key() == Qt::Key_P) {
        qDebug() << this->stop;
        if (this->stop) {
            this->handlePrevInstruction();
        }
    }
}

void Replay::performInstruction() {
    Instruction *actual = this->instructions[this->instructionIndex];

    if (this->prev) {
        Instruction* next = this->instructions[this->instructionIndex + 1];

        if (next->type == KEYL) {
            ++this->map->numberOfKeysLeft;
            --this->map->score;
            this->map->scoreLabel->setText(QString("Score: %1").arg(this->map->score));
            this->map->scene->addItem(this->map->keys[stoul(next->arg1)]->item);
        } else if (next->type == KILL) {
            ++this->map->numberOfLives;
            this->map->scene->addItem(this->map->liveItems[static_cast<unsigned long>(this->map->numberOfLives - 1)]);
        }
    }

    if (actual->type == PCM) {
        this->map->pacman->move(stoi(actual->arg1), stoi(actual->arg2));
    } else if (actual->type == GM) {
        this->map->ghosts[stoul(actual->arg1)]->move(stoi(actual->arg2), stoi(actual->arg3));
    } else if (actual->type == KEYL && !this->prev) {
        this->map->deleteKey(this->map->getField(this->map->keys[stoul(actual->arg1)]->x1, this->map->keys[stoul(actual->arg1)]->y1, DEFAULT));
    } else if (actual->type == KILL && !this->prev) {
        this->map->handleGameOver();
    }
}

void Replay::getAllInstructions() {
    openLogRead(this->srcPath.toStdString(), this->file);

    Instruction* inst = getInstruction(this->file);

    while (inst->type != NONE) {
        this->instructions.push_back(inst);
        inst = getInstruction(this->file);
    }

    closeLog(this->file);
}

void Replay::handlePrevInstruction() {
    if (this->instructionIndex - 1 != 0) {
        if ((this->runback && !this->stop) || (!this->runback && this->stop)) {
            --this->instructionIndex;
            this->prev = true;
            this->performInstruction();
            this->prev = false;
        }
    } else {
        this->runTimer->stop();
        this->run = false;
        this->runback = false;
        this->stop = true;
    }
}

void Replay::handleNextInstruction() {
    if (this->instructionIndex + 1 != this->instructions.size() - 1) {
        if ((this->run && !this->stop) || (!this->run && this->stop)) {
            ++this->instructionIndex;
            this->performInstruction();
        }
    } else {
        this->runTimer->stop();
        this->run = false;
        this->runback = false;
        this->stop = true;
    }
}

void Replay::deleteAllInstructions() {
    for (auto inst : this->instructions) {
        delete inst;
    }
}
