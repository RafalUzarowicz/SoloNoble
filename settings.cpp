#include "settings.h"

settings::settings(QObject *parent) : QObject(parent)
{
    m_isEuropean = false;
    m_pawnColor = Qt::white;
    m_boardColor = Qt::black;
}
