/**
 * @file ghost.cpp
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Definition of Ghost class.
 */


#include "ghost.h"
#include "map.h"


Ghost::Ghost(QGraphicsScene* scene, int x1, int y1, int x2, int y2, Map *map, QString srcPath) : Field (x1, y1, x2, y2, map, GHOST) {
    QImage ghostImage(srcPath + "/images/ghost.png");
    ghostImage = ghostImage.scaled(QSize(x2-x1, y2-y1), Qt::KeepAspectRatio);

    ghostItem = new QGraphicsPixmapItem(QPixmap::fromImage(ghostImage));
    ghostItem->setPos(x1, y1);
    this->ghostItem->setZValue(1);
    scene->addItem(ghostItem);
}

void Ghost::move(int x, int y){
    ghostItem->setPos(x, y);

    // Field *f = this->map->getField(0, 0);
//    this->scene->addItem(pathItem);
}

bool Ghost::ghostMove( Ghost *ghost){

    int x1 = ghost->x1;
    int x2 = ghost->x2;
    int y1 = ghost->y1;
    int y2 = ghost->y2;
    Field *FirstCorner = this->map->getField(x1,y1);
    Field *SecondCorner = this->map->getField(x1,y1);

    switch (ghost->nextDirection){
    case Direction::UP:
        y1 -= 1;
        y2 -= 1;
        FirstCorner = this->map->getField(x1,y1);
        SecondCorner = this->map->getField(x2,y1);
        break;
    case Direction::DOWN:
        y1 += 1;
        y2 += 1;
        FirstCorner = this->map->getField(x1,y2);
        SecondCorner = this->map->getField(x2,y2);
        break;
    case Direction::LEFT:
        x1 -= 1;
        x2 -= 1;
        FirstCorner = this->map->getField(x1,y1);
        SecondCorner = this->map->getField(x1,y2);

        break;
    case Direction::RIGHT:
        x1 += 1;
        x2 += 1;
        FirstCorner = this->map->getField(x2,y1);
        SecondCorner = this->map->getField(x2,y2);
        break;
    case Direction::STOP:
        break;
    }

    if (FirstCorner == nullptr or SecondCorner == nullptr) {
        return false;
    }

    //todo there is a problem with the pacman position at start how to edit every step position of pacman on map or maybe dont
    if(FirstCorner->type == PATH && SecondCorner->type == PATH){

        ghost->x1 = x1;
        ghost->x2 = x2;
        ghost->y1 = y1;
        ghost->y2 = y2;
        ghost->move(x1,y1);
        // qDebug() << "ghost turn!";
        // qDebug() << "x1: " << x1 << " y1: " << y1;

        return true;
    }
    else{
        qDebug() << "WALL";

        // Generate a random number between 0 and 3
        int ghostDirection = std::rand() % 4;

        ghost->nextDirection = static_cast<Direction>(ghostDirection);
        return false;
    }
}

/*** End of ghost.cpp ***/
