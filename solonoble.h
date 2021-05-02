#ifndef SOLONOBLE_H
#define SOLONOBLE_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include "board.h"
#include "boardview.h"
#include "settingsdialog.h"
#include "settings.h"
#include "endgamedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SoloNoble; }
QT_END_NAMESPACE

class SoloNoble : public QMainWindow
{
    Q_OBJECT

public:
    SoloNoble(QWidget* = nullptr);
    ~SoloNoble();

private:
    Ui::SoloNoble *ui;
    Board* board;
    BoardView* boardView;
    SettingsDialog* settingsDialog;
    EndGameDialog* endGameDialog;

public slots:
    void updateScore(int);
    void updateBoardBackground(QColor);
};
#endif // SOLONOBLE_H
