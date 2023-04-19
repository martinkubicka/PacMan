/**
 * @file customgraphicsview.h
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Declaration of CustomGraphicsView class used to disable mouse wheel event.
 */

#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QWidget>
#include <QWheelEvent>
#include <QGraphicsView>

/**
 * @brief Custom QGraphicsView class used to disable mouse wheel event.
 */
class CustomGraphicsView : public QGraphicsView {
public:
    CustomGraphicsView(QWidget* parent = nullptr) : QGraphicsView(parent) {}
protected:
    /**
     * @brief Function for disabling mouse wheel event.
     * 
     * @param event
     */
    void wheelEvent(QWheelEvent* event) override {
        event->ignore();
    }
};

#endif // CUSTOMGRAPHICSVIEW_H

/*** End of customgraphicsview.h ***/
