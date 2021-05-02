#ifndef ENDGAMEDIALOG_H
#define ENDGAMEDIALOG_H

#include <QDialog>
#include <QPainter>

namespace Ui {
class EndGameDialog;
}

class EndGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EndGameDialog(QWidget *parent = nullptr);
    ~EndGameDialog();

public slots:
    void showEndGame(int);

private:
    Ui::EndGameDialog *ui;
};

#endif // ENDGAMEDIALOG_H
