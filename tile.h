#ifndef HOLE_H
#define HOLE_H

#include <QGraphicsItem>
#include <QGraphicsLayoutItem>
#include <QPainter>
#include <QVector>

class Board;

class Tile : public QObject, public QGraphicsItem, public QGraphicsLayoutItem
{
    Q_OBJECT

    friend Board;

public:
    Tile(int, QGraphicsItem* = nullptr);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;
    QSizeF sizeHint(Qt::SizeHint, const QSizeF& = QSizeF()) const override;
    void setGeometry(const QRectF&);

signals:
    void highlightMoves(bool);
    void tileSelected(Tile*);
    void markPossibleMoves(int);
    void unmarkPossibleMoves(int);
    void removePawns(int, int);


    void startHighlightSetH(bool);
    void startHighlightSetV(bool);
    void continueHighlightSetH(bool);
    void continueHighlightSetV(bool);

    void updateScore();

    void testSignal(bool);

public slots:

    void testSlot(bool);
    void checkHighlightPossibilityH(bool);
    void checkHighlightPossibilityV(bool);
    void highlightTileH(bool);
    void highlightTileV(bool);

    void deselect();
    void markMovePossibility(int);
    void unmarkMovePossibility(int);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;


    void removePawn();
    void placePawn();

private:
    QColor pawnColor;
    QColor pawnBackground;

    bool isSelected;
    bool isOccupied;
    bool isPossibleMove;
    bool isHighlighted;

    int id;
    int whoWillMove;
};

#endif // HOLE_H
