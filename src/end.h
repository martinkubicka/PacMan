/**
 * @file end.h
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Declaration of End class.
 */

#ifndef END_H
#define END_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "field.h"

/**
 * @brief End object which represents end field in map UI.
 */
class End : public Field {
public:
    /**
     * @brief Constructructor of End object.
     * 
     * @param scene scene where object will be added
     * @param x1 top left x position (from) in px
     * @param y1 top left y position (from) in px
     * @param x2 bottom right x position (to) in px
     * @param y2 bottom right position (to) in px
     * @param srcPath src directory path
     */
    explicit End(QGraphicsScene* scene = nullptr, int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, QString srcPath = "");
};

#endif // END_H

/*** End of end.h ***/
