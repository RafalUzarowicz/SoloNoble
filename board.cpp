#include "board.h"

Board::Board(int size) : boardSize(size), selectedTile(nullptr), score(0)
{
    setBackgroundBrush(Qt::green);
    layout = new QGraphicsGridLayout;
    Tile* pawn = nullptr;
    for(int i = 0; i<boardSize*boardSize; ++i){
        pawn = new Tile(i);
        layout->addItem(pawn, i%boardSize, i/boardSize);
    }
    initialBoard();
    setNeighboursConnection();
    form = new QGraphicsWidget;
    form->setLayout(layout);
    addItem(form);
    form->adjustSize();
}

void Board::newTileSelected(Tile* newTile){
    if(selectedTile){
        connect(this, &Board::clearSelection, selectedTile, &Tile::deselect);
        emit clearSelection();
        disconnect(this, &Board::clearSelection, selectedTile, &Tile::deselect);
    }
    selectedTile = newTile;
}

void Board::removePawns(int target, int source){
    int x1 = target%boardSize;
    int y1 = target/boardSize;
    int x2 = source%boardSize;
    int y2 = source/boardSize;

    int betweenX = (x1+x2)/2;
    int betweenY = (y1+y2)/2;

    Tile* pawn = (Tile*)layout->itemAt(boardSize*betweenY + betweenX);
    pawn->removePawn();

    pawn = (Tile*)layout->itemAt(boardSize*y2 + x2);
    pawn->removePawn();
}

bool Board::isTileOnBoard(const int& x, const int& y, const bool& isEuropean){
    return (y>1 && y<5) || (x>1 && x<5) || (isEuropean && ((x==1&&y==1) || (x==1&&y==5) || (x==5&&y==1)|| (x==5&&y==5)));
}

void Board::initialBoard(){
    Tile* pawn = nullptr;
    for(int i = 0; i<boardSize*boardSize; ++i){
        pawn = (Tile*)layout->itemAt(i);
        connect(pawn, &Tile::tileSelected, this, &Board::newTileSelected);
        connect(pawn, &Tile::removePawns, this, &Board::removePawns);
        connect(pawn, &Tile::updateScore, this, &Board::updateScore);
    }
    resetBoard();
}

void Board::resetBoard(bool isEuropean){
    score = 0;
    Tile* pawn = nullptr;
    for(int i = 0; i<boardSize*boardSize; ++i){
        int x = i%boardSize;
        int y = i/boardSize;
        pawn = (Tile*)layout->itemAt(i);
        if(isTileOnBoard(x, y, isEuropean)){
            ++score;
            pawn->setEnabled(true);
            pawn->setVisible(true);
            pawn->placePawn();
        }else{
            pawn->setVisible(false);
            pawn->setEnabled(false);
        }
    }
    pawn = (Tile*)layout->itemAt(boardSize*boardSize/2);
    pawn->removePawn();
    --score;
    setBackgroundBrush(Qt::green);
    emit scoreChanged(score);
}

void Board::connectPawns(Tile* mainPawn, Tile* middlePawn, Tile* movePawn, bool isHorizontal){
    if(isHorizontal){
        connect(mainPawn, &Tile::startHighlightSetH, middlePawn, &Tile::checkHighlightPossibilityH);
        connect(middlePawn, &Tile::continueHighlightSetH, movePawn, &Tile::highlightTileH);
    }else{
        connect(mainPawn, &Tile::startHighlightSetV, middlePawn, &Tile::checkHighlightPossibilityV);
        connect(middlePawn, &Tile::continueHighlightSetV, movePawn, &Tile::highlightTileV);
    }
    connect(mainPawn, &Tile::markPossibleMoves, movePawn, &Tile::markMovePossibility);
    connect(mainPawn, &Tile::unmarkPossibleMoves, movePawn, &Tile::unmarkMovePossibility);
}

