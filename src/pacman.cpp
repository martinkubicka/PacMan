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

Pacman::Pacman(QGraphicsScene* scene, int x1, int y1, int x2, int y2, QString srcPath) : Field (x1, y1, x2, y2, PACMAN) {
    QImage pacmanImage(srcPath + "/images/pacman.png");
    pacmanImage = pacmanImage.scaled(QSize(x2-x1, y2-y1), Qt::KeepAspectRatio);
    this->scene = scene;

    this->pathItem = new QGraphicsPixmapItem(QPixmap::fromImage(pacmanImage));
    this->pathItem->setZValue(1);
    pathItem->setPos(x1, y1);
    scene->addItem(pathItem);

}

void Pacman::move(int x, int y){
    pathItem->setPos(x, y);
//    this->scene->addItem(pathItem);
}

    /*** End of pacman.cpp ***/
