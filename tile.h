#ifndef HOLE_H
#define HOLE_H

#include <QGraphicsItem>
#include <QGraphicsLayoutItem>
#include <QPainter>
#include <QVector>
#include <QPropertyAnimation>

class Board;

class Tile : public QObject, public QGraphicsItem, public QGraphicsLayoutItem
{
    Q_OBJECT

    Q_PROPERTY(QColor pawnColor WRITE setPawnColor)
    Q_PROPERTY(QColor highlightColor WRITE setHighlightColor)
    Q_PROPERTY(QColor markColor WRITE setMarkColor)

    Q_PROPERTY(bool isOccupied WRITE occupied READ isOccupied)
    Q_PROPERTY(bool isSelected WRITE select READ isSelected)
    Q_PROPERTY(bool isPossibleMove WRITE mark READ isPossibleMove)
    Q_PROPERTY(bool isHighlighted WRITE highlight READ isHighlighted)

    Q_PROPERTY(QVector<Tile*> closeNeighbours READ closeNeighbours)
    Q_PROPERTY(QVector<Tile*> farNeighbours READ farNeighbours)

    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible)

public:
    Tile(QColor = Qt::green, QGraphicsItem* = nullptr);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;
    QSizeF sizeHint(Qt::SizeHint, const QSizeF& = QSizeF()) const override;
    void setGeometry(const QRectF&) override;

    QVector<Tile*>& closeNeighbours();
    QVector<Tile*>& farNeighbours();

    bool isOccupied() const;
    bool isSelected() const;
    bool isHighlighted() const;
    bool isPossibleMove() const;

    void occupied(bool);
    void select(bool);
    void highlight(bool);
    void mark(bool);

signals:
    void tileHoverChanged(bool);
    void tileSelected(Tile*);
    void emptyTileSelected(Tile*);

public slots:
    void setPawnColor(QColor);
    void setHighlightColor(QColor);
    void setMarkColor(QColor);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;

private:
    QColor m_pawnColor;
    QColor m_highlightColor;
    QColor m_markColor;

    bool m_isOccupied;
    bool m_isSelected;
    bool m_isPossibleMove;
    bool m_isHighlighted;

    QVector<Tile*> m_closeNeighbours;
    QVector<Tile*> m_farNeighbours;
};

#endif // HOLE_H
