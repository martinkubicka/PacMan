/**
 * @file key.cpp
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Definition of Key class.
 */

#include "key.h"

Key::Key(QGraphicsScene* scene, int x1, int y1, int x2, int y2, QString srcPath) : Field (x1, y1, x2, y2, KEY) {
    QImage keyImage(srcPath + "/images/key.png");
    keyImage = keyImage.scaled(QSize(x2-x1, y2-y1), Qt::KeepAspectRatio);

    QGraphicsPixmapItem* keyItem = new QGraphicsPixmapItem(QPixmap::fromImage(keyImage));
    keyItem->setPos(x1, y1);

    scene->addItem(keyItem);
}

/*** End of key.cpp ***/
