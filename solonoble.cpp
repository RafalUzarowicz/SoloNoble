#include "solonoble.h"
#include "./ui_solonoble.h"

SoloNoble::SoloNoble(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SoloNoble)
{
    ui->setupUi(this);

    board = new Board();
    board->setBackgroundBrush(Qt::blue);

    BoardView* boardView = new BoardView();
    boardView->setBackgroundBrush(Qt::red);

    boardView->setScene(board);

    ui->centralwidget->layout()->addWidget(boardView);
    boardView->update();
//    ui->boardView->setScene(board);
}

SoloNoble::~SoloNoble()
{
    delete ui;
}

