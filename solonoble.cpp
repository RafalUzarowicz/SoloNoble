#include "solonoble.h"
#include "./ui_solonoble.h"

SoloNoble::SoloNoble(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SoloNoble)
{
    ui->setupUi(this);

    setWindowTitle("Solo Noble");

    board = new Board();

    boardView = new BoardView();
    boardView->setScene(board);

    ui->centralwidget->layout()->addWidget(boardView);

    settingsDialog = new SettingsDialog();
    settingsDialog->setWindowTitle("Game settings");

    connect(board, &Board::scoreChanged, this, &SoloNoble::updateScore);
    connect(ui->action_Settings, &QAction::triggered, settingsDialog, &SettingsDialog::show);

    updateScore(board->getScore());


}

SoloNoble::~SoloNoble()
{
    delete ui;
}

void SoloNoble::updateScore(int score){
    QString message = QString("Pawns left: ") + QString::number(score);
    ui->statusBar->showMessage(message);
}

void SoloNoble::newGame(){

}
