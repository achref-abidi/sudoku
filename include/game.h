#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <vector>
#include<iostream>
#include<cmath>
#include<string>

#include <QGraphicsScene>
#include <QLineEdit>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QGraphicsTextItem>

#include "cell.h"


class Game: public QGraphicsScene
{
public:
    Game(int variant, int level, std::string dbPath);
    virtual ~Game();
    void setGrid();
    void getConfig();

public slots:
    void FillGrid();
    void validateGrid();
    void solve();
    void reSet();

private:
    std::string configStr;
    std::string solutionStr;
    Cell* grid ;
    int level;
    int gridSize;
    int subGridSize[2];
    std::string dbPath;

};

#endif // GAME_H
