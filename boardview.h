#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QGraphicsView>

class BoardView : public QGraphicsView
{
public:
    BoardView(QWidget* = nullptr);
protected:
    void resizeEvent(QResizeEvent* event) override;
};

#endif // BOARDVIEW_H
