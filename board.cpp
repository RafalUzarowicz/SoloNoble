#include "board.h"

Board::Board()
{
    layout = new QGraphicsGridLayout;
    Hole* pawn = nullptr;
    for(int i = 0; i<49; ++i){
        pawn = new Hole();
        layout->addItem(pawn, i%7, i/7);
    }
    resetBoard();
    QGraphicsWidget *form = new QGraphicsWidget;
    form->setLayout(layout);
    addItem(form);
}

void Board::resetBoard(bool isEuropean){
    Hole* pawn = nullptr;
    for(int i = 0; i<49; ++i){
        int x = i%7;
        int y = i/7;
        pawn = (Hole*)layout->itemAt(i);
        if((y>1 && y<5) || (x>1 && x<5) || (isEuropean && ((x==1&&y==1) || (x==1&&y==5) || (x==5&&y==1)|| (x==5&&y==5)))){
            pawn->setEnabled(true);
            pawn->setVisible(true);
        }else{
            pawn->setVisible(false);
            pawn->setEnabled(false);
        }
    }

    setMoves();
}

void Board::setMoves(){
    Hole* pawn = nullptr;
    for(int i = 0; i<49; ++i){
        int x = i%7;
        int y = i/7;
        pawn = (Hole*)layout->itemAt(i);
        QVector<Hole*>& moves = pawn->getMoves();

        moves.clear();

        int tempX = x-2;
        if(tempX>=0 && tempX<7){
            pawn = (Hole*)layout->itemAt(tempX + y*7);
            if(pawn->isEnabled()){
                moves.push_back(pawn);
            }
        }
        tempX = x+2;
        if(tempX<7){
            pawn = (Hole*)layout->itemAt(tempX + y*7);
            if(pawn->isEnabled()){
                moves.push_back(pawn);
            }
        }

        int tempY = y-2;
        if(tempY>=0){
            pawn = (Hole*)layout->itemAt(x + tempY*7);
            if(pawn->isEnabled()){
                moves.push_back(pawn);
            }
        }
        tempY = y+2;
        if(tempY<7){
            pawn = (Hole*)layout->itemAt(x + tempY*7);
            if(pawn->isEnabled()){
                moves.push_back(pawn);
            }
        }
    }
}
