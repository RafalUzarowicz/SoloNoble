#include "solonoble.h"
#include "./ui_solonoble.h"

SoloNoble::SoloNoble(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SoloNoble){

    ui->setupUi(this);
    // Setup window
    setWindowTitle("Solo Noble");

    QPixmap pixmap( ICON_SIZE, ICON_SIZE );
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setBrush(Qt::black);
    painter.setFont(QFont("Arial"));
    QFont font = painter.font();
    font.setPixelSize(ICON_SIZE*2/3);
    painter.setFont(font);
    painter.drawText(QRect(0, 0, ICON_SIZE, ICON_SIZE), Qt::AlignCenter, tr("SN"));
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
    connect(ui->actionSettings, &QAction::triggered, settingsDialog, &SettingsDialog::show);
    connect(ui->actionNewGame, &QAction::triggered, board, &Board::resetBoardAnimation);

    connect(&settingsDialog->currentSettings, &Settings::pawnColorChanged, &board->m_boardSettings, &Settings::setPawnColor);
    connect(&settingsDialog->currentSettings, &Settings::boardColorChanged, &board->m_boardSettings, &Settings::setBoardColor);
    connect(&settingsDialog->currentSettings, &Settings::boardColorChanged, this, &SoloNoble::updateBoardBackground);
    connect(&settingsDialog->currentSettings, &Settings::pawnHighlightColorChanged, &board->m_boardSettings, &Settings::setPawnHighlightColor);
    connect(&settingsDialog->currentSettings, &Settings::pawnMarkColorChanged, &board->m_boardSettings, &Settings::setPawnMarkColor);
    connect(&settingsDialog->currentSettings, &Settings::isEuropeanChanged, &board->m_boardSettings, &Settings::setEuropean);

    // Setup initial status
    updateScore(board->getScore());
}

SoloNoble::~SoloNoble(){
    delete ui;
    delete settingsDialog;
    delete endGameDialog;
    delete board;
}

void SoloNoble::updateScore(int score){
    QString message = QString("Pawns left: ") + QString::number(score);
    ui->statusBar->showMessage(message);
}

void SoloNoble::updateBoardBackground(QColor color){
    boardView->setBackgroundBrush(color);
    boardView->update();
}
