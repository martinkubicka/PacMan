/**
 * @file map.cpp
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Definitions of functions declared in Map class.
 */

#include "map.h"
#include "mainwindow.h"
#include "key.h"

void Map::copyMap(string map, ofstream& outputFile) {
    std::ifstream inputFile(map);

    if (!inputFile.is_open()) {
        cerr << "ERROR: Opening file." << endl;
        exit(EXIT_FAILURE);
    }

    char c;
    while (inputFile.get(c)) {
        outputFile.put(c);
    }

    outputFile.put('\n');

    inputFile.close();
}

void Map::handleExit() {
    foreach (QTimer* timer, findChildren<QTimer*>()) {
        timer->stop();
    }

    this->deleteAll();
    this->mainwindow->createUi();
}

void Map::createExitButton() {
    this->exitButton = new QPushButton("Exit");
    exitButton->setGeometry(570, 0, 80, 30);
    exitButton->setStyleSheet("QPushButton{color:white; border: 1px solid white; border-radius: 3px; padding-bottom: 3px; background-color: black;}  QPushButton:pressed{border: 1px solid gray;}");

    QFont exitButtonFont("Arial Black", 16);
    exitButton->setFont(exitButtonFont);

    this->scene->addWidget(exitButton);

    connect(exitButton, &QPushButton::clicked, this, &Map::handleExit);
}

Map::Map(MainWindow *parent, std::string map, QString srcPath, bool replay) : QWidget(parent), replay(replay) {
    this->openFile(map);

    if (!this->replay) {
        openLogWrite(srcPath.toStdString(), this->log);
    }

    this->getSizeOfBlock();

    this->mainwindow = parent;
    parent->setStyleSheet("background-color: black;");

    scene = this->createScene();

    this->createMap(scene, srcPath);

    if (!this->replay) {
        this->createExitButton();
    }

    this->copyMap(map, this->log);
    if (!this->replay) {
        writeToLog("MAP " + map, this->log);
    }

    this->createView(parent, scene);
}

Map::~Map() {
    this->file.close();
    closeLog(this->log);
}

QGraphicsScene* Map::createScene() {
    QGraphicsScene* scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, this->sizeOfBlock*(this->x+2) + this->x + 1, this->sizeOfBlock*(this->y+2) + this->y + 1 + 130);

    return scene;
}

CustomGraphicsView* Map::createView(QWidget *parent, QGraphicsScene *scene) {
    CustomGraphicsView* view = new CustomGraphicsView(parent);
    view->setScene(scene); // set the scene to the view
    view->setDragMode(QGraphicsView::NoDrag); // disable mouse drag mode
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // disable horizontal scroll bar
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // disable vertical scroll bar
    view->setFixedSize(HEIGHT, WIDTH + 100); // set the fixed size of the view to match the scene size
    view->show();
    return view;
}

void Map::openFile(std::string map) {
    this->file.open(map);

    if (!this->file.is_open()) {
        std::cerr << "Failed to open file.\n";
        exit(EXIT_FAILURE);
    }
}

std::string Map::getWord() {
    std::string word;
    char ch;
    while (file.get(ch) && !std::isspace(ch)) {
        word += ch;
    }

    return word;
}

Field* Map::getField(int x, int y, FieldType calledBy) {
    if (calledBy == GHOST) {
        if (pacman->x1 <= x && x <= pacman->x2 && pacman->y1 <= y && y <= pacman->y2) {
            return pacman;
        }
    }

    if (calledBy == PACMAN) {
        for (auto ghostI : ghosts) {
            if (ghostI->x1 <= x && x <= ghostI->x2 && ghostI->y1 <= y && y <= ghostI->y2) {
                return ghostI;
            }
        }
    }

    for (auto wallI : walls) {
        if (wallI->x1 <= x && x <= wallI->x2 && wallI->y1 <= y && y <= wallI->y2) {
            return wallI;
        }
    }

    for (auto keyI : keys) { // have to check keys before paths (keys above paths)
        if (keyI->x1 <= x && x <= keyI->x2 && keyI->y1 <= y && y <= keyI->y2) {
            return keyI;
        }
    }

    for (auto pathI : paths) {
        if (pathI->x1 <= x && x <= pathI->x2 && pathI->y1 <= y && y <= pathI->y2) {
            return pathI;
        }
    }

    if (end->x1 <= x && x <= end->x2 && end->y1 <= y && y <= end->y2) {
        return end;
    }

    return nullptr;
}

