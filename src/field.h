#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QGraphicsScene>

/**
 * @brief Field object which represents a base class of wall, pacman etc..
 */
class Field : public QWidget {
public:
    /**
     * @brief Constructructor of Field object.
     *
     * @param x1 top left x position (from) in px
     * @param y1 top left y position (from) in px
     * @param x2 bottom right x position (to) in px
     * @param y2 bottom right position (to) in px
     */
    explicit Field(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0);

protected:
    int x1, y1, x2, y2; /** Field object position attributes */
};
#endif // FIELD_H
