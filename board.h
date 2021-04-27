#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsScene>
#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include "hole.h"

class Board : public QGraphicsScene
{
public:
    Board();

public:
    void resetBoard(bool isEuropean = false);

private:
    QGraphicsGridLayout *layout;
    void setMoves();
};

#endif // BOARD_H
