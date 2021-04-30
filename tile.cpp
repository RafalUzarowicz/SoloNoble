#include "tile.h"

Tile::Tile(int id, QGraphicsItem *parent) : QGraphicsItem(parent), id(id), pawnColor(Qt::green), pawnBackground(Qt::yellow) {
    setAcceptHoverEvents(true);
    setGraphicsItem(this);
    isSelected = false;
    isOccupied = true;
    isPossibleMove = false;
    isHighlighted = false;
    whoWillMove = -1;
}

QRectF Tile::boundingRect() const {
    return QRectF(0, 0, 100, 100);
}

QPainterPath Tile::shape() const {
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Tile::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
    painter->setRenderHint(QPainter::Antialiasing);
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

QSizeF Tile::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const{
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

void Tile::setGeometry(const QRectF &geom)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(geom);
    setPos(geom.topLeft());
}

void Tile::testSlot(bool value){

}

void Tile::checkHighlightPossibilityH(bool newIsHighlighted){
    if(isOccupied){
        emit continueHighlightSetH(newIsHighlighted);
    }
}

void Tile::checkHighlightPossibilityV(bool newIsHighlighted){
    if(isOccupied){
        emit continueHighlightSetV(newIsHighlighted);
    }
}

void Tile::highlightTileH(bool newIsHighlighted){
    if(!isOccupied){
        isHighlighted = newIsHighlighted;
        update();
    }
}

void Tile::highlightTileV(bool newIsHighlighted){
    if(!isOccupied){
        isHighlighted = newIsHighlighted;
        update();
    }
}

void Tile::deselect(){
    isSelected = false;
    update();
    emit unmarkPossibleMoves(id);
}

void Tile::markMovePossibility(int idOfWhoWillMove){
    if(!isOccupied && isHighlighted){
        isPossibleMove = true;
        whoWillMove = idOfWhoWillMove;
        update();
    }
}

void Tile::unmarkMovePossibility(int idOfWhoWillMove){
    if(!isOccupied){
        isPossibleMove = false;
        whoWillMove = idOfWhoWillMove;
        update();
    }
}

void Tile::hoverEnterEvent(QGraphicsSceneHoverEvent* e){
    if(isOccupied){
        emit startHighlightSetH(true);
        emit startHighlightSetV(true);
    }
    QGraphicsItem::hoverEnterEvent(e);
}
void Tile::hoverLeaveEvent(QGraphicsSceneHoverEvent* e){
    if(isOccupied){
        emit startHighlightSetH(false);
        emit startHighlightSetV(false);
    }
    QGraphicsItem::hoverLeaveEvent(e);
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent* e){
    if(isOccupied && !isSelected){
        isSelected = true;
        emit tileSelected(this);
        emit markPossibleMoves(id);
    }else if(!isOccupied && isPossibleMove){
        isOccupied = true;
        isSelected = true;
        isPossibleMove = false;

        emit removePawns(id, whoWillMove);
        emit tileSelected(this);
        emit startHighlightSetH(true);
        emit startHighlightSetV(true);
        emit markPossibleMoves(id);

        emit updateScore();
    }
    QGraphicsItem::mousePressEvent(e);
    update();
}


void Tile::removePawn(){
    isOccupied = false;
    isSelected = false;
    isPossibleMove = false;
    update();
}

void Tile::placePawn(){
    isOccupied = true;
    isSelected = false;
    isPossibleMove = false;
    update();
}
