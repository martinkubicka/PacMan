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


Map::Map(QWidget *parent, std::string map, QString srcPath) : QWidget(parent) {
    this->openFile(map);

    this->getSizeOfBlock();

    parent->setStyleSheet("background-color: black;");

    QGraphicsScene *scene = this->createScene();

    this->createMap(scene, srcPath);

    CustomGraphicsView* view = this->createView(parent, scene);

    (void)view; // todo remove me - maybe not needed
}

Map::~Map() {
    this->file.close();
}

QGraphicsScene* Map::createScene() {
    QGraphicsScene* scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, this->sizeOfBlock*(this->x+2), this->sizeOfBlock*(this->y+2));

    return scene;
}

CustomGraphicsView* Map::createView(QWidget *parent, QGraphicsScene *scene) {
    CustomGraphicsView* view = new CustomGraphicsView(parent);
    view->setScene(scene); // set the scene to the view
    view->setDragMode(QGraphicsView::NoDrag); // disable mouse drag mode
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // disable horizontal scroll bar
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // disable vertical scroll bar
    view->setFixedSize(HEIGHT, WIDTH); // set the fixed size of the view to match the scene size
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

template<typename T>
T Map::getField(int x, int y) { 
    for (auto wallI : walls) {
        if (wallI->x1 <= x && x < wallI->x2 && wallI->y1 <= y && y < wallI->y2) {
            return wallI;
        }
    }

    for (auto keyI : keys) {
        if (keyI->x1 <= x && x < keyI->x2 && keyI->y1 <= y && y < keyI->y2) {
            return keyI;
        }
    }

    for (auto pathI : paths) {
        if (pathI->x1 <= x && x < pathI->x2 && pathI->y1 <= y && y < pathI->y2) {
            return pathI;
        }
    }

    for (auto ghostI : ghosts) {
        if (ghostI->x1 <= x && x < ghostI->x2 && ghostI->y1 <= y && y < ghostI->y2) {
            return ghostI;
        }
    }

    if (pacman->x1 <= x && x < pacman->x2 && pacman->y1 <= y && y < pacman->y2) {
        return pacman;
    }

    if (end->x1 <= x && x < end->x2 && end->y1 <= y && y < end->y2) {
        return end;
    }

    return nullptr;
}

void Map::getSizeOfBlock() {
    try {
        this->x = std::stoi(this->getWord()); // get x size from map file
        this->y = std::stoi(this->getWord()); // get y size from map file
    } catch (const std::exception& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    // we want bigger number
    if (this->x > this->y) {
        this->sizeOfBlock = (HEIGHT - EDGE_OFFSET*2) / (this->x + 2); // *2 -> both sides,  +2 -> default walls
    } else {
        this->sizeOfBlock = (HEIGHT - EDGE_OFFSET*2) / (this->y + 2); // *2 -> both sides,  +2 -> default walls
    }
}

void Map::createMap(QGraphicsScene* scene, QString srcPath) {
    std::vector<char> validChars = {'T', 'X', 'G', 'K', '.', 'S', '\n'}; // vector of valid character in a map

    // top border
    for (int i = 0; i < this->x + 2; i++) {
        wall = new Wall(scene, this->sizeOfBlock*i, 0,  this->sizeOfBlock*(i+1), this->sizeOfBlock, srcPath); //x,y (left top) + x,y (right bottom)
        walls.push_back(wall);
    }

    char ch;
    while (file.get(ch) && std::isspace(ch)) {} // skip white spaces
    file.unget(); // ungetting first char of a map

    // auxiliary variables to know actual position
    int actualX = this->sizeOfBlock; // skip borders
    int actualY = this->sizeOfBlock;  // skip borders

    wall = new Wall(scene, 0, actualY,  this->sizeOfBlock, actualY + this->sizeOfBlock, srcPath); // first left border of a map
    walls.push_back(wall);

    int actualRow = 1; // auxiliary variable to know actual row in a map

    while (file.get(ch)) {
        auto found = std::find(validChars.begin(), validChars.end(), ch); // check if valid char
        if (found != validChars.end()) {
            switch (ch) {
                case 'T':
                    end = new End(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, srcPath);
                    break;

                case 'X':
                    wall = new Wall(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, srcPath);
                    walls.push_back(wall);
                    break;

                case 'G':
                    ghost = new Ghost(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, srcPath);
                    ghosts.push_back(ghost);
                    break;

                case 'K':
                    key = new Key(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, srcPath);
                    keys.push_back(key);
                    this->numberOfKeysLeft++;
                    break;

                case '.':
                    path = new Path(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, srcPath);
                    paths.push_back(path);
                    break;

                case 'S':
                    path = new Path(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, srcPath);
                    paths.push_back(path);

                    pacman = new Pacman(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, srcPath);

                    break;

                case '\n':
                    wall = new Wall(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, srcPath);
                    walls.push_back(wall);

                    actualX = 0;
                    actualY += this->sizeOfBlock;
                    wall = new Wall(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, srcPath);
                    walls.push_back(wall);
                    actualX += this->sizeOfBlock;

                    actualRow++;
                    break;
            } // switch(ch)
        } else {
            std::cerr << ch << " is not valid map character.\n";
            exit(EXIT_FAILURE);
        }

        if (ch != '\n') {
            actualX += this->sizeOfBlock;
        }
    } // while

    // EOF

    // last right border if needed (not \n just EOF)
    if (actualRow != this->y) { 
        wall = new Wall(scene, actualX, actualY,  actualX + this->sizeOfBlock, actualY + this->sizeOfBlock, srcPath);
        walls.push_back(wall);
    }

    // bottom border
    for (int i = 0; i < this->x + 2; i++) {
        wall = new Wall(scene, this->sizeOfBlock*i, this->sizeOfBlock*(this->y+2), this->sizeOfBlock*(i+1), this->sizeOfBlock*(this->y+3), srcPath); //x,y (left top) + x,y (right bottom)
        walls.push_back(wall);
    }

} // createMap


void Map::Start(){
    this->gameStart();
}

void Map::gameStart()
{
    qDebug() << "timer initialized!";
    pacman_timer = new QTimer(this);
    connect(pacman_timer, SIGNAL(timeout()), this , SLOT(pacmanHandler()));
    pacman_timer->start(DELAY);
}

void Map::pacmanHandler()
{
    if(this->pacman->direction != Direction::STOP){
        pacmanMove(this->pacman->direction);
        qDebug() << "game start!";
    }

    //todo add win state
}

void Map::pacmanMove(Direction direction){

    //postup:   1. Kontrola zda muzu do daneho smeru
    //          2. cyklus kde budu posouvat pacmana dokud nenarazi na zed
    //          3.
    qDebug() << "pacman move!";


    int x;
    int y;

    switch (direction){
        case Direction::UP:
            x= this->pacman->x1;
            // y= this->pacman->y1-this->sizeOfBlock;
            y= this->pacman->y1-1;
            w = this->getField<Field *>(x,this->pacman->y1-this->sizeOfBlock);
            break;

        case Direction::DOWN:
            x=this->pacman->x1;
            // y=this->pacman->y1+this->sizeOfBlock;
            y=this->pacman->y1+1;
            w = this->getField<Field *>(x,this->pacman->y1+this->sizeOfBlock);
            break;

        case Direction::LEFT:
            // x=this->pacman->x1-this->sizeOfBlock;
            x=this->pacman->x1-1;
            y=this->pacman->y1;

            w = this->getField<Field *>(this->pacman->x1-this->sizeOfBlock,y);

            break;

        case Direction::RIGHT:
            // x=this->pacman->x1+this->sizeOfBlock;
            x=this->pacman->x1+1;
            y=this->pacman->y1;
            w = this->getField<Field *>(this->pacman->x1+this->sizeOfBlock,y);

            break;
        case Direction::STOP:
            break;
    }

    if (w != nullptr) {
       if (w->type == WALL) {
           // viem ze tam je stena
       } else if (w->type == PATH) {
//           w->pathItem->setPos(x,y);
           this->pacman->x1 = x;
           this->pacman->y1 = y;
           this->pacman->move(x,y);
//           this->pacman->pathItem->setPos(x,y);
           // chodnik
       } else if(w->type == KEY){

       } else if(w->type == GHOST){

       } else if(w->type == END){

       }
    }
}
/*** End of map.cpp ***/
