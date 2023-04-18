#ifndef CELL_H
#define CELL_H

#include <QLineEdit>
#include<QFocusEvent>
#include <QRegularExpressionValidator>

class Cell: public QLineEdit
{
    Q_OBJECT
public:
    Cell();
    void setText(QString text);
    void setColor(QString color);
    int getCellSize();

protected:
   void focusInEvent(QFocusEvent* e);
   void focusOutEvent(QFocusEvent *e);

private:
   const int cellSize = 53;
};

#endif // CELL_H
