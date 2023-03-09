/**
 * @file path.h
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Declaration of Path class.
 */

#ifndef PATH_H
#define PATH_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

/**
 * @brief Path object which represents path field in map UI.
 */
class Path : public QWidget {
public:
    /**
     * @brief Constructructor of Path object.
     * 
     * @param scene scene where object will be added
     * @param x1 top left x position (from) in px
     * @param y1 top left y position (from) in px
     * @param x2 bottom right x position (to) in px
     * @param y2 bottom right position (to) in px
     */
    explicit Path(QGraphicsScene* scene = nullptr, int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0);

private:
    int x1, y1, x2, y2; /** Path object position attributes */
};
#endif // PATH_H

/*** End of path.h ***/
