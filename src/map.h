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
#include "wall.h"
#include "path.h"
#include "ghost.h"
#include "key.h"
#include "pacman.h"
#include "end.h"
#include "customgraphicsview.h"
#include <QTimer>
#include <QDebug>
#include "endgamewindow.h"
#include <vector>
#include <QPixmap>
#include "replay.h"
#include <QGraphicsProxyWidget>

/** offset which prevents creating map at [0, 0] etc.. */
#define EDGE_OFFSET 20

/** height of window */
#define HEIGHT 700

/** width of window */
#define WIDTH 700

/** move delay pacman */
#define DELAY 10

/** move delay ghost */
#define DELAYGHOST 15

class MainWindow; // forward declaration

/**
 * @brief Class used to create map.
 */
class Map : public QWidget {
    Q_OBJECT
public:
    /** map resolution (number of blocks) */
    int x, y;

    /** vectors of objects which map contains */
    std::vector<Wall *> walls;
    std::vector<Path *> paths;
    std::vector<Ghost *> ghosts;
    std::vector<Key *> keys;
    Pacman *pacman;
    End *end;

    MainWindow *mainwindow; /// pointer to mainwindow
    QGraphicsScene *scene; /// pointer to scene where map objects are created

    QLabel *scoreLabel; /// label in map with score
    int score = 0; /// actual score

    QPushButton* exitButton; /// pointer to exitbutton

    int numberOfLives = 3; /// number of lives
    std::vector<QGraphicsPixmapItem*> liveItems; /// vector hearth images

    int gameStarted = 0; /// if 0 game paused if 1 game is running

    int numberOfKeysLeft = 0; /// auxiliary counter which helps us to know how many keys are left on map

    bool replay; /// if true replay mode is active otherwise flase

    ofstream log; /// ofstream log file for writing
    
    /**
     * @brief Constructor of Map object
     * 
     * @param parent parent
     * @param map map file string
     * @param srcPath src directory path
     */
    explicit Map(MainWindow *parent = nullptr, std::string map = "map01.txt", QString srcPath = "", bool replay = false);
    
    /**
     * @brief Custom map destructor.
    */
    ~Map();

    /**
     * @brief Function which return wall, path, ghost etc.. pointer object based on x, y cooridinates
     * 
     * @param x x
     * @param y y
     * 
     * @return T Wall|Path|End|Ghost|Pacman|Key pointer object
     */
    Field* getField(int x, int y, FieldType calledBy);

    /**
     * @brief Function calls method which creates timers for pacman and ghosts.
     * 
     */
    void Start();

    /**
     * @brief Function which creates timers for pacman and ghosts.
     * 
     */
    void gameStart();

    /**
     * @brief Method which deletes key from map and decreases number of keys left etc..
     *
     * @param key pointer to Key Field
     */
    void deleteKey(Field *key);

    /**
     * @brief Method which deletes all objects from map
     */
    void deleteAll();

    /**
     * @brief Method which deletes hearth icon and decreases number of lives left etc..
     */
    void deleteLive();

    /**
     * @brief Method which delete all object and call function for creating win end game window.
     */
    void handleWin();

    /**
     * @brief Method which delete all object and call function for creating game over end game window.
     */
    void handleGameOver();

private slots:
    /**
     * @brief Method which handles pacman. It is called every DELAY ms.
     * 
     */
    void pacmanHandler();

    /**
     * @brief Method which handles ghost. It is called every DELAYGHOST ms.
     * 
     * @param ghostNum number of ghost
     */
    void ghostHandler(int ghostNum);

private:
    // attributes
    std::ifstream file; /// file with map
    int sizeOfBlock; /// size in px of one block (path, pacman, wall..)

    /** Temporary objects which are used for creating map */
    Wall *wall;
    Path *path;
    Ghost *ghost;
    Key *key;

    /** Timers */
    QTimer *pacman_timer;
    vector<QTimer*> ghost_timer;

    // methods

    /**
     * @brief Method which creates score label etc..
     */
    void createScore();

    /**
     * @brief Method which creates hearths icons etc..
     */
    void createLives();

    /**
     * @brief Method which restart positions of ghosts and pacman to default.
     */
    void restartPositions();

    /**
     * @brief Method which creates exit button.
     */
    void createExitButton();

    /**
     * @brief Method which is called after clicking exit button.
     */
    void handleExit();

    /**
     * @brief copyMap Method which copies map txt to log
     *
     * @param map map txt name
     * @param outputFile log file
     */
    void copyMap(string map, ofstream& outputFile);

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
