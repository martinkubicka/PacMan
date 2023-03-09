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

Ghost::Ghost(QGraphicsScene* scene, int x1, int y1, int x2, int y2, QString srcPath) : Field (x1, y1, x2, y2) {
    QImage ghostImage(srcPath + "/images/ghost.png");
    ghostImage = ghostImage.scaled(QSize(x2-x1, y2-y1), Qt::KeepAspectRatio);

    QGraphicsPixmapItem* ghostItem = new QGraphicsPixmapItem(QPixmap::fromImage(ghostImage));
    ghostItem->setPos(x1, y1);

    scene->addItem(ghostItem);
}

/*** End of ghost.cpp ***/
