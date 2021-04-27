#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QColor>

class settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isEuropean READ isEuropean WRITE setEuropean NOTIFY isEuropeanChanged)
    Q_PROPERTY(QColor pawnColor READ pawnColor WRITE setPawnColor NOTIFY pawnColorChanged)
    Q_PROPERTY(QColor boardColor READ boardColor WRITE setBoardColor NOTIFY boardColorChanged)
public:
    explicit settings(QObject *parent = nullptr);


    void setEuropean(bool isEuropean ){
        m_isEuropean = isEuropean;
    }
    bool isEuropean(){
        return m_isEuropean;
    }

    QColor pawnColor(){
        return m_pawnColor;
    }
    void setPawnColor(QColor color){
        m_pawnColor = color;
    }

    QColor boardColor(){
        return m_boardColor;
    }
    void setBoardColor(QColor color){
        m_boardColor = color;
    }

signals:
    void isEuropeanChanged(bool);
    void pawnColorChanged(QColor);
    void boardColorChanged(QColor);

private:
    bool m_isEuropean;
    QColor m_pawnColor;
    QColor m_boardColor;
};

#endif // SETTINGS_H
