#include "solonoble.h"
#include "./ui_solonoble.h"

SoloNoble::SoloNoble(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SoloNoble)
{
    ui->setupUi(this);
    // Setup window
    setWindowTitle("Solo Noble");

    QPixmap pixmap( 32, 32 );
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setBrush(Qt::blue);
    painter.setFont(QFont("Arial"));
    QFont font = painter.font();
    font.setPixelSize(25);
    painter.setFont(font);
    painter.drawText(QRect(0, 0, 32, 32), Qt::AlignCenter, tr("SN"));
    setWindowIcon(QIcon(pixmap));

    // Setup board scene
    board = new Board();

    boardView = new BoardView();
    boardView->setScene(board);
    boardView->setBackgroundBrush(board->m_boardSettings.boardColor());

    ui->centralwidget->layout()->addWidget(boardView);

    // Setup settings dialog
    settingsDialog = new SettingsDialog();
    settingsDialog->setWindowTitle("Game settings");
    settingsDialog->setModal(true);
    // Setup end game dialog
    endGameDialog = new EndGameDialog();
    endGameDialog->setModal(true);

    // Setup connections
    connect(board, &Board::scoreChanged, this, &SoloNoble::updateScore);
    connect(board, &Board::gameEnd, endGameDialog, &EndGameDialog::showEndGame);
    connect(ui->action_Settings, &QAction::triggered, settingsDialog, &SettingsDialog::show);
    connect(ui->actionNew_game, &QAction::triggered, board, &Board::resetBoard);

    connect(&settingsDialog->currentSettings, &Settings::pawnColorChanged, &board->m_boardSettings, &Settings::setPawnColor);
    connect(&settingsDialog->currentSettings, &Settings::boardColorChanged, &board->m_boardSettings, &Settings::setBoardColor);
    connect(&settingsDialog->currentSettings, &Settings::boardColorChanged, this, &SoloNoble::updateBoardBackground);
    connect(&settingsDialog->currentSettings, &Settings::pawnHighlightColorChanged, &board->m_boardSettings, &Settings::setPawnHighlightColor);
    connect(&settingsDialog->currentSettings, &Settings::pawnMarkColorChanged, &board->m_boardSettings, &Settings::setPawnMarkColor);
    connect(&settingsDialog->currentSettings, &Settings::isEuropeanChanged, &board->m_boardSettings, &Settings::setEuropean);

    // Setup initial status
    updateScore(board->getScore());
}

SoloNoble::~SoloNoble()
{
    delete ui;
    delete settingsDialog;
    delete endGameDialog;
}

void SoloNoble::updateScore(int score){
    QString message = QString("Pawns left: ") + QString::number(score);
    ui->statusBar->showMessage(message);
}

void SoloNoble::updateBoardBackground(QColor color){
    boardView->setBackgroundBrush(color);
    boardView->update();
}
