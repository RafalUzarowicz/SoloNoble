#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    currentSettings()
{
    ui->setupUi(this);

    // Setup dialog widgets

    m_pawnColorDialog = new QColorDialog;
    m_pawnColorDialog->setModal(true);
    m_pawnColorDialog->setWindowTitle("Pawn color selection");

    m_boardColorDialog = new QColorDialog;
    m_boardColorDialog->setModal(true);
    m_boardColorDialog->setWindowTitle("Board color selection");

    m_highlightColorDialog = new QColorDialog;
    m_highlightColorDialog->setModal(true);
    m_highlightColorDialog->setWindowTitle("Highlight color selection");

    m_markColorDialog = new QColorDialog;
    m_markColorDialog->setModal(true);
    m_markColorDialog->setWindowTitle("Mark color selection");

    // Setup signals

    connect(ui->pawnColorButton, &QPushButton::clicked, m_pawnColorDialog, &QColorDialog::show);
    connect(ui->boardColorButton, &QPushButton::clicked, m_boardColorDialog, &QColorDialog::show);
    connect(ui->highlightColorButton, &QPushButton::clicked, m_highlightColorDialog, &QColorDialog::show);
    connect(ui->markColorButton, &QPushButton::clicked, m_markColorDialog, &QColorDialog::show);

    connect(m_pawnColorDialog, &QColorDialog::colorSelected, this, &SettingsDialog::setPawnColorView);
    connect(m_boardColorDialog, &QColorDialog::colorSelected, this, &SettingsDialog::setBoardColorView);
    connect(m_highlightColorDialog, &QColorDialog::colorSelected, this, &SettingsDialog::setHighlightColorView);
    connect(m_markColorDialog, &QColorDialog::colorSelected, this, &SettingsDialog::setMarkColorView);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SettingsDialog::acceptSettings);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &SettingsDialog::rejectSettings);

    // Prepare color widgets

    QPalette pal = ui->pawnColorView->palette();
    pal.setColor(QPalette::Window, currentSettings.pawnColor());
    ui->pawnColorView->setAutoFillBackground(true);
    ui->pawnColorView->setPalette(pal);

    pal = ui->boardColorView->palette();
    pal.setColor(QPalette::Window, currentSettings.boardColor());
    ui->boardColorView->setAutoFillBackground(true);
    ui->boardColorView->setPalette(pal);

    pal = ui->highlightColorView->palette();
    pal.setColor(QPalette::Window, currentSettings.pawnHighlightColor());
    ui->highlightColorView->setAutoFillBackground(true);
    ui->highlightColorView->setPalette(pal);

    pal = ui->markColorView->palette();
    pal.setColor(QPalette::Window, currentSettings.pawnMarkColor());
    ui->markColorView->setAutoFillBackground(true);
    ui->markColorView->setPalette(pal);

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::setPawnColorView(QColor color){
    QPalette pal = ui->pawnColorView->palette();
    pal.setColor(QPalette::Window, color);
    ui->pawnColorView->setPalette(pal);
}

void SettingsDialog::setBoardColorView(QColor color){
    QPalette pal = ui->boardColorView->palette();
    pal.setColor(QPalette::Window, color);
    ui->boardColorView->setPalette(pal);
}

void SettingsDialog::setHighlightColorView(QColor color){
    QPalette pal = ui->highlightColorView->palette();
    pal.setColor(QPalette::Window, color);
    ui->highlightColorView->setPalette(pal);
}

void SettingsDialog::setMarkColorView(QColor color){
    QPalette pal = ui->markColorView->palette();
    pal.setColor(QPalette::Window, color);
    ui->markColorView->setPalette(pal);
}

void SettingsDialog::acceptSettings(){
    currentSettings.setPawnColor(ui->pawnColorView->palette().color(QPalette::Window));
    currentSettings.setBoardColor(ui->boardColorView->palette().color(QPalette::Window));
    currentSettings.setPawnHighlightColor(ui->highlightColorView->palette().color(QPalette::Window));
    currentSettings.setPawnMarkColor(ui->markColorView->palette().color(QPalette::Window));
    currentSettings.setEuropean(ui->comboBox->currentIndex());
}

void SettingsDialog::rejectSettings(){
    setPawnColorView(currentSettings.pawnColor());
    setBoardColorView(currentSettings.boardColor());
    setHighlightColorView(currentSettings.pawnHighlightColor());
    setMarkColorView(currentSettings.pawnMarkColor());
    ui->comboBox->setCurrentIndex(currentSettings.isEuropean());
}
