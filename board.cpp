#include "board.h"

Board::Board(int size) : boardSize(size), m_boardSettings(), selectedTile(nullptr),  score(0)
{
    // Create pawns
    layout = new QGraphicsGridLayout;
    Tile* pawn{};
    int x{};
    int y{};
    for(int i{}; i<boardSize*boardSize; ++i){
        x = i%boardSize;
        y = i/boardSize;
        pawn = new Tile();
        layout->addItem(pawn, y, x);
        connect(&m_boardSettings, &Settings::pawnColorChanged, pawn, &Tile::setPawnColor);
        connect(&m_boardSettings, &Settings::pawnHighlightColorChanged, pawn, &Tile::setHighlightColor);
        connect(&m_boardSettings, &Settings::pawnMarkColorChanged, pawn, &Tile::setMarkColor);
    }
    // Setup connections
    connect(&m_boardSettings, &Settings::isEuropeanChanged, this, &Board::changeBoardType);
    // Set pawns
    initialBoard();
    setNeighboursConnection();
    // Widget used to store layout
    form = new QGraphicsWidget;
    form->setLayout(layout);
    addItem(form);
    form->adjustSize();
    // Animations tile
    animationTile = new Tile();
    animationTile->setPos(((Tile*) layout->itemAt(0))->pos());
    animationTile->setVisible(false);
    addItem(animationTile);

    connect(&m_boardSettings, &Settings::pawnColorChanged, animationTile, &Tile::setPawnColor);
    connect(&m_boardSettings, &Settings::pawnHighlightColorChanged, animationTile, &Tile::setHighlightColor);
    connect(&m_boardSettings, &Settings::pawnMarkColorChanged, animationTile, &Tile::setMarkColor);

    // Animations setup


    /*
     * 1. move animation pawn to selected pawn
     * 2. make selected pawn invisible
     * 3. move animation pawn to middle pawn
     * 4. make middle pawn invisible
     * 5. move animation pawn to target pawn
     * 6. make target pawn visible
     * 7. make animation pawn invisible
     */
}

int Board::getScore() const{
    return score;
}

void Board::setScore(int newScore){
    score = newScore;
}

void Board::selectNewTile(Tile* newSelectedTile){
    // Remove old selection
    if(selectedTile){
        selectedTile->select(false);
        selectedTile->update();
        markMoves(false);
    }
    // Update selection
    selectedTile = newSelectedTile;
    selectedTile->select(true);
    markMoves(true);
    selectedTile->update();


}

void Board::tryMovingPawn(Tile* emptySelectedTile){
    // Check if move is possible
    Tile* pawn = emptySelectedTile;
    if(selectedTile){
        Tile* closeNeighbour{};
        for(int i{}; i<selectedTile->m_closeNeighbours.size(); ++i){
            closeNeighbour = selectedTile->m_closeNeighbours.at(i);
            if(selectedTile->m_farNeighbours.at(i) == pawn && isMovePossible(selectedTile, closeNeighbour, pawn)){
                // Remove old selection
                selectedTile->select(false);
                markMoves(false);
                // Remove pawns
                selectedTile->occupied(false);
                selectedTile->update();
                closeNeighbour->occupied(false);
                closeNeighbour->update();
                // Move pawn and select
                selectedTile = pawn;
                selectedTile->select(true);
                selectedTile->occupied(true);
                selectedTile->update();
                // Set new score
                updateScore();
                // New marking
                markMoves(true);
                return;
            }
        }
    }
}

void Board::highlightMoves(bool doHighlight){
    Tile* pawn = (Tile*)QObject::sender();
    if(pawn){
        Tile* pawnToHighlight{};
        for (int i{}; i<pawn->m_closeNeighbours.size(); ++i) {
            pawnToHighlight = pawn->m_farNeighbours.at(i);
            // Highlight if move is possible
            if(isMovePossible(pawn, pawn->m_closeNeighbours.at(i), pawnToHighlight)){
                pawnToHighlight->highlight(doHighlight);
                pawnToHighlight->update();
            }
        }
    }
}

void Board::markMoves(bool doMark){
    if(selectedTile){
        Tile* pawnToHighlight{};
        for (int i{}; i<selectedTile->m_closeNeighbours.size(); ++i) {
            pawnToHighlight = selectedTile->m_farNeighbours.at(i);
            // Mark if move is possible
            if(isMovePossible(selectedTile, selectedTile->m_closeNeighbours.at(i), pawnToHighlight)){
                pawnToHighlight->mark(doMark);
                pawnToHighlight->update();
            }
        }
    }
}

