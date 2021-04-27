#ifndef SOLONOBLE_H
#define SOLONOBLE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SoloNoble; }
QT_END_NAMESPACE

class SoloNoble : public QMainWindow
{
    Q_OBJECT

public:
    SoloNoble(QWidget *parent = nullptr);
    ~SoloNoble();

private:
    Ui::SoloNoble *ui;
};
#endif // SOLONOBLE_H
