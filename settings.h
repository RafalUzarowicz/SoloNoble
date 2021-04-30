#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QColor>

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isEuropean READ isEuropean WRITE setEuropean NOTIFY isEuropeanChanged)
    Q_PROPERTY(QColor pawnColor READ pawnColor WRITE setPawnColor NOTIFY pawnColorChanged)
    Q_PROPERTY(QColor boardColor READ boardColor WRITE setBoardColor NOTIFY boardColorChanged)
public:
    explicit Settings(QObject* = nullptr);

    void setEuropean(bool);
    bool isEuropean();

    QColor pawnColor();
    void setPawnColor(QColor);

    QColor boardColor();
    void setBoardColor(QColor);

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
