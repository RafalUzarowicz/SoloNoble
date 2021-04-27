#include "solonoble.h"
#include "./ui_solonoble.h"

SoloNoble::SoloNoble(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SoloNoble)
{
    ui->setupUi(this);
}

SoloNoble::~SoloNoble()
{
    delete ui;
}

