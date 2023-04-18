#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QWidget>
#include <QGraphicsView>
#include <QPushButton>
#include <QComboBox>
#include <iostream>
#include "game.h"


class Launcher : public QWidget
{
    Q_OBJECT
public:
    explicit Launcher(std::string dbPath, QWidget *parent = nullptr);

public slots:
    void LaunchGame();

private:
    QPushButton* startBtn;
    QComboBox* variantsBox;
    QComboBox* levelBox;

    std::string dbPath;
};

#endif // LAUNCHER_H
