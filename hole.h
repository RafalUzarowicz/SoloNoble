#ifndef HOLE_H
#define HOLE_H

#include <QGraphicsItem>
#include <QGraphicsLayoutItem>
#include <QPainter>
#include <QVector>

class Board;

class Hole : public QObject, public QGraphicsItem, public QGraphicsLayoutItem
{
    Q_OBJECT

    friend Board;

public:
    Hole(int id, QGraphicsItem *parent = nullptr) : QGraphicsItem(parent), id(id) {
        setAcceptHoverEvents(true);
        setGraphicsItem(this);
        isSelected = false;
        isOccupied = true;
        isPossibleMove = false;
        isHighlighted = false;
        whoWillMove = -1;
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
        if(isPossibleMove){
            painter->setBrush(Qt::red);
        }else if(isHighlighted){
            painter->setBrush(Qt::blue);
        }
        painter->drawRoundedRect(boundingRect(), 10, 10);
        if(isOccupied){
            if(isSelected){
                painter->setBrush(Qt::black);
            }else{
                painter->setBrush(pawnColor);
            }
            painter->drawEllipse(boundingRect());
        }else{
            painter->setBrush(Qt::black);
            QRectF bRect = boundingRect();
            painter->drawEllipse(bRect.x()+0.4*bRect.width(), bRect.y()+0.4*bRect.height(), 0.2*bRect.width(), 0.2*bRect.height());
        }
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

signals:
    void highlightMoves(bool);
    void tileSelected(Hole*);
    void markPossibleMoves(int);
    void unmarkPossibleMoves(int);
    void removePawns(int, int);

public slots:
    void highlightTile(bool isHighlighted){
        if(!isOccupied){
            this->isHighlighted = isHighlighted;
            update();
        }
    }

    void deselect(){
        if(isSelected){
            pawnColor = Qt::green;
            isSelected = false;
            update();
            emit unmarkPossibleMoves(id);
        }
    }

    void markMovePossibility(int idOfWhoWillMove){
        if(!isOccupied){
            isPossibleMove = true;
            whoWillMove = idOfWhoWillMove;
            update();
        }
    }

    void unmarkMovePossibility(int idOfWhoWillMove){
        if(!isOccupied){
            isPossibleMove = false;
            whoWillMove = idOfWhoWillMove;
            update();
        }
    }

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *e) override{
        if(isOccupied){
            emit highlightMoves(true);
        }
        QGraphicsItem::hoverEnterEvent(e);
    }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *e) override{
        if(isOccupied){
            emit highlightMoves(false);
        }
        QGraphicsItem::hoverLeaveEvent(e);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent* e) override{
        if(isOccupied && !isSelected){
            isSelected = true;
            QGraphicsItem::mousePressEvent(e);
            update();
            emit tileSelected(this);
            emit markPossibleMoves(id);
        }else if(!isOccupied && isPossibleMove){
            isOccupied = true;
            isSelected = true;
            isPossibleMove = false;
            QGraphicsItem::mousePressEvent(e);
            update();
            emit tileSelected(this);
            emit markPossibleMoves(id);
            emit removePawns(id, whoWillMove);
        }
    }


    void removePawn(){
        isOccupied = false;
        isSelected = false;
        isPossibleMove = false;
        update();
    }

private:
    QColor pawnColor = Qt::green;
    QColor pawnBackground = Qt::yellow;

    bool isSelected;
    bool isOccupied;
    bool isPossibleMove;
    bool isHighlighted;

    int id;
    int whoWillMove;
};

#endif // HOLE_H
