#include "game.h"

using namespace std;

Game::Game(int variant, int l, string dbPath)
{
    gridSize = variant;
    level = l;
    this->dbPath = dbPath;
    getConfig();

    if(gridSize == 6){
        subGridSize[0] = 2;
        subGridSize[1] = 3;
    }else{
        subGridSize[0] = sqrt(gridSize);
        subGridSize[1] = sqrt(gridSize);
    }

    grid = new Cell[gridSize * gridSize];
    setGrid();


    QPixmap pixFondEcran;
    pixFondEcran.load(":/img/panel.jpg");
    QGraphicsScene::setBackgroundBrush(pixFondEcran);

    QGraphicsTextItem* label;
    QFont font("Calibri", 13);
    label = new QGraphicsTextItem(QString("Sudoku"));
    label->setFont(font);
    label->setDefaultTextColor(QColor(196,129,42));
    label->setPos(16, 12);
    QGraphicsScene::addItem(label);


    float posx = 16;
    float posy = 57.5;

    QPushButton* newButton = new QPushButton("nouvelle grille");
    QGraphicsScene::addWidget(newButton);
    newButton->setGeometry(posx, posy + 0*35 , 183 , 29);
    connect(newButton, &QPushButton::released, this, &Game::FillGrid);
    newButton->setStyleSheet("QPushButton{border: 1px solid #000000;color: white;font-weight:bold;text-transform:uppercase;font-size: 12px;background-image:url(:/img/Button01.png);}");


    QPushButton* validateButton = new QPushButton("Valider");
    QGraphicsScene::addWidget(validateButton);
    validateButton->setGeometry(posx, posy + 1*35 , 183 , 29);
    connect(validateButton, &QPushButton::released, this, &Game::validateGrid);
    validateButton->setStyleSheet("QPushButton{border: 1px solid #000000;color: white;font-weight:bold;text-transform:uppercase;font-size: 12px;background-image:url(:/img/Button01.png);}");

    QPushButton* resetButton = new QPushButton("effacer");
    QGraphicsScene::addWidget(resetButton);
    resetButton->setGeometry(posx , posy + 2*35 , 183 , 29);
    connect(resetButton, &QPushButton::released, this, &Game::reSet);
    resetButton->setStyleSheet("QPushButton{border: 1px solid #000000;color: white;font-weight:bold;text-transform:uppercase;font-size: 12px;background-image:url(:/img/Button01.png);}");

    QPushButton* solveButton = new QPushButton("solution");
    QGraphicsScene::addWidget(solveButton);
    solveButton->setGeometry(posx  , posy+ 3* 35 , 183 , 29);
    connect(solveButton, &QPushButton::released, this, &Game::solve);
    solveButton->setStyleSheet("QPushButton{border: 1px solid #000000;color: white;font-weight:bold;text-transform:uppercase;font-size: 12px;background-image:url(:/img/Button01.png);}");


    const int margin = 1;
    const int QlineEditSize = 53;
    float x = 250;
    float y = 75;
    const int gridLength = QlineEditSize * gridSize + (gridSize - 1) * margin;
    QGraphicsScene::setSceneRect(0,0, gridLength +x +16, y+ gridLength +16 );

}

Game::~Game()
{
    delete [] grid;
}

void Game::setGrid()
{
    const int QlineEditSize = 53;
    const int margin = 1;
    const int gridLength = QlineEditSize * gridSize + (gridSize - 1) * margin;
    int posx = 250;
    int posy = 75;

    for(int l=0; l < gridSize*gridSize; l++){
        if(configStr[l] == '.'){
            grid[l].setText("");
        }else{
            grid[l].setReadOnly(true);
            grid[l].setText(QString(configStr[l]));
        }

        QGraphicsProxyWidget* wdj = QGraphicsScene::addWidget(grid + l);
        int i = floor(l/ gridSize);
        int j = l - i * gridSize;
        wdj->setPos(j*(QlineEditSize) +250,i*(QlineEditSize) +75);

    }

    QPen line(QBrush(QColor(42,54,60)), 2);
    // Add the vertical lines first
    for (int j=1; j< subGridSize[1]; j++){
        int alpha = j * subGridSize[1] * QlineEditSize;
        QGraphicsScene::addLine(alpha + posx , posy + 1 , alpha + posx, gridLength - gridSize *1 + posy  , line);
    }
    // Now add the horizontal lines
    for (int i =1 ; i< subGridSize[0]; i++){
        int alpha = i * subGridSize[0] * QlineEditSize;
        QGraphicsScene::addLine(posx + 1, alpha + posy, gridLength - gridSize *1 + posx, alpha + posy, line);
    }
}

void Game::validateGrid()
{
    for(int l=0; l < gridSize * gridSize; l++){
        if(configStr[l] == '.'){
            if(grid[l].text() == solutionStr[l]){
                grid[l].setColor("green");
            }else{
                grid[l].setColor("red");
            }
        }
    }
}

void Game::solve()
{
    for(int l=0; l < gridSize*gridSize; l++){
        if(configStr[l] == '.'){
            grid[l].setText(QString(solutionStr[l]));
        }
    }
}

void Game::reSet()
{
    for(int l=0; l < gridSize*gridSize; l++){
        if(configStr[l] == '.'){
            grid[l].setText("");
        }
    }
}

void Game::FillGrid()
{
    getConfig();
    for(int l=0; l < gridSize*gridSize; l++){
        if(configStr[l] == '.'){
            grid[l].setReadOnly(false);
            grid[l].setText("");
        }else{
            grid[l].setReadOnly(true);
            grid[l].setText(QString(configStr[l]));
        }
    }
}

void Game::getConfig()
{
    std::ifstream dataBase;
    dataBase.open(dbPath);

    string ligne;
    vector<string> configArr;
    vector<string> solutionArr;
    while(getline(dataBase,ligne)){
        size_t pos;
        string str;
        vector<string> strArr;
        while ((pos = ligne.find(" ")) != std::string::npos) {
            str = ligne.substr(0, pos);
            ligne.erase(0, pos + 1);
            strArr.push_back(str);
        }
        strArr.push_back(ligne);

        if (stoi(strArr.at(0)) == gridSize && stoi(strArr.at(1)) == level) {
            configArr.push_back(strArr.at(2));
            solutionArr.push_back(strArr.at(3));
        }
    }

    dataBase.clear();
    cout << "### chosen config str:" << endl ;
    for(auto i : configArr){
        cout << i << endl;
    }

    int index = rand() % configArr.size();
    configStr = configArr.at(index);
    solutionStr = solutionArr.at(index);
    //cout << ">>" <<  configStr << " :: " << solutionStr << endl;
}
