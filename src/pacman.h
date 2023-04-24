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


/**
 * @brief Pacman object which represents pacman field in map UI.
 */
class Pacman : public Field {
public:
    /** attributes which specifies actaul and next direction of pacman */
    Direction direction = Direction::STOP;
    Direction nextDirection = Direction::STOP;
    
    /** Attributes which store default position of pacman -> used in replay mode */
    int startX, startY;

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

    /**
     * @brief Set the Next Direction object
     * 
     * @param dir 
     */
    void setNextDirection(Direction dir);

    /**
     * @brief Method which moves Pacman object on a scene.
     * 
     * @param x x px where pacman will be moved
     * @param y y px where pacman will be moved
     */
    void move(int x,int y);

    /**
     * @brief Method which gets field of next position and check if it is wall, ghost, finish, path or key. 
     * For the key it calls method which adds key to pacman and delete key from map. For the ghost option 
     * it calls method handleGameOver, which look at the number of lives and if it is 0, it calls method to end game.
     * For the finish option it calls method handleWin, which look at the number of keys and if it is 0, it 
     * calls method to end game. For the path option it calls method to move pacman to next position.
     * 
     * @param direction direction where pacman will be moved
     */
    bool pacmanMove(Direction direction);
};

#endif // PACMAN_H

/*** End of pacman.h ***/
