/**
 * @file wall.h
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Declaration of Wall class.
 */

#ifndef WALL_H
#define WALL_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "field.h"

/**
 * @brief Wall object which represents wall field in map UI.
 */
class Wall : public Field {
public:
    /**
     * @brief Constructructor of Wall object.
     * 
     * @param scene scene where object will be added
     * @param x1 top left x position (from) in px
     * @param y1 top left y position (from) in px
     * @param x2 bottom right x position (to) in px
     * @param y2 bottom right position (to) in px
     * @param srcPath src directory path
     */
    explicit Wall(QGraphicsScene* scene = nullptr, int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, QString srcPath = "");
};

#endif // WALL_H

/*** End of wall.h ***/