bool Board::isTileOnBoard(const int& x, const int& y){
    int uppedBound = boardSize-2;
    return (y>1 && y<uppedBound) ||
           (x>1 && x<boardSize-2) ||
           (
               m_boardSettings.isEuropean() &&
               (
                   (x==1&&y==1) ||
                   (x==1&&y==(uppedBound)) ||
                   (x==(uppedBound)&&y==1)||
                   (x==uppedBound&&y==uppedBound)
                )
           );
}

void Board::initialBoard(){
    Tile* pawn = nullptr;
    // Setup pawns signals
    for(int i = 0; i<boardSize*boardSize; ++i){
        pawn = (Tile*)layout->itemAt(i);
        connect(pawn, &Tile::tileSelected, this, &Board::selectNewTile);
        connect(pawn, &Tile::emptyTileSelected, this, &Board::tryMovingPawn);
        connect(pawn, &Tile::tileHoverChanged, this, &Board::highlightMoves);
    }
    // Set board to initial state
    resetBoard();
}

void Board::resetBoard(){
    // Reset all pawns
    if(selectedTile){
        selectedTile->select(false);
        selectedTile = nullptr;
    }
    score = 0;
    Tile* pawn = nullptr;
    for(int i = 0; i<boardSize*boardSize; ++i){
        int x = i%boardSize;
        int y = i/boardSize;
        pawn = (Tile*)layout->itemAt(i);
        if(isTileOnBoard(x, y)){
            ++score;
            pawn->setEnabled(true);
            pawn->setVisible(true);
            pawn->occupied(true);
            pawn->highlight(false);
            pawn->mark(false);
        }else{
            pawn->setVisible(false);
            pawn->setEnabled(false);
        }
    }
    // Remove middle pawn
    pawn = (Tile*)layout->itemAt(boardSize*boardSize/2);
    pawn->occupied(false);
    --score;
    // Update view
    setBackgroundBrush(Qt::transparent);
    emit scoreChanged(score);
}

void Board::createPawnNeighbourhood(Tile* mainPawn, Tile* closePawn, Tile* farPawn){
    // Connect pawn with his neighbours
    if(closePawn->isEnabled()){
        mainPawn->m_closeNeighbours.emplace_back(closePawn);
        mainPawn->m_farNeighbours.emplace_back(farPawn);
    }
}

void Board::updateScore(){
    // Update score
    --score;
    emit scoreChanged(score);
    // Check end conditions
    if(isGameEnding()){
        emit gameEnd(score);
    }
}

bool Board::isGameEnding(){
    Tile* mainPawn{};
    Tile* closePawn{};
    Tile* farPawn{};
    // Check if any pawn has any move
    for(int i = 0; i<boardSize*boardSize; ++i){
        mainPawn = (Tile*)layout->itemAt(i);
        if(mainPawn->isEnabled()){
            for(int j{}; j<mainPawn->m_closeNeighbours.size(); ++j){
                closePawn = mainPawn->m_closeNeighbours.at(j);
                farPawn = mainPawn->m_farNeighbours.at(j);
                if(isMovePossible(mainPawn, closePawn, farPawn)){
                    return false;
                }
            }
        }
    }
    return true;
}

bool Board::isMovePossible(Tile* sourcePawn, Tile* middlePawn, Tile* targetPawn) const{
    return sourcePawn->m_isOccupied && middlePawn->m_isOccupied && !targetPawn->m_isOccupied;
}

void Board::setNeighboursConnection(){
    Tile* mainPawn{};
    Tile* closePawn{};
    Tile* farPawn{};
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
            closePawn = (Tile*)layout->itemAt(tempX + y*boardSize);
            farPawn = (Tile*)layout->itemAt(tempX+1 + y*boardSize);
            createPawnNeighbourhood(mainPawn, farPawn, closePawn);
        }
        tempX = x+2;
        if(tempX<boardSize){
            closePawn = (Tile*)layout->itemAt(tempX + y*7);
            farPawn = (Tile*)layout->itemAt(tempX-1 + y*boardSize);
            createPawnNeighbourhood(mainPawn, farPawn, closePawn);
        }

        tempY = y-2;
        if(tempY>=0){
            closePawn = (Tile*)layout->itemAt(x + tempY*7);
            farPawn = (Tile*)layout->itemAt(x + (tempY+1)*boardSize);
            createPawnNeighbourhood(mainPawn, farPawn, closePawn);
        }
        tempY = y+2;
        if(tempY<boardSize){
            closePawn = (Tile*)layout->itemAt(x + tempY*7);
            farPawn = (Tile*)layout->itemAt(x + (tempY-1)*boardSize);
            createPawnNeighbourhood(mainPawn, farPawn, closePawn);
        }
    }
}

void Board::changeBoardType(bool isEuropean){
    Q_UNUSED(isEuropean);
    resetBoard();
}
