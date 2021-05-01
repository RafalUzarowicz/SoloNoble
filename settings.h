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
    Q_PROPERTY(QColor pawnHighlightColor READ pawnHighlightColor WRITE setPawnHighlightColor NOTIFY pawnHighlightColorChanged)
    Q_PROPERTY(QColor pawnMarkColor READ pawnMarkColor WRITE setPawnMarkColor NOTIFY pawnMarkColorChanged)
public:
    explicit Settings(QObject* = nullptr);

    void setEuropean(bool);
    bool isEuropean();

    QColor pawnColor();
    void setPawnColor(QColor);

    QColor boardColor();
    void setBoardColor(QColor);

    void setPawnHighlightColor(QColor);
    QColor pawnHighlightColor();

    void setPawnMarkColor(QColor);
    QColor pawnMarkColor();

signals:
    void isEuropeanChanged(bool);
    void pawnColorChanged(QColor);
    void boardColorChanged(QColor);
    void pawnHighlightColorChanged(QColor);
    void pawnMarkColorChanged(QColor);

private:
    bool m_isEuropean;
    QColor m_pawnColor;
    QColor m_boardColor;
    QColor m_pawnHighlightColor;
    QColor m_pawnMarkColor;
};

#endif // SETTINGS_H
