/**
 * @file pacman.cpp
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Definition of Pacman class.
 */

#include "pacman.h"
#include "map.h"
#include "QDebug" // TODO REMOVE ME

Pacman::Pacman(QGraphicsScene* scene, int x1, int y1, int x2, int y2, Map *map, QString srcPath) : Field (x1, y1, x2, y2, map, PACMAN) {
    QImage pacmanImage(srcPath + "/images/pacman.png");
    pacmanImage = pacmanImage.scaled(QSize(x2-x1, y2-y1), Qt::KeepAspectRatio);
    // this->scene = scene; // to mi dava err tak som zakomentoval

    this->item = new QGraphicsPixmapItem(QPixmap::fromImage(pacmanImage));
    this->item->setZValue(1);
    item->setPos(x1, y1);
    scene->addItem(item);
}

void Pacman::setNextDirection(Direction dir){
    this->nextDirection = dir;
}

void Pacman::move(int x, int y){
    item->setPos(x, y);
}

bool Pacman::pacmanMove(Direction direction){
        int x1 = this->x1;
        int x2 = this->x2;
        int y1 = this->y1;
        int y2 = this->y2;
        Field *FirstCorner = nullptr;
        Field *SecondCorner = nullptr;

        switch (direction){
        case Direction::UP:
            y1 -= 1;
            y2 -= 1;
            FirstCorner = this->map->getField(x1,y1, PACMAN);
            SecondCorner = this->map->getField(x2,y1, PACMAN);
            break;
        case Direction::DOWN:
            y1 += 1;
            y2 += 1;
            FirstCorner = this->map->getField(x1,y2, PACMAN);
            SecondCorner = this->map->getField(x2,y2, PACMAN);
            break;
        case Direction::LEFT:
            x1 -= 1;
            x2 -= 1;
            FirstCorner = this->map->getField(x1,y1, PACMAN);
            SecondCorner = this->map->getField(x1,y2, PACMAN);

            break;
        case Direction::RIGHT:
            x1 += 1;
            x2 += 1;
            FirstCorner = this->map->getField(x2,y1, PACMAN);
            SecondCorner = this->map->getField(x2,y2, PACMAN);
            break;
        case Direction::STOP:
            return false;
    }
  
    if (FirstCorner == nullptr && SecondCorner == nullptr) {
        return false;
    }

    if (FirstCorner->type == WALL or SecondCorner->type == WALL) {
        return false;
        // viem ze tam je stena
    } else if (FirstCorner->type == PATH && SecondCorner->type == PATH) {
        // chodnik
    } else if(FirstCorner->type == KEY && SecondCorner->type == KEY){
        qDebug() << "key";
        this->map->numberOfKeysLeft--;
        //delete key from map
        this->map->deleteKey(FirstCorner);
    } else if(FirstCorner->type == GHOST && SecondCorner->type == GHOST){
        qDebug() << "pacman died";
    } else if(FirstCorner->type == END && SecondCorner->type == END){
        if(this->map->numberOfKeysLeft == 0){
            qDebug() << "pacman won";
            return true;
        }
    }else{
        return false;
    }
    
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
    move(x1,y1);
    return true;
}

    /*** End of pacman.cpp ***/
