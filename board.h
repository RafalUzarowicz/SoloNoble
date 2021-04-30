#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsScene>
#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include "tile.h"

class Board : public QGraphicsScene
{
    Q_OBJECT

    Q_PROPERTY(int score READ getScore WRITE setScore NOTIFY scoreChanged)
public:
    Board(int = 7);

public:
    void resetBoard(bool = false);

    int getScore() const{
        return score;
    }

    void setScore(int newScore){
        score = newScore;
    }

signals:
    void clearSelection();
    void scoreChanged(int);

public slots:
    void newTileSelected(Tile*);
    void removePawns(int, int);
    void updateScore();

private:
    void initialBoard();
    void connectPawns(Tile*, Tile*, Tile*, bool);
    bool isGameEnding();

    inline bool isMovePossible(Tile*, Tile*, Tile*) const;

    QGraphicsGridLayout *layout;
    QGraphicsWidget *form;
    void setNeighboursConnection();
    bool isTileOnBoard(const int&, const int&, const bool& = false);
    int boardSize;
    Tile* selectedTile;

    int score;
};

#endif // BOARD_H
