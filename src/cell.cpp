#include "cell.h"

Cell::Cell()
{
    setFixedSize(cellSize, cellSize);
    setAlignment(Qt::AlignHCenter);
    setValidator(new QRegularExpressionValidator(QRegularExpression("[1-9]*")));
    setMaxLength(4);
}

void Cell::setText(QString text)
{
    if(!isReadOnly()){
        setStyleSheet("QLineEdit{ border: 1px solid #000000;color: white;image: url(:/img/Cell01.png);}");
    }else{
        setStyleSheet("QLineEdit{ border: 1px solid #000000;color: black;font-weight:bold;font-size:12px;image: url(:/img/Cell01.png);}");
    }
    QLineEdit::setText(text);
}

void Cell::setColor(QString color = "")
{
    if(color == "red"){
        setStyleSheet("QLineEdit{border: 1px solid #000000;color:white;image: url(:/img/Cell02.png);}");
    }else if(color == "green"){
        setStyleSheet("QLineEdit{border: 1px solid #000000;color:white;image: url(:/img/Cell03.png);}");
    }else{
        setStyleSheet("QLineEdit{border: 1px solid #000000;color:white;image: url(:/img/Cell01.png);}");
    }
}

int Cell::getCellSize()
{
    return cellSize;
}

void Cell::focusInEvent(QFocusEvent *e)
{
    if(!isReadOnly())
        QLineEdit::setStyleSheet("QLineEdit{ border: 1px solid #000000;color: white;image: url(:/img/Cell04.png);}");
    QLineEdit::focusInEvent(e);
}

void Cell::focusOutEvent(QFocusEvent *e)
{
    if(!isReadOnly()){
        QLineEdit::setStyleSheet("QLineEdit{ border: 1px solid #000000;color: white;image: url(:/img/Cell01.png);}");
    }else{
        QLineEdit::setStyleSheet("QLineEdit{ border: 1px solid #000000;color: black;image: url(:/img/Cell01.png);}");
    }
        QLineEdit::focusOutEvent(e);

}
