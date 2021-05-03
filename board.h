#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsScene>
#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include "tile.h"
#include "settings.h"

class SoloNoble;

class Board : public QGraphicsScene
{
    Q_OBJECT

    Q_PROPERTY(int score READ getScore WRITE setScore NOTIFY scoreChanged)
    Q_PROPERTY(Settings boardSettings)
public:
    Board(int = 7);

public:

    int getScore() const;

    void setScore(int);

signals:
    void clearSelection();
    void scoreChanged(int);
    void gameEnd(int);

public slots:
    void selectNewTile(Tile*);
    void tryMovingPawn(Tile*);
    void highlightMoves(bool);

    void resetBoardAnimation();

    void changeBoardType(bool);

private slots:
    void resetBoard();
    void onAnimationEnd();

private:
    void markMoves(bool);
    void updateScore();
    void initialBoard();
    void createPawnNeighbourhood(Tile*, Tile*, Tile*);
    bool isGameEnding();
    void movePawn(Tile*, Tile*);

    inline bool isMovePossible(Tile*, Tile*, Tile*) const;

    QGraphicsGridLayout *layout;
    QGraphicsWidget *form;
    void setNeighboursConnection();
    bool isTileOnBoard(const int&, const int&);
    int boardSize;

    Settings m_boardSettings;

    Tile* selectedTile;

    Tile* animationTile;
    int score;

    QSequentialAnimationGroup* pawnMoveAnimation;

    QPropertyAnimation* sourcePawnRemove;
    QPropertyAnimation* middlePawnRemove;
    QPropertyAnimation* targetPawnAnimation;

    QPropertyAnimation* animationTileShow;
    QPropertyAnimation* animationTileHide;

    QPropertyAnimation* movingAnimationToMiddle;
    QPropertyAnimation* movingAnimationToTarget;

    QParallelAnimationGroup* hideAllPawns;
    QParallelAnimationGroup* showAllPawns;

    friend class SoloNoble;
};

#endif // BOARD_H
