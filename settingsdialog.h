#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QColorDialog>

#include "settings.h"

class SoloNoble;

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(Settings currentSettigs)
public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

private:
    Ui::SettingsDialog *ui;
    QColorDialog* m_pawnColorDialog;
    QColorDialog* m_boardColorDialog;
    QColorDialog* m_highlightColorDialog;
    QColorDialog* m_markColorDialog;

    Settings currentSettings;

public slots:
    void setPawnColorView(QColor);
    void setBoardColorView(QColor);
    void setHighlightColorView(QColor);
    void setMarkColorView(QColor);

    void acceptSettings();
    void rejectSettings();

    friend class SoloNoble;
};

#endif // SETTINGSDIALOG_H
