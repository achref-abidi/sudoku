#include "launcher.h"

using namespace std;

Launcher::Launcher(std::string dbPath, QWidget *parent) : QWidget(parent)
{
    // Set size of the window
    setFixedSize(300 , 300);

    this->dbPath = dbPath;
    variantsBox = new QComboBox(this);
    variantsBox->addItems({"Sudoku 6x6", "Sudoku 9x9"});
    variantsBox->setGeometry(300/2 - 183/2, 300/2 - 29/2 - 29 -20 , 183 , 29);

    levelBox = new QComboBox(this);
    levelBox->addItems({"Très Facile", "Facile", "Moyen", "Difficile", "Diabolique"});
    levelBox->setGeometry(300/2 - 183/2, 300/2-29/2 , 183 , 29);

    startBtn = new QPushButton("Commencer Le Jeu", this);
    startBtn->setGeometry(300/2 - 183/2, 300/2-29/2+29+20 , 183 , 29);
    connect(startBtn, SIGNAL(released()), this, SLOT(LaunchGame()));

    std::cout << dbPath << std::endl;
}

void Launcher::LaunchGame()
{

    Game* game;
    int variant, level = levelBox->currentIndex();

    switch (variantsBox->currentIndex()) {
    case 0 : //
        variant = 6;
        break;
    case 1:
        variant = 9;
        break;
    default:
        variant = 6;
        break;
    }

    game = new Game(variant, level, dbPath);
    QGraphicsView* view = new QGraphicsView(game);
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    view->show();

    this->close();
}
