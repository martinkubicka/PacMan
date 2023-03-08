#include "map.h"
#include "mainwindow.h"

#include <iostream> //todo remove me

Map::Map(QWidget *parent, std::string map) : QWidget(parent) {
    this->file.open(map);

    if (!this->file.is_open()) {
        std::cerr << "Failed to open file.\n";
        exit(EXIT_FAILURE);
    }

    parent->setStyleSheet("background-color: black;");

    this->getSizeOfBlock();

    this->createMap();

    // TODO + postup

    // vo for cykle generovat jednotlive veci a volat a pridavat

    // vygeneruj zdi vzdy ak novy riadok alebo koniec alebo top alebo EOF (pozor kedy a ci neni viac \n\n!!)

    // special constructor na start/end block
}

Map::~Map() {
    this->file.close();
}

std::string Map::getWord() {
    std::string word;
    char ch;
    while (file.get(ch) && !std::isspace(ch)) {
        word += ch;
    }

    return word;
}

void Map::getSizeOfBlock() {
    try {
        this->y = std::stoi(this->getWord());
        this->x = std::stoi(this->getWord());
    } catch (const std::exception& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    if (this->x > this->y) {
        this->sizeOfBlock = (HEIGHT - EDGE_OFFSET*2) / (this->x + 2); // *2 - both sides, + 2 default walls
    } else {
        this->sizeOfBlock = (HEIGHT - EDGE_OFFSET*2) / (this->y + 2); // *2 - both sides, + 2 default walls
    }
}

void Map::createMap() {
    //todo
}

