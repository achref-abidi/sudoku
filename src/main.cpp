#include <string>
#include <QApplication>
#include "launcher.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    /*size_t pos;
    int p= 0 ;
    std::string str = argv[0];
    while((pos = str.find("\\")) != std::string::npos){
        str = str.erase(0, pos+1);
        p += pos+1;
    }

    std::string dbPath;

    dbPath = argv[0];
    dbPath = dbPath.substr(0, p) + "db.txt";*/
    std::string dbPath("../../db.txt");

    std::cout << dbPath << std::endl;

    Launcher window(dbPath);
    window.show();



    return a.exec();
}
