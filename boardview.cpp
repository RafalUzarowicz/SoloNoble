#include "boardview.h"

BoardView::BoardView(QWidget* parent) : QGraphicsView(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
