/**
 * @file ghost.h
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Declaration of Ghost class.
 */

#ifndef GHOST_H
#define GHOST_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <string>
#include "field.h"

/**
 * @brief Ghost object which represents ghost field in map UI.
 */
class Ghost : public Field  {
public:

    /**
     * @brief Constructructor of Ghost object.
     * 
     * @param scene scene where object will be added
     * @param x1 top left x position (from) in px
     * @param y1 top left y position (from) in px
     * @param x2 bottom right x position (to) in px
     * @param y2 bottom right position (to) in px
     * @param map pointer to map object
     * @param srcPath src directory path
     */
    explicit Ghost(QGraphicsScene* scene = nullptr, int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, Map *map = nullptr, QString srcPath = "", int sizeOfBlock = 0);

    /** setting default direction of ghost */
    Direction nextDirection = Direction::UP;

    /** Attributes used to store default positions -> needed when reseting positions */
    int startX, startY;

    /**
     * @brief Method which moves Ghost object on a scene.
     *
     * @param x x px where ghost will be moved
     * @param y y px where ghost will be moved
     */
    void move(int x, int y);

    /**
     * @brief ghostMove TODO
     *
     * @param ghost TODO
     *
     * @return TODO
     */
    bool ghostMove(Ghost *ghost);
private: 
    /** size of block in px */
    int sizeOfBlock;

    /** id of ghost */
    int id;
};

#endif // GHOST_H

/*** End of ghost.h ***/
