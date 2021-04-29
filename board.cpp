#include "board.h"

Board::Board(int size) : boardSize(size)
{
    layout = new QGraphicsGridLayout;
    Hole* pawn = nullptr;
    for(int i = 0; i<boardSize*boardSize; ++i){
        pawn = new Hole(i);
        layout->addItem(pawn, i%boardSize, i/boardSize);
    }
    QGraphicsWidget *form = new QGraphicsWidget;
    form->setLayout(layout);
    addItem(form);
    initialBoard();
    setNeighboursConnection();
}

bool Board::isTileOnBoard(const int& x, const int& y, const bool& isEuropean){
//    return (y>1 && y<5) || (x>1 && x<5) || (isEuropean && ((x==1&&y==1) || (x==1&&y==5) || (x==5&&y==1)|| (x==5&&y==5)));
    return true;
}

void Board::initialBoard(){
    Hole* pawn = nullptr;
    for(int i = 0; i<boardSize*boardSize; ++i){
        int x = i%boardSize;
        int y = i/boardSize;
        pawn = (Hole*)layout->itemAt(i);
        if(isTileOnBoard(x, y)){
            pawn->setEnabled(true);
            pawn->setVisible(true);
            connect(this, &Board::clearSelection, pawn, &Hole::deselect);
            connect(pawn, &Hole::tileSelected, this, &Board::newTileSelected);
            connect(pawn, &Hole::removePawns, this, &Board::removePawns);
        }else{
            pawn->setVisible(false);
            pawn->setEnabled(false);
        }
    }
    pawn = (Hole*)layout->itemAt(boardSize*boardSize/2);
    pawn->isOccupied = false;
}

void Board::resetBoard(bool isEuropean){
    Hole* pawn = nullptr;
    for(int i = 0; i<boardSize*boardSize; ++i){
        int x = i%boardSize;
        int y = i/boardSize;
        pawn = (Hole*)layout->itemAt(i);
        if(isTileOnBoard(x, y, isEuropean)){
            pawn->setEnabled(true);
            pawn->setVisible(true);
            connect(this, &Board::clearSelection, pawn, &Hole::deselect);
            connect(pawn, &Hole::tileSelected, this, &Board::newTileSelected);
        }else{
            pawn->setVisible(false);
            pawn->setEnabled(false);
            disconnect(this, &Board::clearSelection, pawn, &Hole::deselect);
            disconnect(pawn, &Hole::tileSelected, this, &Board::newTileSelected);
        }
    }
}

void Board::setNeighboursConnection(){
    Hole* mainPawn = nullptr;
    Hole* pawn = nullptr;
    for(int i = 0; i<boardSize*boardSize; ++i){
        int x = i%boardSize;
        int y = i/boardSize;
        mainPawn = (Hole*)layout->itemAt(i);

        int tempX = x-2;
        if(tempX>=0){
            pawn = (Hole*)layout->itemAt(tempX + y*7);
            if(pawn->isEnabled()){
                connect(mainPawn, &Hole::highlightMoves, pawn, &Hole::highlightTile);
                connect(mainPawn, &Hole::markPossibleMoves, pawn, &Hole::markMovePossibility);
                connect(mainPawn, &Hole::unmarkPossibleMoves, pawn, &Hole::unmarkMovePossibility);
            }
        }
        tempX = x+2;
        if(tempX<boardSize){
            pawn = (Hole*)layout->itemAt(tempX + y*7);
            if(pawn->isEnabled()){
                connect(mainPawn, &Hole::highlightMoves, pawn, &Hole::highlightTile);
                connect(mainPawn, &Hole::markPossibleMoves, pawn, &Hole::markMovePossibility);
                connect(mainPawn, &Hole::unmarkPossibleMoves, pawn, &Hole::unmarkMovePossibility);
            }
        }

        int tempY = y-2;
        if(tempY>=0){
            pawn = (Hole*)layout->itemAt(x + tempY*7);
            if(pawn->isEnabled()){
                connect(mainPawn, &Hole::highlightMoves, pawn, &Hole::highlightTile);
                connect(mainPawn, &Hole::markPossibleMoves, pawn, &Hole::markMovePossibility);
                connect(mainPawn, &Hole::unmarkPossibleMoves, pawn, &Hole::unmarkMovePossibility);
            }
        }
        tempY = y+2;
        if(tempY<boardSize){
            pawn = (Hole*)layout->itemAt(x + tempY*7);
            if(pawn->isEnabled()){
                connect(mainPawn, &Hole::highlightMoves, pawn, &Hole::highlightTile);
                connect(mainPawn, &Hole::markPossibleMoves, pawn, &Hole::markMovePossibility);
                connect(mainPawn, &Hole::unmarkPossibleMoves, pawn, &Hole::unmarkMovePossibility);
            }
        }
    }
}