void Map::deleteKey(Field *key){
    this->score++;
    this->numberOfKeysLeft--;

    this->scoreLabel->setText(QString("Score: %1").arg(this->score));

    if (!this->replay) {
        writeToLog("KEYL " + to_string(key->id) + " : Key obtained", this->log);
    }

    // delete from ui
    this->scene->removeItem(key->item);

    key->x1 = key->x2 = key->y1 = key->y2 = -1; // replay previous step -> cant delete
}

void Map::getSizeOfBlock() {
    try {
        this->y = std::stoi(this->getWord()); // get x size from map file
        this->x = std::stoi(this->getWord()); // get y size from map file
    } catch (const std::exception& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    // we want bigger number
    if (this->x > this->y) {
        this->sizeOfBlock = (HEIGHT - EDGE_OFFSET*2 - this->x + 1) / (this->x + 2); // *2 -> both sides,  +2 -> default walls
    } else {
        this->sizeOfBlock = (HEIGHT - EDGE_OFFSET*2 - this->y + 1) / (this->y + 2); // *2 -> both sides,  +2 -> default walls
    }
}

void Map::createScore() {
    scoreLabel = new QLabel(QString("Score: %1").arg(this->score));
    QFont labelFont("Arial Black", 15);
    scoreLabel->setFont(labelFont);
    scoreLabel->setStyleSheet("color:white; background-color: black;");

    QGraphicsProxyWidget *proxy = scene->addWidget(scoreLabel);
    proxy->setPos(300, 0);
    proxy->setZValue(1);
}

void Map::createLives() {
    QImage hearthImage(this->mainwindow->srcPath + "/images/hearth.png");
    hearthImage = hearthImage.scaled(QSize(30, 30), Qt::KeepAspectRatio);

    for (int i = 0; i < this->numberOfLives; i++) {
        QGraphicsPixmapItem* hearth = new QGraphicsPixmapItem(QPixmap::fromImage(hearthImage));
        this->liveItems.push_back(hearth);
        hearth->setZValue(1);
        hearth->setPos(i*30 + 10, 0);
        scene->addItem(hearth);
    }
}

void Map::deleteLive() {
    if (this->liveItems.size() != 0) {
        this->scene->removeItem(this->liveItems[static_cast<unsigned long>(this->numberOfLives)]);
    }
    this->restartPositions();
}

void Map::restartPositions() {
    // stopping all timers
    foreach (QTimer* timer, findChildren<QTimer*>()) {
        timer->stop();
    }

    // paused
    this->gameStarted = 0;

    // default positions
    pacman->x1 = pacman->startX;
    pacman->y1 = pacman->startY;
    pacman->x2 = pacman->startX + this->sizeOfBlock;
    pacman->y2 = pacman->startY + this->sizeOfBlock;
    pacman->move(pacman->startX, pacman->startY);

    for (auto ghostI : ghosts) {
        ghostI->x1 = ghostI->startX;
        ghostI->y1 = ghostI->startY;
        ghostI->x2 = ghostI->startX + this->sizeOfBlock;
        ghostI->y2 = ghostI->startY + this->sizeOfBlock;
        ghostI->move(ghostI->startX, ghostI->startY);
    }
}

void Map::createMap(QGraphicsScene* scene, QString srcPath) {
    this->createScore();
    this->createLives();

    std::vector<char> validChars = {'T', 'X', 'G', 'K', '.', 'S', '\n'}; // vector of valid character in a map

    // top border
    for (int i = 0; i < this->x + 2; i++) {
        wall = new Wall(scene, this->sizeOfBlock*i + i, 0 + 40,  this->sizeOfBlock*(i+1) + i, this->sizeOfBlock + 40, this, srcPath); //x,y (left top) + x,y (right bottom)
        walls.push_back(wall);
    }

    char ch;
    while (file.get(ch) && std::isspace(ch)) {} // skip white spaces
    file.unget(); // ungetting first char of a map

    // auxiliary variables to know actual position
    int actualX = this->sizeOfBlock + 1; // skip borders
    int actualY = this->sizeOfBlock + 1 + 40;  // skip borders

    wall = new Wall(scene, 0, actualY,  this->sizeOfBlock, actualY + this->sizeOfBlock, this, srcPath); // first left border of a map
    walls.push_back(wall);

    int actualRow = 1; // auxiliary variable to know actual row in a map

    while (file.get(ch)) {
        auto found = std::find(validChars.begin(), validChars.end(), ch); // check if valid char
        if (found != validChars.end()) {
            switch (ch) {
                case 'T':
                    end = new End(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, this, srcPath);
                    break;

                case 'X':
                    wall = new Wall(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, this, srcPath);
                    walls.push_back(wall);
                    break;

                case 'G':
                    // creating path below ghost
                    path = new Path(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, this, srcPath);
                    paths.push_back(path);

                    // creating ghost
                    ghost = new Ghost(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, this, srcPath);
                    ghosts.push_back(ghost);
                    break;

                case 'K':
                    // creating path below key
                    path = new Path(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, this, srcPath);
                    paths.push_back(path);
                    // creating key
                    key = new Key(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, this, srcPath);
                    keys.push_back(key);
                    this->numberOfKeysLeft++;
                    break;

                case '.':
                    path = new Path(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, this, srcPath);
                    paths.push_back(path);

                    break;

                case 'S':
                    path = new Path(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, this, srcPath);
                    paths.push_back(path);

                    pacman = new Pacman(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, this, srcPath);

                    break;

                case '\n':
                    wall = new Wall(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, this, srcPath);
                    walls.push_back(wall);

                    actualX = 0;
                    actualY += this->sizeOfBlock + 1;
                    wall = new Wall(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, this, srcPath);
                    walls.push_back(wall);
                    actualX += this->sizeOfBlock + 1;

                    actualRow++;
                    break;
            } // switch(ch)
        } else {
            std::cerr << ch << " is not valid map character.\n";
            exit(EXIT_FAILURE);
        }

        if (ch != '\n') {
            actualX += this->sizeOfBlock + 1;
        }
    } // while

    // EOF

    // last right border if needed (not \n just EOF)
    if (actualRow != this->y) { 
        wall = new Wall(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, this, srcPath);
        walls.push_back(wall);
    }

    // bottom border
    for (int i = 0; i < this->x + 2; i++) {
        wall = new Wall(scene, this->sizeOfBlock*i + i, this->sizeOfBlock*(this->y+1)+40 + this->y + 1, this->sizeOfBlock*(i+1) + i, this->sizeOfBlock*(this->y+2) + this->y + 1 + 40, this, srcPath); //x,y (left top) + x,y (right bottom)
        walls.push_back(wall);
    }

} // createMap

void Map::Start(){
    if (!this->replay) {
        writeToLog("GS : Game started", this->log);
    }

    this->gameStart();
}

void Map::gameStart()
{
    pacman_timer = new QTimer(this);
    connect(pacman_timer, SIGNAL(timeout()), this , SLOT(pacmanHandler()));
    pacman_timer->start(DELAY);

    for (int i = 0; i < int(ghosts.size()); i++) {
        ghost_timer[i] = new QTimer(this);
        connect(ghost_timer[i], &QTimer::timeout, [=](){ghostHandler(i);} );
        ghost_timer[i]->start(DELAYGHOST);
    }
}

void Map::pacmanHandler()
{
    bool hasMoved = this->pacman->pacmanMove(this->pacman->nextDirection);
    if(hasMoved)
    {
        this->pacman->direction = this->pacman->nextDirection;
        return;
    }

    this->pacman->pacmanMove(this->pacman->direction);
}

void Map::ghostHandler(int ghostNum){
    auto ghost = ghosts.at(static_cast<uint>(ghostNum));
    this->ghost->ghostMove(ghost);
}

void Map::deleteAll() {
    if (this->liveItems.size() != 0) {
        for (auto item : this->liveItems) {
            this->scene->removeItem(item);
        }
    }

    this->exitButton->deleteLater();

    this->scoreLabel->deleteLater();

    this->scene->removeItem(this->pacman->item);
    delete this->pacman;

    this->scene->removeItem(this->end->item);
    delete this->end;

    for (auto ghostI : ghosts) {
        this->scene->removeItem(ghostI->item);
        delete ghostI;
    }

    for (auto wallI : walls) {
        this->scene->removeItem(wallI->item);
        delete wallI;
    }

    for (auto keyI : keys) {
        this->scene->removeItem(keyI->item);
        delete keyI;
    }

    for (auto pathI : paths) {
        this->scene->removeItem(pathI->item);
        delete pathI;
    }
}

void Map::handleWin() {
    // Stop all running timers - needs to be here - crash
    foreach (QTimer* timer, findChildren<QTimer*>()) {
        timer->stop();
    }

    this->deleteAll();
    EndGameWindow(this->mainwindow, WIN);
    if (!this->replay) {
        writeToLog("GE : Game ended", this->log);
    }
}

void Map::handleGameOver() {
    --this->numberOfLives;
    if (!this->replay) {
        writeToLog("KILL : PacMan died", this->log);
    }
    this->deleteLive();
    if (!this->numberOfLives && !this->replay) {
        this->deleteAll();
        EndGameWindow(this->mainwindow, GAMEOVER);
        writeToLog("GE : Game ended", this->log);
    }
}

/*** End of map.cpp ***/
