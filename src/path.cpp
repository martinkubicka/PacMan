/**
 * @file path.cpp
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Definition of Path class.
 */

#include "path.h"

Path::Path(QGraphicsScene* scene, int x1, int y1, int x2, int y2, QString srcPath) : Field (x1, y1, x2, y2) {
    QImage pathImage(srcPath + "/images/path.png");
    pathImage = pathImage.scaled(QSize(x2-x1, y2-y1), Qt::KeepAspectRatio);

    QGraphicsPixmapItem* pathItem = new QGraphicsPixmapItem(QPixmap::fromImage(pathImage));
    pathItem->setPos(x1, y1);

    scene->addItem(pathItem);
}

/*** End of path.cpp ***/
