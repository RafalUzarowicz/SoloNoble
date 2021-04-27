#ifndef SOLONOBLE_H
#define SOLONOBLE_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include "board.h"
#include "boardview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SoloNoble; }
QT_END_NAMESPACE

class SoloNoble : public QMainWindow
{
    Q_OBJECT

public:
    SoloNoble(QWidget *parent = nullptr);
    ~SoloNoble();

private:
    Ui::SoloNoble *ui;
    Board* board;
};
#endif // SOLONOBLE_H
