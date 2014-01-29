#include "USettings.h"

/// PUBLIC
USettings::USettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::USettings)
{
    setWindowFlags(Qt::WindowCloseButtonHint
                   | Qt::Dialog);

    ui->setupUi(this);

    ui->gBoxIris->hide();
    ui->gBoxPupil->hide();

    setWindowTitle("Настройки");
}

USettings::~USettings()
{
    delete ui;
}

Ui::USettings * USettings::gui()
{
    return ui;
}
