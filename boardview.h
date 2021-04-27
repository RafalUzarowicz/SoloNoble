#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QGraphicsView>

class BoardView : public QGraphicsView
{
public:
    BoardView(QWidget* = nullptr);

    void zoomToFit()
    {
        fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
    }

protected:
    void resizeEvent(QResizeEvent* event) override{
        zoomToFit();
    }
};

#endif // BOARDVIEW_H