void Board::updateScore(){
    --score;
    emit scoreChanged(score);

    if(isGameEnding()){
        setBackgroundBrush(Qt::red);
    }
}

bool Board::isGameEnding(){
    Tile* mainPawn{};
    Tile* movePawn{};
    Tile* middlePawn{};
    int x{};
    int y{};
    int tempX{};
    int tempY{};

    for(int i = 0; i<boardSize*boardSize; ++i){
        x = i%boardSize;
        y = i/boardSize;
        mainPawn = (Tile*)layout->itemAt(i);
        if(mainPawn->isEnabled()){
            tempX = x-2;
            if(tempX>=0){
                movePawn = (Tile*)layout->itemAt(tempX + y*boardSize);
                middlePawn = (Tile*)layout->itemAt(tempX+1 + y*boardSize);
                if(isMovePossible(mainPawn, middlePawn, movePawn)){
                    return false;
                }
            }
            tempX = x+2;
            if(tempX<boardSize){
                movePawn = (Tile*)layout->itemAt(tempX + y*7);
                middlePawn = (Tile*)layout->itemAt(tempX-1 + y*boardSize);
                if(isMovePossible(mainPawn, middlePawn, movePawn)){
                    return false;
                }
            }

            tempY = y-2;
            if(tempY>=0){
                movePawn = (Tile*)layout->itemAt(x + tempY*7);
                middlePawn = (Tile*)layout->itemAt(x + (tempY+1)*boardSize);
                if(isMovePossible(mainPawn, middlePawn, movePawn)){
                    return false;
                }
            }
            tempY = y+2;
            if(tempY<boardSize){
                movePawn = (Tile*)layout->itemAt(x + tempY*7);
                middlePawn = (Tile*)layout->itemAt(x + (tempY-1)*boardSize);
                if(isMovePossible(mainPawn, middlePawn, movePawn)){
                    return false;
                }
            }
        }
    }
    return true;
}

bool Board::isMovePossible(Tile* sourcePawn, Tile* middlePawn, Tile* targetPawn) const{
    return sourcePawn->isOccupied && middlePawn->isOccupied && !targetPawn->isOccupied;
}

void Board::setNeighboursConnection(){
    Tile* mainPawn{};
    Tile* movePawn{};
    Tile* middlePawn{};
    int x{};
    int y{};
    int tempX{};
    int tempY{};

    for(int i = 0; i<boardSize*boardSize; ++i){
        x = i%boardSize;
        y = i/boardSize;
        mainPawn = (Tile*)layout->itemAt(i);

        tempX = x-2;
        if(tempX>=0){
            movePawn = (Tile*)layout->itemAt(tempX + y*boardSize);
            middlePawn = (Tile*)layout->itemAt(tempX+1 + y*boardSize);
            if(movePawn->isEnabled()){
                connectPawns(mainPawn, middlePawn, movePawn, true);
            }
        }
        tempX = x+2;
        if(tempX<boardSize){
            movePawn = (Tile*)layout->itemAt(tempX + y*7);
            middlePawn = (Tile*)layout->itemAt(tempX-1 + y*boardSize);
            if(movePawn->isEnabled()){
                connectPawns(mainPawn, middlePawn, movePawn, true);
            }
        }

        tempY = y-2;
        if(tempY>=0){
            movePawn = (Tile*)layout->itemAt(x + tempY*7);
            middlePawn = (Tile*)layout->itemAt(x + (tempY+1)*boardSize);
            if(movePawn->isEnabled()){
                connectPawns(mainPawn, middlePawn, movePawn, false);
            }
        }
        tempY = y+2;
        if(tempY<boardSize){
            movePawn = (Tile*)layout->itemAt(x + tempY*7);
            middlePawn = (Tile*)layout->itemAt(x + (tempY-1)*boardSize);
            if(movePawn->isEnabled()){
                connectPawns(mainPawn, middlePawn, movePawn, false);
            }
        }
    }
}
