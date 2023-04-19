/**
 * @file field.h
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Declaration of Field class used to identify types of fields in map.
 */

#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QGraphicsScene>

/** Enum which specifies type of every field of the map */
enum FieldType {
    PATH,
    WALL,
    PACMAN,
    KEY,
    GHOST,
    END,
    DEFAULT
};

/** Enum which specifies direction of pacman/ghost */
enum Direction {
    UP,
    LEFT,
    DOWN,
    RIGHT,
    STOP
};

class Map; // forward declaration

/**
 * @brief Field object which represents a base class of wall, pacman etc..
 */
class Field : public QWidget {
public:
    /** Pointer to item created on map -> so we can delete if needed */
    QGraphicsPixmapItem* item;
    /** Field object position attributes */
    int x1, y1, x2, y2;
    /** pointer to map */
    Map *map;
    /** Type of field */
    FieldType type;
    /** Id of item -> needed in some types of fields in replay mode */
    int id;

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

/*** End of field.h ***/
