/**
 * @file key.h
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Declaration of Key class.
 */

#ifndef KEY_H
#define KEY_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "field.h"

/**
 * @brief Key object which represents key field in map UI.
 */
class Key : public Field {
public:
    /** Attributes used to store default positions -> needed when replaying */
    int startX1, startX2, startY1, startY2;

    /**
     * @brief Constructructor of Key object.
     * 
     * @param scene scene where object will be added
     * @param x1 top left x position (from) in px
     * @param y1 top left y position (from) in px
     * @param x2 bottom right x position (to) in px
     * @param y2 bottom right position (to) in px
     * @param map pointer to map object
     * @param srcPath src directory path
     */
    explicit Key(QGraphicsScene* scene = nullptr, int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, Map *map = nullptr, QString srcPath = "");
};

#endif // KEY_H

/*** End of key.h ***/
