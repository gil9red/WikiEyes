#include "UAboutProgram.h"
#include "ui_UAboutProgram.h"

UAboutProgram::UAboutProgram(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UAboutProgram)
{
    setWindowFlags(Qt::WindowCloseButtonHint);

    ui->setupUi(this);

    connect(ui->pButtonClose, SIGNAL(clicked()),
            this, SLOT(close()));

    ui->labelVersion->setText(qApp->applicationVersion());
}

UAboutProgram::~UAboutProgram()
{
    delete ui;
}
