#include "solonoble.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsGridLayout>
#include "pawn.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SoloNoble w;
    w.show();
    return a.exec();
}
