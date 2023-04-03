/**
 * @file wall.cpp
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Definition of Wall class.
 */

#include "wall.h"

Wall::Wall(QGraphicsScene* scene, int x1, int y1, int x2, int y2, Map *map ,QString srcPath) : Field (x1, y1, x2, y2, map, WALL) {
    QImage wallImage(srcPath + "/images/wall.png");
    wallImage = wallImage.scaled(QSize(x2-x1, y2-y1), Qt::KeepAspectRatio);

    this->item = new QGraphicsPixmapItem(QPixmap::fromImage(wallImage));
    item->setPos(x1, y1);

    scene->addItem(item);
}

/*** End of wall.cpp ***/
