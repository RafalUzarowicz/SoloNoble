#include "settings.h"

Settings::Settings(QObject *parent) : QObject(parent)
{
    m_isEuropean = false;
    m_pawnColor = Qt::white;
    m_boardColor = Qt::black;
}

void Settings::setEuropean(bool isEuropean ){
    m_isEuropean = isEuropean;
}
bool Settings::isEuropean(){
    return m_isEuropean;
}

QColor Settings::pawnColor(){
    return m_pawnColor;
}
void Settings::setPawnColor(QColor color){
    m_pawnColor = color;
}

QColor Settings::boardColor(){
    return m_boardColor;
}
void Settings::setBoardColor(QColor color){
    m_boardColor = color;
}
