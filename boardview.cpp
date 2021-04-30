#include "boardview.h"

BoardView::BoardView(QWidget* parent) : QGraphicsView(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void BoardView::zoomToFit()
{
    fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}

void BoardView::resizeEvent(QResizeEvent* event){
    zoomToFit();
    QGraphicsView::resizeEvent(event);
}
