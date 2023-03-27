/**
 * @file end.cpp
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Definition of End class.
 */

#include "end.h"

End::End(QGraphicsScene* scene, int x1, int y1, int x2, int y2, Map *map, QString srcPath) : Field (x1, y1, x2, y2, map, END) {
    QImage endImage(srcPath + "/images/end.png");
    endImage = endImage.scaled(QSize(x2-x1, y2-y1), Qt::KeepAspectRatio);

    QGraphicsPixmapItem* endItem = new QGraphicsPixmapItem(QPixmap::fromImage(endImage));
    endItem->setPos(x1, y1);

    scene->addItem(endItem);
}

/*** End of end.cpp ***/
