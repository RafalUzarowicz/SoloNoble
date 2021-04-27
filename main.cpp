#include "solonoble.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SoloNoble w;
    w.show();
    return a.exec();
}
