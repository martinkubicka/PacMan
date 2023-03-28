/**
 * @file pacman.h
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Declaration of Pacman class.
 */

#ifndef PACMAN_H
#define PACMAN_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "field.h"

enum Direction {
    UP,
    LEFT,
    DOWN,
    RIGHT,
    STOP
};
/**
 * @brief Pacman object which represents pacman field in map UI.
 */
class Pacman : public Field {
public:
    Direction direction = Direction::STOP;
    /**
     * @brief Constructructor of Pacman object.
     * 
     * @param scene scene where object will be added
     * @param x1 top left x position (from) in px
     * @param y1 top left y position (from) in px
     * @param x2 bottom right x position (to) in px
     * @param y2 bottom right position (to) in px
     * @param map pointer to map object
     * @param srcPath src directory path
     */
    explicit Pacman(QGraphicsScene* scene = nullptr, int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, Map *map = nullptr, QString srcPath = "");
    bool nextToWall = false;
    void move(int x,int y);
    void IsValidDirection();

};

#endif // PACMAN_H

/*** End of pacman.h ***/
