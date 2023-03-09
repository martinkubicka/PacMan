/**
 * @file map.h
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Declaration Map class.
 */

#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <string>
#include <fstream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
#include "mainwindow.h"
#include "wall.h"
#include "path.h"
#include "ghost.h"
#include "key.h"
#include "pacman.h"
#include "end.h"
#include "customgraphicsview.h"


#define EDGE_OFFSET 20 // offset which prevents creating map at [0, 0] etc..

/**
 * @brief Class used to create map.
 */
class Map : public QWidget {
public:
    /**
     * @brief Constructor of Map object
     * 
     * @param parent parent
     * @param map map file string
     * @param srcPath src directory path
     */
    explicit Map(QWidget *parent = nullptr, std::string map = "map01.txt", QString srcPath = "");
    
    ~Map();
private:
    // attributes
    std::ifstream file; /** file with map */
    int sizeOfBlock; /** size in px of one block (path, pacman, wall..) */
    int numberOfKeysLeft = 0; /** auxiliary counter which helps us to know how many keys are left on map */
    int x, y; /** map resolution (number of blocks) */

    Wall *wall; 
    Path *path;
    Ghost *ghost;
    Key *key;
    Pacman *pacman;
    End *end;

    // methods

    /**
     * @brief Function used to calculate size of block. Depends on how large map is..
     */
    void getSizeOfBlock();

    /**
     * @brief Function used to get resolutions of map from map file.
     * 
     * @return std::string word
     */
    std::string getWord();

    /**
     * @brief Function which read map file and creates map based on map characters.
     * 
     * @param scene scene
     * @param srcPath path to src directory
     */
    void createMap(QGraphicsScene* scene, QString srcPath);
    
    /**
     * @brief Function for opening file based on map name.
     * 
     * @param map map name
     */
    void openFile(std::string map);

    /**
     * @brief Function for creating scene.
     * 
     * @return QGraphicsScene* scene
     */
    QGraphicsScene* createScene();

    /**
     * @brief Function for creating view.
     * 
     * @param parent 
     * @param scene 
     * @return CustomGraphicsView* 
     */
    CustomGraphicsView* createView(QWidget *parent, QGraphicsScene *scene);
};

#endif // MAP_H

/*** End of map.h ***/
