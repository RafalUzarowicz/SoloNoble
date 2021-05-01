#include "tile.h"

Tile::Tile(QColor pawnColor, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_pawnColor(pawnColor),
    m_highlightColor(Qt::blue),
    m_markColor(Qt::red),
    m_isOccupied(true),
    m_isSelected(false),
    m_isPossibleMove(false),
    m_isHighlighted(false) {

    m_closeNeighbours.reserve(4);
    m_farNeighbours.reserve(4);

    setAcceptHoverEvents(true);
    setGraphicsItem(this);
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
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);

    if(m_isPossibleMove){
        painter->setBrush(m_markColor);
        painter->drawRoundedRect(boundingRect(), 40, 40);
    }else if(m_isHighlighted){
        painter->setBrush(m_highlightColor);
        painter->drawRoundedRect(boundingRect(), 40, 40);
    }
    if(m_isOccupied){
        if(m_isSelected){
            painter->setBrush(Qt::black);
            painter->drawEllipse(boundingRect());
        }
        painter->setBrush(m_pawnColor);
        painter->drawEllipse(boundingRect().center(), 0.9*boundingRect().width()/2, 0.9*boundingRect().height()/2);
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

void Tile::setGeometry(const QRectF &geom){
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(geom);
    setPos(geom.topLeft());
}

QVector<Tile*> Tile::closeNeighbours(){
    return m_closeNeighbours;
}

QVector<Tile*> Tile::farNeighbours(){
    return m_farNeighbours;
}

void Tile::occupied(bool isOccupied){
    this->m_isOccupied = isOccupied;
}

void Tile::select(bool isSelected){
    this->m_isSelected = isSelected;
}

void Tile::highlight(bool isHighlighted){
    this->m_isHighlighted = isHighlighted;
}

void Tile::mark(bool isPossibleMove){
    this->m_isPossibleMove = isPossibleMove;
}

void Tile::hoverEnterEvent(QGraphicsSceneHoverEvent* e){
    emit tileHoverChanged(true);
    QGraphicsItem::hoverEnterEvent(e);
}

void Tile::hoverLeaveEvent(QGraphicsSceneHoverEvent* e){
    emit tileHoverChanged(false);
    QGraphicsItem::hoverLeaveEvent(e);
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent* e){
    if(m_isOccupied){
        emit tileSelected(this);
    }else{
        emit emptyTileSelected(this);
    }
    QGraphicsItem::mousePressEvent(e);
}

void Tile::setPawnColor(QColor color){
    m_pawnColor = color;
    update();
}

void Tile::setHighlightColor(QColor color){
    m_highlightColor = color;
    update();
}

void Tile::setMarkColor(QColor color){
    m_markColor = color;
    update();
}
