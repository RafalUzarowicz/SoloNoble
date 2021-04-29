#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsScene>
#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include "hole.h"

class Board : public QGraphicsScene
{
    Q_OBJECT
public:
    Board(int = 7);

public:
    void resetBoard(bool = false);

signals:
    void clearSelection();

public slots:
    void newTileSelected(Hole* newTile){
        disconnect(this, &Board::clearSelection, newTile, &Hole::deselect);
        emit clearSelection();
        connect(this, &Board::clearSelection, newTile, &Hole::deselect);
    }

    void removePawns(int target, int source){
        int x1 = target%boardSize;
        int y1 = target/boardSize;
        int x2 = source%boardSize;
        int y2 = source/boardSize;

        int betweenX = (x1+x2)/2;
        int betweenY = (y1+y2)/2;

        Hole* pawn = (Hole*)layout->itemAt(boardSize*betweenY + betweenX);
        pawn->removePawn();

        pawn = (Hole*)layout->itemAt(boardSize*y2 + x2);
        pawn->removePawn();
    }

private:
    void initialBoard();

    QGraphicsGridLayout *layout;
    void setNeighboursConnection();
    bool isTileOnBoard(const int&, const int&, const bool& = false);
    int boardSize;
};

#endif // BOARD_H
