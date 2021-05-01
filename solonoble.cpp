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

    boardView->setBackgroundBrush(board->m_boardSettings.boardColor());

    ui->centralwidget->layout()->addWidget(boardView);

    settingsDialog = new SettingsDialog();
    settingsDialog->setWindowTitle("Game settings");
    settingsDialog->setModal(true);

    connect(board, &Board::scoreChanged, this, &SoloNoble::updateScore);
    connect(board, &Board::sendGameStateMessage, this, &SoloNoble::updateStatusMessage);
    connect(ui->action_Settings, &QAction::triggered, settingsDialog, &SettingsDialog::show);
    connect(ui->actionNew_game, &QAction::triggered, board, &Board::resetBoard);

    connect(&settingsDialog->currentSettings, &Settings::pawnColorChanged, &board->m_boardSettings, &Settings::setPawnColor);
    connect(&settingsDialog->currentSettings, &Settings::boardColorChanged, &board->m_boardSettings, &Settings::setBoardColor);
    connect(&settingsDialog->currentSettings, &Settings::boardColorChanged, this, &SoloNoble::updateBoardBackground);
    connect(&settingsDialog->currentSettings, &Settings::pawnHighlightColorChanged, &board->m_boardSettings, &Settings::setPawnHighlightColor);
    connect(&settingsDialog->currentSettings, &Settings::pawnMarkColorChanged, &board->m_boardSettings, &Settings::setPawnMarkColor);
    connect(&settingsDialog->currentSettings, &Settings::isEuropeanChanged, &board->m_boardSettings, &Settings::setEuropean);

    updateScore(board->getScore());
}

SoloNoble::~SoloNoble()
{
    settingsDialog->close();
    delete ui;
}

void SoloNoble::updateScore(int score){
    QString message = QString("Pawns left: ") + QString::number(score);
    ui->statusBar->showMessage(message);
}

void SoloNoble::updateStatusMessage(QString message){
    ui->statusBar->showMessage(message);
}

void SoloNoble::updateBoardBackground(QColor color){
    boardView->setBackgroundBrush(color);
    boardView->update();
}
