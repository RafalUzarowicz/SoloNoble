#include "boardview.h"

BoardView::BoardView(QWidget* parent) : QGraphicsView(parent){
}

void BoardView::resizeEvent(QResizeEvent* event){
    fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(event);
}
