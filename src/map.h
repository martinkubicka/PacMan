#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <string>
#include <fstream>
#include "mainwindow.h"


#define EDGE_OFFSET 20

class Map : public QWidget
{
public:
    explicit Map(QWidget *parent = nullptr, std::string map = "map01.txt");
    ~Map();
private:
    std::ifstream file;
    int sizeOfBlock;
    int numberOfKeysLeft = 0;
    int x, y;

    void getSizeOfBlock();
    std::string getWord();
    void createMap();
};

#endif // MAP_H
