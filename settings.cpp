#include "settings.h"

Settings::Settings(QObject *parent) : QObject(parent){
    m_isEuropean = false;
    m_pawnColor = Qt::green;
    m_pawnHighlightColor = Qt::blue;
    m_pawnMarkColor = Qt::red;
    m_boardColor = Qt::white;
}

void Settings::setEuropean(bool isEuropean ){
    if(m_isEuropean != isEuropean){
        m_isEuropean = isEuropean;
        emit isEuropeanChanged(isEuropean);
    }
}

bool Settings::isEuropean(){
    return m_isEuropean;
}

QColor Settings::pawnColor() const{
    return m_pawnColor;
}

void Settings::setPawnColor(QColor color){
    if(m_pawnColor != color){
        m_pawnColor = color;
        emit pawnColorChanged(color);
    }
}

QColor Settings::boardColor() const{
    return m_boardColor;
}

void Settings::setBoardColor(QColor color){
    if(m_boardColor != color){
        m_boardColor = color;
        emit boardColorChanged(color);
    }
}

void Settings::setPawnHighlightColor(QColor color){
    if(m_pawnHighlightColor != color){
        m_pawnHighlightColor = color;
        emit pawnHighlightColorChanged(color);
    }
}

QColor Settings::pawnHighlightColor() const{
    return m_pawnHighlightColor;
}

void Settings::setPawnMarkColor(QColor color){
    if(m_pawnMarkColor != color){
        m_pawnMarkColor = color;
        emit pawnMarkColorChanged(color);
    }
}

QColor Settings::pawnMarkColor() const{
    return m_pawnMarkColor;
}
