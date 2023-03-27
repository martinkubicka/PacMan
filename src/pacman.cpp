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

    this->pathItem = new QGraphicsPixmapItem(QPixmap::fromImage(pacmanImage));
    this->pathItem->setZValue(1);
    pathItem->setPos(x1, y1);
    scene->addItem(pathItem);

}

void Pacman::move(int x, int y){
    pathItem->setPos(x, y);

    Field *f = this->map->getField(0, 0);
//    this->scene->addItem(pathItem);
}

    /*** End of pacman.cpp ***/
