#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QGraphicsScene>

// field type
enum FieldType {
    PATH,
    WALL,
    PACMAN,
    KEY,
    GHOST,
    END,
    DEFAULT
};

enum Direction {
    UP,
    LEFT,
    DOWN,
    RIGHT,
    STOP
};
class Map;

/**
 * @brief Field object which represents a base class of wall, pacman etc..
 */
class Field : public QWidget {
public:
    QGraphicsPixmapItem* pathItem;
    QGraphicsPixmapItem* ghostItem;
    int x1, y1, x2, y2; /** Field object position attributes */
    Map *map; /** pointer to map */
    FieldType type; /** Type of field */

    /**
     * @brief Constructructor of Field object.
     *
     * @param x1 top left x position (from) in px
     * @param y1 top left y position (from) in px
     * @param x2 bottom right x position (to) in px
     * @param y2 bottom right position (to) in px
     * @param map pointer to map object
     * @param type type of dield
     */
    explicit Field(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, Map *map = nullptr, FieldType type = DEFAULT);
 };
#endif // FIELD_H
