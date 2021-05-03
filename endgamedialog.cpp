#include "endgamedialog.h"
#include "ui_endgamedialog.h"

EndGameDialog::EndGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EndGameDialog){
    ui->setupUi(this);
    // Setup window
    setWindowTitle("Game over!");
    QPixmap pixmap( ICON_SIZE, ICON_SIZE );
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setBrush(Qt::red);
    painter.drawLine(0, 0, ICON_SIZE, ICON_SIZE);
    painter.drawLine(0, ICON_SIZE, ICON_SIZE, 0);
    setWindowIcon(QIcon(pixmap));
}

EndGameDialog::~EndGameDialog(){
    delete ui;
}

void EndGameDialog::showEndGame(int score){
    ui->scoreLabel->setText(QString("Pawns left: ")+QString::number(score));
    show();
}
