#ifndef HOLE_H
#define HOLE_H

#include <QGraphicsItem>
#include <QGraphicsLayoutItem>
#include <QPainter>
#include <QVector>

class Hole : public QGraphicsItem, public QGraphicsLayoutItem
{
public:
    QVector<Hole*>& getMoves(){
        return m_moves;
    }

    void setPawnColor(QColor newPawnColor){
        pawnColor = newPawnColor;
    }

    void setPawnBackground(QColor newPawnBackground){
        pawnBackground = newPawnBackground;
    }

    Hole(QGraphicsItem *parent = nullptr) : QGraphicsItem(parent) {
        pawnColor = Qt::green;
        pawnBackground = Qt::yellow;
        setAcceptHoverEvents(true);
        setGraphicsItem(this);
    }

    QRectF boundingRect() const {
        return QRectF(0, 0, 100, 100);
    }
    QPainterPath shape() const {
        QPainterPath path;
        path.addEllipse(boundingRect());
        return path;
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        painter->setBrush(pawnBackground);
        painter->drawRect(boundingRect());
        painter->setBrush(pawnColor);
        painter->drawEllipse(boundingRect());
    }
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const override{
        switch (which) {
            case Qt::MinimumSize:
                return QSizeF(80,80);
            case Qt::PreferredSize:
                return QSizeF(100,100);
            case Qt::MaximumSize:
                return QSizeF(1000,1000);
            default:
                break;
        }
        return constraint;
    }
    void setGeometry(const QRectF &geom)
    {
        prepareGeometryChange();
        QGraphicsLayoutItem::setGeometry(geom);
        setPos(geom.topLeft());
    }

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *e) override{
        pawnColor = Qt::red;
        for(Hole* move : m_moves){
            move->setPawnColor(Qt::blue);
            move->update();
        }
        QGraphicsItem::hoverEnterEvent(e);
    }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *e) override{
        pawnColor = Qt::green;
        for(Hole* move : m_moves){
            move->setPawnColor(Qt::green);
            move->update();
        }
        QGraphicsItem::hoverLeaveEvent(e);
    }

private:
    QColor pawnColor;
    QColor pawnBackground;
    QVector<Hole*> m_moves;
};

#endif // HOLE_H
